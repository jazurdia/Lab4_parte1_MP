/***
* Extraído de lab 3 de Programación de Microprocesadores
* https://github.com/jazurdia/Lab_03_MP
 *
 * Laboratorio 4 parte 1 B
 * Implementación de Mutex.
*/


#include <iostream>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
using namespace std;

// funcion para p_threads que evalua n en la sumatoria.
void *sumatoria(void *arg){
    float *n;
    n = (float *)arg;
    float *resultado;
    resultado = (float *)malloc(sizeof(float));
    *resultado = 1/((*n)*((*n)+1));
    return (void *)resultado;
}

int main(){
    float n;
    cout << "Ingrese el numero n: " << endl;
    cin >> n;
    float resSumatoria = 0;

    for (int i = 1; i < n; i++) {
        pthread_t hilo;
        pthread_attr_t attr;

        float v = (float) i;

        pthread_attr_init(&attr);
        pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

        void *exit_value;
        pthread_create(&hilo, &attr, sumatoria, (void *) &v);
        pthread_join(hilo, &exit_value);
        float res = *((float *) exit_value);
        free(exit_value);

        resSumatoria += res;
    }







    cout << "El valor de la sumatoria es: " << resSumatoria << endl;

    return 0;

}