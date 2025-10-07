#include <iostream>
#include <string>

int *ids = nullptr;
float *pesos = nullptr;
std::string *destinos = nullptr;
int *prioridades = nullptr;
char *estados = nullptr;

int capacidad = 0;
int num_paquetes = 0;
int frente = 0;
int fin = 0;

void reporte() {
    std::string destinoBuscado;
    std::cout << "Ingrese el destino para el reporte: ";
    std::cin.ignore();
    std::getline(std::cin, destinoBuscado);

    int contador = 0;
    float pesoTotal = 0.0;

    for (int i = frente; i < fin; i++) {
        if (estados[i] == 'E' && destinos[i] == destinoBuscado) {
            contador++;
            pesoTotal += pesos[i];
        }
    }

    std::cout << "Reporte para destino '" << destinoBuscado << "':\n";
    std::cout << "  Paquetes en cola: " << contador << "\n";
    if (contador > 0)
        std::cout << "  Peso promedio: " << (pesoTotal / contador) << " kg\n";
}

void pop(){

}

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

    estados[fin] = 'D';

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

    std::cout << "Analizando Cola... Buscando ALTA PRIORIDAD.\n";

    int indice = -1;
    for (int i = frente; i < fin; i++) {
        if (estados[i] == 'D' && prioridades[i] == 1) {
            indice = i;
            break;
        }
    }

    if (indice == -1) {
        std::cout << "No hay paquetes de prioridad ALTA en cola.\n";
        return;
    }

    estados[indice] = 'E';
    std::cout << "DESPACHADO: Paquete " << ids[indice]
              << " (Prioridad 1). Estado: 'E'.\n";

    if (indice == frente) {
        frente++;
    }
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
        std::cout << "1. Recibir nuevo paquete (Push)\n";
        std::cout << "2. Procesar recepcion (pop y encolar) \n";
        std::cout << "3. Despachar (desencolar con prioridad)\n";
        std::cout << "4. Reporte de estados \n";
        std::cout << "5. Salir (Liberar Memoria)\n";
        std::cout << "Seleccione una opcion: ";
        std::cin >> opcion;

        switch (opcion) {
            case 1: agregarPaquete(); break; // ya jala
            case 2: pop(); break;
            case 3: despacharPaquete(); break; // YA JALAAA
            case 4: reporte(); break; // ya jala
            case 5: liberarMemoria(); break; // ya jala
            default: std::cout << "Opcion invalida\n"; // ya jala
        }
    } while (opcion != 5);

    return 0;
}