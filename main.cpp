//
// Created by Alejandro Azurdia on 4/09/22.
//

#include <iostream>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <mutex>
using namespace std;

float resultado;
float sumaParcial;
pthread_mutex_t candado;

void *sumatoria(void *arg){

    pthread_mutex_lock(&candado);
    float input = *((float *) arg);
    //float abajo = input * ( input + 1);
    sumaParcial = 1/(input*(input + 1));
    //sumaParcial = 1/abajo;
    pthread_mutex_unlock(&candado);

}

int main(){
    int num_max;
    cout << "Ingrese el numero n: " << endl;
    cin >> num_max;

    // instanciar los hilos.
    pthread_t idThread[num_max]; // para n hilos con idThread[i] para el i-esimo hilo.
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

    for (int i = 1; i < num_max; i++) {
        float n = (float) i;
        pthread_create(&idThread[i], &attr, sumatoria, (void *) &n);
    }

    for (int i = 1; i < num_max; i++) {
        pthread_join(idThread[i], NULL);
        resultado += sumaParcial;
        //cout << "El resultado de la sumatoria es: " << resultado << endl;

    }

    cout << "" << endl;
    cout << "El resultado de la sumatoria es: " << resultado << endl;

    //liberar memoria
    pthread_attr_destroy(&attr);
    pthread_mutex_destroy(&candado);
    pthread_exit(NULL);
    return 0;

}


