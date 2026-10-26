#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>
#include <cstdint>

using namespace std;

// Estructura del Nodo del Árbol
struct Nodo {
    int valor;
    Nodo* izq;
    Nodo* der;

    Nodo(int v) : valor(v), izq(nullptr), der(nullptr) {}
};

// Representación de un Marco de Pila (Stack Frame)
struct MarcoPila {
    string funcion; // Nombre o contexto de la llamada
    int nodo_valor; // Valor del nodo procesado (-1 representa NULL)
    uintptr_t ip;   // Dirección simulada de retorno (IP)
};

// Pila global para visualizar el Call Stack
vector<MarcoPila> call_stack;

// Función auxiliar para imprimir el estado actual de la Pila
void mostrar_stack(const string& evento) {
    cout << "\n==================================================\n";
    cout << " EVENTO: " << evento << "\n";
    cout << "--------------------------------------------------\n";
    cout << " PILA DE LLAMADAS (Creciendo hacia abajo ->):\n\n";

    if (call_stack.empty()) {
        cout << "  [ Pila Vacía ]\n";
    } else {
        cout << "  +----------------------+--------------------+--------+\n";
        cout << "  | Función              | Nodo en [BP+4/6]   | IP Ret |\n";
        cout << "  +----------------------+--------------------+--------+\n";
        // Recorremos la pila desde el elemento más antiguo al más reciente (Cima)
        for (size_t i = 0; i < call_stack.size(); ++i) {
            string nodo_str = (call_stack[i].nodo_valor == -1) ? "NULL" : to_string(call_stack[i].nodo_valor);
            bool es_cima = (i == call_stack.size() - 1);

            cout << "  | " << left << setw(20) << call_stack[i].funcion
                 << " | " << setw(18) << nodo_str
                 << " | 0x" << hex << setfill('0') << setw(4) << call_stack[i].ip << dec << setfill(' ')
                 << " |" << (es_cima ? " <-- CIMA (SP)" : "") << "\n";
        }
        cout << "  +----------------------+--------------------+--------+\n";
    }
    cout << "==================================================\n";
}

// Función recursiva que simula la rutina de ensamblador
int profundidad(Nodo* nodo, uintptr_t ip_retorno) {
    int valor_nodo = (nodo != nullptr) ? nodo->valor : -1;

    // 1. PUSH del marco de pila al ENTRAR (Simula PUSH BP, PUSH Regs)
    call_stack.push_back({"PROFUNDIDAD", valor_nodo, ip_retorno});
    mostrar_stack("PUSH -> Entrada a PROFUNDIDAD(Nodo " + (nodo ? to_string(nodo->valor) : "NULL") + ")");

    // 2. CASO BASE (nodo == NULL)
    if (nodo == nullptr) {
        mostrar_stack("EJECUCIÓN -> Retornando 0 (Caso Base NULL)");
        
        // POP del marco al SALIR (Simula POP Regs, POP BP, RET)
        call_stack.pop_back();
        mostrar_stack("POP -> Salida por RET (Caso Base)");
        return 0;
    }

    // 3. Llamada Subárbol Izquierdo
    // Simulamos una dirección de retorno para la llamada izquierda (0x1020)
    int prof_izq = profundidad(nodo->izq, 0x1020);

    // 4. Llamada Subárbol Derecho
    // Simulamos una dirección de retorno para la llamada derecha (0x1040)
    int prof_der = profundidad(nodo->der, 0x1040);

    // 5. Cálculo del resultado
    int resultado = 1 + max(prof_izq, prof_der);

    mostrar_stack("EJECUCIÓN -> Calculado 1 + max(" + to_string(prof_izq) + ", " + to_string(prof_der) + ") = " + to_string(resultado) + " para Nodo " + to_string(nodo->valor));

    // POP del marco al SALIR
    call_stack.pop_back();
    mostrar_stack("POP -> Salida por RET (Nodo " + to_string(nodo->valor) + ")");

    return resultado;
}

int main() {
    /*
        Construcción del Árbol:
               3
              / \
             1   7
              \
               4
    */
    Nodo* raiz = new Nodo(3);
    raiz->izq = new Nodo(1);
    raiz->der = new Nodo(7);
    raiz->izq->der = new Nodo(4);

    cout << "INICIO DE LA EJECUCIÓN RECURSIVA\n";

    // Llamada inicial desde el programa principal (IP Retorno principal = 0x8000)
    int prof_total = profundidad(raiz, 0x8000);

    cout << "\nRESULTADO FINAL: La profundidad del árbol es " << prof_total << "\n";

    // Limpieza de memoria
    delete raiz->izq->der;
    delete raiz->izq;
    delete raiz->der;
    delete raiz;

    return 0;
}