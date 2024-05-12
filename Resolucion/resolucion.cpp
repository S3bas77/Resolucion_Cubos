#include<bits/stdc++.h>
#include "movimientos.cpp"

using namespace std;

// Definición de la estructura Face
using Face = vector<vector<char>>;

// Definición de la estructura Cube
struct Cube {
    unordered_map<string, Face> faces;
};

// Definición de la estructura State
struct State {
    Cube cube;
    string moves;

    State(const Cube& c, const string& m) : cube(c), moves(m) {}
};

bool is_solved(const Cube& cube) {
    for (const auto& [name, face] : cube.faces) {
        char color = face[0][0];
        for (const auto& row : face) {
            for (char c : row) {
                if (c != color) {
                    return false;
                }
            }
        }
    }
    return true;
}

vector<string> solve(const Cube& cube) {
    queue<State> q;
    q.push(State(cube, ""));

    while (!q.empty()) {
        State current = q.front();
        q.pop();

        if (is_solved(current.cube)) {
            vector<string> solution;
            for (char move : current.moves) {
                string m(1, move);
                solution.push_back(m);
            }
            return solution;
        }

        // Aplica todos los movimientos posibles
        for (auto& move : {"R", "Rp", "L", "Lp", "F", "Fp", "B", "Bp", "U", "Up", "D", "Dp"}) {
            Cube new_cube = current.cube;
            if (move == "R") {
                R(new_cube.faces);
            } else if (move == "Rp") {
                Rp(new_cube.faces);
            } else if (move == "L") {
                L(new_cube.faces);
            } else if (move == "Lp") {
                Lp(new_cube.faces);
            } else if (move == "F") {
                F(new_cube.faces);
            } else if (move == "Fp") {
                Fp(new_cube.faces);
            } else if (move == "B") {
                B(new_cube.faces);
            } else if (move == "Bp") {
                Bp(new_cube.faces);
            } else if (move == "U") {
                U(new_cube.faces);
            } else if (move == "Up") {
                Up(new_cube.faces);
            } else if (move == "D") {
                D(new_cube.faces);
            } else if (move == "Dp") {
                Dp(new_cube.faces);
            }
            q.push(State(new_cube, current.moves + move));
        }
    }

    return {}; // No se encontró solución
}

int main() {
    input;
    // Aquí deberías leer el cubo desde la entrada
    // Luego, convierte el unordered_map en un objeto Cube
    unordered_map<string, Face> cubo = leer_caras_cubo();
    Cube cube{cubo};

    // Llama a la función solve y muestra la solución encontrada
    vector<string> movimientos = solve(cube);
    cout << movimientos.size() << endl;
    for (const auto& move : movimientos) {
        cout << move << " ";
    }
    cout << endl;

    return 0;
}
