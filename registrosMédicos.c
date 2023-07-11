#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct paciente
{
    char apellido[50];
    char nombre[50];
    int edad;
    float altura;
    float peso;
    float presion;
};

void ingresoDatos(const char *archivo, struct paciente nuevo)
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
        strftime(output,128,"%d/%m/%y %H:%M:%S",tlocal);
        fprintf(archivoP, "%s;%s;%d;%.2f;%.2f;%.2f;%s\n", nuevo.apellido, nuevo.nombre, nuevo.edad, nuevo.altura, nuevo.peso, nuevo.presion, output);
        
    }

    fclose(archivoP);
}

int main()
{
    int menu, menu1;
    struct paciente nuevo;
    char nombreArchivo[40] = "Registros medicos.txt";

    puts("Bienvenido a su sistema de registros medicos\n");

    do
    {
        puts("Elija una de las siguientes opciones:\n");
        puts("1. Ingresar nuevo paciente\n");
        puts("2. Encontrar paciente\n");
        puts("3. Salir\n");
        scanf("%d", &menu);

        switch (menu)
        {
        case 1:
            do
            {
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
                while (menu1 != 1 && menu1 != 2)
                {
                    puts("Esa no es una opcion valida elija:\n1.Si\n2.No");
                    scanf("%d", &menu1);
                }

            } while (menu1 == 1);
            break;
        case 2:
            /* code */
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
