#include<bits/stdc++.h>

#define input freopen("in.txt", "r", stdin)  // Entrada desde archivo
#define output freopen("out.txt", "w", stdout)  // Salida hacia archivo

using namespace std;

using Face = vector<vector<char>>;

unordered_map<string, Face> read_rubik_faces() {
    unordered_map<char, string> color_map = {
        {'V', "Verde"},
        {'A', "Amarillo"},
        {'N', "Naranja"},
        {'R', "Rojo"},
        {'B', "Blanco"},
        {'C', "Celeste"}
    };

    unordered_map<string, Face> cube;

    // Verificar si se puede leer correctamente
    if (cin.eof()) {
        cout << "Error: no hay entrada" << endl;
        return cube;
    }

    for (int i = 0; i < 6; ++i) {
        char face_color;
        if (!(cin >> face_color)) {
            cout << "Error al leer el identificador de la cara" << endl;
            break;
        }

        Face face(3, vector<char>(3));
        for (int row = 0; row < 3; ++row) {
            for (int col = 0; col < 3; ++col) {
                if (!(cin >> face[row][col])) {
                    cout << "Error al leer datos de la matriz" << endl;
                    break;
                }
            }
        }
        cube[color_map[face_color]] = face;
    }

    return cube;
}

// Imprimir caras para ver si se leen correctamente
void print_rubik_faces(const unordered_map<string, Face>& cube) {
    if (cube.empty()) {
        cout << "El cubo está vacío o no se pudo leer." << endl;
        return;
    }

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

int main() {
    input;  // Configurar entrada desde archivo
    output;  // Configurar salida hacia archivo

    unordered_map<string, Face> cube = read_rubik_faces();  // Leer las caras del cubo

    // Validar si la entrada fue correcta
    if (cube.empty()) {
        cout << "Error: no se pudo leer el cubo." << endl;
        return 1;  // Salir con código de error
    }

    // Imprimir todas las caras para verificar el estado del cubo
    print_rubik_faces(cube); 

    return 0;
}
