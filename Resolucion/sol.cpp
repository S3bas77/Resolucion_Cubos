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
            return true;
        }
    }
    return true;
}
size_t split(const std::string &txt, std::vector<std::string> &strs, char ch)
{
    size_t pos = txt.find( ch );
    size_t initialPos = 0;
    strs.clear();

    // Decompose statement
    while( pos != std::string::npos ) {
        strs.push_back( txt.substr( initialPos, pos - initialPos ) );
        initialPos = pos + 1;

        pos = txt.find( ch, initialPos );
    }

    // Add the last one
    strs.push_back( txt.substr( initialPos, std::min( pos, txt.size() ) - initialPos + 1 ) );

    return strs.size();
}
vector<string> solve(const Cube& cube) {
    queue<State> q;
    int max = 10000;
    q.push(State(cube, ""));
    vector<string> posibles = {"R", "Rp", "L", "Lp", "F", "Fp", "B", "Bp", "U", "Up", "D", "Dp"};
    string last = "";
    while (true) {
        State current = q.front();
        q.pop();
        if (is_solved(current.cube)) {
            vector<string> solution;
            split(current.moves, solution,' ');
            imprimir_caras_cubo(current.cube.faces);
            return solution;
        }
        if (!max--) {
            cout<<"No se encontró la solución en 1000 movimientos"<<endl;
            break;
        }
            
        // Aplica todos los movimientos posibles        
        string move;
        int movimiento_actual = rand() % 12;
        move = posibles.at(movimiento_actual);

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
        cout<<"movimiento: "<<move<<endl;
        imprimir_caras_cubo(new_cube.faces);
        q.push(State(new_cube, current.moves +" "+move));
        
    }

    return {}; // No se encontró solución
}
void clearConsole(){
    cout<<"\033[2J\033[1;1H";
}
    //Inicia el menu del programa. El switch tiene las opciones que puede elegir el usuario
void iniciarMenu() {
    int choice;
    unordered_map<string, Face> cubo;
    Cube cube{cubo};
    do
    {
            cout << endl<< "-------------Escoge una opcion-------------" << endl;
            cout << "1. problema aleatorio" << endl;
            cout << "2. Mostrar el resultado del problema del cubo brindado aleatoriamente" << endl;
            cout << "3. Salir" << endl;
            cout << "Ingresa tu opcion: ";
            cin >> choice;
            unordered_map<string, Face> cubo_aleatorio; // Variable global para almacenar el estado del cubo aleatorio
            // Definir los movimientos posibles
            vector<void (*)(unordered_map<string, Face>&)> movimientos = {L, R, Rp, B, Up, Lp, D, Dp};
            // Generar un número aleatorio de movimientos entre 1 y 100
            int num_movimientos = rand() % 30 + 1;
            vector<string> resultados;
            switch (choice)
            {
            //Llama al metodo knap en base a un presupuesto dado por el usuario
            
            case 1:
                // Crear un problema aleatorio del cubo
                cubo = leer_caras_cubo();
                // Realizar movimientos aleatorios
                cout<<"movimientos:"<<num_movimientos<<endl;
                for (int i = 0; i < num_movimientos; ++i) {
                    int movimiento_index = rand() % movimientos.size(); // Seleccionar un movimiento aleatorio
                    movimientos[movimiento_index](cubo); // Ejecutar el movimiento seleccionado en el cubo
                }

                // Almacenar el estado del cubo aleatorio
                cubo_aleatorio = cubo;
                cube = {cubo};
                // Imprimir el cubo resultante
                cout << "Problema aleatorio generado:" << endl;
                imprimir_caras_cubo(cubo);
                break;

            case 2:
                // Mostrar el resultado del problema del cubo generado aleatoriamente
                cout << "Resultado del problema del cubo brindado aleatoriamente:" << endl;
                resultados = solve(cube);
                cout << resultados.size() << endl;
                for (const auto& move : resultados) {
                    cout << move << " ";
                }
                cout << endl;
                break;
            case 3:
                // Salir del programa
                cout << "Saliendo del programa..." << endl;
                break;
            default:
                // Opción inválida
                cout << "Ingresa una opción válida." << endl;
                break;           }
        } while (choice != 3);
}

int main() {
    srand(time(nullptr)); 
    cout << "Presiona cualquier tecla para ingresar al menu: ";
    cin.ignore();
    cin.get();
    iniciarMenu();
    return 0;
}