#include <iostream>
#include <cstdlib>
using namespace std;

const int FILAS = 4;
const int COLUMNAS = 4;
const int MINA = -1; // Valor que representa una mina en el tablero
const int MINAS = COLUMNAS + 1;

int tablero[FILAS][COLUMNAS];
bool descubierto[FILAS][COLUMNAS];

int inicializar_juego() {
    for (int i = 0; i < FILAS; i++) {
        for (int j = 0; j < COLUMNAS; j++) {
            tablero[i][j] = 0;
            descubierto[i][j] = false;
        }
    }
    return 0;
}

int generar_minas() {
    int minas_colocadas = 0;
    
    while (minas_colocadas < MINAS) {
        int fila = rand() % FILAS;
        int col = rand() % COLUMNAS;
        
        if (tablero[fila][col] != MINA) {
            tablero[fila][col] = MINA;
            minas_colocadas++;
        }
    }
    return minas_colocadas;
}

int contar_adyacentes(int fila, int col) {
    int contador = 0;
    
    for (int i = fila - 1; i <= fila + 1; i++) {
        for (int j = col - 1; j <= col + 1; j++) {
            if (i >= 0 && i < FILAS && j >= 0 && j < COLUMNAS) {
                if (tablero[i][j] == MINA) {
                    contador++;
                }
            }
        }
    }
    
    return contador;
}

int calcular_numeros() {
    for (int i = 0; i < FILAS; i++) {
        for (int j = 0; j < COLUMNAS; j++) {
            if (tablero[i][j] != MINA) {
                tablero[i][j] = contar_adyacentes(i, j);
            }
        }
    }
    return 0;
}

int mostrar_tablero_real() {
    cout << "  ";
    for (int j = 0; j < COLUMNAS; j++) {
        cout << j << " ";
    }
    cout << endl;
    
    for (int i = 0; i < FILAS; i++) {
        cout << i << " ";
        for (int j = 0; j < COLUMNAS; j++) {
            if (tablero[i][j] == MINA) {
                cout << "M ";
            } else {
                cout << tablero[i][j] << " ";
            }
        }
        cout << endl;
    }
    cout << endl;
    return 0;
}

int mostrar_tablero_jugador() {
    cout << "  ";
    for (int j = 0; j < COLUMNAS; j++) {
        cout << j << " ";
    }
    cout << endl;
    
    for (int i = 0; i < FILAS; i++) {
        cout << i << " ";
        for (int j = 0; j < COLUMNAS; j++) {
            if (descubierto[i][j]) {
                if (tablero[i][j] == MINA) {
                    cout << "* ";
                } else {
                    cout << tablero[i][j] << " ";
                }
            } else {
                cout << "- ";
            }
        }
        cout << endl;
    }
    cout << endl;
    return 0;
}

int destapar(int fila, int col) {
    if (fila < 0 || fila >= FILAS || col < 0 || col >= COLUMNAS) {
        return -1;
    }
    
    if (descubierto[fila][col]) {
        return 0;
    }
    
    descubierto[fila][col] = true;
    
    if (tablero[fila][col] == 0) {
        for (int i = fila - 1; i <= fila + 1; i++) {
            for (int j = col - 1; j <= col + 1; j++) {
                destapar(i, j);
            }
        }
    }
    return 1;
}

bool verificar_victoria() {
    for (int i = 0; i < FILAS; i++) {
        for (int j = 0; j < COLUMNAS; j++) {
            if (tablero[i][j] != MINA && !descubierto[i][j]) {
                return false;
            }
        }
    }
    return true;
}

int mostrar_todas_minas() {
    for (int i = 0; i < FILAS; i++) {
        for (int j = 0; j < COLUMNAS; j++) {
            if (tablero[i][j] == MINA) {
                descubierto[i][j] = true;
            }
        }
    }
    return 0;
}

int main() {
    srand(123); 
    
    cout << "=== BUSCAMINAS ===" << endl;
    cout << "Tablero: " << FILAS << "x" << COLUMNAS << endl;
    cout << "Minas: " << MINAS << endl << endl;
    
    inicializar_juego();
    generar_minas();
    calcular_numeros();
    
    cout << "Tablero generado:" << endl;
    mostrar_tablero_real();
    
    cout << "Presiona Enter para comenzar el juego...";
    cin.get();
    
    cout << "\n\n=== JUEGO INICIADO ===" << endl;
    
    bool juego_activo = true;
    
    while (juego_activo) {
        mostrar_tablero_jugador();
        
        if (verificar_victoria()) {
            cout << "¡felicidaes! ganaste " << endl;
            break;
        }
        
        int fila, col;
        cout << "Ingrese fila y columna (0-" << FILAS-1 << " 0-" << COLUMNAS-1 << "): ";
        cin >> fila >> col;
        
        if (fila < 0 || fila >= FILAS || col < 0 || col >= COLUMNAS) {
            cout << "coordenadas inválidas. Intenta otra vez." << endl;
            continue;
        }
        
        if (descubierto[fila][col]) {
            cout << "esta celda ya está descubierta. Intenta otra." << endl;
            continue;
        }
        
        if (tablero[fila][col] == MINA) {
            mostrar_todas_minas();
            mostrar_tablero_jugador();
            cout << " boom! encontraste una mina. perdiste " << endl;
            juego_activo = false;
        } else {
            destapar(fila, col);
            cout << "Celda destapada" << endl;
        }
        
        cout << endl;
    }
    
    cout << "Gracias por jugar" << endl;
    return 0;
}