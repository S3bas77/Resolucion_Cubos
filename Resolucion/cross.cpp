#include<bits/stdc++.h>
#include "movimientos.cpp"

#define input freopen("in.txt", "r", stdin)  // Entrada desde archivo
#define output freopen("out.txt", "w", stdout)  // Salida hacia archivo

using namespace std;

int main() {
    input;  
    output;
    // Leer las caras del cubo desde el input
    unordered_map<string, Face> cubo = leer_caras_cubo();  
    F(cubo);
    imprimir_caras_cubo(cubo);

    return 0;
}