#include <iostream>

using namespace std;

bool evaluarId(int, int, int[][4], int);
bool revisarExistenciaElemento(int, int[][4], int, int);
void mostrarPokemon(string, int, string, int);

int main()
{

    setlocale(LC_ALL, "");

    const int NIVEL_MAXIMO = 100;
    const int MAXIMO_OPCIONES_MENU = 5;
    const int MAXIMO_POKEMONES = 25;
    const int CIFRAS_ID = 6;

    const int CASILLA_ESTADO = 0;
    const int CASILLA_ID = 1;
    const int CASILLA_TIPO = 2;
    const int CASILLA_NIVEL = 3;

    int seleccionMenu;
    int seleccionEntrenamiento;
    int equipoPokemon[MAXIMO_POKEMONES][4];
    int cantidadPokemones = 0;

    bool esSeleccionMenuValida;
    bool esSeleccionEntrenamientoValida;
    bool salir;
    bool casillaLlena;

    string nombresPokemones[MAXIMO_POKEMONES];
    string tipoPokemones[4] = {"fuego", "agua", "planta", "el�ctrico"};
    string menuInicio = "\n\n************************************\n"
                        "Sistema de entrenamiento Pok�mon.\n"
                        "1. Registrar un Pok�mon.\n"
                        "2. Entrenar un Pok�mon.\n"
                        "3. Mostrar el equipo Pok�mon.\n"
                        "4. Mostrar el Pok�mon m�s fuerte\n"
                        "5. Salir del Programa.\n"
                        "Seleccione una opcion: ";

    string menuEntrenamiento = "\nIngrese el tipo de entrenamiento que quiere realizar:\n"
                               "1. Combate en gimnasio.\n"
                               "2. Batalla con otro entrenador.\n"
                               "3. Pr�ctica de habilidades.\n";

    do
    {
        esSeleccionMenuValida = false;
        salir = false;
        esSeleccionEntrenamientoValida = false;
        seleccionMenu = 0;

        cout << menuInicio;
        cin >> seleccionMenu;
        /*Esto me permite evaluar la seleccion y guardar el resultado en una variable para leer
        el c�digo con mayor facilidad*/
        esSeleccionMenuValida = (seleccionMenu >= 1 && seleccionMenu <= MAXIMO_OPCIONES_MENU);

        // Falta hacer las validaciones de entrada de cada caso.

        switch (seleccionMenu)
        {
        case 1:
        {
            string nombrePokemon;
            int idPokemon;
            int codigoTipoPokemon;
            int nivelPokemon;

            bool idValido = false;
            bool codigoTipoValido = false;
            bool idYaExiste = false;
            bool nivelValido = false;
            int cantidadCifrasId;
            int copiaID = 0;

            cout << "\nRegistro de Pok�mon. \n";
            cout << "Ingrese el nombre del Pok�mon: ";
            cin >> nombrePokemon;

            do
            {

                cout << "\nIngrese el ID del Pok�mon: ";
                cin >> idPokemon;

                idValido = evaluarId(idPokemon, CIFRAS_ID, equipoPokemon, MAXIMO_POKEMONES);
                idYaExiste = revisarExistenciaElemento(idPokemon, equipoPokemon, MAXIMO_POKEMONES, CASILLA_ID);

                // Evaluara si la cifra  es v�lida o no.
                if (idValido)
                {
                    cout << "\nERROR: La cantidad de cifras no es valida, deben ser 6" << endl;
                    continue;
                }
                else if (idYaExiste)
                {
                    cout << "\nERROR: Este Id ya existe" << endl;
                }

            } while (!idValido || idYaExiste);

            do
            {
                cout << "\n 0. Fuego"
                     << "\n 1. Agua"
                     << "\n 2. Planta"
                     << "\n 3. El�ctrico"
                     << "\nSeleccione el tipo del Pok�mon: ";

                cin >> codigoTipoPokemon;

                if (codigoTipoPokemon > 3 || codigoTipoPokemon < 0)
                {
                    cout << "\nERROR: Elegiste un tipo no existente." << endl;
                }
                else
                {
                    codigoTipoValido = true;
                }
            } while (!codigoTipoValido);

            do
            {
                cout << "\nIngrese el nivel del Pokemon (1 a 100)";
                cin >> nivelPokemon;

                if (nivelPokemon > NIVEL_MAXIMO || nivelPokemon < 1)
                {
                    cout << "\nERROR: El nivel est� fuera de rango." << endl;
                }
                else
                {
                    nivelValido = true;
                }

            } while (!nivelValido);

            nombresPokemones[cantidadPokemones] = nombrePokemon;
            equipoPokemon[cantidadPokemones][CASILLA_ESTADO] = 1;
            equipoPokemon[cantidadPokemones][CASILLA_ID] = idPokemon;
            equipoPokemon[cantidadPokemones][CASILLA_TIPO] = codigoTipoPokemon;
            equipoPokemon[cantidadPokemones][CASILLA_NIVEL] = nivelPokemon;
            cantidadPokemones++;
        }

        break;

        case 2:

        {
            if (cantidadPokemones == 0)
            {
                cout << "No hay pokemones registrados";
            }
            else
            {
                string nombrePokemon;
                int idPokemon = 0;
                int posicionPokemon = 0;
                int dificultadEntrenamiento = 0;
                bool idValido = false;
                bool idYaExiste = false;
                bool dificultadValida = false;
                int cantidadCifrasId = 0;
                int copiaID = 0;

                cout << "\nEntrenar Pok�mon. \n";

                do
                {

                    cout << "\nIngrese el ID del Pok�mon: ";
                    cin >> idPokemon;
                    copiaID = idPokemon;
                    // Calcula la cantidad de cifras del ID
                    idValido = evaluarId(idPokemon, CIFRAS_ID, equipoPokemon, MAXIMO_POKEMONES);
                    idYaExiste = revisarExistenciaElemento(idPokemon, equipoPokemon, MAXIMO_POKEMONES, CASILLA_ID);

                    // Evaluara si la cifra  es v�lida o no.
                    if (idValido)
                    {
                        cout << "\nERROR: La cantidad de cifras no es valida, deben ser 6" << endl;
                        continue;
                    }
                    else if (!idYaExiste)
                    {
                        cout << "\nERROR: Pok�mon no encontrado" << endl;
                    }

                } while (!(idValido && idYaExiste));

                cout << menuEntrenamiento;
                cin >> seleccionEntrenamiento;

                //!!Tal vez pueda reducir codigo declarando un arreglo arriba con opciones
                switch (seleccionEntrenamiento)
                {
                case 1:
                    cout << "\nHas elegido Combate en gimnasio!\n";
                    break;
                case 2:
                    cout << "\nHas elegido Combate en gimnasio!\n";
                    break;
                case 3:
                    cout << "\nHas elegido Combate en gimnasio!\n";
                    break;
                default:
                    cout << "\nSelección no valida" << endl;
                    break;
                }

                do
                {
                    cout << "\nIngrese dificultad de entrenamiento (1 a 100): ";
                    cin >> dificultadEntrenamiento;

                    if (dificultadEntrenamiento > NIVEL_MAXIMO || dificultadEntrenamiento < 1)
                    {
                        cout << "\nERROR: La dificultad est� fuera de rango." << endl;
                    }
                    else
                    {
                        dificultadValida = true;
                    }

                } while (!dificultadValida);

                if (dificultadEntrenamiento > equipoPokemon[posicionPokemon][CASILLA_NIVEL])
                {
                    cout << "Entrenamiento fallido. " << nombresPokemones[posicionPokemon]
                         << " necesita m�s pr�ctica antes de intentarlo de nuevo." << endl;
                }
                else
                {
                    cout << "Entrenamiento exitoso!. " << nombresPokemones[posicionPokemon]
                         << " ha ganado +10 puntos de poder." << endl;
                    if (equipoPokemon[posicionPokemon][CASILLA_NIVEL] >= 90)
                    {
                        equipoPokemon[posicionPokemon][CASILLA_NIVEL] = 100;
                    }
                    else
                    {
                        equipoPokemon[posicionPokemon][CASILLA_NIVEL] += 10;
                    }
                }
            }
        }

        break;

        case 3:
        {
            if (cantidadPokemones == 0)
            {
                cout << "No hay pokemones registrados";
            }
            else
            {
                string nombrePokemon;
                int idPokemon;
                int codigoTipoPokemon;
                int nivelPokemon;
                cout << "\nMostrar el equipo Pok�mon! \n"
                     << "===========================\n"
                     << "     EQUIPO POKEMON\n"
                     << "===========================\n";
                for (int posicion = 0; posicion < MAXIMO_POKEMONES; posicion++)
                {
                    casillaLlena = equipoPokemon[posicion][CASILLA_ESTADO] == 1;
                    if (casillaLlena)
                    {

                        codigoTipoPokemon = equipoPokemon[posicion][CASILLA_TIPO];

                        mostrarPokemon(nombresPokemones[posicion], equipoPokemon[posicion][CASILLA_TIPO], tipoPokemones[codigoTipoPokemon], equipoPokemon[posicion][CASILLA_NIVEL]);
                    }
                }
            }
        }

        break;

        case 4:

        {
            int nivelMayor = 0;
            int posicionNivelMayor = 0;
            int nivelActual = 0;
            if (cantidadPokemones == 0)
            {
                cout << "No hay pokemones registrados";
            }
            else
            {
                string nombrePokemon;
                int idPokemon;
                int codigoTipoPokemon;
                int nivelPokemon;
                cout << "\nMostrar el Pok�mon m�s fuerte! \n";
                for (int posicionActual = 0; posicionActual < MAXIMO_POKEMONES; posicionActual++)
                {
                    casillaLlena = equipoPokemon[posicionActual][CASILLA_ESTADO] == 1;

                    if (casillaLlena)
                    {

                        nivelActual = equipoPokemon[posicionActual][CASILLA_NIVEL];

                        if (nivelActual > nivelMayor)
                        {
                            nivelMayor = nivelActual;
                            posicionNivelMayor = posicionActual;
                        }
                    }
                }
                codigoTipoPokemon = equipoPokemon[posicionNivelMayor][CASILLA_TIPO];

                mostrarPokemon(nombresPokemones[posicionNivelMayor], equipoPokemon[posicionNivelMayor][CASILLA_TIPO], tipoPokemones[codigoTipoPokemon], equipoPokemon[posicionNivelMayor][CASILLA_NIVEL]);
            }
        }

        break;

        case 5:
            salir = true;
            break;
        default:
            cout << "\nERROR: No existe una opci�n con este n�mero, intenta de nuevo.\n";
            break;
        }
    } while (!salir);

    return 0;
}

bool evaluarId(int idEvaluar, int cifrasRequeridas, int equipoPokemon[][4], int arregloTamanio)
{

    int copiaID = idEvaluar;
    int totalCifrasId = 0;

    while (copiaID > 0)
    {
        copiaID /= 10;
        totalCifrasId++;
    }

    // Evaluara si la cantidad de cifras  es válida o no.
    if (totalCifrasId != cifrasRequeridas)
    {
        return false;
    }
    else
    {
        // Revisa si el ID est� repetido
        return true;
    }
};

bool revisarExistenciaElemento(int idBuscado, int equipoPokemon[][4], int arregloTamanio, int casillaId)
{
    for (int i = 0; i < arregloTamanio; i++)
    {
        if (idBuscado == equipoPokemon[i][casillaId])
        {
            cout << "\nERROR: La cifra est� repetida" << endl;
            return true;
        }
        else if (i == arregloTamanio - 1)
        {
            return false;
        }
    }
}

void mostrarPokemon(string nombrePokemon, int idPokemon, string tipoPokemon, int nivelPokemon)
{
    cout << "Nombre: " << nombrePokemon << endl
         << "ID: " << idPokemon << endl
         << "Tipo: " << tipoPokemon << endl
         << "Nivel: " << nivelPokemon << endl
         << "--------------------------------------------------" << endl;
}