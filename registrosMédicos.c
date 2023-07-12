#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

struct paciente
{
    char codigo[50];
    char apellido[50];
    char nombre[50];
    int edad;
    float altura;
    float peso;
    float presion;
};

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
        fprintf(archivoP, "%s;%s;%s;%d;%.2f;%.2f;%.2f;%s\n", nuevo.codigo, nuevo.apellido, nuevo.nombre, nuevo.edad, nuevo.altura, nuevo.peso, nuevo.presion, output);
    }
    fclose(archivoP);
}

int encontrarDatos(char *archivo, char *codigo)
{
    int posicion = -1;
    char codigoEncontrado[50];
    char nombre[50], apellido[50];
    int edad;
    float altura, peso, presion;
    char timestamp[128];
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
            (num = fscanf(archivoP, "%[^;];%[^;];%[^;];%d;%f;%f;%f;%127[^\n]\n", codigoEncontrado, apellido, nombre, &edad, &altura, &peso, &presion, timestamp));
            if (strcmp(codigo, codigoEncontrado) == 0)
            {
                break;
            }
            else
            {
                posicion = -1;
            }
        } while (num == 8);

        fclose(archivoP);
    }
    return posicion;
}

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
    float altura, peso, presion;
    char timestamp[128];
    FILE *archivoP;
    archivoP = fopen(archivo, "r");
    if (archivoP == NULL)
    {
        printf("No se pudo abrir el archivo.\n");
    }
    else
    {
        fseek(archivoP, posicion, 0);
        fscanf(archivoP, "%[^;];%[^;];%[^;];%d;%f;%f;%f;%127[^\n]\n", codigoEncontrado, apellido, nombre, &edad, &altura, &peso, &presion, timestamp);
        printf("Los datos encontrados son:\n %s;%s;%s;%d;%.2f;%.2f;%.2f\n", codigoEncontrado, apellido, nombre, edad, altura, peso, presion);
    }
    fclose(archivoP);
}

int main()
{
    char codigo[50];
    int menu, menu1, posicion;
    struct paciente nuevo;
    char nombreArchivo[40] = "Registros medicos.txt";

    puts("Bienvenido a su sistema de registros medicos\n");

    do
    {
        puts("\nElija una de las siguientes opciones:\n");
        puts("1. Ingresar nuevo paciente\n");
        puts("2. Encontrar paciente\n");
        puts("3. Salir\n");
        scanf("%d", &menu);
        fflush(stdin);

        switch (menu)
        {
        case 1:
            do
            {
                puts("\nCodigo de paciente");
                scanf("%s", nuevo.codigo);
                puts("\nApellido:");
                scanf("%s", nuevo.apellido);
                fflush(stdin);
                puts("\nNombre:");
                scanf("%s", nuevo.nombre);
                fflush(stdin);
                puts("\nEdad:");
                scanf("%d", &nuevo.edad);
                fflush(stdin);
                puts("\nAltura:");
                scanf("%f", &nuevo.altura);
                fflush(stdin);
                puts("\nPeso:");
                scanf("%f", &nuevo.peso);
                fflush(stdin);
                puts("\nPresion:");
                scanf(" %f", &nuevo.presion);
                fflush(stdin);
                puts("\nDatos guardados\n");
                ingresoDatos(nombreArchivo, nuevo);

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
            printf("Ingrese el codigo del paciente que desea encontrar\n");
            scanf("%s", codigo);
            posicion = encontrarDatos(nombreArchivo, codigo);
            mostrarDatos(nombreArchivo, posicion);
            break;
        case 3:
            /* code */
            break;
        default:
            printf("Lo siento, esa no es una opcion\n");
            break;
        }

    } while (menu != 3);

    puts("Gracias por usar nuestro servicio\nAdios");
    return 0;
}
