#include<bits/stdc++.h>

using namespace std;

#define input freopen("in.txt","r",stdin)
#define output freopen("out.txt","w",stdout)

using Face = vector<vector<char>>;

// Función para leer las caras del cubo de Rubik
unordered_map<string, Face> read_rubik_faces() {
    // Mapeo de iniciales a colores (si es necesario)
    unordered_map<char, string> colors = {
        {'V', "Verde"},
        {'A', "Amarillo"},
        {'N', "Naranja"},
        {'R', "Rojo"},
        {'B', "Blanco"},
        {'C', "Celeste"}
    };
    
    unordered_map<string, Face> cube;  // Mapa para almacenar las caras del cubo
    vector<string> face_order = {"Verde", "Rojo", "Amarillo", "Blanco", "Naranja", "Azul"};  // Orden de caras
    
    for (const auto& face_name : face_order) {
        Face face(3, vector<char>(3));  // Crear una matriz 3x3 para la cara
        char face_color;
        cin >> face_color;  // Leer el color de la cara
        
        for (int row = 0; row < 3; ++row) {
            for (int col = 0; col < 3; ++col) {
                cin >> face[row][col];  // Leer cada color de la cara
            }
        }
        cube[colors[face_color]] = face;  // Agregar la cara al mapa del cubo
    }
    
    return cube;  // Retornar el mapa del cubo con todas las caras
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

int main() {
    input;
    // Leer las caras del cubo
    auto cube = read_rubik_faces();
    
    // Imprimir las caras para verificar
    print_rubik_faces(cube);

    return 0;
}