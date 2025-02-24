#include <iostream>
#include <limits>

using namespace std;

// Prototipo de funciones.
int buscarId(int[][4]);
void ejecutarEntrenamiento(int[][4], string[], int, int);
int escribirId(int[][4]);
void entrenarPokemon(int[][4], string[], string, int);
bool evaluarId(int, int, int[][4], int);
void insertarPokemon(string[], int[][4], int, string, int, int, int);
void mostrarEquipoPokemon(int[][4], string[], string[], int &);
void mostrarPokemon(string, int, string, int);
void mostrarPokemonMasFuerte(int[][4], string[], string[], int &);
void registrarPokemon(int[][4], string[], int &);
void seleccionarTipoEntrenamiento(string);
int seleccionarTipoPokemon();
int solicitarDificultadEntrenamiento();
bool revisarExistenciaElemento(int, int[][4], int, int);

// Constantes
const int CASILLA_ESTADO = 0;
const int CASILLA_ID = 1;
const int CASILLA_NIVEL = 3;
const int CASILLA_TIPO = 2;
const int CIFRAS_ID = 6;
const int MAXIMO_OPCIONES_MENU = 5;
const int MAXIMO_POKEMONES = 25;
const int NIVEL_MAXIMO = 100;

int main()
{
    setlocale(LC_ALL, "");

    int cantidadPokemones = 0;
    int equipoPokemon[MAXIMO_POKEMONES][4];
    int seleccionMenu = 0;
    bool salir = false;

    // Guardo los menus en strings antes de mostrarlos en pantalla para facilitar modificacion
    string menuEntrenamiento = "\nIngrese el tipo de entrenamiento que quiere realizar:\n"
                               "1. Combate en gimnasio.\n"
                               "2. Batalla con otro entrenador.\n"
                               "3. Práctica de habilidades.\n";
    string menuInicio = "\n\n************************************\n"
                        "Sistema de entrenamiento Pokémon.\n"
                        "1. Registrar un Pokémon.\n"
                        "2. Entrenar un Pokémon.\n"
                        "3. Mostrar el equipo Pokémon.\n"
                        "4. Mostrar el Pokémon más fuerte\n"
                        "5. Salir del Programa.\n"
                        "Seleccione una opcion: ";

    string nombresPokemones[MAXIMO_POKEMONES];
    string tipoPokemones[4] = {"fuego", "agua", "planta", "eléctrico"};

    do
    {
        cout << menuInicio;
        cin >> seleccionMenu;

        if (!cin.good())
        {
            cout << "Sólo se permite el ingreso de números" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        else
        {
            switch (seleccionMenu)
            {
            case 1:
                registrarPokemon(equipoPokemon, nombresPokemones, cantidadPokemones);
                cout << "Presione Enter para continuar...";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cin.get();
                break;

            case 2:
                entrenarPokemon(equipoPokemon, nombresPokemones, menuEntrenamiento, cantidadPokemones);
                cout << "Presione Enter para continuar...";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cin.get();
                break;

            case 3:
                mostrarEquipoPokemon(equipoPokemon, nombresPokemones, tipoPokemones, cantidadPokemones);
                cout << "Presione Enter para continuar...";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cin.get();
                break;

            case 4:
                mostrarPokemonMasFuerte(equipoPokemon, nombresPokemones, tipoPokemones, cantidadPokemones);
                cout << "Presione Enter para continuar...";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cin.get();
                break;

            case 5:
                salir = true;
                break;
            default:
                cout << "\nERROR: No existe una opción con este número, intenta de nuevo.\n";
                cout << "Presione Enter para continuar...";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cin.get();
                break;
            }
        }

    } while (!salir);

    return 0;
}

int buscarId(int equipoPokemon[][4])
{
    int idPokemon = 0;
    bool idValido = false;
    bool idYaExiste = false;

    do
    {
        cout << "\nIngrese el ID del Pokémon: ";
        cin >> idPokemon;

        if (!cin.good())
        {
            cout << "Sólo se permite el ingreso de números" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        else
        {
            idValido = evaluarId(idPokemon, CIFRAS_ID, equipoPokemon, MAXIMO_POKEMONES);
            idYaExiste = revisarExistenciaElemento(idPokemon, equipoPokemon, MAXIMO_POKEMONES, CASILLA_ID);

            if (!idValido)
            {
                cout << "\nERROR: La cantidad de cifras no es valida, deben ser 6" << endl;
            }
            else if (!idYaExiste)
            {
                cout << "\nERROR: Pokémon no encontrado" << endl;
            }
        }

    } while (!(idValido && idYaExiste));
    return idPokemon;
}

void ejecutarEntrenamiento(int equipoPokemon[][4], string nombresPokemones[], int dificultadEntrenamiento, int posicionPokemon)
{
    if (dificultadEntrenamiento > equipoPokemon[posicionPokemon][CASILLA_NIVEL])
    {
        cout << "Entrenamiento fallido. " << nombresPokemones[posicionPokemon]
             << " necesita más práctica antes de intentarlo de nuevo." << endl;
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

void entrenarPokemon(int equipoPokemon[][4], string nombresPokemones[], string menuEntrenamiento, int cantidadPokemones)
{

    if (cantidadPokemones == 0)
    {
        cout << "No hay pokemones registrados";
    }
    else
    {
        string nombrePokemon;
        int dificultadEntrenamiento = 0;
        int idPokemon = 0;
        int posicionPokemon = 0;

        cout << "\nEntrenar Pokémon. \n";

        idPokemon = buscarId(equipoPokemon);

        seleccionarTipoEntrenamiento(menuEntrenamiento);

        dificultadEntrenamiento = solicitarDificultadEntrenamiento();
        for (int i; i < cantidadPokemones; i++)
        {
            if (idPokemon == equipoPokemon[i][CASILLA_ID])
            {
                posicionPokemon = i;
            }
        }

        ejecutarEntrenamiento(equipoPokemon, nombresPokemones, dificultadEntrenamiento, posicionPokemon);
    }
}

int escribirId(int equipoPokemon[][4])
{
    int idPokemon = 0;
    bool idValido = false;
    bool idYaExiste = false;
    do
    {

        cout << "\nIngrese el ID del Pokémon: ";
        cin >> idPokemon;

        if (!cin.good())
        {
            cout << "Sólo se permite el ingreso de números" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        else
        { // Evaluara si la cifra  es válida o no.
            idValido = evaluarId(idPokemon, CIFRAS_ID, equipoPokemon, MAXIMO_POKEMONES);
            idYaExiste = revisarExistenciaElemento(idPokemon, equipoPokemon, MAXIMO_POKEMONES, CASILLA_ID);
            if (!idValido)
            {
                cout << "\nERROR: La cantidad de cifras no es valida, deben ser 6" << endl;
            }
            else if (idYaExiste)
            {
                cout << "\nERROR: Este Id ya existe" << endl;
            }
        }
    } while (!idValido || idYaExiste);

    return idPokemon;
}
// Calcula la cantidad de cifras
bool evaluarId(int idEvaluar, int cifrasRequeridas, int equipoPokemon[][4], int arregloTamanio)
{
    int copiaID = idEvaluar;
    int totalCifrasId = 0;

    while (copiaID > 0)
    {
        copiaID /= 10;
        totalCifrasId++;
    }

    if (totalCifrasId != cifrasRequeridas)
    {
        return false;
    }
    return true;
};

int ingresarNivelPokemon()
{
    int nivelPokemon = 0;
    bool nivelValido = false;
    do
    {
        cout << "\nIngrese el nivel del Pokemon (1 a 100): ";
        cin >> nivelPokemon;

        if (!cin.good())
        {
            cout << "Sólo se permite el ingreso de números" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        else
        {
            if (nivelPokemon > NIVEL_MAXIMO || nivelPokemon < 1)
            {
                cout << "\nERROR: El nivel está fuera de rango." << endl;
            }
            else
            {
                nivelValido = true;
            }
        }

    } while (!nivelValido);
    return nivelPokemon;
}

void insertarPokemon(string nombresPokemones[], int equipoPokemon[][4], int cantidadPokemones, string nombrePokemon, int idPokemon, int codigoTipoPokemon, int nivelPokemon)
{
    nombresPokemones[cantidadPokemones] = nombrePokemon;
    equipoPokemon[cantidadPokemones][CASILLA_ESTADO] = 1;
    equipoPokemon[cantidadPokemones][CASILLA_ID] = idPokemon;
    equipoPokemon[cantidadPokemones][CASILLA_TIPO] = codigoTipoPokemon;
    equipoPokemon[cantidadPokemones][CASILLA_NIVEL] = nivelPokemon;
}

void mostrarEquipoPokemon(int equipoPokemon[][4], string nombresPokemones[], string tipoPokemones[], int &cantidadPokemones)
{
    bool casillaLlena = false;
    if (cantidadPokemones == 0)
    {
        cout << "No hay pokemones registrados";
    }
    else
    {
        string nombrePokemon;
        int codigoTipoPokemon;
        cout << "\nMostrar el equipo Pokémon! \n"
             << "===========================\n"
             << "     EQUIPO POKEMON\n"
             << "===========================\n";
        for (int posicion = 0; posicion < cantidadPokemones; posicion++)
        {
            casillaLlena = equipoPokemon[posicion][CASILLA_ESTADO] == 1;
            if (casillaLlena)
            {
                codigoTipoPokemon = equipoPokemon[posicion][CASILLA_TIPO];
                mostrarPokemon(nombresPokemones[posicion], equipoPokemon[posicion][CASILLA_ID], tipoPokemones[codigoTipoPokemon], equipoPokemon[posicion][CASILLA_NIVEL]);
            }
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

void mostrarPokemonMasFuerte(int equipoPokemon[][4], string nombresPokemones[], string tipoPokemones[], int &cantidadPokemones)
{
    int nivelMayor = 0;
    int posicionNivelMayor = 0;
    int nivelActual = 0;
    bool casillaLlena = false;

    if (cantidadPokemones == 0)
    {
        cout << "No hay pokemones registrados";
    }
    else
    {
        string nombrePokemon;
        int codigoTipoPokemon;
        cout << "\nMostrar el Pokémon más fuerte! \n";
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

        mostrarPokemon(nombresPokemones[posicionNivelMayor], equipoPokemon[posicionNivelMayor][CASILLA_ID], tipoPokemones[codigoTipoPokemon], equipoPokemon[posicionNivelMayor][CASILLA_NIVEL]);
    }
}

bool revisarExistenciaElemento(int idBuscado, int equipoPokemon[][4], int arregloTamanio, int casillaId)
{
    for (int i = 0; i < arregloTamanio; i++)
    {
        if (idBuscado == equipoPokemon[i][casillaId])
        {
            return true;
        }
        else if (i == arregloTamanio - 1)
        {
            return false;
        }
    }
    return false;
}

void registrarPokemon(int equipoPokemon[][4], string nombresPokemones[], int &cantidadPokemones)
{
    string nombrePokemon;
    int idPokemon;
    int codigoTipoPokemon;
    int nivelPokemon;

    cout << "\nRegistro de Pokémon. \n";
    cout << "Ingrese el nombre del Pokémon: ";
    cin >> nombrePokemon;

    idPokemon = escribirId(equipoPokemon);
    codigoTipoPokemon = seleccionarTipoPokemon();
    nivelPokemon = ingresarNivelPokemon();

    insertarPokemon(nombresPokemones, equipoPokemon, cantidadPokemones, nombrePokemon,
                    idPokemon, codigoTipoPokemon, nivelPokemon);
    cantidadPokemones++;
}

void seleccionarTipoEntrenamiento(string menuEntrenamiento)
{
    int seleccionEntrenamiento;

    cout << menuEntrenamiento;
    cin >> seleccionEntrenamiento;

    if (!cin.good())
    {
        cout << "Sólo se permite el ingreso de números" << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    else
    {
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
    }
}

int seleccionarTipoPokemon()
{
    int codigoTipoPokemon = 0;
    bool codigoTipoValido = false;
    do
    {
        cout << "\n 0. Fuego"
             << "\n 1. Agua"
             << "\n 2. Planta"
             << "\n 3. Eléctrico"
             << "\nSeleccione el tipo del Pokémon: ";

        cin >> codigoTipoPokemon;

        if (!cin.good())
        {
            cout << "Sólo se permite el ingreso de números" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        else
        {
            if (codigoTipoPokemon > 3 || codigoTipoPokemon < 0)
            {
                cout << "\nERROR: Elegiste un tipo no existente." << endl;
            }
            else
            {
                codigoTipoValido = true;
            }
        }

    } while (!codigoTipoValido);

    return codigoTipoPokemon;
}

int solicitarDificultadEntrenamiento()
{
    int dificultadEntrenamiento = 0;
    bool dificultadValida = false;

    do
    {
        cout << "\nIngrese dificultad de entrenamiento (1 a 100): ";
        cin >> dificultadEntrenamiento;

        if (!cin.good())
        {
            cout << "Sólo se permite el ingreso de números" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        else
        {
            if (dificultadEntrenamiento > NIVEL_MAXIMO || dificultadEntrenamiento < 1)
            {
                cout << "\nERROR: La dificultad está fuera de rango." << endl;
            }
            else
            {
                dificultadValida = true;
            }
        }

    } while (!dificultadValida);

    return dificultadEntrenamiento;
}
