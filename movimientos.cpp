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

// Aplicar el movimiento "F'" (rotación de la cara frontal en sentido antihorario)
void applyMovementFPrime(unordered_map<string, Face>& cube) {
    const int BOTTOM_ROW = 2;

    // Rotar la cara frontal (Naranja) 90 grados en sentido antihorario
    cube["Blanco"] = rotate_90_degreesA(cube["Naranja"]);

    // Ajustar las filas inferiores entre caras afectadas por el movimiento "F'"
    vector<char> tmp = cube["Azul"][BOTTOM_ROW];  // Fila inferior de la cara azul

    cube["Azul"][BOTTOM_ROW] = cube["Blanco"][BOTTOM_ROW];  // Fila inferior de blanco a azul
    cube["Blanco"][BOTTOM_ROW] = cube["Naranja"][BOTTOM_ROW];  // Fila inferior de naranja a blanco
    cube["Naranja"][BOTTOM_ROW] = cube["Verde"][BOTTOM_ROW];  // Fila inferior de verde a naranja
    cube["Verde"][BOTTOM_ROW] = tmp;  // Fila inferior de azul a verde
}
// Aplicar el movimiento "B" (rotación de la cara posterior en sentido horario)
void applyMovementB(unordered_map<string, Face>& cube) {
    const int BOTTOM_ROW = 2;

    // Rotar la cara posterior (Amarillo) 90 grados en sentido horario
    cube["Amarillo"] = rotate_90_degrees(cube["Amarillo"]);

    // Ajustar las filas inferiores entre caras afectadas por el movimiento "B"
    vector<char> tmp = cube["Rojo"][BOTTOM_ROW];  // Fila inferior de la cara roja

    cube["Rojo"][BOTTOM_ROW] = cube["Amarillo"][BOTTOM_ROW];  // Fila inferior de amarillo a rojo
    cube["Amarillo"][BOTTOM_ROW] = cube["Verde"][BOTTOM_ROW];  // Fila inferior de verde a amarillo
    cube["Verde"][BOTTOM_ROW] = cube["Azul"][BOTTOM_ROW];  // Fila inferior de azul a verde
    cube["Azul"][BOTTOM_ROW] = tmp;  // Fila inferior de rojo a azul
}

// Aplicar el movimiento "B'" (rotación de la cara posterior en sentido antihorario)
void applyMovementBPrime(unordered_map<string, Face>& cube) {
    const int BOTTOM_ROW = 2;

    // Rotar la cara posterior (Amarillo) 90 grados en sentido antihorario
    cube["Amarillo"] = rotate_90_degreesA(cube["Amarillo"]);

    // Ajustar las filas inferiores entre caras afectadas por el movimiento "B'"
    vector<char> tmp = cube["Azul"][BOTTOM_ROW];  // Fila inferior de la cara azul

    cube["Azul"][BOTTOM_ROW] = cube["Verde"][BOTTOM_ROW];  // Fila inferior de verde a azul
    cube["Verde"][BOTTOM_ROW] = cube["Amarillo"][BOTTOM_ROW];  // Fila inferior de amarillo a verde
    cube["Amarillo"][BOTTOM_ROW] = cube["Rojo"][BOTTOM_ROW];  // Fila inferior de rojo a amarillo
    cube["Rojo"][BOTTOM_ROW] = tmp;  // Fila inferior de azul a rojo
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
