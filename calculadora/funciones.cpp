#include <iostream>
#include "funciones.h"

using namespace std;

/*void fDiv (float num1, float num2) {
    if (num2 != 0) {
        cout <<"El resultado es: "<< num1 / num2;
    }

    else {
        cout <<"El numero no puede ser didivo entre 0";
    }
    
} */

float fDiv (float num1, float num2) {
    if ( num2 != 0) {
        return num1 / num2;
    }

    else {
    cout <<"El numero no puede ser didivo entre 0";
    return 0.0f;
    }
}

/*void fMult (float num1, float num2) { 
    cout <<"El resultado es: "<< num1 * num2;
} */

float fMult (float num1, float num2) { 
    return num1 * num2;
}


/*void fSum (float num1, float num2) {
    cout <<"El resultado es: "<< num1 + num2;
}*/

float fSum (float num1, float num2) {
    return num1 + num2;
}

/*void fRes (float num1, float num2) {
    cout <<"El resultado es: "<< num1 - num2;
}*/

float fRes (float num1, float num2) {
    return num1 - num2;
}