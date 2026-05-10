
#include <iostream>
using namespace std;

//Lista doblemente enlazada para almacenar los datos de los alumnos
// Metodo de ordenamiento indefinido, dicho ordenamiento se debe de hacer por su matricula

struct Alumno
{
    int matricula;
    string nombre;
    int edad;
    float promedio_general;
    string direccion;
    int telefono;
    Alumno* siguiente;
    Alumno* anterior;
};

typedef struct Alumno* Nodo_alumno;

void alta_alumno(Nodo_alumno& head);
void baja_alumno(Nodo_alumno& head, int contador, Nodo_alumno& stack_head);
bool busqueda_binaria(Nodo_alumno& head, int matricula, int contador, Nodo_alumno& stack_head);
void push(Nodo_alumno& stack_head, Nodo_alumno alumno);
void pop(Nodo_alumno& stack_head);




main()
{
    int contador = 0;
    int opcion; 
    Nodo_alumno head = nullptr;
    Nodo_alumno stack_head = nullptr;


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
        cin >> opcion;

        switch (opcion)
        {
            case 1:
                cout << "--Alta de alumnos--" << endl;
                string ans;
                do
                {
                    alta_alumno(head);
                    //aqui iría el metodo de ordenamiento para ordenar a los alumnos cada que se ingrese uno nuevo
                    contador ++;
                    cout << "Desea ingresar un nuevo alumno? (si/no): ";
                    cin >> ans;
                    
                }while (ans == "si");
                
                break;

            case 2:
                baja_alumno(head, contador, stack_head);
                break;
            
            case 3:
                
                break;

            case 4: 
                
                break;

            case 5:
                
                break;

            case 6:
                cout << "Saliendo del programa..." << endl;
                break;
            
            default:
                break;
        }
    }while (opcion != 6);
   
    

}


void alta_alumno(Nodo_alumno& head)
{

    Nodo_alumno nuevo_alumno = new Alumno;
    cout << "Ingrese la matricula del alumno: ";
    cin >> nuevo_alumno->matricula;
    cout << "Ingrese el nombre del alumno: ";
    cin >> nuevo_alumno->nombre;
    cout << "Ingrese la edad del alumno: ";
    cin >> nuevo_alumno->edad;
    cout << "Ingrese el promedio general del alumno: ";
    cin >> nuevo_alumno->promedio_general;
    cout << "Ingrese la direccion del alumno: ";
    cin >> nuevo_alumno->direccion;
    cout << "Ingrese el telefono del alumno: ";
    cin >> nuevo_alumno->telefono;

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

void baja_alumno(Nodo_alumno& head, int contador, Nodo_alumno& stack_head)
{
    int opcion;
    string ans;
    do
    {

        cout << "Busqueda de alumno "<< endl;
        cout << "1. Buscar por matricula" << endl;
        cout << "2. Buscar por nombre" << endl;
        cin >> opcion;
        

        if (opcion == 1)
        {
            int matricula;
            cout << "Ingrese la matricula del alumno: ";
            cin >> matricula;
            if (busqueda_binaria(head, matricula, contador, stack_head))
            {

                cout << "Alumno temporalmente eliminado con exito" << endl;
            }
            else
            {
                cout << "Alumno no encontrado" << endl;
            }
        }

        else if (opcion == 2)
        {
            bool flag = true;
            string nombre;
            cout << "Ingrese el nombre del alumno: ";
            cin >> nombre;

            Nodo_alumno temp = head;
            while (temp != nullptr)
            {
                if (temp->nombre == nombre)
                {
                    push(stack_head, temp);
                    cout << "Alumno temporalmente eliminado con exito" << endl;
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
    
        cout << "Desea eliminar otro alumno? (si/no): ";
        cin >> ans;

    } while (ans == "si");
    
}

bool busqueda_binaria(Nodo_alumno& head, int matricula, int contador, Nodo_alumno& stack_head)
{
    int inicio = 0;
    int fin = contador - 1;

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