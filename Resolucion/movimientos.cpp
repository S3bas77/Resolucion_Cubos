#include<bits/stdc++.h>

#define input freopen("in.txt", "r", stdin)  // Entrada desde archivo
#define output freopen("out.txt", "w", stdout)  // Salida hacia archivo

using namespace std;

// Definición de una cara del cubo de Rubik (matriz 3x3)
using Face = vector<vector<char>>;

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
Face rotate_90_degreesA(const Face& face){
    Face rotated_face(3, vector<char>(3));
    for (int row = 0; row < 3; ++row) {
        for (int col = 0; col < 3; ++col) {
            rotated_face[row][col] = face[col][2 - row];// Rotar 90 grados en sentido antihorario
        }
    }
    return rotated_face;
}

// Aplicar el movimiento "B" (rotación de la cara posterior)
void D(unordered_map<string, Face>& cube) {
    // Rotar la cara inferior (Blanco) 90 grados en sentido horario
    cube["Blanco"] = rotate_90_degrees(cube["Blanco"]);

    // Ajustar las filas inferiores entre caras afectadas por el movimiento "D"
    vector<char> tmp = cube["Verde"][2];  // Fila inferior de la cara verde

    cube["Verde"][2] = cube["Rojo"][2];  // Fila inferior de rojo a verde
    cube["Rojo"][2] = cube["Celeste"][2];  // Fila inferior de celeste a rojo
    cube["Celeste"][2] = cube["Naranja"][2];  // Fila inferior de naranja a celeste
    cube["Naranja"][2] = tmp;  // Fila inferior de verde a naranja
}

void Dp(unordered_map<string, Face>& cube) {
    // Rotar la cara inferior (Blanco) 90 grados en sentido antihorario
    cube["Blanco"] = rotate_90_degreesA(cube["Blanco"]);  // Usar rotación antihoraria

    // Ajustar las filas inferiores entre caras afectadas por el movimiento "Dp"
    vector<char> tmp = cube["Verde"][2];  // Guardar fila inferior de la cara verde

    cube["Verde"][2] = cube["Naranja"][2];  // Fila inferior de naranja a verde
    cube["Naranja"][2] = cube["Celeste"][2];  // Fila inferior de celeste a naranja
    cube["Celeste"][2] = cube["Rojo"][2];  // Fila inferior de rojo a celeste
    cube["Rojo"][2] = tmp;  // Fila inferior de verde a rojo
}

// Función para imprimir todas las caras del cubo
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
    output;
    
    unordered_map<string, Face> cube = read_rubik_faces();  // Leer las caras del cubo desde el input
    Dp(cube);
    // Imprimir todas las caras para verificar el estado del cubo
    print_rubik_faces(cube); 
    return 0;
}
