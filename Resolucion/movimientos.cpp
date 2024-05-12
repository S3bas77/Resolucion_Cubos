#include<bits/stdc++.h>
#define input freopen("in.txt", "r", stdin) 
#define output freopen("out.txt", "w", stdout) 
using namespace std;
using Face = vector<vector<char>>;
unordered_map<string, Face> leer_caras_cubo() {
    unordered_map<char, string> mapa_color = {
        {'V', "Verde"},
        {'A', "Amarillo"},
        {'N', "Naranja"},
        {'R', "Rojo"},
        {'B', "Blanco"},
        {'C', "Celeste"}
    };
    unordered_map<string, Face> cubo;
    for (int i = 0; i < 6; ++i) {
        char inicial_de_la_cara;
        cin >> inicial_de_la_cara;
        Face face(2, vector<char>(2)); 
        for (int fil = 0; fil < 2; fil++) { 
            for (int col = 0; col < 2; col++) { 
                cin >> face[fil][col];
            }
        }
        cubo[mapa_color[inicial_de_la_cara]] = face;  
    }
    return cubo;  
}
Face rotacion_horaria(const Face& face) {
    Face cara_rotada(2, vector<char>(2));
    for (int fil = 0; fil < 2; ++fil) {
        for (int col = 0; col < 2; ++col) {
            cara_rotada[col][1 - fil] = face[fil][col];
        }
    }
    return cara_rotada;
}
Face rotacion_antihoraria(const Face& face){
    Face cara_rotada(2, vector<char>(2));
    for (int fil = 0; fil < 2; ++fil) {
        for (int col = 0; col < 2; ++col) {
            cara_rotada[fil][col] = face[col][1 - fil];
        }
    }
    return cara_rotada;
}
void R(unordered_map<string, Face>& cubo) {
    cubo["Naranja"] = rotacion_horaria(cubo["Naranja"]); 
    cubo["Verde"][0][1] = cubo["Blanco"][0][1];   
    cubo["Verde"][1][1] = cubo["Blanco"][1][1];  
    cubo["Blanco"][0][1] = cubo["Celeste"][1][0]; 
    cubo["Blanco"][1][1] = cubo["Celeste"][0][0]; 
    cubo["Celeste"][0][0] = cubo["Amarillo"][1][1];  
    cubo["Celeste"][1][0] = cubo["Amarillo"][0][1];  
    cubo["Amarillo"][0][1] = cubo["Verde"][0][1];  
    cubo["Amarillo"][1][1] = cubo["Verde"][1][1];  
}
void Rp(unordered_map<string, Face>& cubo) {
    cubo["Naranja"] = rotacion_antihoraria(cubo["Naranja"]);

    cubo["Verde"][0][1] = cubo["Amarillo"][0][1];  
    cubo["Verde"][1][1] = cubo["Amarillo"][1][1];  
    cubo["Amarillo"][0][1] = cubo["Celeste"][1][0];  
    cubo["Amarillo"][1][1] = cubo["Celeste"][0][0];
    cubo["Celeste"][0][0] = cubo["Blanco"][1][1];
    cubo["Celeste"][1][0] = cubo["Blanco"][0][1];
    cubo["Blanco"][0][1] = cubo["Verde"][0][1];  
    cubo["Blanco"][1][1] = cubo["Verde"][1][1]; 
}
void L(unordered_map<string, Face>& cubo) {
    cubo["Rojo"] = rotacion_horaria(cubo["Rojo"]); 

    cubo["Verde"][0][0] = cubo["Amarillo"][0][0];
    cubo["Verde"][1][0] = cubo["Amarillo"][1][0];
    cubo["Amarillo"][0][0] = cubo["Celeste"][1][1];  
    cubo["Amarillo"][1][0] = cubo["Celeste"][0][1];  
    cubo["Celeste"][0][1] = cubo["Blanco"][1][0];
    cubo["Celeste"][1][1] = cubo["Blanco"][0][0];  
    cubo["Blanco"][0][0] = cubo["Verde"][0][0]; 
    cubo["Blanco"][1][0] = cubo["Verde"][1][0]; 
}
void Lp(unordered_map<string, Face>& cubo) {
    cubo["Rojo"] = rotacion_antihoraria(cubo["Rojo"]);  

    cubo["Verde"][0][0] = cubo["Blanco"][0][0];  
    cubo["Verde"][1][0] = cubo["Blanco"][1][0];  
    cubo["Blanco"][0][0] = cubo["Celeste"][1][1];
    cubo["Blanco"][1][0] = cubo["Celeste"][0][1];
    cubo["Celeste"][0][1] = cubo["Amarillo"][1][0]; 
    cubo["Celeste"][1][1] = cubo["Amarillo"][0][0]; 
    cubo["Amarillo"][0][0] = cubo["Verde"][0][0]; 
    cubo["Amarillo"][1][0] = cubo["Verde"][1][0]; 

} 
void F(unordered_map<string, Face>& cubo) {
    cubo["Verde"] = rotacion_horaria(cubo["Verde"]);
    vector<char> tmp(2);
    for (int i = 0; i < 2; ++i) {
        tmp[i] = cubo["Naranja"][i][0];
    }
    for (int i = 0; i < 2; ++i) {
        cubo["Naranja"][i][0] = cubo["Amarillo"][1][i]; 
    }
    cubo["Amarillo"][1][0] = cubo["Rojo"][1][1];
    cubo["Amarillo"][1][1] = cubo["Rojo"][0][1];
    for (int i = 0; i < 2; ++i) {
        cubo["Rojo"][i][1] = cubo["Blanco"][0][i];
    }
    cubo["Blanco"][0][0] = tmp[1];
    cubo["Blanco"][0][1] = tmp[0];
}
void Fp(unordered_map<string, Face>& cubo) {
    cubo["Verde"] = rotacion_antihoraria(cubo["Verde"]);
    vector<char> tmp(2);
    for (int i = 0; i < 2; ++i) {
        tmp[i] = cubo["Naranja"][i][0];
    }
    cubo["Naranja"][0][0]=cubo["Blanco"][0][1];
    cubo["Naranja"][1][0]=cubo["Blanco"][0][0];
    cubo["Blanco"][0][0]=cubo["Rojo"][0][1];
    cubo["Blanco"][0][1]=cubo["Rojo"][1][1];
    cubo["Rojo"][0][1]=cubo["Amarillo"][1][1];
    cubo["Rojo"][1][1]=cubo["Amarillo"][1][0];
    cubo["Amarillo"][1][0]=tmp[0];
    cubo["Amarillo"][1][1]=tmp[1];
}
void B(unordered_map<string, Face>& cubo){
    cubo["Celeste"] = rotacion_horaria(cubo["Celeste"]);
    vector<char> tmp(2);
    for (int i = 0; i < 2; ++i) {
        tmp[i] = cubo["Naranja"][i][1];
    }
    cubo["Naranja"][0][1] = cubo["Blanco"][1][1];
    cubo["Naranja"][1][1] = cubo["Blanco"][1][0];
    cubo["Blanco"][1][0] = cubo["Rojo"][0][0];
    cubo["Blanco"][1][1] = cubo["Rojo"][1][0];
    cubo["Rojo"][0][0] = cubo["Amarillo"][0][1];
    cubo["Rojo"][1][0] = cubo["Amarillo"][0][0];
    for (int i = 0; i < 2; ++i) {
        cubo["Amarillo"][0][i] = tmp[i];
    }
}
void Bp(unordered_map<string, Face>& cubo){
    cubo["Verde"] = rotacion_horaria(cubo["Verde"]);
    vector<char> tmp(2);
    for (int i = 0; i < 2; ++i) {
        tmp[i] = cubo["Naranja"][i][1];
    }
    for (int i = 0; i < 2; ++i) {
        cubo["Naranja"][i][1] = cubo["Amarillo"][0][i]; 
    }
    cubo["Amarillo"][0][0] = cubo["Rojo"][1][0];
    cubo["Amarillo"][0][1] = cubo["Rojo"][0][0];
    for (int i = 0; i < 2; ++i) {
        cubo["Rojo"][i][0] = cubo["Blanco"][1][i];
    }
    cubo["Blanco"][1][0] = tmp[1];
    cubo["Blanco"][1][1] = tmp[0];
}
void U(unordered_map<string, Face>& cubo) {
    cubo["Amarillo"] = rotacion_horaria(cubo["Amarillo"]);
    vector<char> tmp = cubo["Naranja"][0];  
    cubo["Naranja"][0] = cubo["Celeste"][0]; 
    cubo["Celeste"][0] = cubo["Rojo"][0];  
    cubo["Rojo"][0] = cubo["Verde"][0];  
    cubo["Verde"][0] = tmp;  
}
void D(unordered_map<string, Face>& cubo) {
    cubo["Blanco"] = rotacion_horaria(cubo["Blanco"]);
    vector<char> tmp = cubo["Verde"][1]; 
    cubo["Verde"][1] = cubo["Rojo"][1]; 
    cubo["Rojo"][1] = cubo["Celeste"][1];  
    cubo["Celeste"][1] = cubo["Naranja"][1];  
    cubo["Naranja"][1] = tmp;  
}
void Up(unordered_map<string, Face>& cubo) {
    cubo["Amarillo"] = rotacion_antihoraria(cubo["Amarillo"]);
    vector<char> tmp = cubo["Rojo"][0]; 
    cubo["Rojo"][0] = cubo["Celeste"][0]; 
    cubo["Celeste"][0] = cubo["Naranja"][0]; 
    cubo["Naranja"][0] = cubo["Verde"][0];  
    cubo["Verde"][0] = tmp;  
}
void Dp(unordered_map<string, Face>& cubo) {
    cubo["Blanco"] = rotacion_antihoraria(cubo["Blanco"]); 
    vector<char> tmp = cubo["Verde"][1];  
    cubo["Verde"][1] = cubo["Naranja"][1];  
    cubo["Naranja"][1] = cubo["Celeste"][1]; 
    cubo["Celeste"][1] = cubo["Rojo"][1]; 
    cubo["Rojo"][1] = tmp; 
}
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
//int main() {
//    input;  
//    output;
//    unordered_map<string, Face> cubo = leer_caras_cubo();  
//    F(cubo);
//    imprimir_caras_cubo(cubo);
//    return 0;
//}