#include <iostream>
#include "funciones.h"

using namespace std;
char opc = 0;
float num1,num2 = 0;

int main () {
    cout <<"Bienvenido a Dalsar calculator" <<endl;
    cout <<""<<endl;

    cout <<"Para suma ingrese: s " <<endl;
    cout <<"Para resta ingrese: r " <<endl;
    cout <<"Para multiplicacion ingrese: m " <<endl;
    cout <<"Para division ingrese: d " <<endl;
    cout <<""<<endl;    

    cout << "Ingrese la operacion que necesita realizar: ";
    cin >>opc;

    cout << "Ingrese el primer numero : ";
    cin >> num1;
    
    cout << "Ingrese el segundo numero : ";
    cin >> num2;


switch (opc) {

    case 's':
    case 'S':

    fSum (num1,num2);

    break;

    case'r': 
    case'R': 

    fRes (num1,num2);

    
    break;

    case 'm':
    case 'M':

    fMult (num1,num2);
 
    break;

    case 'd':
    case 'D':
    fDiv (num1,num2);

    break;


    default:
    cout <<"La opcion ingresada es invalida\n";
    break;

}
    return 0;

}

