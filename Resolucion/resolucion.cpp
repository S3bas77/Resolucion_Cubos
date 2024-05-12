#include <bits/stdc++.h>
#include "movimientos.cpp"

#define input freopen("in.txt", "r", stdin)
#define output freopen("out.txt", "w", stdout)

using namespace std;

struct State {
    unordered_map<string, Face> cube;
    string moves;
    int costo_estimado; // Costo estimado hasta el objetivo

    State(const unordered_map<string, Face>& c, const string& m, int costo) : cube(c), moves(m), costo_estimado(costo) {}

    // Sobrecarga del operador de comparación para la cola de prioridad
    bool operator<(const State& other) const {
        return costo_estimado > other.costo_estimado; // Orden ascendente basado en el costo estimado
    }
};

// Función para verificar si el cubo está resuelto
bool es_cubo_resuelto(const unordered_map<string, Face>& cubo) {
    for (const auto& [name, face] : cubo) {
        char color = face[0][0];
        for (int i = 0; i < 2; ++i) {
            for (int j = 0; j < 2; ++j) {
                if (face[i][j] != color) {
                    return false;
                }
            }
        }
    }
    return true;
}

// Función para calcular el costo estimado desde el estado actual hasta el estado objetivo
int calcular_costo_estimado(const unordered_map<string, Face>& cubo) {
    int total_cost = 0;
    for (const auto& [name, face] : cubo) {
        int color_sum = 0;
        char color = face[0][0];
        for (int i = 0; i < 2; ++i) {
            for (int j = 0; j < 2; ++j) {
                color_sum += abs(face[i][j] - color);
            }
        }
        total_cost += color_sum;
    }
    return total_cost;
}

// Función para resolver el cubo de Rubik utilizando el algoritmo A*
string resolver_cubo_a_estrella(const unordered_map<string, Face>& cubo_inicial) {
    priority_queue<State> cola_prioridad;
    cola_prioridad.push(State(cubo_inicial, "", calcular_costo_estimado(cubo_inicial)));

    while (!cola_prioridad.empty()) {
        State actual = cola_prioridad.top();
        cola_prioridad.pop();

        if (es_cubo_resuelto(actual.cube)) {
            return actual.moves;
        }

        for (auto& movimiento : {"R", "Rp", "L", "Lp", "F", "Fp", "B", "Bp", "U", "Up", "D", "Dp"}) {
            auto nuevo_cubo = actual.cube;
            if (movimiento == "R") {
                R(nuevo_cubo);
            } else if (movimiento == "Rp") {
                Rp(nuevo_cubo);
            } else if (movimiento == "L") {
                L(nuevo_cubo);
            } else if (movimiento == "Lp") {
                Lp(nuevo_cubo);
            } else if (movimiento == "F") {
                F(nuevo_cubo);
            } else if (movimiento == "Fp") {
                Fp(nuevo_cubo);
            } else if (movimiento == "B") {
                B(nuevo_cubo);
            } else if (movimiento == "Bp") {
                Bp(nuevo_cubo);
            } else if (movimiento == "U") {
                U(nuevo_cubo);
            } else if (movimiento == "Up") {
                Up(nuevo_cubo);
            } else if (movimiento == "D") {
                D(nuevo_cubo);
            } else if (movimiento == "Dp") {
                Dp(nuevo_cubo);
            }

            string nuevos_movimientos = actual.moves + movimiento;
            int costo_estimado = calcular_costo_estimado(nuevo_cubo);
            cola_prioridad.push(State(nuevo_cubo, nuevos_movimientos, costo_estimado));
        }
    }

    return "No se encontró solución";
}

int main() {
    input;
    output;

    // Leer las caras del cubo desde el input
    unordered_map<string, Face> cubo = leer_caras_cubo();

    // Resolver el cubo de Rubik utilizando el algoritmo A*
    string movimientos = resolver_cubo_a_estrella(cubo);

    // Imprimir los movimientos necesarios para resolver el cubo
    cout << movimientos.size() << endl;
    cout << movimientos << endl;

    return 0;
}
