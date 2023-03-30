#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <math.h>
#include <fstream>

using namespace std;

//  en el grafico, la parte de abajo tiene que ser en intervalos. es decir, va a haber varios datos cercanos. APLICA ESTADISTICA, tienes resultados, debes tener 7 grupos, halla el w
// y el eje y es la FRECUENCIA, el f, la cantidad de datos que estan dentro de esos parametros

vector<float> matriz[100][2];
const int nComparaciones = 100;
//vector<float> respuestas(( nComparaciones*(nComparaciones + 1) ) / 2) ;
vector<float> respuestas;

class VectorCreator{
private:
    int sizeVector;
    //vector<float> matriz[100][2]; // Donde se guardaran los vectores

public:
    VectorCreator(int _sizeVector){
        sizeVector = _sizeVector;
    }

    vector<float> funcionRandom(int sizeVector, vector<float> vectorA){
        for(int i = 0; i < sizeVector; i++){
            float numeroRandom = 0 + static_cast<float>(rand()) * static_cast<float>(1-0)/RAND_MAX;
            vectorA.push_back(numeroRandom);
        }
        return vectorA;
    }

    void printVector(int sizeVector, vector<float> vectorA){
        cout << " [ ";
        for(int i = 0; i < sizeVector; i++){
            cout << vectorA[i] << " - ";
        }
        cout << " ] ";
    }

    //Llena la matrix
    void completeMatrix(){
        srand(time(0));
        for(int i = 0; i < nComparaciones; i++){
            vector<float> auxiliar;
            auxiliar = funcionRandom(sizeVector, auxiliar); // Llenamos el vector con valores aleatorios
            matriz[i][0] = auxiliar; // Llenamos matriz
            matriz[i][1] = auxiliar; // LLenamos matriz
        }
    }

    void printMatrix(){
        cout << "########## MATRIZ ############" << endl;
        for(int i = 0; i < nComparaciones; i++){
            for(int j = 0; j < 2; j++){
                printVector(sizeVector,matriz[i][j]);
            }
            cout << endl;
        }
    }
};

float distanciaEuclidiana(vector<float> a, vector<float> b, int sizeVector){
    //cout << "################ NUEVO #####################" << endl;
    float suma = 0;
    for (int i = 0; i < sizeVector; i++)
    {
        //cout << b[i] << " - " << a[i] << " = " << pow(b[i] - a[i], 2) << endl;
        float aux =  pow(b[i] - a[i], 2);
        //cout << "aux: "  << aux  << endl;
        suma = suma + aux;
        //cout << "SUMA ACUMULATIVA: " << suma << endl;
    }
    return sqrt(suma);
}

class CourseDimensionality{
    private:
        int sizeVector;

    public:
        CourseDimensionality(int _sizeVector){
            sizeVector = _sizeVector;
        }

        void obtenerDistancias(){
            VectorCreator createVec(sizeVector);
            createVec.completeMatrix();
            //createVec.printMatrix();

            // Sacamos Distancias euclidiandas (todos contra todos)
            int contadorSaltos = 0;
            for( int i = 0; i < nComparaciones; i++ ){
                for (int j = 0 + contadorSaltos; j < nComparaciones; j++) {
                    //cout << i << ",0 - " << j << ",1" << endl;
                    float respuesaParcial = distanciaEuclidiana(matriz[i][0], matriz[j][1], sizeVector);
                    //cout << "respusestaP: " << respuesaParcial << endl;
                    respuestas.push_back(respuesaParcial);
                }
                contadorSaltos++;
            }
        }
};

void escribirTXT(){
    ofstream archivo;
    archivo.open("prueba.txt",ios::out);

    if(archivo.fail()){
        cout << "No se puedo habrir el txt" << endl;
        exit(1);
    }

    archivo<<"Prueba es escritura";

    archivo.close();
}

int main() {

    // to do...
    int sizeVector = 500;

    CourseDimensionality test1(sizeVector);
    test1.obtenerDistancias();

    // ################### TXT ############################
    ofstream archivo;
    archivo.open("prueba.txt",ios::out);

    if(archivo.fail()){
        cout << "No se puedo habrir el txt" << endl;
        exit(1);
    }

    int contador = 0;
    cout << endl << "########### SALIDA #################" << endl;
    for(int i = 0; i <  nComparaciones*(nComparaciones + 1) / 2; i++ ){
        if(respuestas[i] != 0){
            //cout << respuestas[i] << endl;
            archivo << respuestas[i] << endl;
            contador++;
        }
    }
    cout << "Se crearon " << nComparaciones << " puntos de " << sizeVector << " dimensiones" << endl;
    cout << "Se registraron " <<  contador << " resultados" << endl;
    cout << "El txt se exporto correctamente. Ejecute el archivo .py (../GraficoBarras/main.py) " << endl;

    archivo.close();
    // #####################################################

    return 0;
}
