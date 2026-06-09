#include <iostream>
#include "funciones.h"
// modificar float de void para que pueda reutilizar resultados de switch
using namespace std;
char opc = 0, continuar = 0;
float num1, num2 = 0, sumReciente = 0, multReciente = 0, acumulador = 0;

int main()
{
    cout << "Bienvenido a Dalsar calculator" << endl;
    cout << "" << endl;

    do
    {
        cout << "Para suma ingrese: s " << endl;
        cout << "Para resta ingrese: r " << endl;
        cout << "Para multiplicacion ingrese: m " << endl;
        cout << "Para division ingrese: d " << endl;
        cout << "Para obtener suma de resultado de s y m ingrese: e " << endl;

        cout << "" << endl;

        cout << "Ingrese la operacion que necesita realizar: ";
        cin >> opc;
        // cin.ignore (); //esto sirve para evitar bug donde enter terminaba la app usado
        // en casos donde usamos cin.getline (nombre,20);

        if (opc != 'e' && opc != 'E')
        {
            cout << "Ingrese el primer numero : ";
            cin >> num1;

            cout << "Ingrese el segundo numero : ";
            cin >> num2;
        }

        switch (opc)
        {

        case 's':
        case 'S':

            sumReciente = fSum(num1, num2);
            acumulador += sumReciente;
            cout << "Resultado: " << sumReciente << endl;
            break;

        case 'r':
        case 'R':

            cout << "Resultado: " << fRes(num1, num2);

            break;

        case 'm':
        case 'M':

            multReciente = fMult(num1, num2);
            acumulador += multReciente;
            cout << "Resultado: " << multReciente << endl;

            break;

        case 'd':
        case 'D':
            cout << "Resultado: " << fDiv(num1, num2);

            break;

        case 'e':
        case 'E':
            cout << "El resultado acumulado de suma, y multiplicacion es: " << acumulador;
            break;

            break;

        default:
            cout << "La opcion ingresada es invalida\n";
            break;
        }

        cout << "\nDeseas realizar mas operaciones? Y/N: \n";
        cin >> continuar;

    } while (continuar == 'y' || continuar == 'Y');
    cout << "\nGracias por usar Dalsar calculator!\n";

    return 0;
}
