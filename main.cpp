#include <iostream>

int *ids = nullptr;
float *pesos = nullptr;
std::string *destinos = nullptr;
int *prioridades = nullptr;
char *estados = nullptr;

int capacidad = 0;
int num_paquetes = 0;
int frente = 0;
int fin = 0;

void CrearArray() {
    capacidad = 50;
    ids = new int[capacidad];
    pesos = new float[capacidad];
    destinos = new std::string[capacidad];
    prioridades = new int[capacidad];
    estados = new char[capacidad];
}

void redimensionar() {
    int nuevaCap = capacidad * 2;

    int *n_ids = new int[nuevaCap];
    float *n_pesos = new float[nuevaCap];
    std::string *n_destinos = new std::string[nuevaCap];
    int *n_prioridades = new int[nuevaCap];
    char *n_estados = new char[nuevaCap];

    for (int i = 0; i < num_paquetes; i++) {
        n_ids[i] = ids[i];
        n_pesos[i] = pesos[i];
        n_destinos[i] = destinos[i];
        n_prioridades[i] = prioridades[i];
        n_estados[i] = estados[i];
    }

    delete [] ids;
    delete [] pesos;
    delete [] destinos;
    delete [] prioridades;
    delete [] estados;

    ids = n_ids;
    pesos = n_pesos;
    destinos = n_destinos;
    prioridades = n_prioridades;
    estados = n_estados;

    capacidad = nuevaCap;
    std::cout << "Capacidad duplicada a " << capacidad << ".\n";
}

void agregarPaquete() {
    if (num_paquetes == capacidad) {
        redimensionar();
    }

    std::cout << "Ingrese ID: ";
    std::cin >> ids[fin];
    std::cout << "Ingrese peso: ";
    std::cin >> pesos[fin];
    std::cout << "Ingrese destino: ";
    std::cin.ignore();
    std::getline(std::cin, destinos[fin]);
    std::cout << "Ingrese prioridad (1=Alta, 2=Media, 3=Baja): ";
    std::cin >> prioridades[fin];

    estados[fin] = 'E';

    fin++;
    num_paquetes++;

    std::cout << "Paquete " << ids[fin-1] << " encolado. Capacidad utilizada: "
              << num_paquetes << "/" << capacidad << ".\n";
}

void despacharPaquete() {
    if (frente == fin) {
        std::cout << "No hay paquetes en cola.\n";
        return;
    }

    std::cout << "Despachando paquete...\n";
    estados[frente] = 'D';
    std::cout << "Paquete " << ids[frente] << " despachado con exito. Estado: 'D'.\n";
    frente++;
}

void liberarMemoria() {
    delete [] ids;
    delete [] pesos;
    delete [] destinos;
    delete [] prioridades;
    delete [] estados;
    std::cout << "Memoria liberada.\n";
}

int main() {

    CrearArray();

    int opcion;
    do {
        std::cout << "\n--- Sistema de Despacho Logistico MegaEnvio (Modo Punteros) ---\n";
        std::cout << "1. Agregar Paquete (Encolar)\n";
        std::cout << "2. Despachar Paquete (Desencolar)\n";
        std::cout << "3. Salir (Liberar Memoria)\n";
        std::cout << "Seleccione una opcion: ";
        std::cin >> opcion;

        switch (opcion) {
            case 1: agregarPaquete(); break;
            case 2: despacharPaquete(); break;
            case 3: liberarMemoria(); break;
            default: std::cout << "Opcion invalida\n";
        }
    } while (opcion != 3);

    return 0;
}