/*
CARLOS EDUARDO BARRIOS BARRÓN
OLIVER ALEXANDER VEGA CASAS
LUIS ANTONIO DIAZ CHAVEZ 
JORGE LUIS ALANIS PRUNEDA 
EFREN SOTO MARTINEZ 
*/

#include <iostream>
#include <cstring>
#include <cctype>
#include <string>
#include <sstream>
using namespace std;

//Lista doblemente enlazada para almacenar los datos de los alumnos
// Metodo de ordenamiento indefinido, dicho ordenamiento se debe de hacer por su matricula

struct Alumno
{
    int matricula;
    char nombre[100];
    int edad;
    float promedio_general;
    char direccion[100];
    int telefono;
    Alumno* siguiente;
    Alumno* anterior;
};

typedef struct Alumno* Nodo_alumno;

// Funciones de validación
bool validarNombre(char nombre[]);
bool validarMatricula(int matricula);
bool validarEdad(int edad);
bool validarTelefono(int telefono);
bool validarSiNo(string respuesta);
int leerEntero();
float leerFloat();

void alta_alumno(Nodo_alumno& head);
void baja_alumno(Nodo_alumno& head, int& contador, Nodo_alumno& stack_head);
bool busqueda_binaria(Nodo_alumno& head, int matricula, int contador, Nodo_alumno& stack_head);
void push(Nodo_alumno& stack_head, Nodo_alumno alumno);
void pop(Nodo_alumno& stack_head);
Nodo_alumno quick_sort(Nodo_alumno head);
void insertar_en_lista(Nodo_alumno& headf, Nodo_alumno nuevo);
void recuperar_alumno(Nodo_alumno& head, Nodo_alumno& stack_head, int&contador);
void imprimir_alumnos(Nodo_alumno& head);
void reportes(Nodo_alumno& head, Nodo_alumno& stack_head, int contador);
void control_inscripciones(Nodo_alumno& head_queue, Nodo_alumno& tail_queue, Nodo_alumno& head);
Nodo_alumno quick_sort_promedios(Nodo_alumno& head);
void encolar(Nodo_alumno& head_queue, Nodo_alumno& tail_queue, Nodo_alumno alumno);
Nodo_alumno desencolar(Nodo_alumno& head_queue, Nodo_alumno& tail_queue);

int main()
{
    int contador = 0;
    int opcion;
    string ans;

    Nodo_alumno head = nullptr;
    Nodo_alumno stack_head = nullptr;
    Nodo_alumno head_queue = nullptr;
    Nodo_alumno tail_queue = nullptr;

    do
    {
        cout << "-----INSTITUCION EDUCATIVA IMAK----- " << endl;
        cout << "1. Alta de alumnos" << endl;
        cout << "2. Baja de alumnos" << endl;
        cout << "3. Recuperar alumnos" << endl;
        cout << "4. Reportes " << endl;
        cout << "5. Control de inscripciones" << endl;
        cout << "6. Salir" << endl;
        cout << "Ingrese una opcion: ";
        opcion = leerEntero();

        switch (opcion)
        {
            case 1:
                cout << "--Alta de alumnos--" << endl;

                do
                {
                    alta_alumno(head);

                    head = quick_sort(head);

                    contador++;

                    cout << "Desea ingresar un nuevo alumno? (si/no): ";
                    cin >> ans;
                    
                    while(!validarSiNo(ans))
                    {
                        cout << "Respuesta invalida. Ingrese 'si' o 'no': ";
                        cin >> ans;
                    }

                } while (ans == "si");

                break;

            case 2:
                baja_alumno(head, contador, stack_head);
                break;

            case 3:
                recuperar_alumno(head, stack_head, contador);
                head = quick_sort(head);
                break;

            case 4:
                reportes(head, stack_head, contador);
                break;

            case 5:
                control_inscripciones(head_queue, tail_queue, head);
                break;

            case 6:
                cout << "Saliendo del programa..." << endl;
                break;

            default:
                imprimir_alumnos(head);
                break;
        }

    } while (opcion != 6);
}

bool validarNombre(char nombre[])
{
    if(strlen(nombre) == 0)
        return false;
    
    for(int i = 0; i < strlen(nombre); i++)
    {
        if(!isalpha(nombre[i]) && nombre[i] != ' ')
            return false;
    }
    return true;
}

bool validarMatricula(int matricula)
{
    if(matricula < 10000000 || matricula > 99999999)
        return false;
    return true;
}

bool validarEdad(int edad)
{
    if(edad < 1 || edad > 199)
        return false;
    return true;
}

bool validarTelefono(int telefono)
{
    if(telefono < 10000000 || telefono > 99999999)
        return false;
    return true;
}

bool validarSiNo(string respuesta)
{
    return (respuesta == "si" || respuesta == "no");
}

int leerEntero()
{
    string input;
    int numero;
    
    while(true)
    {
        cin >> input;
        
        bool esNumero = true;
        for(int i = 0; i < input.length(); i++)
        {
            if(!isdigit(input[i]))
            {
                esNumero = false;
                break;
            }
        }
        
        if(esNumero)
        {
            stringstream ss(input);
            ss >> numero;
            return numero;
        }
        else
        {
            cout << "Error: Debe ingresar solo numeros. Intente nuevamente: ";
        }
    }
}

float leerFloat()
{
    string input;
    float numero;
    int puntos = 0;
    
    while(true)
    {
        cin >> input;
        
        bool esNumero = true;
        puntos = 0;
        
        for(int i = 0; i < input.length(); i++)
        {
            if(input[i] == '.')
            {
                puntos++;
                if(puntos > 1)
                {
                    esNumero = false;
                    break;
                }
            }
            else if(!isdigit(input[i]))
            {
                esNumero = false;
                break;
            }
        }
        
        if(esNumero)
        {
            stringstream ss(input);
            ss >> numero;
            return numero;
        }
        else
        {
            cout << "Error: Debe ingresar un numero valido. Intente nuevamente: ";
        }
    }
}

void alta_alumno(Nodo_alumno& head)
{
    Nodo_alumno nuevo_alumno = new Alumno;
    bool datoValido;
    string input;

    do
    {
        datoValido = true;
        cout << "Ingrese la matricula del alumno (8 digitos): ";
        nuevo_alumno->matricula = leerEntero();
        
        if(!validarMatricula(nuevo_alumno->matricula))
        {
            cout << "Error: La matricula debe tener exactamente 8 digitos" << endl;
            datoValido = false;
        }
        
    } while(!datoValido);

    do
    {
        datoValido = true;
        cout << "Ingrese el nombre del alumno (solo letras y espacios): ";
        cin >> ws;
        cin.getline(nuevo_alumno->nombre, 100);
        
        if(!validarNombre(nuevo_alumno->nombre))
        {
            cout << "Error: El nombre solo puede contener letras y espacios, y no puede estar vacio" << endl;
            datoValido = false;
        }
        
    } while(!datoValido);

    do
    {
        datoValido = true;
        cout << "Ingrese la edad del alumno (1-199): ";
        nuevo_alumno->edad = leerEntero();
        
        if(!validarEdad(nuevo_alumno->edad))
        {
            cout << "Error: La edad debe ser mayor a 1 y menor a 200" << endl;
            datoValido = false;
        }
        
    } while(!datoValido);

    do
    {
        datoValido = true;
        cout << "Ingrese el promedio general del alumno (0-100): ";
        nuevo_alumno->promedio_general = leerFloat();
        
        if(nuevo_alumno->promedio_general < 0 || nuevo_alumno->promedio_general > 100)
        {
            cout << "Error: El promedio debe estar entre 0 y 100" << endl;
            datoValido = false;
        }
        
    } while(!datoValido);

    cout << "Ingrese la direccion del alumno: ";
    cin >> ws;
    cin.getline(nuevo_alumno->direccion, 100);

    do
    {
        datoValido = true;
        cout << "Ingrese el telefono del alumno (8 digitos): ";
        nuevo_alumno->telefono = leerEntero();
        
        if(!validarTelefono(nuevo_alumno->telefono))
        {
            cout << "Error: El telefono debe tener exactamente 8 digitos" << endl;
            datoValido = false;
        }
        
    } while(!datoValido);

    nuevo_alumno->siguiente = nullptr;
    nuevo_alumno->anterior = nullptr;

    if (head == nullptr)
    {
        head = nuevo_alumno;
    }
    else
    {
        Nodo_alumno temp = head;

        while (temp->siguiente != nullptr)
        {
            temp = temp->siguiente;
        }

        temp->siguiente = nuevo_alumno;
        nuevo_alumno->anterior = temp;
    }
}

void baja_alumno(Nodo_alumno& head, int& contador, Nodo_alumno& stack_head)
{
    int opcion;
    string ans;

    do
    {
        cout << "Busqueda de alumno " << endl;
        cout << "1. Buscar por matricula" << endl;
        cout << "2. Buscar por nombre" << endl;

        opcion = leerEntero();

        if (opcion == 1)
        {
            int matricula;

            cout << "Ingrese la matricula del alumno: ";
            matricula = leerEntero();

            if (busqueda_binaria(head, matricula, contador, stack_head))
            {
                cout << "Alumno temporalmente eliminado con exito" << endl;
                contador--;
            }
            else
            {
                cout << "Alumno no encontrado" << endl;
            }
        }

        else if (opcion == 2)
        {
            bool flag = true;

            char nombre[100];

            cout << "Ingrese el nombre del alumno: ";
            cin >> ws;
            cin.getline(nombre, 100);

            Nodo_alumno temp = head;

            while (temp != nullptr)
            {
                if (strcmp(temp->nombre, nombre) == 0)
                {
                    push(stack_head, temp);

                    if (temp == head)
                    {
                        head = temp->siguiente;

                        if (head != nullptr)
                        {
                            head->anterior = nullptr;
                        }
                    }

                    else if (temp->siguiente == nullptr)
                    {
                        temp->anterior->siguiente = nullptr;
                    }

                    else
                    {
                        temp->anterior->siguiente = temp->siguiente;
                        temp->siguiente->anterior = temp->anterior;
                    }

                    cout << "Alumno temporalmente eliminado con exito" << endl;
                	contador--;
                    delete temp;
                    flag = false;

                    break;
                }

                temp = temp->siguiente;
            }

            if (flag)
            {
                cout << "Alumno no encontrado" << endl;
            }
        }
        else
        {
            cout << "Opcion invalida" << endl;
        }

        cout << "Desea eliminar otro alumno? (si/no): ";
        cin >> ans;
        
        while(!validarSiNo(ans))
        {
            cout << "Respuesta invalida. Ingrese 'si' o 'no': ";
            cin >> ans;
        }

    } while (ans == "si");
}

bool busqueda_binaria(Nodo_alumno& head, int matricula, int contador, Nodo_alumno& stack_head)
{
    int inicio = 0;
    int fin = contador - 1;
	
	if(head == nullptr) return false;
	
    while (inicio <= fin)
    {
        int medio = (inicio + fin) / 2;

        Nodo_alumno temp = head;

        for (int i = 0; i < medio; i++)
        {
            temp = temp->siguiente;
        }

        if (temp->matricula == matricula)
        {
            push(stack_head, temp);

            if (temp == head)
            {
                head = temp->siguiente;

                if (head != nullptr)
                {
                    head->anterior = nullptr;
                }
            }

            else if (temp->siguiente == nullptr)
            {
                temp->anterior->siguiente = nullptr;
            }

            else
            {
                temp->anterior->siguiente = temp->siguiente;
                temp->siguiente->anterior = temp->anterior;
            }

            delete temp;

            return true;
        }

        else if (temp->matricula < matricula)
        {
            inicio = medio + 1;
        }

        else
        {
            fin = medio - 1;
        }
    }

    return false;
}

void push(Nodo_alumno& stack_head, Nodo_alumno alumno)
{
    if (stack_head == nullptr)
    {
        Nodo_alumno copia = new Alumno;

        *copia = *alumno;

        copia->anterior = nullptr;
        copia->siguiente = nullptr;

        stack_head = copia;
    }
    else
    {
        Nodo_alumno copia = new Alumno;

        *copia = *alumno;

        copia->anterior = nullptr;
        copia->siguiente = stack_head;

        stack_head = copia;
    }
}

void pop(Nodo_alumno& stack_head)
{
    if (stack_head != nullptr)
    {
        Nodo_alumno temp = stack_head;

        stack_head = stack_head->siguiente;

        delete temp;
    }
    else
    {
        cout << "La pila esta vacia" << endl;
    }
}

Nodo_alumno quick_sort(Nodo_alumno head)
{
    if (head == nullptr || head->siguiente == nullptr)
    {
        return head;
    }

    Nodo_alumno pivote = head;
    Nodo_alumno actual = head->siguiente;

    pivote->siguiente = nullptr;
    pivote->anterior = nullptr;

    Nodo_alumno menores = nullptr;
    Nodo_alumno mayores = nullptr;

    while (actual != nullptr)
    {
        Nodo_alumno siguiente = actual->siguiente;

        actual->siguiente = nullptr;
        actual->anterior = nullptr;

        if (actual->matricula <= pivote->matricula)
        {
            insertar_en_lista(menores, actual);
        }
        else
        {
            insertar_en_lista(mayores, actual);
        }

        actual = siguiente;
    }

    menores = quick_sort(menores);
    mayores = quick_sort(mayores);

    Nodo_alumno resultado;

    if (menores != nullptr)
    {
        resultado = menores;

        Nodo_alumno temp = menores;

        while (temp->siguiente != nullptr)
        {
            temp = temp->siguiente;
        }

        temp->siguiente = pivote;
        pivote->anterior = temp;
    }
    else
    {
        resultado = pivote;
    }

    if (mayores != nullptr)
    {
        pivote->siguiente = mayores;
        mayores->anterior = pivote;
    }

    return resultado;
}

void insertar_en_lista(Nodo_alumno& headf, Nodo_alumno nuevo)
{
    if (headf == nullptr)
    {
        headf = nuevo;
    }
    else
    {
        Nodo_alumno temp = headf;

        while (temp->siguiente != nullptr)
        {
            temp = temp->siguiente;
        }

        temp->siguiente = nuevo;
        nuevo->anterior = temp;
    }
}

void recuperar_alumno(Nodo_alumno& head, Nodo_alumno& stack_head, int& contador)
{
    char ans[3];
    do
    {
        if (stack_head != nullptr)
        {
            Nodo_alumno temp = stack_head;

            stack_head = stack_head->siguiente;

            temp->siguiente = nullptr;
            temp->anterior = nullptr;

            insertar_en_lista(head, temp);
            contador ++;

            cout << "Ultimo alumno recuperado con exito" << endl;
        }
        else
        {
            cout << "No hay alumnos, La pila esta vacia" << endl;
        }
        
        cout << "Desea recuperar al siguiente alumno? (si/no): ";
        cin >> ws;
        cin.getline(ans, 3);
        
        while(strcmp(ans, "si") != 0 && strcmp(ans, "no") != 0)
        {
            cout << "Respuesta invalida. Ingrese 'si' o 'no': ";
            cin.getline(ans, 3);
        }

    } while (strcmp(ans, "si") == 0);
    
}

void imprimir_alumnos(Nodo_alumno& head)
{
    if (head == nullptr)
    {
        cout << "No hay alumnos registrados" << endl;
    }
    else
    {
        Nodo_alumno temp = head;

        while (temp != nullptr)
        {
            cout << "Matricula: " << temp->matricula << endl;
            cout << "Nombre: " << temp->nombre << endl;
            cout << "Edad: " << temp->edad << endl;
            cout << "Promedio General: " << temp->promedio_general << endl;
            cout << "Direccion: " << temp->direccion << endl;
            cout << "Telefono: " << temp->telefono << endl;
            cout << "-----------------------------" << endl;

            temp = temp->siguiente;
        }
    }
}

void reportes(Nodo_alumno& head, Nodo_alumno& stack_head, int contador)
{
    int opcion_reporte,contador_alumno,contador_inactivo;
    int aprobados = 0;
    int reprobados = 0;
    
    do
    {
        cout << "\n----- REPORTES -----" << endl;
        cout << "1. Porcentaje de alumnos aprobados y reprobados" << endl;
        cout << "2. Datos generales de estudiantes activos" << endl;
        cout << "3. Alumnos inactivos (pila de bajas)" << endl;
        cout << "4. Volver al menu principal" << endl;
        cout << "Ingrese una opcion: ";
        opcion_reporte = leerEntero();
        
        switch(opcion_reporte)
        {
            case 1:
            {
                if(head == nullptr)
                
                    cout << "No hay alumnos activos" << endl;
                
                else
                {
                    Nodo_alumno temp = head;
                    
                    while(temp != nullptr)
                    {
                        if(temp->promedio_general >= 70)

                            aprobados++;
                    
                        else
                        
                            reprobados++;
                        
                        temp = temp->siguiente;
                    }
                    
                    
                    cout << "\n----- RESULTADOS -----" << endl;
                    cout << "Total de alumnos activos: " << contador << endl;
                    cout << "Alumnos aprobados: " << aprobados << " (" << (aprobados * 100.0) / contador << "%)" << endl;
                    cout << "Alumnos reprobados: " << reprobados << " (" << (reprobados * 100.0) / contador << "%)" << endl;
                }
                break;
            }
            
            case 2:
            {
                if(head == nullptr)
                
                    cout << "No hay alumnos activos" << endl;
                
                else
                {
                    cout << "\n----- DATOS GENERALES DE ALUMNOS ACTIVOS -----" << endl;
                    Nodo_alumno temp = head;
                    contador_alumno = 1;
                    
                    while(temp != nullptr)
                    {
                        cout << "\nAlumno #" << contador_alumno << endl;
                        cout << "Nombre: " << temp->nombre << endl;
                        cout << "Edad: " << temp->edad << endl;
                        cout << "Direccion: " << temp->direccion << endl;
                        cout << "Telefono: " << temp->telefono << endl;
                        cout << "-----------------------------------" << endl;
                        
                        temp = temp->siguiente;
                        contador_alumno++;
                    }
                }
                break;
            }
            
            case 3:
            {
                if(stack_head == nullptr)
                
                    cout << "No hay alumnos inactivos" << endl;
                
                else
                {
                    cout << "\n----- ALUMNOS INACTIVOS (BAJAS PARCIALES) -----" << endl;
                    Nodo_alumno temp = stack_head;
                    contador_inactivo = 1;
                    
                    while(temp != nullptr)
                    {
                        cout << "\nAlumno #" << contador_inactivo << endl;
                        cout << "Matricula: " << temp->matricula << endl;
                        cout << "Nombre: " << temp->nombre << endl;
                        cout << "-----------------------------------" << endl;
                        
                        temp = temp->siguiente;
                        contador_inactivo++;
                    }
                }
                break;
            }
            
            case 4:
                break;
                
            default:
                cout << "Opcion no valida" << endl;
                break;
        }
        
    } while(opcion_reporte != 4);
}

void control_inscripciones(Nodo_alumno& head_queue, Nodo_alumno& tail_queue, Nodo_alumno& head)
{
    Nodo_alumno head_sorted_prom = head;
    head_sorted_prom = quick_sort_promedios(head_sorted_prom);
    int grupos=0, alumnos=0, i=0, j=0;


    cout << "\n----- CONTROL DE INSCRIPCIONES -----" << endl;
    cout << "Ingrese el numero de grupos disponibles: ";
    grupos = leerEntero();
    cout << "Ingrese el numero maximo de alumnos por grupo: ";
    alumnos = leerEntero();
    int matriz[grupos][alumnos];

    Nodo_alumno temp = head_sorted_prom;
    while (temp != nullptr)
    {
        encolar(head_queue, tail_queue, temp);
        temp = temp->siguiente;
    }

    for(i = 0; i < grupos; i++)
    {
        cout << "\nGrupo #" << i + 1 << endl;
        for(j = 0; j < alumnos; j++)
        {
            Nodo_alumno alumno_inscrito = desencolar(head_queue, tail_queue);
            if(alumno_inscrito != nullptr)
            {
                matriz[i][j] = alumno_inscrito->matricula;
                cout << "Alumno matricula: " << alumno_inscrito->matricula << " - Nombre: " << alumno_inscrito->nombre << "\nAgreado con exito" << endl;
            }
            else
            {
                cout << "No hay mas alumnos para inscribir" << endl;
                break;
            }
        }
    }
}

Nodo_alumno quick_sort_promedios(Nodo_alumno& head)
{
        if (head == nullptr || head->siguiente == nullptr)
        {
            return head;
        }
    
        Nodo_alumno pivote = head;
        Nodo_alumno actual = head->siguiente;
    
        pivote->siguiente = nullptr;
        pivote->anterior = nullptr;
    
        Nodo_alumno menores = nullptr;
        Nodo_alumno mayores = nullptr;
    
        while (actual != nullptr)
        {
            Nodo_alumno siguiente = actual->siguiente;
    
            actual->siguiente = nullptr;
            actual->anterior = nullptr;
    
            if (actual->promedio_general >= pivote->promedio_general)
            {
                insertar_en_lista(menores, actual);
            }
            else if(actual->promedio_general == pivote->promedio_general)
            {
                if(strcmp(actual->nombre, pivote->nombre) < 0)
                {
                    insertar_en_lista(menores, actual);
                }
                else
                {
                    insertar_en_lista(mayores, actual);
                }
            }
            else
            {
                insertar_en_lista(mayores, actual);
            }
    
            actual = siguiente;
        }
    
        menores = quick_sort_promedios(menores);
        mayores = quick_sort_promedios(mayores);
    
        Nodo_alumno resultado;
    
        if (menores != nullptr)
        {
            resultado = menores;
    
            Nodo_alumno temp = menores;
    
            while (temp->siguiente != nullptr)
            {
                temp = temp->siguiente;
            }
    
            temp->siguiente = pivote;
            pivote->anterior = temp;
        }
        else
        {
            resultado = pivote;
        }
    
        if (mayores != nullptr)
        {
            pivote->siguiente = mayores;
            mayores->anterior = pivote;
        }
    
        return resultado;
}

void encolar(Nodo_alumno& head_queue, Nodo_alumno& tail_queue, Nodo_alumno alumno)
{
    Nodo_alumno nuevo_nodo = new Alumno;

    *nuevo_nodo = *alumno;
    nuevo_nodo->siguiente = nullptr;
    nuevo_nodo->anterior = nullptr;

    if (head_queue == nullptr)
    {
        head_queue = nuevo_nodo;
        tail_queue = nuevo_nodo;
    }
    else
    {
        tail_queue->siguiente = nuevo_nodo;
        tail_queue = nuevo_nodo;
    }
}

Nodo_alumno desencolar(Nodo_alumno& head_queue, Nodo_alumno& tail_queue)
{
    if (head_queue != nullptr)
    {
        Nodo_alumno temp = head_queue;
        head_queue = head_queue->siguiente;

        if (head_queue == nullptr)
        {
            tail_queue = nullptr;
        }

        temp->siguiente = nullptr;
        temp->anterior = nullptr;

        return temp;
    }
    else
    {
        cout << "La cola esta vacia" << endl;
        return nullptr;
    }
    
}