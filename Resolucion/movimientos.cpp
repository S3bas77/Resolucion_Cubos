#include<bits/stdc++.h>

#define input freopen("in.txt", "r", stdin)  // Entrada desde archivo
#define output freopen("out.txt", "w", stdout)  // Salida hacia archivo

using namespace std;

// Definición de una cara del cubo de Rubik (matriz 3x3)
using Face = vector<vector<char>>;

// Función para leer las caras del cubo de Rubik desde la entrada
unordered_map<string, Face> leer_caras_cubo() {
    unordered_map<char, string> color_map = {
        {'V', "Verde"},
        {'A', "Amarillo"},
        {'N', "Naranja"},
        {'R', "Rojo"},
        {'B', "Blanco"},
        {'C', "Celeste"}
    };
    unordered_map<string, Face> cubo;  // Mapa para almacenar caras del cubo
    // Leer las caras del cubo desde la entrada
    for (int i = 0; i < 6; ++i) {
        char inicial_de_la_cara;
        cin >> inicial_de_la_cara;  // Leer el identificador de la cara
        
        Face face(3, vector<char>(3));  // Crear matriz 3x3
        for (int fil = 0; fil < 3; fil++) {  // Recorrer filas
            for (int col = 0; col < 3; col++) {  // Recorrer columnas
                cin >> face[fil][col];  // Leer datos para la matriz
            }
        }
        cubo[color_map[inicial_de_la_cara]] = face;  // Asignar la cara al mapa del cubo
    }
    return cubo;  // Retornar el cubo con todas las caras
}
// Función para rotar una capa 90 grados en sentido horario
Face rotacion_x_horaria(const Face& face) {
    Face cara_rotada(3, vector<char>(3));
    for (int fil = 0; fil < 3; ++fil) {
        for (int col = 0; col < 3; ++col) {
            cara_rotada[col][2 - fil] = face[fil][col];  // Rotar 90 grados
        }
    }
    return cara_rotada;
}
// Función para rotar una capa 90 grados en sentido antihorario
Face rotacion_x_antihoraria(const Face& face){
    Face cara_rotada(3, vector<char>(3));
    for (int fil = 0; fil < 3; ++fil) {
        for (int col = 0; col < 3; ++col) {
            cara_rotada[fil][col] = face[col][2 - fil];// Rotar 90 grados en sentido antihorario
        }
    }
    return cara_rotada;
}

Face rotacion_y_horaria(const Face& face) {
    Face cara_rotada(3, vector<char>(3));
    for (int col = 0; col < 3; ++col) {
        for (int fil = 0; fil < 3; ++fil) {
            cara_rotada[2 - fil][col] = face[fil][col];  // Mover fila hacia arriba (rotación en eje "y")
        }
    }
    return cara_rotada;
}
void R(unordered_map<string, Face>& cubo) {
    // Rotar la cara derecha (Rojo) 90 grados en sentido horario
    cubo["Naranja"] = rotacion_x_horaria(cubo["Naranja"]);  // Rotar la cara naranja

    // Guardar la columna derecha de la cara verde
    vector<char> tmp(3);
    for (int i = 0; i < 3; ++i) {
        tmp[i] = cubo["Verde"][i][2];
    }

    // Ajustar las columnas entre caras afectadas por el movimiento "R"
    for (int i = 0; i < 3; ++i) {
        cubo["Verde"][i][2] = cubo["Blanco"][i][2];  // De Blanco a Verde
        cubo["Blanco"][i][2] = cubo["Celeste"][i][2];  // De Amarillo a Blanco
        cubo["Celeste"][i][2] = cubo["Amarillo"][i][2];  // De Naranja a Amarillo
        cubo["Amarillo"][i][2] = tmp[i];  // De Verde a Naranja
    }
}
void F(unordered_map<string, Face>& cubo) {
    // Rotar la cara derecha (Rojo) 90 grados en sentido horario
    cubo["Verde"] = rotacion_x_horaria(cubo["Verde"]);  // Rotar la cara naranja

    // Guardar la columna derecha de la cara verde
    vector<char> tmp(3);
    for (int i = 0; i < 3; ++i) {
        tmp[i] = cubo["Naranja"][i][2];
    }

    // Ajustar las columnas entre caras afectadas por el movimiento "R"
    for (int i = 0; i < 3; ++i) {
        cubo["Naranja"][i][0] = cubo["Amarillo"][i][0];  // De Blanco a Verde
    }
    cubo["Amarillo"][2] = cubo["Rojo"][2];  // De Amarillo a Blanco
    for (int i = 0; i < 3; ++i) {
        cubo["Rojo"][i][2] = cubo["Blanco"][i][2];  // De Naranja a Amarillo
    }
    
    cubo["Blanco"][2] = tmp;  // De Verde a Naranja
}
void U(unordered_map<string, Face>& cubo) {
    // Rotar la cara superior (Amarillo) 90 grados en sentido horario
    cubo["Amarillo"] = rotacion_x_horaria(cubo["Amarillo"]);

    // Ajustar las filas superiores entre caras afectadas por el movimiento "U"
    vector<char> tmp = cubo["Naranja"][0];  // Fila superior de la cara naranja

    cubo["Naranja"][0] = cubo["Celeste"][0];  // Fila superior de celeste a naranja
    cubo["Celeste"][0] = cubo["Rojo"][0];  // Fila superior de rojo a celeste
    cubo["Rojo"][0] = cubo["Verde"][0];  // Fila superior de Verde a rojo
    cubo["Verde"][0] = tmp;  // Fila superior de naranja a Verde
}

// Aplicar el movimiento "B" (rotación de la cara posterior)
void D(unordered_map<string, Face>& cubo) {
    // Rotar la cara inferior (Blanco) 90 grados en sentido horario
    cubo["Blanco"] = rotacion_x_horaria(cubo["Blanco"]);

    // Ajustar las filas inferiores entre caras afectadas por el movimiento "D"
    vector<char> tmp = cubo["Verde"][2];  // Fila inferior de la cara verde

    cubo["Verde"][2] = cubo["Rojo"][2];  // Fila inferior de rojo a verde
    cubo["Rojo"][2] = cubo["Celeste"][2];  // Fila inferior de celeste a rojo
    cubo["Celeste"][2] = cubo["Naranja"][2];  // Fila inferior de naranja a celeste
    cubo["Naranja"][2] = tmp;  // Fila inferior de verde a naranja
}
void Up(unordered_map<string, Face>& cubo) {
    // Rotar la cara superior (Amarillo) 90 grados en sentido horario
    cubo["Amarillo"] = rotacion_x_antihoraria(cubo["Amarillo"]);

    // Ajustar las filas superiores entre caras afectadas por el movimiento "U"
    vector<char> tmp = cubo["Rojo"][0];  // Fila superior de la cara naranja

    cubo["Rojo"][0] = cubo["Celeste"][0];  // Fila superior de celeste a Rojo
    cubo["Celeste"][0] = cubo["Naranja"][0];  // Fila superior de Naranja a celeste
    cubo["Naranja"][0] = cubo["Verde"][0];  // Fila superior de Verde a rojo
    cubo["Verde"][0] = tmp;  // Fila superior de naranja a Verde
}
void Dp(unordered_map<string, Face>& cubo) {
    // Rotar la cara inferior (Blanco) 90 grados en sentido antihorario
    cubo["Blanco"] = rotacion_x_antihoraria(cubo["Blanco"]);  // Usar rotación antihoraria

    // Ajustar las filas inferiores entre caras afectadas por el movimiento "Dp"
    vector<char> tmp = cubo["Verde"][2];  // Guardar fila inferior de la cara verde
    cubo["Verde"][2] = cubo["Naranja"][2];  // Fila inferior de naranja a verde
    cubo["Naranja"][2] = cubo["Celeste"][2];  // Fila inferior de celeste a naranja
    cubo["Celeste"][2] = cubo["Rojo"][2];  // Fila inferior de rojo a celeste
    cubo["Rojo"][2] = tmp;  // Fila inferior de verde a rojo
}

// Función para imprimir todas las caras del cubo
void imprimir_caras_cubo(const unordered_map<string, Face>& cubo) {
    for (const auto& [name, face] : cubo) {
        cout << "Cara: " << name << endl;
        for (const auto& fil : face) {
            for (const auto& color : fil) {
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
    // Leer las caras del cubo desde el input
    unordered_map<string, Face> cubo = leer_caras_cubo();  
    F(cubo);
    imprimir_caras_cubo(cubo);

    return 0;
}