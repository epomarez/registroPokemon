#include <iostream>

using namespace std;

int main(){

    setlocale(LC_ALL, "");

    const int NIVEL_MAXIMO = 100;
    const int MAXIMO_OPCIONES_MENU = 5;
    const int MAXIMO_POKEMONES = 25;
    const int CIFRAS_ID = 6;




    //Ya que un arreglo sólo puede tener un sólo tipo, decidí usar un sistemas de codigos.
    //El 50 hace referencia a la cantidad máxima de pokemones que se pueden registrar.
    //El 4 indica la cantidad de atributos.
    //Seguiré este orden:
    //
    //[x][] La posicion x del pokemon indica la posicion x en el que
    // esta guardado su nombre en nombresPokemones[].
    //[x][0] Indica si la casilla está llena con valor 1, 0 si no lo está.
    //[x][1] Se almacena el ID del Pokémon.
    //[x][2] Se almacena la posicion en el que el tipo del
    //Pokémon está registrado en el arreglo tipoPokemon[]
    //[x][3] Se almacena el nivel de poder del Pokémon.
    //

    int equipoPokemon[50][4];
    const int CASILLA_ESTADO = 0;
    const int CASILLA_ID = 1;
    const int CASILLA_TIPO = 2;
    const int CASILLA_NIVEL = 3;

    //Ayudará a manipular los datos.


    //Ayudará a mantener el control del límite máximo de Pokemones.
    /*!!REVISAR: Si puedo encontar manera de eliminar esta variable
    * mediante los valores equipoPokemon[x][0] y bucles for.
    */
    int cantidadPokemones = 0;

    string nombresPokemones[50];
    string tipoPokemones[4] = {"fuego", "agua", "planta", "eléctrico"};
    string menuInicio = "\n\n************************************\n"
                        "Sistema de entrenamiento Pokémon.\n"
                        "1. Registrar un Pokémon.\n"
                        "2. Entrenar un Pokémon.\n"
                        "3. Mostrar el equipo Pokémon.\n"
                        "4. Mostrar el Pokémon más fuerte\n"
                        "5. Salir del Programa.\n"
                        "Seleccione una opcion: ";

    string menuEntrenamiento = "\nIngrese el tipo de entrenamiento que quiere realizar:\n"
                                "1. Combate en gimnasio.\n"
                                "2. Batalla con otro entrenador.\n"
                                "3. Práctica de habilidades.\n";
    int seleccionMenu;
    int seleccionEntrenamiento;

    bool esSeleccionMenuValida;
    bool esSeleccionEntrenamientoValida = false;
    bool salir;
    bool casillaLlena;


    do{
        esSeleccionMenuValida = false;
        salir = false;
        seleccionMenu = 0;

        cout << menuInicio;
        cin >> seleccionMenu;
        /*Esto me permite evaluar la seleccion y guardar el resultado en una variable para leer
        el código con mayor facilidad*/
        esSeleccionMenuValida = (seleccionMenu >= 1 && seleccionMenu <= MAXIMO_OPCIONES_MENU);

        //Falta hacer las validaciones de entrada de cada caso.
        if(esSeleccionMenuValida){

            switch(seleccionMenu){
                case 1:
                    {
                        string nombrePokemon;
                        int idPokemon;
                        int codigoTipoPokemon;
                        int nivelPokemon;

                        bool idValido = false;
                        bool codigoTipoValido = false;
                        bool nivelValido = false;
                        int cantidadCifrasId;
                        int copiaID = 0;


                        cout << "\nRegistro de Pokémon. \n";
                        cout << "Ingrese el nombre del Pokémon: ";
                        cin >> nombrePokemon;


                        do{

                            cout << "\nIngrese el ID del Pokémon: ";
                            cin >> idPokemon;

                            copiaID = idPokemon;
                            cantidadCifrasId = 0;

                            //Calcula la cantidad de cifras del ID
                            while(copiaID>0){
                                copiaID /= 10;
                                cantidadCifrasId++;
                            }

                            //Evaluara si la cifra  es válida o no.
                            if(cantidadCifrasId!=CIFRAS_ID){
                                cout << "\nERROR: La cantidad de cifras no es valida, deben ser 6" << endl;
                                continue;
                            } else {
                                //Revisa si el ID está repetido
                                for(int i = 0; i < MAXIMO_POKEMONES; i++){

                                    if(idPokemon == equipoPokemon[i][CASILLA_ID]){
                                        cout << "\nERROR: La cifra está repetida" << endl;
                                        break;
                                    } else if(i == MAXIMO_POKEMONES-1){
                                        idValido = true;
                                    }

                                }

                            }

                        }while(!idValido);

                        do{
                            cout << "\n 0. Fuego"
                                 << "\n 1. Agua"
                                 << "\n 2. Planta"
                                 << "\n 3. Eléctrico"
                                 << "\nSeleccione el tipo del Pokémon: ";

                            cin  >> codigoTipoPokemon;

                            if(codigoTipoPokemon > 3 || codigoTipoPokemon < 0){
                                cout << "\nERROR: Elegiste un tipo no existente." << endl;
                            } else {
                                codigoTipoValido = true;
                            }
                        }while(!codigoTipoValido);

                        do{
                            cout << "\nIngrese el nivel del Pokemon (1 a 100)";
                            cin  >> nivelPokemon;

                            if(nivelPokemon > NIVEL_MAXIMO || nivelPokemon < 1){
                                cout << "\nERROR: El nivel está fuera de rango." << endl;
                            } else {
                                nivelValido = true;
                            }

                        }while(!nivelValido);

                        nombresPokemones[cantidadPokemones] = nombrePokemon;
                        equipoPokemon[cantidadPokemones][CASILLA_ESTADO] = 1;
                        equipoPokemon[cantidadPokemones][CASILLA_ID] = idPokemon;
                        equipoPokemon[cantidadPokemones][CASILLA_TIPO] = codigoTipoPokemon;
                        equipoPokemon[cantidadPokemones][CASILLA_NIVEL] = nivelPokemon;
                        cantidadPokemones ++;
                    }

                    break;

                case 2:

                    if(cantidadPokemones == 0){
                            cout << "No hay pokemones registrados";
                        } else {
                            string nombrePokemon;
                            int idPokemon = 0;
                            int posicionPokemon = 0;
                            int dificultadEntrenamiento = 0;
                            bool idValido = false;
                            bool dificultadValida = false;
                            int cantidadCifrasId = 0;
                            int copiaID = 0;


                            cout << "\nEntrenar Pokémon. \n";





                            do{

                                cout << "\nIngrese el ID del Pokémon: ";
                                cin >> idPokemon;
                                copiaID = idPokemon;
                                 //Calcula la cantidad de cifras del ID
                                while(copiaID>0){
                                    copiaID /= 10;
                                    cantidadCifrasId++;
                                }

                                //Evaluara si la cifra  es válida o no.
                                if(cantidadCifrasId!=CIFRAS_ID){
                                    cout << "\nERROR: La cantidad de cifras no es valida, deben ser 6" << endl;
                                    continue;
                                } else {
                                    //Revisa si el ID está repetido
                                    for(int i = 0; i < MAXIMO_POKEMONES; i++){

                                        if(idPokemon == equipoPokemon[i][CASILLA_ID]){

                                            posicionPokemon = i;
                                            idValido = true;
                                            break;
                                        } else if(i == MAXIMO_POKEMONES-1){
                                            cout << "\nERROR: Pokémon no encontrado" << endl;
                                            idValido = false;
                                        }

                                    }

                                }
                            }while(!idValido);


                            cout << menuEntrenamiento;
                            cin >> seleccionEntrenamiento;

                            if(esSeleccionEntrenamientoValida){
                                    //!!Tal vez pueda reducir codigo declarando un arreglo arriba con opciones
                                switch(seleccionEntrenamiento){
                                    case 1:
                                        cout << "\nHas elegido Combate en gimnasio!\n";
                                        break;
                                    case 2:
                                        cout << "\nHas elegido Combate en gimnasio!\n";
                                        break;
                                    case 3:
                                        cout << "\nHas elegido Combate en gimnasio!\n";
                                        break;
                                }
                            }

                             do{
                            cout << "\nIngrese dificultad de entrenamiento (1 a 100): ";
                            cin  >> dificultadEntrenamiento;

                            if(dificultadEntrenamiento > NIVEL_MAXIMO || dificultadEntrenamiento < 1){
                                cout << "\nERROR: La dificultad está fuera de rango." << endl;
                            } else {
                                dificultadValida = true;
                            }

                            }while(!dificultadValida);

                            if(dificultadEntrenamiento > equipoPokemon[posicionPokemon][CASILLA_NIVEL]){
                                cout << "Entrenamiento fallido. " << nombresPokemones[posicionPokemon]
                                     << " necesita más práctica antes de intentarlo de nuevo." << endl;
                            } else {
                                cout << "Entrenamiento exitoso!. " << nombresPokemones[posicionPokemon]
                                     << " ha ganado +10 puntos de poder." << endl;
                                     if(equipoPokemon[posicionPokemon][CASILLA_NIVEL] >= 90){
                                        equipoPokemon[posicionPokemon][CASILLA_NIVEL] = 100;
                                     } else {
                                        equipoPokemon[posicionPokemon][CASILLA_NIVEL] += 10;
                                     }

                            }
                        }
                        break;

                case 3:
                    if(cantidadPokemones == 0){
                            cout << "No hay pokemones registrados";
                        } else {
                            string nombrePokemon;
                            int idPokemon;
                            int codigoTipoPokemon;
                            int nivelPokemon;
                            cout << "\nMostrar el equipo Pokémon! \n"
                             << "===========================\n"
                             << "     EQUIPO POKEMON\n"
                             << "===========================\n";
                            for(int posicion=0; posicion < MAXIMO_POKEMONES; posicion++){
                                    casillaLlena = equipoPokemon[posicion][CASILLA_ESTADO]==1;
                                if(casillaLlena){

                                    nombrePokemon = nombresPokemones[posicion];
                                    idPokemon = equipoPokemon[posicion][CASILLA_ID];
                                    codigoTipoPokemon = equipoPokemon[posicion][CASILLA_TIPO];
                                    nivelPokemon = equipoPokemon[posicion][CASILLA_NIVEL];

                                    cout << "Nombre: " << nombrePokemon << endl
                                         << "ID: " << idPokemon << endl
                                         << "Tipo: " << tipoPokemones[codigoTipoPokemon] << endl
                                         << "Nivel: " << nivelPokemon << endl
                                         << "--------------------------------------------------"<< endl;
                                }
                            }
                        }
                    break;

                case 4:

                    {
                        int nivelMayor = 0;
                        int posicionNivelMayor = 0;
                        int nivelActual = 0;
                        if(cantidadPokemones == 0){
                            cout << "No hay pokemones registrados";
                        } else {
                            string nombrePokemon;
                            int idPokemon;
                            int codigoTipoPokemon;
                            int nivelPokemon;
                            cout << "\nMostrar el Pokémon más fuerte! \n";
                            for(int posicionActual=0; posicionActual < MAXIMO_POKEMONES; posicionActual++){
                            casillaLlena = equipoPokemon[posicionActual][CASILLA_ESTADO]==1;

                            if(casillaLlena){


                                nivelActual = equipoPokemon[posicionActual][CASILLA_NIVEL];

                                if(nivelActual>nivelMayor){
                                    nivelMayor = nivelActual;
                                    posicionNivelMayor = posicionActual;
                                }
                            }
                            }
                            nombrePokemon = nombresPokemones[posicionNivelMayor];
                            idPokemon = equipoPokemon[posicionNivelMayor][CASILLA_ID];
                            codigoTipoPokemon = equipoPokemon[posicionNivelMayor][CASILLA_TIPO];
                            nivelPokemon = equipoPokemon[posicionNivelMayor][CASILLA_NIVEL];

                            cout << "Nombre: " << nombrePokemon << endl
                                         << "ID: " << idPokemon << endl
                                         << "Tipo: " << tipoPokemones[codigoTipoPokemon] << endl
                                         << "Nivel: " << nivelPokemon << endl
                                         << "--------------------------------------------------";
                        }


                    }

                    break;

                case 5:
                    salir = true;
                    break;
            }
        } else{
            cout << "\nERROR: No existe una opción con este número, intenta de nuevo.\n";
        }


    } while(!salir);


    cout << "Hello world!" << endl;
    return 0;
}
