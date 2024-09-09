#include <string>
#include <fstream>
#include <iostream>

using namespace std;

const int INSTRUCCIONES_MAXIMO = 20;   // Constantes que pidió el profe
const int DATOS_MAXIMO = 1024;
const int NUMERO_REGISTROS = 8;
const int PC_REGISTRO = 7;

int datos_Memoria[DATOS_MAXIMO] = {0};
int reg[NUMERO_REGISTROS] = {0};

struct instruccion {
    string comando;                // Comando de la instrucción (Puede ser LD, HALT, etc.)
    int argumentos[4];             // (r, s, t, d)
};

instruccion instrucciones_Programa[INSTRUCCIONES_MAXIMO];   // Crea un arreglo de estructuras con el tamaño máximo de instrucciones

void leerArchivo(const string nombreArchivo) {
    
    ifstream archivo(nombreArchivo);

    if (!archivo)
    {
        cerr << "No se pudo abrir el archivo, vuelve a verificar el nombre de tu archivo. (Recuerda incluir la extensión)"<<endl;
        cerr << "Nombre del archivo que intentaste abrir: " << nombreArchivo <<endl;                                                // cerr es como cout pero imprime en la terminal.
        return;
    }

    // Leer las instrucciones...
}

int main(int argc, char *argv[]) {

/*
    Imitando un poco lo que hace la máquina del profe, se optó por tener la siguiente sintáxis al ejecutar la máquina de ejecución: 
    C:/root> Maquina_de_ejecucion.exe el_codigo.txt
    Por lo que el sistema esperara dos argumentos.
    argc -> es un entero que indica el número de argumentos ingresados.
    argv -> matriz de cadenas que representa los argumentos en la línea de comandos.
*/

    if (argc != 2) {                                             // Si los argumentos ingresados son diferentes a dos, no se podrá correr el programa de manera exitosa.
        cerr << "El uso de la máquina de ejecución es el siguiente: "<< argv[0] << " tu_codigo.txt"<<endl;
        return 1;                                               // Indica que hubo un error y el código no terminó de manera exitosa.
    }

    string nombreArchivo;
    leerArchivo(nombreArchivo);
    return 0;            // Indica que el código termino de manera exitosa.
}