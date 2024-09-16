#include <string>
#include <fstream>
#include <iostream>
#include <regex>

using namespace std;
                                                            // Constantes que pidió el profe. 
const unsigned int INSTRUCCIONES_MAXIMO = 20 * 48;          // Mas o menos calcule el tamaño de una instrucción (48 bytes) por un máximo de 20 instrucciones.
const unsigned int DATOS_MAXIMO = 1024;
const unsigned int NUMERO_REGISTROS = 8;
const unsigned int PC_REGISTRO = 7;             // Define cuál es el registro de la instrucción que se ejecuta (tomaremos el último de los registros para esto el 7)

int datos_Memoria[DATOS_MAXIMO] = {0};          // Arreglo de enteros para almacenar datos
int reg[NUMERO_REGISTROS] = {0};                // Arreglo de enteros para los 8 registros

struct instruccion {
    string comando;                // Comando de la instrucción (Puede ser LD, HALT, etc.)
    unsigned int argumentos[4];             // (r, s, t, d)
};

instruccion instrucciones_Memoria[INSTRUCCIONES_MAXIMO];   // Crea un arreglo de estructuras con el tamaño máximo de instrucciones
instruccion nueva_instruccion;                             // Nuevo comando a agregar a Instrucciones_Memoria
ifstream archivoGlobal;

unsigned int indiceInstrucciones = 0;

bool leerArchivo(string nombreArchivo) {
    
    archivoGlobal.open(nombreArchivo);

    if (!archivoGlobal)
    {
        cerr << "No se pudo abrir el archivo, vuelve a verificar el nombre de tu archivo. (Recuerda incluir la extensión)"<<endl;
        cerr << "Nombre del archivo que intentaste abrir: " << nombreArchivo <<endl;                                                // cerr es como cout pero imprime en la terminal.
        return false;
    }

    else {
        return true; // Se pudo leer el archivo
    }
    
}

void procesarInstrucciones(ifstream& archivoGlobal) {
    string linea;
    int indiceInstrucciones = 0;
    bool valido;
    while(getline(archivoGlobal,linea)) {  //Lee todas las líneas del archivo
        valido = checarSintaxis(linea);
        
        if (!valido) {
            // Función que muestra el error disparado.
            return;
        }

        else{

            // Función para ejecutar la instrucción valida
            // No ejecutar nada y seguir con la lectura de las otras líneas si es un comentario o línea en blanco.

        }
    }
}

bool checarSintaxis(const string& linea) {        // Verifica la sintaxis, pero no verifica si los números de los datos maximos o los números de los registros esten dentro de rango.

     // Eliminar espacios en blanco al inicio y al final de la línea
    string linea_limpia = linea;
    linea_limpia.erase(0, linea_limpia.find_first_not_of(" \t"));  // Quitar espacios iniciales
    linea_limpia.erase(linea_limpia.find_last_not_of(" \t") + 1);  // Quitar espacios finales


    if (linea_limpia.empty() || linea_limpia[0] == '*') {
        return true;  // Es una línea válida (comentario o línea en blanco). Salta a verificar la siguiente línea.
    }

    regex instruccionRegex(R"(^\d+:\s*(\w+)\s*(.*)$)");
    smatch coincidencia;

    if (regex_match(linea_limpia, coincidencia, instruccionRegex)){     // Checamos si la sintaxis es válida. La variable coincidencia toma en el índice 0 la línea completa,
        string comando = coincidencia[1];                               // en el índice 1 el comando y en el 2 los argumentos.
        string argumentos = coincidencia[2];

        string comandosValidos[] = {"HALT", "IN", "OUT", "ADD", "SUB", "MUL", "DIV", 
                                    "LD", "LDA", "LDC", "ST", 
                                    "JLT", "JLE", "JGE", "JGT", "JEQ", "JNE"};

        bool comandoValido = false;
        for (const string& cmd : comandosValidos) {  // Verifica si es un comando válido
            if (comando == cmd) {
                comandoValido = true;
                break;
            }
        }

        if (!comandoValido) {
            cerr << "Error: Comando inválido '" << comando << "' en la línea: " << linea << endl;
            return false;      // El comando no es válido
        }

        return checarFormato(coincidencia);
    }

    else {
        return false;        // La sintaxis es inválida
    }
}

bool checarFormato(smatch coincidencia) {        // Checamos el formato de los argumentos para ver si son válidos.
    string comando = coincidencia[1];
    string argumentos = coincidencia[2];
    unsigned int nuevo_arg;
    smatch argsMatch;                            // Almacena los argumentos válidos para insertarlos en nueva_instrucción

    regex formatoHaltInOut(R"(^(\d+)\s*,\s*(\d+)\s*,\s*(\d+)$)"); // Para HALT, IN, OUT
    regex formatoOperacion(R"(^(\d+)\s*,\s*(\d+)\s*,\s*(\d+)$)"); // Para ADD, SUB, MUL, DIV
    regex formatoMemoria(R"(^(\d+)\s*,\s*(\d+)\s*\(\s*(\d+)\s*\)$)"); // Para LD, LDA, LDC, ST, JLT, JLE, JGE, JGT, JEQ, JNE

    nueva_instruccion.comando = "";
    fill(begin(nueva_instruccion.argumentos), end(nueva_instruccion.argumentos), 0); // Borra los elementos de nueva_instruccion para poder evitar que se empalmen con una nueva.

    if (comando == "HALT" || comando == "IN" || comando == "OUT") {
        if (!regex_match(argumentos, argsMatch, formatoHaltInOut)) {           // Verifica que los argumentos cumplan la regla de regex
            cerr << "Error: Argumentos inválidos para la instrucción '" << comando << "' en la línea: " << argumentos << endl;
            return false;
        }
        else {
            nueva_instruccion.comando = comando;
            nueva_instruccion.argumentos[0] = stoul(argsMatch[1].str());   // Parsear int de argsMatch[1] a unsigned int de nueva_instruccion.argumentos.
            almacenarInstrucción(nueva_instruccion);
            return true;
        }
    }

    else if (comando == "ADD" || comando == "SUB" || comando == "MUL" || comando == "DIV") {
        if (!regex_match(argumentos, argsMatch, formatoOperacion)) {           // Verifica que los argumentos cumplan la regla de regex
            cerr << "Error: Argumentos inválidos para la instrucción '" << comando << "' en la línea: " << argumentos << endl;
            return false;
        }
        else {
            // Antes de almacenarlos hay que verificar la posición de r,d,s,t con los argumentos para almacenarlos adecuadamente.
            return true;
        }
    }

    else {
        if (!regex_match(argumentos, argsMatch, formatoMemoria)) {             // Verifica que los argumentos cumplan la regla de regex
            cerr << "Error: Argumentos inválidos para la instrucción '" << comando << "' en la línea: " << argumentos << endl;
            return;
        }
        else {
            // Antes de almacenarlos hay que verificar la posición de r,d,s,t con los argumentos para almacenarlos adecuadamente.
            return true;
        }
    }

}

void almacenarInstrucción(instruccion nueva) {  // Almacena el comando y los argumentos dentro de la lista de instrucciones que el programa ejecutara.
    if ((indiceInstrucciones * 48) < INSTRUCCIONES_MAXIMO) {    // Verificar el espacio
        instrucciones_Memoria[indiceInstrucciones] = nueva;     // Inserta la nueva instrucción
        indiceInstrucciones++;
    } else {
        cerr << "Error: Se ha alcanzado el límite máximo de instrucciones." << endl;
    }
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

    if (!leerArchivo(argv[1])) {
        // Mostrar mensaje de error: no encontró el archivo
        return 1;                                               // Indica que hubo un error y el código no terminó de manera exitosa.
    }

    else {
        procesarInstrucciones(archivoGlobal);

        // Mas cosas

        archivoGlobal.close();
        return 0;            // Indica que el código termino de manera exitosa.
    }
}