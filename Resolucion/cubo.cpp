#include<bits/stdc++.h>

#define input freopen("in.txt", "r", stdin)  // Entrada desde archivo
#define output freopen("out.txt", "w", stdout)  // Salida hacia archivo

using namespace std;

// Definición de una cara del cubo de Rubik (matriz 3x3)
using Face = vector<vector<char>>;

// Estructura para representar el estado del cubo de Rubik
struct RubikState {
    unordered_map<string, Face> faces;  // Caras del cubo
    string moves;  // Para rastrear los movimientos realizados
    
    // Operador de igualdad para comparar estados
    bool operator==(const RubikState& other) const {
        return faces == other.faces && moves == other.moves;
    }
};

// Hash para permitir uso de RubikState en unordered_set
namespace std {
template <>
struct hash<RubikState> {
    size_t operator()(const RubikState& state) const {
        size_t hash_value = 0;
        for (const auto& [key, face] : state.faces) {
            for (const auto& row : face) {
                for (const auto& color : row) {
                    hash_value ^= hash<char>()(color);
                }
            }
        }
        return hash_value;
    }
};
}

// Función para rotar una capa 90 grados en sentido horario
Face rotate_90_degrees(const Face& face) {
    Face rotated_face(3, vector<char>(3));
    for (int row = 0; row < 3; ++row) {
        for (int col = 0; col < 3; ++col) {
            rotated_face[col][2 - row] = face[row][col];  // Rotar 90 grados
        }
    }
    return rotated_face;
}

// Aplicar movimientos básicos al cubo
RubikState apply_move(const RubikState& state, const string& move) {
    RubikState new_state = state;  // Copiar el estado actual
    new_state.moves += move + " ";  // Registrar el movimiento

    // Aplicar movimientos básicos según el comando
    if (move == "U") {
        new_state.faces["Verde"] = rotate_90_degrees(new_state.faces["Verde"]);  // Capa superior
    } else if (move == "D") {
        new_state.faces["Blanco"] = rotate_90_degrees(new_state.faces["Blanco"]);  // Capa inferior
    } else if (move == "L") {
        new_state.faces["Naranja"] = rotate_90_degrees(new_state.faces["Naranja"]);  // Capa izquierda
    } else if (move == "R") {
        new_state.faces["Rojo"] = rotate_90_degrees(new_state.faces["Rojo"]);  // Capa derecha
    } else if (move == "F") {
        new_state.faces["Azul"] = rotate_90_degrees(new_state.faces["Azul"]);  // Capa frontal
    } else if (move == "B") {
        new_state.faces["Amarillo"] = rotate_90_degrees(new_state.faces["Amarillo"]);  // Capa posterior
    }

    return new_state;  // Retornar el estado actualizado
}

// Función para leer las caras del cubo de Rubik desde la entrada
unordered_map<string, Face> read_rubik_faces() {
    unordered_map<char, string> color_map = {
        {'V', "Verde"},
        {'A', "Amarillo"},
        {'N', "Naranja"},
        {'R', "Rojo"},
        {'B', "Blanco"},
        {'C', "Celeste"}
    };

    unordered_map<string, Face> cube;  // Mapa para almacenar caras del cubo

    // Leer las caras del cubo desde la entrada
    for (int i = 0; i < 6; ++i) {
        char face_color;
        cin >> face_color;  // Leer el identificador de la cara
        
        Face face(3, vector<char>(3));  // Crear matriz 3x3
        for (int row = 0; row < 3; row++) {  // Recorrer filas
            for (int col = 0; col < 3; col++) {  // Recorrer columnas
                cin >> face[row][col];  // Leer datos para la matriz
            }
        }
        cube[color_map[face_color]] = face;  // Asignar la cara al mapa del cubo
    }

    return cube;  // Retornar el cubo con todas las caras
}

// Función para imprimir las caras del cubo
void print_rubik_faces(const unordered_map<string, Face>& cube) {
    for (const auto& [name, face] : cube) {
        cout << "Cara: " << name << endl;
        for (const auto& row : face) {
            for (const auto& color : row) {
                cout << color << " ";
            }
            cout << endl;
        }
        cout << endl;
    }
}

// BFS para formar la cruz blanca
void find_white_cross(const unordered_map<string, Face>& cube) {
    RubikState initial_state;
    initial_state.faces = cube;  // Estado inicial del cubo
    initial_state.moves = "";

    queue<RubikState> q;  // Cola para BFS
    unordered_set<RubikState> visited;  // Conjunto para evitar duplicados

    q.push(initial_state);  // Añadir estado inicial
    visited.insert(initial_state);

    while (!q.empty()) {
        RubikState current = q.front();
        q.pop();

        // Posibles movimientos básicos para BFS
        vector<string> possible_moves = {"U", "D", "L", "R", "F", "B"};  // Movimientos básicos

        // Aplicar cada movimiento y agregar al BFS si no ha sido visitado
        for (const auto& move : possible_moves) {
            RubikState new_state = apply_move(current, move);  // Aplicar movimiento

            if (visited.find(new_state) == visited.end()) {  // Evitar duplicados
                q.push(new_state);  // Añadir nuevo estado a la cola
                visited.insert(new_state);
            }
        }
    }

    cout << "No se pudo completar la cruz blanca." << endl;  // En caso de falla
}

// Función principal para obtener datos del input y resolver la cruz blanca
int main() {
    input;  // Configurar entrada desde archivo
    output;  // Configurar salida hacia archivo
    
    unordered_map<string, Face> cube = read_rubik_faces();  // Leer las caras del cubo desde el input
    
    print_rubik_faces(cube);  // Imprimir las caras para verificar
    
    find_white_cross(cube);  // Resolver la cruz blanca usando BFS

    return 0;//hola
}
