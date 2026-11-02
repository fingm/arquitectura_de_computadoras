#include <stdio.h>
#include <stdbool.h>

void out(int reg, unsigned int val);
unsigned char in(int reg);

// Direcciones de registros de E/S
#define TECLADO 0x10   // Solo lectura (1 byte)
#define BARRAS  0x20   // Solo escritura (1 byte)
#define DISPLAY 0x30   // Solo escritura (4 bytes / 32 bits)

// Códigos especiales
#define ENTER 0xD0
#define GUIONES_ERROR 0xFFFFFFFF  // 8 guiones (0xFF cada uno)
#define DISPLAY_VACIO 0xEEEEEEEE  // Display apagado (0xEE cada uno)

// Tiempos (a 2 Hz: 2 tics = 1 segundo)
#define TICS_5_SEG  10            // 5 * 2
#define TICS_2_HORAS 14400        // 2 * 3600 * 2

// Estados del sistema
bool abierta = true;
bool bloqueada = false;
int intentos_fallidos = 0;
int tics_timer = 0;

// Estructura para el buffer de dígitos ingresados (máximo 8)
typedef struct {
    unsigned char digitos[8];
    int len;
} Buffer;

Buffer buffer_entrada;
Buffer clave_guardada;

// Borra la memoria temporal y apaga el display
void limpiarEntrada() {
    buffer_entrada.len = 0;
    out(DISPLAY, DISPLAY_VACIO);
}

// Agrega un dígito BCD (0-9) al buffer. Si hay más de 8, despalza y conserva los últimos 8.
void agregarDigito(unsigned char digito) {
    if (buffer_entrada.len < 8) {
        buffer_entrada.digitos[buffer_entrada.len] = digito;
        buffer_entrada.len++;
    } else {
        // Desplazar hacia la izquierda para descartar el más antiguo
        for (int i = 0; i < 7; i++) {
            buffer_entrada.digitos[i] = buffer_entrada.digitos[i + 1];
        }
        buffer_entrada.digitos[7] = digito;
    }
}

// Actualiza el display de 32 bits con los dígitos del buffer alineados a la izquierda
void actualizarDisplay() {
    unsigned int reg_display = DISPLAY_VACIO;
    for (int i = 0; i < buffer_entrada.len; i++) {
        int shift = 28 - (i * 4);
        // Limpiamos los 4 bits del destino e insertamos el dígito BCD
        reg_display &= ~(0xF << shift);
        reg_display |= ((buffer_entrada.digitos[i] & 0x0F) << shift);
    }
    out(DISPLAY, reg_display);
}

// Compara la clave ingresada con la guardada al cerrar
bool validarClave() {
    if (buffer_entrada.len != clave_guardada.len) {
        return false;
    }
    for (int i = 0; i < buffer_entrada.len; i++) {
        if (buffer_entrada.digitos[i] != clave_guardada.digitos[i]) {
            return false;
        }
    }
    return true;
}

// Rutina de interrupción del Timer (Frecuencia: 2 Hz)
void tiempo() {
    if (bloqueada) {
        tics_timer++;
        if (tics_timer >= TICS_2_HORAS) {
            bloqueada = false;
            intentos_fallidos = 0;
            tics_timer = 0;
            limpiarEntrada();
        }
    } else if (buffer_entrada.len > 0) {
        tics_timer++;
        if (tics_timer >= TICS_5_SEG) {
            tics_timer = 0;
            limpiarEntrada();
        }
    }
}

// Rutina de interrupción del Teclado
void tecla() {
    // Si la caja está bloqueada, cualquier tecla provoca error
    if (bloqueada) {
        out(DISPLAY, GUIONES_ERROR);
        return;
    }

    unsigned char lect = in(TECLADO);
    tics_timer = 0; // Se reinicia el temporizador de 5s tras presionar una tecla

    if (lect == ENTER) {
        if (abierta) {
            // Requisito: mínimo 4 dígitos para cerrar
            if (buffer_entrada.len >= 4) {
                // Guardar la clave elegida por el huésped
                clave_guardada = buffer_entrada;
                abierta = false;
                out(BARRAS, 0x80); // Extender barras (bit MSB = 1)
                limpiarEntrada();
            }
        } else { // Caja cerrada
            if (validarClave()) {
                abierta = true;
                intentos_fallidos = 0;
                out(BARRAS, 0x01); // Retraer barras (bit LSB = 1)
                limpiarEntrada();
            } else {
                intentos_fallidos++;
                out(DISPLAY, GUIONES_ERROR);
                buffer_entrada.len = 0; // Vaciar buffer para nuevo intento

                if (intentos_fallidos >= 3) {
                    bloqueada = true;
                    tics_timer = 0;
                }
            }
        }
    } else {
        // Es una tecla numérica (los 4 bits más significativos traen el valor BCD)
        unsigned char digito = (lect >> 4) & 0x0F;
        agregarDigito(digito);
        actualizarDisplay();
    }
}

int main() {
    // Inicialización del display
    out(DISPLAY, DISPLAY_VACIO);
    
    while (1) {
        // El flujo principal queda a la espera de las interrupciones tecla() y tiempo()
    }
    return 0;
}