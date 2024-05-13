#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <queue>
#include "movimientos.cpp" 
#include "OLL.cpp"
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

bool is_white_solved(const Cube& cube) {
    // Verifica si la cara blanca está resuelta
    Face white_face = cube.faces.at("Blanco"); // Cambio aquí
    char color = white_face[0][0];
    for (const auto& row : white_face) {
        for (char c : row) {
            if (c != color) {
                return false;
            }
        }
    }
    return true;
}

vector<string> solveWhiteFace(const Cube& cube) {
    queue<State> q;
    q.push(State(cube, ""));

    while (!q.empty()) {
        State current = q.front();
        q.pop();

        if (is_white_solved(current.cube)) {
            vector<string> solution;
            for (char move : current.moves) {
                string m(1, move);
                solution.push_back(m);
            }
            return solution;
        }

        // Aplica solo los movimientos que afectan a la cara blanca
        for (auto& move : {"R", "Rp", "L", "Lp", "F", "Fp", "B", "Bp"}) {
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
            }
            q.push(State(new_cube, current.moves + move));
        }
    }

    return {}; // No se encontró solución
}

int main() {
    input;
     output;
    // Aquí deberías leer el cubo desde la entrada
    // Luego, convierte el unordered_map en un objeto Cube
    unordered_map<string, Face> cubo = leer_caras_cubo();
    Cube cube{cubo};

    // Llama a la función solveWhiteFace y muestra la solución encontrada
    vector<string> movimientos = solveWhiteFace(cube);
    cout << movimientos.size() << endl;
    for (const auto& move : movimientos) {
        cout << move << " ";
    }
    cout << endl;

    return 0;
}
