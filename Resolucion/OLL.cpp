#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <queue>
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

bool is_yellow_solved(const Cube& cube) {
    // Verifica si la cara blanca está resuelta
    Face yellow_face = cube.faces.at("Amarillo"); // Cambio aquí
    char color = yellow_face[0][0];
    for (const auto& row : yellow_face) {
        for (char c : row) {
            if (c != color) {
                return false;
            }
        }
    }
    return true;
}

vector<string> solveYellowFace(const Cube& cube) {
    queue<State> q;
    q.push(State(cube, ""));

    int shortest_solution_length = INT_MAX; // Longitud de la solución más corta encontrada

    while (!q.empty()) {
        State current = q.front();
        q.pop();

        if (current.moves.size() >= shortest_solution_length) {
            // Si el número de movimientos realizados es igual o mayor que la solución más corta, detener la búsqueda
            continue;
        }

        if (is_yellow_solved(current.cube)) {
            vector<string> solution;
            for (char move : current.moves) {
                string m(1, move);
                solution.push_back(m);
            }
            shortest_solution_length = min(shortest_solution_length, static_cast<int>(solution.size()));
            // Actualizar la longitud de la solución más corta
            return solution;
        }

        // Aplica solo los movimientos que afectan a la cara blanca
        for (auto& move : {"Case1", "Case2", "Case3", "Case4", "Case5", "Case6", "Case7"}) {
            Cube new_cube = current.cube;
            if (move == "Case1") {
                R(new_cube.faces);
                U(new_cube.faces);
                Rp(new_cube.faces);
                U(new_cube.faces);
                R(new_cube.faces);
                U(new_cube.faces);
                U(new_cube.faces);
                Rp(new_cube.faces);
            } else if (move == "Case2") {
                R(new_cube.faces);
                U(new_cube.faces);
                U(new_cube.faces);
                Rp(new_cube.faces);
                Up(new_cube.faces);
                R(new_cube.faces);
                Up(new_cube.faces);
                Rp(new_cube.faces);
            } else if (move == "Case3") {
                R(new_cube.faces);
                R(new_cube.faces);
                U(new_cube.faces);
                U(new_cube.faces);
                R(new_cube.faces);
                U(new_cube.faces);
                U(new_cube.faces);
                R(new_cube.faces);
                R(new_cube.faces);
            } else if (move == "Case4") {
                F(new_cube.faces);
                R(new_cube.faces);
                U(new_cube.faces);
                Rp(new_cube.faces);
                Up(new_cube.faces);
                R(new_cube.faces);
                U(new_cube.faces);
                Rp(new_cube.faces);
                Up(new_cube.faces);
                Fp(new_cube.faces);
            } else if (move == "Case5") {
                F(new_cube.faces);
                R(new_cube.faces);
                U(new_cube.faces);
                Rp(new_cube.faces);
                Up(new_cube.faces);
                Fp(new_cube.faces);
            } else if (move == "Case6") {
                R(new_cube.faces);
                U(new_cube.faces);
                Rp(new_cube.faces);
                Up(new_cube.faces);
                Rp(new_cube.faces);
                F(new_cube.faces);
                R(new_cube.faces);
                Fp(new_cube.faces);
            } else if (move == "Case7") {
                F(new_cube.faces);
                R(new_cube.faces);
                Up(new_cube.faces);
                Rp(new_cube.faces);
                Up(new_cube.faces);
                R(new_cube.faces);
                U(new_cube.faces);
                Rp(new_cube.faces);
                Fp(new_cube.faces);
            }
            //q.push(State(new_cube, current.moves + move));
            if (is_yellow_solved(new_cube)) {
                vector<string> solution;
                for (char m : current.moves) {
                    string mv(1, m);
                    solution.push_back(mv);
                }
                solution.push_back(move);
                shortest_solution_length = min(shortest_solution_length, static_cast<int>(solution.size()));
                // Actualizar la longitud de la solución más corta
                return solution;
            }
            if (move == "Case7") { // Si es el último movimiento y no se ha resuelto, mover U
                Cube new_cube_U = current.cube;
                U(new_cube_U.faces); // Mover U
                q.push(State(new_cube_U, current.moves + "U"));
            } else {
                q.push(State(new_cube, current.moves + move));
            }   
        }
    }
    return {}; // No se encontró solución
}


int main() {
    input;
    output;
    unordered_map<string, Face> cubo = leer_caras_cubo();
    Cube cube{cubo};

    // Llama a la función solveWhiteFace y muestra la solución encontrada
    vector<string> movimientos = solveYellowFace(cube);
    cout << movimientos.size() << endl;
    for (const auto& move : movimientos) {
        cout << move << " ";
    }
    cout << endl;
    return 0;
}
