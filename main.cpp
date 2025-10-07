#include <iostream>
#include <string>

int *ids = nullptr;
float *pesos = nullptr;
std::string *destinos = nullptr;
int *prioridades = nullptr;
char *estados = nullptr;

int capacidad = 0;

int fin = 0;
int top_pila = -1;
int frente_cola = 0;
int final_cola = 0;

void CrearArray() {
    capacidad = 50;
    ids         = new int[capacidad];
    pesos       = new float[capacidad];
    destinos    = new std::string[capacidad];
    prioridades = new int[capacidad];
    estados     = new char[capacidad];

    fin = 0;
    top_pila = -1;
    frente_cola = 0;
    final_cola = 0;

    std::cout << "Inicializando sistema con capacidad para " << capacidad << " paquetes...\n";
}

void redimensionar() {
    int nuevaCap = capacidad * 2;
    int *n_ids = new int[nuevaCap];
    float *n_pesos = new float[nuevaCap];
    std::string *n_destinos = new std::string[nuevaCap];
    int *n_prioridades = new int[nuevaCap];
    char *n_estados = new char[nuevaCap];

    for (int i = 0; i < fin; i++) {
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
    if (fin == capacidad) redimensionar();

    std::cout << "Ingrese ID: ";
    std::cin >> ids[fin];
    std::cout << "Ingrese peso: ";
    std::cin >> pesos[fin];
    std::cout << "Ingrese destino: ";
    std::cin.ignore();
    std::getline(std::cin, destinos[fin]);
    std::cout << "Ingrese prioridad (1=Alta, 2=Media, 3=Baja): ";
    std::cin >> prioridades[fin];

    estados[fin] = 'R';
    top_pila = fin;
    fin++;

    std::cout << "Paquete " << ids[top_pila] << " recibido. Estado: 'R'. top_pila = " << top_pila << ".\n";
}

void pop() {
    if (top_pila == -1) {
        std::cout << "Pila vacia. No hay paquetes recibidos para procesar.\n";
        return;
    }

    int idx = top_pila;
    estados[idx] = 'E';

    if (idx + 1 > final_cola) final_cola = idx + 1;

    std::cout << "POP de Pila: Paquete " << ids[idx] << " transferido a Cola. Estado: 'E'. frente_cola = "
              << frente_cola << ", final_cola = " << final_cola - 1 << ".\n";

    top_pila = -1;
    for (int i = idx - 1; i >= 0; --i) {
        if (estados[i] == 'R') {
            top_pila = i;
            break;
        }
    }
}

void despachar() {
    if (frente_cola >= final_cola) {
        std::cout << "No hay paquetes en cola.\n";
        return;
    }

    std::cout << "Analizando Cola... buscando por prioridad (1->2->3).\n";

    int indice = -1;

    for (int i = frente_cola; i < final_cola; ++i) {
        if (estados[i] == 'E' && prioridades[i] == 1) { indice = i; break; }
    }
    if (indice == -1) {
        for (int i = frente_cola; i < final_cola; ++i) {
            if (estados[i] == 'E' && prioridades[i] == 2) { indice = i; break; }
        }
    }
    if (indice == -1) {
        for (int i = frente_cola; i < final_cola; ++i) {
            if (estados[i] == 'E' && prioridades[i] == 3) { indice = i; break; }
        }
    }

    if (indice == -1) {
        std::cout << "No hay paquetes disponibles para despachar.\n";
        return;
    }

    estados[indice] = 'D';
    std::cout << "DESPACHADO: Paquete " << ids[indice] << " (Prioridad " << prioridades[indice] << "). Estado: 'D'.\n";

    if (indice == frente_cola) {
        int i = frente_cola + 1;
        while (i < final_cola) {
            if (estados[i] == 'E') break;
            ++i;
        }
        frente_cola = i;
    }

}

void reporte() {
    int contR = 0, contE = 0, contD = 0;
    for (int i = 0; i < fin; ++i) {
        if (estados[i] == 'R') ++contR;
        else if (estados[i] == 'E') ++contE;
        else if (estados[i] == 'D') ++contD;
    }

    std::cout << "--- Reporte de Estados ---\n";
    std::cout << "Pila (Recibidos - 'R'): " << contR << "\n";
    std::cout << "Cola  (En espera - 'E') : " << contE << " (frente_cola=" << frente_cola << ", final_cola=" << final_cola << ")\n";
    std::cout << "Despachados ('D'): " << contD << "\n";

    std::string destinoBuscado;
    std::cout << "¿Desea un reporte por destino de la cola? (s/n): ";
    char c; std::cin >> c;
    if (c == 's' || c == 'S') {
        std::cin.ignore();
        std::cout << "Ingrese el destino para el reporte: ";
        std::getline(std::cin, destinoBuscado);

        int contador = 0;
        float pesoTotal = 0.0f;
        for (int i = frente_cola; i < final_cola; ++i) {
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
}

void liberarMemoria() {
    delete [] ids;
    delete [] pesos;
    delete [] destinos;
    delete [] prioridades;
    delete [] estados;
    ids = nullptr;
    pesos = nullptr;
    destinos = nullptr;
    prioridades = nullptr;
    estados = nullptr;
    std::cout << "Memoria liberada.\n";
}

int main() {
    CrearArray();

    int opcion;
    do {
        std::cout << "\n--- MegaEnvio ---\n";
        std::cout << "1. Recibir Nuevo Paquete (PUSH)\n";
        std::cout << "2. Procesar Recepcion (POP de Pila -> ENCOLAR)\n";
        std::cout << "3. Despachar (DESENCOLAR con Prioridad)\n";
        std::cout << "4. Reporte de Estados\n";
        std::cout << "5. Salir (Liberar Memoria)\n";
        std::cout << "Seleccione una opcion: ";
        std::cin >> opcion;

        switch (opcion) {
            case 1: agregarPaquete(); break;
            case 2: pop(); break;
            case 3: despachar(); break;
            case 4: reporte(); break;
            case 5: liberarMemoria(); break;
            default: std::cout << "Opcion invalida\n"; break;
        }
    } while (opcion != 5);

    return 0;
}
