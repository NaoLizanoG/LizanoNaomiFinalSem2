#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>

// estructura para almacenar los datos de los nuevos pacientes
struct paciente
{
    char codigo[50];
    char apellido[50];
    char nombre[50];
    int edad;
    float altura;
    float peso;
    char presion[50];
    float IMC;
};

// funcion para ingresar los datos de nuevos pacientes
void ingresoDatos(char *archivo, struct paciente nuevo)
{
    // comandos que me permiten determinar la fecha y hora actual
    time_t tiempo = time(0);
    struct tm *tlocal = localtime(&tiempo);
    char output[128];

    // se crea y abre el archivo
    FILE *archivoP;
    archivoP = fopen(archivo, "a+");

    // Comandos para cuando hay algun error con el archivo y no se puede abrir
    if (archivoP == NULL)
    {
        printf("No se pudo abrir el archivo.\n");
        return;
    }
    else
    {
        // comando para determianr fecha y horas exactas
        strftime(output, 128, "%d/%m/%y %H:%M:%S", tlocal);

        // se imprimien los valores dados en el archivo
        fprintf(archivoP, "%s;%s;%s;%d;%.2f;%.2f;%s;%.2f;%s   \n", nuevo.codigo, nuevo.apellido, nuevo.nombre, nuevo.edad, nuevo.altura, nuevo.peso, nuevo.presion, nuevo.IMC, output);
    }
    // se cierra el archivo
    fclose(archivoP);
}

// funciona para encontrar los datos mediante el codigo del paciente
int encontrarDatos(char *archivo, char *codigo)
{
    // se almacenará la posicion del puntero para luego mediante la siguiente funcion imprimir esos datos para el usuario
    int posicion = -1;

    char codigoEncontrado[50];
    char nombre[50], apellido[50];
    int edad;
    float altura, peso, IMC;
    char presion[50], timestamp[128];
    FILE *archivoP;
    archivoP = fopen(archivo, "r");

    // Comandos para cuando hay algun error con el archivo y no se puede abrir
    if (archivoP == NULL)
    {
        printf("No se pudo abrir el archivo.\n");
        return -1;
    }
    else
    {
        int num;
        do
        {
            // se usa ftell para determinar la posicion del puntero y se almacena en [posicion]
            posicion = ftell(archivoP);
            // Se usa la variable num para saber que fscanf está leyendo los 9 datos de la linea, si no hay mas datos esa variable será 0 por lo tanto se acabrá el ciclo
            num = fscanf(archivoP, "%[^;];%[^;];%[^;];%d;%f;%f;%[^;];%f;%127[^\n]\n", codigoEncontrado, apellido, nombre, &edad, &altura, &peso, presion, &IMC, timestamp);
            if (strcmp(codigo, codigoEncontrado) == 0)
            {
                break;
            }
            else
            {
                // Si no hay coincidencias se retorna posicion como -1, meidante esto la siguiente funcion avisará al usuario que no hay datos coincidentes
                posicion = -1;
            }
        } while (num == 9);

        // Se cierra el archivo
        fclose(archivoP);
    }
    // Devuelve la posicion del dato coincidente
    return posicion;
}

// funcion para mostrar los datos encontrados en la funcion anterior
void mostrarDatos(char *archivo, int posicion)
{
    // Comando para cuando no se encontraron datos coincidentes
    if (posicion == -1)
    {
        printf("No hay un paciente con ese codigo registrado.\n");
        return;
    }

    char codigoEncontrado[50];
    char nombre[50], apellido[50];
    int edad;
    float altura, peso, IMC;
    char presion[50], timestamp[128];
    FILE *archivoP;
    archivoP = fopen(archivo, "r");

    // Comandos para cuando hay algun error con el archivo y no se puede abrir
    if (archivoP == NULL)
    {
        printf("No se pudo abrir el archivo.\n");
    }
    else
    {
        // fseek ubica el puntero en la fila de los datos coincidentes para mostrarlos en pantalla
        fseek(archivoP, posicion, 0);
        fscanf(archivoP, "%[^;];%[^;];%[^;];%d;%f;%f;%[^;];%f;%127[^\n]\n", codigoEncontrado, apellido, nombre, &edad, &altura, &peso, presion, &IMC, timestamp);
        printf("Los datos encontrados son:\n Codigo: %s\n Apellido:%s\n Nombre:%s\n Edad:%d\n Altura:%.2f\n Peso:%.2f\n Presion:%s\n IMC:%.2f\n", codigoEncontrado, apellido, nombre, edad, altura, peso, presion, IMC);
    }
    fclose(archivoP);
}

// Funcion para reemplazar los datos por nuevos
void reemplazarDatos(char *archivo, int posicion, struct paciente nuevo)
{
    char codigo[20], apellido[50], nombre[50], presion[50], timestamp[128];
    int edad;
    float altura, peso, IMC;

    // Comandos para determinar hora y tiempo actuales
    char output[128];
    time_t tiempo = time(0);
    struct tm *tlocal = localtime(&tiempo);
    FILE *archivoP;
    archivoP = fopen(archivo, "r+");

    // Comandos para cuando hay algun error con el archivo y no se puede abrir
    if (archivoP == NULL)
    {
        printf("No se pudo abrir el archivo.\n");
        return;
    }
    else
    {
        // Comandos para determinar hora y tiempo actuales
        strftime(output, 128, "%d/%m/%y %H:%M:%S", tlocal);
        // Función fseek ubica el puntero en la fila de los datos coincidentes para reemplazarlos
        fseek(archivoP, posicion, 0);
        fscanf(archivoP, "%[^;];%[^;];%[^;];%d;%f;%f;%[^;];%f;%127[^\n]\n", codigo, apellido, nombre, &edad, &altura, &peso, &presion, &IMC, timestamp);
        fseek(archivoP, posicion, 0);
        fprintf(archivoP, "%s;%s;%s;%d;%.2f;%.2f;%s;%.2f;%s", nuevo.codigo, nuevo.apellido, nuevo.nombre, nuevo.edad, nuevo.altura, nuevo.peso, nuevo.presion, nuevo.IMC, output);
    }
    fclose(archivoP);
}

// funcion principal
int main()
{
    char codigo[50];
    int menu, menu1, menu2, posicion, validar;
    struct paciente nuevo;
    char nombreArchivo[40] = "Registros medicos.txt";

    puts("Bienvenido a su sistema de registros medicos\n");

    // Se usa un do-while para que el programa se mantenga funcionando hasta que el usuario decida apgarlo
    do
    {
        puts("\nElija una de las siguientes opciones escribiendo el numero de la opcion correspondiente:\n");
        puts("1. Ingresar nuevo paciente\n");
        puts("2. Encontrar paciente\n");
        puts("3. Salir\n");

        // comandos para validar el ingreso de caracteres
        if (scanf("%d", &menu) != 1)
        {
            menu = 4;
        }

        fflush(stdin);

        // Menu que permitirá al usuario elegir qué hacer
        switch (menu)
        {
            // Opcion para que el usuario ingrese un nuevo registro médico
        case 1:
            do
            {
                puts("\nPor favor, ingrese los datos sin espacios al inicio o al final");
                puts("\nCodigo de paciente");
                scanf("%s", nuevo.codigo);
                puts("\nApellido:");
                scanf("%s", nuevo.apellido);
                fflush(stdin);
                puts("\nNombre:");
                scanf("%s", nuevo.nombre);
                fflush(stdin);

                puts("\nEdad:");

                // Validaciones para evitar que el usuario ingrese datos ilógicos o caracteres
                do
                {
                    validar = scanf("%d", &nuevo.edad);
                    fflush(stdin);
                    if (nuevo.edad > 130 || nuevo.edad < 0 || validar != 1)
                    {
                        puts("Ingrese un numero valido\n");
                    }

                } while (nuevo.edad > 130 || nuevo.edad < 0 || validar != 1);

                puts("\nAltura(m):");
                // Validaciones para evitar que el usuario ingrese datos ilógicos o caracteres
                do
                {
                    validar = scanf("%f", &nuevo.altura);
                    fflush(stdin);
                    if (nuevo.altura > 2.51 || nuevo.altura < 0.30 || validar != 1)
                    {
                        puts("Ingrese un numero valido:\n");
                    }

                } while (nuevo.altura > 2.51 || nuevo.altura < 0.30 || validar != 1);

                puts("\nPeso(kg):");
                // Validaciones para evitar que el usuario ingrese datos ilógicos o caracteres
                do
                {
                    validar = scanf("%f", &nuevo.peso);
                    fflush(stdin);
                    if (nuevo.peso > 440 || nuevo.peso < 2 || validar != 1)
                    {
                        puts("Ingrese un numero valido:\n");
                    }

                } while (nuevo.peso > 440 || nuevo.peso < 2 || validar != 1);

                puts("\nPresion:");
                scanf(" %s", &nuevo.presion);
                fflush(stdin);

                nuevo.IMC = (nuevo.peso / pow(nuevo.altura, 2));
                printf("El indice de masa corporal es %.2f\n", nuevo.IMC);

                // Se ejecuta la función para el ingreso de datos al archivo
                ingresoDatos(nombreArchivo, nuevo);
                puts("\nDatos guardados\n");

                puts("Desea ingresar otro paciente\n1.Si\n2.No");
                scanf("%d", &menu1);
                fflush(stdin);
                // Funcion para validar el ingreso de datos incorrectos
                while (menu1 != 1 && menu1 != 2)
                {
                    puts("Esa no es una opcion valida elija:\n1.Si\n2.No");
                    scanf("%d", &menu1);
                    fflush(stdin);
                }

            } while (menu1 == 1);
            break;

            // opcion que permite al usuario buscar un registro medico ya existente
        case 2:
            do
            {
                printf("Ingrese el codigo del paciente que desea encontrar\n");
                scanf("%s", codigo);
                // Se ejecuta la funcion para encontrar los datos buscados y se almacena la posicion del puntero
                posicion = encontrarDatos(nombreArchivo, codigo);
                // Se ejecuta la funcion para mostrar al usuario los datos que buscaba en base a la posicion almacenada del puntero
                mostrarDatos(nombreArchivo, posicion);
                puts("\n");

                // Segundo menú para permitir al usuario regresar al menú original, buscar otro registro, o cambiar los datos del registro actual
                do
                {
                    puts("Que desea hacer a continuacion:\n");
                    puts("1. Regresar al menu principal");
                    puts("2. Buscar otro paciente");
                    puts("3. Editar datos de paciente actual");
                    if (scanf("%d", &menu2) != 1)
                    {
                        menu2 = 4;
                    }

                    // Validacion de enrtada de datos incorrectos
                    while (menu2 != 1 && menu2 != 2 && menu2 != 3)
                    {
                        puts("Esa no es una opcion valida");
                        scanf("%d", &menu2);
                        fflush(stdin);
                    }

                    if (menu2 == 3)
                    {
                        puts("Ingrese los nuevos datos:\n");
                        puts("\nCodigo de paciente");
                        scanf("%s", nuevo.codigo);
                        puts("\nApellido:");
                        scanf("%s", nuevo.apellido);
                        fflush(stdin);
                        puts("\nNombre:");
                        scanf("%s", nuevo.nombre);
                        fflush(stdin);
                        puts("\nEdad:");

                        do
                        {
                            validar = scanf("%d", &nuevo.edad);
                            fflush(stdin);
                            if (nuevo.edad > 130 || nuevo.edad < 0 || validar != 1)
                            {
                                puts("Ingrese un numero valido\n");
                            }

                        } while (nuevo.edad > 130 || nuevo.edad < 0 || validar != 1);

                        puts("\nAltura(m):");
                        do
                        {
                            validar = scanf("%f", &nuevo.altura);
                            fflush(stdin);
                            if (nuevo.altura > 2.51 || nuevo.altura < 0.30 || validar != 1)
                            {
                                puts("Ingrese un numero valido:\n");
                            }

                        } while (nuevo.altura > 2.51 || nuevo.altura < 0.30 || validar != 1);

                        puts("\nPeso(kg):");
                        do
                        {
                            validar = scanf("%f", &nuevo.peso);
                            fflush(stdin);
                            if (nuevo.peso > 440 || nuevo.peso < 2 || validar != 1)
                            {
                                puts("Ingrese un numero valido:\n");
                            }

                        } while (nuevo.peso > 440 || nuevo.peso < 2 || validar != 1);

                        puts("\nPresion:");
                        scanf(" %s", &nuevo.presion);
                        fflush(stdin);

                        nuevo.IMC = (nuevo.peso / pow(nuevo.altura, 2));
                        printf("El indice de masa corporal es %.2f\n", nuevo.IMC);
                        puts("\nDatos guardados\n");

                        // Se ejecuta la funcion para reemplazar los datos por nuevos ingresados por el usuario
                        reemplazarDatos(nombreArchivo, posicion, nuevo);
                    }

                } while (menu2 == 3);
            } while (menu2 == 2);

            break;
        case 3:
            break;

        // Se ejecuta esta opcion cuando el usuario ingreso un numero que no es parte del menu o ingreso un caracter
        default:
            printf("\nLo siento, esa no es una opcion\n");
            break;
        }

        // Se repite el programa hasta que el usuario decida terminarlo seleccionando la opcion 3
    } while (menu != 3);

    puts("Gracias por usar nuestro servicio\nAdios");
    return 0;
}
