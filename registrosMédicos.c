#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>

// estructura para almacenar los datos de los pacientes
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
    time_t tiempo = time(0);
    struct tm *tlocal = localtime(&tiempo);
    char output[128];
    FILE *archivoP;
    archivoP = fopen(archivo, "a+");
    if (archivoP == NULL)
    {
        printf("No se pudo abrir el archivo.\n");
        return;
    }
    else
    {
        strftime(output, 128, "%d/%m/%y %H:%M:%S", tlocal);
        fprintf(archivoP, "%s;%s;%s;%d;%.2f;%.2f;%s;%.2f;%s   \n", nuevo.codigo, nuevo.apellido, nuevo.nombre, nuevo.edad, nuevo.altura, nuevo.peso, nuevo.presion, nuevo.IMC, output);
    }
    fclose(archivoP);
}

// funciona para encontrar los datos mediante el codigo del paciente
int encontrarDatos(char *archivo, char *codigo)
{
    int posicion = -1;
    char codigoEncontrado[50];
    char nombre[50], apellido[50];
    int edad;
    float altura, peso, IMC;
    char presion[50], timestamp[128];
    FILE *archivoP;
    archivoP = fopen(archivo, "r");
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
            posicion = ftell(archivoP);
            num = fscanf(archivoP, "%[^;];%[^;];%[^;];%d;%f;%f;%[^;];%f;%127[^\n]\n", codigoEncontrado, apellido, nombre, &edad, &altura, &peso, presion, &IMC, timestamp);
            if (strcmp(codigo, codigoEncontrado) == 0)
            {
                break;
            }
            else
            {
                posicion = -1;
            }
        } while (num == 9);

        fclose(archivoP);
    }
    return posicion;
}

// funcion para mostrar los datos encontrados en la funcion anterior
void mostrarDatos(char *archivo, int posicion)
{
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
    if (archivoP == NULL)
    {
        printf("No se pudo abrir el archivo.\n");
    }
    else
    {
        fseek(archivoP, posicion, 0);
        fscanf(archivoP, "%[^;];%[^;];%[^;];%d;%f;%f;%[^;];%f;%127[^\n]\n", codigoEncontrado, apellido, nombre, &edad, &altura, &peso, presion, &IMC, timestamp);
        printf("Los datos encontrados son:\n %s;%s;%s;%d;%.2f;%.2f;%s;%.2f\n", codigoEncontrado, apellido, nombre, edad, altura, peso, presion, IMC);
    }
    fclose(archivoP);
}

void reemplazarDatos(char *archivo, int posicion, struct paciente nuevo)
{
    char codigo[20], apellido[50], nombre[50], presion[50], timestamp[128];
    int edad;
    float altura, peso, IMC;
    char output[128];
    time_t tiempo = time(0);
    struct tm *tlocal = localtime(&tiempo);
    FILE *archivoP;
    archivoP = fopen(archivo, "r+");
    if (archivoP == NULL)
    {
        printf("No se pudo abrir el archivo.\n");
        return;
    }
    else
    {
        strftime(output, 128, "%d/%m/%y %H:%M:%S", tlocal);
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

    do
    {
        puts("\nElija una de las siguientes opciones escribiendo el numero de la opcion correspondiente:\n");
        puts("1. Ingresar nuevo paciente\n");
        puts("2. Encontrar paciente\n");
        puts("3. Salir\n");
        if (scanf("%d", &menu) != 1)
        {
            menu = 4;
        }

        fflush(stdin);

        switch (menu)
        {
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
                ingresoDatos(nombreArchivo, nuevo);
                puts("\nDatos guardados\n");

                puts("Desea ingresar otro paciente\n1.Si\n2.No");
                scanf("%d", &menu1);
                fflush(stdin);
                while (menu1 != 1 && menu1 != 2)
                {
                    puts("Esa no es una opcion valida elija:\n1.Si\n2.No");
                    scanf("%d", &menu1);
                    fflush(stdin);
                }

            } while (menu1 == 1);
            break;
        case 2:
            do
            {
                printf("Ingrese el codigo del paciente que desea encontrar\n");
                scanf("%s", codigo);
                posicion = encontrarDatos(nombreArchivo, codigo);
                mostrarDatos(nombreArchivo, posicion);
                puts("\n");
                do
                {
                    puts("Que desea hacer a continuacion:\n");
                    puts("1. Regresar al menu principal");
                    puts("2. Buscar otro paciente");
                    puts("3. Editar datos de paciente");
                    if (scanf("%d", &menu2)!= 1)
                    {
                        menu2 = 4;
                    }

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

                        reemplazarDatos(nombreArchivo, posicion, nuevo);
                    }

                } while (menu2 == 3);
            } while (menu2 == 2);

            break;
        case 3:
            break;
        default:
            printf("\nLo siento, esa no es una opcion\n");
            break;
        }

    } while (menu != 3);

    puts("Gracias por usar nuestro servicio\nAdios");
    return 0;
}
