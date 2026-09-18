/*
    ESTUDIO PRELIMINAR DE ESTABILIDAD DE UNA ESTRUCTURA
    ----------------------------------------------------
    Registra elementos, calcula su factor de utilizacion,
    determina su estado de seguridad, identifica el elemento
    mas comprometido, simula un incremento de carga y genera
    un informe final.
*/

#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

const int MAX_ELEMENTOS = 10;

// ---------------------------------------------------------
// PARTE 1: Modelado del elemento
// ---------------------------------------------------------
struct Elemento {
    int codigo;
    string nombre;
    float longitud;
    float cargas[3];          // Carga1, Carga2, Carga3
    float capacidadMaxima;
    float cargaPromedio;      // se calcula en calcularFactor()
    float factorUtilizacion;
    string estadoSeguridad;
};

// ---------------------------------------------------------
// Prototipos de funciones
// ---------------------------------------------------------
void registrarElemento(Elemento &elemento);
float calcularFactor(Elemento *elemento);
void determinarSeguridad(Elemento &elemento);
Elemento* obtenerElementoCritico(Elemento elementos[], int cantidad);
void aumentarCargas(Elemento &elemento, float porcentaje);
void generarInforme(Elemento elementos[], int cantidad);
void mostrarElemento(const Elemento &e); // funcion auxiliar de despliegue

// ===========================================================
// MAIN
// ===========================================================
int main() {
    Elemento elementos[MAX_ELEMENTOS];
    int cantidad;

    // --- Validacion de cantidad de elementos (1 a 10) ---
    do {
        cout << "Ingrese la cantidad de elementos a registrar (1-10): ";
        cin >> cantidad;
        if (cantidad < 1 || cantidad > 10) {
            cout << "Cantidad invalida. Debe estar entre 1 y 10.\n";
        }
    } while (cantidad < 1 || cantidad > 10);

    // -------------------------------------------------------
    // PARTE 2: Registro de elementos
    // -------------------------------------------------------
    for (int i = 0; i < cantidad; i++) {
        cout << "\n--- Registro del elemento " << (i + 1) << " ---\n";
        registrarElemento(elementos[i]);
    }

    // -------------------------------------------------------
    // PARTE 3 y 4: Calculo del factor y estado de seguridad
    // Recorrido mediante PUNTEROS
    // -------------------------------------------------------
    for (Elemento *p = elementos; p < elementos + cantidad; p++) {
        calcularFactor(p);          // calcula y guarda factor dentro del struct
        determinarSeguridad(*p);    // usa el factor guardado para fijar el estado
    }

    // -------------------------------------------------------
    // PARTE 5: Elemento mas comprometido
    // -------------------------------------------------------
    Elemento *critico = obtenerElementoCritico(elementos, cantidad);

    cout << "\n===== ELEMENTO MAS COMPROMETIDO =====\n";
    mostrarElemento(*critico);

    // -------------------------------------------------------
    // PARTE 6: Simulacion de incremento de carga
    // Se aplica sobre el elemento critico, a modo de simulacion
    // -------------------------------------------------------
    float porcentaje;
    cout << "\nIngrese el porcentaje de incremento de carga a simular (%): ";
    cin >> porcentaje;

    aumentarCargas(*critico, porcentaje);   // aumenta cargas[0..2]
    calcularFactor(critico);                // recalcula promedio y factor
    determinarSeguridad(*critico);          // recalcula estado

    cout << "\n===== ELEMENTO DESPUES DEL INCREMENTO =====\n";
    mostrarElemento(*critico);

    // -------------------------------------------------------
    // PARTE 7: Informe final
    // -------------------------------------------------------
    generarInforme(elementos, cantidad);

    return 0;
}

// ===========================================================
// PARTE 2: Registro de elementos
// ===========================================================
void registrarElemento(Elemento &elemento) {
    cout << "Codigo: ";
    cin >> elemento.codigo;

    cout << "Nombre: ";
    cin.ignore();
    getline(cin, elemento.nombre);

    cout << "Longitud (m): ";
    cin >> elemento.longitud;

    cout << "Carga 1 (N): ";
    cin >> elemento.cargas[0];

    cout << "Carga 2 (N): ";
    cin >> elemento.cargas[1];

    cout << "Carga 3 (N): ";
    cin >> elemento.cargas[2];

    cout << "Capacidad maxima (N): ";
    cin >> elemento.capacidadMaxima;
}

// ===========================================================
// PARTE 3: Calculo del factor de utilizacion
// Recibe un puntero y accede al arreglo cargas[] a traves de el
// ===========================================================
float calcularFactor(Elemento *elemento) {
    // Acceso al arreglo interno mediante el puntero
    float suma = elemento->cargas[0] + elemento->cargas[1] + elemento->cargas[2];
    float promedio = suma / 3.0f;

    elemento->cargaPromedio = promedio;
    elemento->factorUtilizacion = promedio / elemento->capacidadMaxima;

    return elemento->factorUtilizacion;
}

// ===========================================================
// PARTE 4: Determinacion del estado de seguridad
// ===========================================================
void determinarSeguridad(Elemento &elemento) {
    float f = elemento.factorUtilizacion;

    if (f >= 0.00f && f <= 0.50f) {
        elemento.estadoSeguridad = "SEGURO";
    } else if (f > 0.50f && f <= 0.80f) {
        elemento.estadoSeguridad = "PRECAUCION";
    } else if (f > 0.80f && f <= 1.00f) {
        elemento.estadoSeguridad = "RIESGO";
    } else { // f > 1.00
        elemento.estadoSeguridad = "SOBRECARGA";
    }
}

// ===========================================================
// PARTE 5: Elemento mas comprometido
// Retorna un puntero al elemento ORIGINAL (no una copia)
// ===========================================================
Elemento* obtenerElementoCritico(Elemento elementos[], int cantidad) {
    Elemento *masCritico = &elementos[0];

    for (int i = 1; i < cantidad; i++) {
        if (elementos[i].factorUtilizacion > masCritico->factorUtilizacion) {
            masCritico = &elementos[i];
        }
    }
    return masCritico;
}

// ===========================================================
// PARTE 6: Simulacion de incremento de carga
// Nueva carga = Carga actual * (1 + porcentaje / 100)
// ===========================================================
void aumentarCargas(Elemento &elemento, float porcentaje) {
    for (int i = 0; i < 3; i++) {
        elemento.cargas[i] = elemento.cargas[i] * (1 + porcentaje / 100.0f);
    }
}

// ===========================================================
// PARTE 7: Informe general de la estructura
// ===========================================================
void generarInforme(Elemento elementos[], int cantidad) {
    int seguros = 0, precaucion = 0, riesgo = 0, sobrecarga = 0;
    float sumaFactores = 0.0f;

    cout << "\n===================== INFORME FINAL =====================\n";
    cout << left << setw(8) << "Codigo" << setw(15) << "Nombre"
         << setw(15) << "CargaProm" << setw(12) << "Factor"
         << setw(12) << "Estado" << "\n";
    cout << "-----------------------------------------------------------\n";

    for (int i = 0; i < cantidad; i++) {
        cout << left << setw(8) << elementos[i].codigo
             << setw(15) << elementos[i].nombre
             << setw(15) << fixed << setprecision(2) << elementos[i].cargaPromedio
             << setw(12) << elementos[i].factorUtilizacion
             << setw(12) << elementos[i].estadoSeguridad << "\n";

        // Conteo por estado
        if (elementos[i].estadoSeguridad == "SEGURO") seguros++;
        else if (elementos[i].estadoSeguridad == "PRECAUCION") precaucion++;
        else if (elementos[i].estadoSeguridad == "RIESGO") riesgo++;
        else if (elementos[i].estadoSeguridad == "SOBRECARGA") sobrecarga++;

        sumaFactores += elementos[i].factorUtilizacion;
    }

    float factorPromedio = sumaFactores / cantidad;

    cout << "-----------------------------------------------------------\n";
    cout << "Elementos SEGURO:      " << seguros << "\n";
    cout << "Elementos PRECAUCION:  " << precaucion << "\n";
    cout << "Elementos RIESGO:      " << riesgo << "\n";
    cout << "Elementos SOBRECARGA:  " << sobrecarga << "\n";
    cout << fixed << setprecision(2);
    cout << "Factor de utilizacion promedio de la estructura: "
         << factorPromedio << "\n";
    cout << "=============================================================\n";
}

// ===========================================================
// Funcion auxiliar: muestra los datos de un elemento
// ===========================================================
void mostrarElemento(const Elemento &e) {
    cout << fixed << setprecision(2);
    cout << "Codigo: " << e.codigo << "\n";
    cout << "Nombre: " << e.nombre << "\n";
    cout << "Longitud: " << e.longitud << " m\n";
    cout << "Carga 1: " << e.cargas[0] << " N\n";
    cout << "Carga 2: " << e.cargas[1] << " N\n";
    cout << "Carga 3: " << e.cargas[2] << " N\n";
    cout << "Capacidad maxima: " << e.capacidadMaxima << " N\n";
    cout << "Factor de utilizacion: " << e.factorUtilizacion << "\n";
    cout << "Estado de seguridad: " << e.estadoSeguridad << "\n";
}
