/*
    PASSWORD MANAGER
    REALIZADO POR:
        HINARA RAMIREZ
        SOFIA IGLESIAS
    INFORMATICA - 1C 2023
    INGENIERIA BIOMEDICA - UNIVERSIDAD NACIONAL DE SAN MARTIN
    hola
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*ESTADOS MAQUINA MENU OPERACIONES*/
#define OPCIONES                0
#define INGRESAR_DATOS          1
#define MOSTRAR_CONTRASENA      2
#define BUSCAR_CONTRASENA       3
#define MODIFICAR_CONTRASENA    4
#define ELIMINAR_CONTRASENA     5
#define INGRESAR_MASTER         7
#define LEVANTAR_ARCHIVO        8
#define SALIR                   9

#define INGRESADO       1
#define NO_INGRESADO    0
#define ELIMINADO       -1

#define MAXIMO          100
#define TAM             100
#define DOSCINCOCINCO   255

#define ENIE_MIN    164
#define ENIE_MAY    165


/*ESTRUCTURAS*/
typedef struct password
{
    int ingreso;
    int id;
    char keyword[TAM];
    char usuario[TAM];
    char contra[TAM];
    char url[DOSCINCOCINCO];              //QUE TAN LARGO PUEDE SER UN LINK?

}password;


/*PROTOTIPOS DE FUNCIONES*/
void maquinaMenu(void);

void inicializar(void);
void levantarArchivo(void);
void recibirValores(void);

int contarCantidadContras(void);

int buscarContra(void);
void mostrarContra(int i);
void mostrarTodasLasContras(void);
void mostrarContraPorPos(int max);
void modificarContra(int max);
void eliminarContra(int max);

void guardarArchivo(void);


/*VARIABLES*/
int estadoMaquinaMenu = LEVANTAR_ARCHIVO;  //TIENE QUE SER UNA VARIABLE GLOBAL    //INICIA EN UN ESTADO
password manager[MAXIMO];
int posCoincidencia[MAXIMO];

FILE *gestor;

//while((getchar()!='\n')) {}

void main()
{
    while(1){                                                       //ASI LO HAGO LOOP
        maquinaMenu();
    }
    return;
}

void maquinaMenu(){

    /*VARIABLES*/
    int numOperacion;
    int numElementos;



    switch(estadoMaquinaMenu)
        {

            case LEVANTAR_ARCHIVO:
                inicializar();
                printf("Hola!\n");
                printf("Levantando archivo!\n");
                levantarArchivo();
                printf("Archivo levantado!");


                estadoMaquinaMenu = OPCIONES;
            break;

            case OPCIONES:

                printf("\nIntroduzca el numero de la operacion que desea realizar. \n 1 INGRESAR NUEVA CONTRASE%cA \n 2 MOSTRAR CONTRASE%cAS \n 3 BUSCAR CONTRASE%cAS \n 4 MODIFICAR CONTRASE%cAS \n 5 ELIMINAR CONTRASE%cAS \n 7 SALIR \n", ENIE_MAY, ENIE_MAY, ENIE_MAY, ENIE_MAY);
                scanf("%i", &numOperacion);

                if(numOperacion == 1){                                        //VOY A ESTADO INGRESAR_DATOS
                    estadoMaquinaMenu = INGRESAR_DATOS;
                }
                if(numOperacion == 2){                                        //VOY A ESTADO MOSTRAR_CONTRASENA
                    estadoMaquinaMenu = MOSTRAR_CONTRASENA;
                }
                if(numOperacion == 3){                                        //VOY A ESTADO BUSCAR_CONTRASENA
                    estadoMaquinaMenu = BUSCAR_CONTRASENA;
                }
                if(numOperacion == 4){                                        //VOY A ESTADO MODIFICAR_CONTRASENA
                    estadoMaquinaMenu = MODIFICAR_CONTRASENA;
                }
                if(numOperacion == 5){                                        //VOY A ESTADO ELIMINAR_CONTRASENA
                    estadoMaquinaMenu = ELIMINAR_CONTRASENA;
                }
                if(numOperacion == 7){                                        //VOY A ESTADO SALIR
                    estadoMaquinaMenu = SALIR;
                }

            break;

            case INGRESAR_DATOS:

                printf("Ok, vamos a ingresar contrase%cas!\n", ENIE_MIN);                    //ñ: 164    Ñ: 165
                recibirValores();
                //guardarArchivo();

                estadoMaquinaMenu = OPCIONES;

            break;

            case MOSTRAR_CONTRASENA:

                printf("Ok, vamos a mostrar todas las contrase%cas!\n", ENIE_MIN);
                mostrarTodasLasContras();


                estadoMaquinaMenu = OPCIONES;

            break;

            case BUSCAR_CONTRASENA:

                printf("Ok, vamos a buscar contrase%cas!\n", ENIE_MIN);
                int nro = buscarContra(), i;

                if(nro>0){
                    printf("Se encontraron %i coincidencias\n", nro);
                    mostrarContraPorPos(nro);
                }
                else{
                    printf("No se encontraron coincidencias\n");
                }

                estadoMaquinaMenu = OPCIONES;

            break;

            case MODIFICAR_CONTRASENA:

                printf("Ok, vamos a modificar contrase%cas!\n", ENIE_MIN);
                int nro1 = buscarContra();
                if(nro1>0){
                    printf("Se encontraron %i coincidencias\n", nro1);
                    mostrarContraPorPos(nro1);
                    modificarContra(nro1);
                }
                else{
                    printf("No se encontraron coincidencias\n");
                }

                estadoMaquinaMenu = OPCIONES;

            break;

            case ELIMINAR_CONTRASENA:

                printf("Ok, vamos a eliminar contrase%cas!\n", ENIE_MIN);
                int nro2 = buscarContra();
                if(nro2>0){
                    printf("Se encontraron %i coincidencias\n", nro2);
                    mostrarContraPorPos(nro2);
                    eliminarContra(nro2);
                }
                else{
                    printf("No se encontraron coincidencias\n");
                }

                estadoMaquinaMenu = OPCIONES;

            break;

            case INGRESAR_MASTER:

                printf("Ok, vamos a ingresar la contrase%ca maestra!\n", ENIE_MIN);                    //ñ: 164    Ñ: 165
                //recibirValores();
                //guardarArchivo();

                estadoMaquinaMenu = OPCIONES;

            break;

            case SALIR:
                printf("Guardando archivo...\n");
                guardarArchivo();
                printf("Saliendo del programa. Nos vemos!\n");
                exit(0);
            break;

        }
}

void inicializar(){
    int i;

    for(i = 0; i<MAXIMO; i++){
        manager[i].ingreso = NO_INGRESADO;
        strcpy(manager[i].keyword, "\0");
        strcpy(manager[i].usuario, "\0");
        strcpy(manager[i].contra, "\0");
        strcpy(manager[i].url, "\0");
    }

    return;
}

void levantarArchivo(){
    int i;

    //system("cls");
	if (!(gestor = fopen("Gestor.dat", "rb")))
	{
		printf("No se puede abrir el archivo\n");
		return (1);
	}

	for (i = 0; i <= contarCantidadContras(); i++){
        fread(&manager[i], sizeof(manager[0]), 1, gestor);
    }

	while (!feof(gestor))
	{
		//printf("\n%100i%100i%100s%100s%100s%255s", manager[i].ingreso, manager[i].id, manager[i].keyword, manager[i].usuario, manager[i].contra, manager[i].url);
		fread(&manager[i], sizeof(manager[0]), 1, gestor);
	}
	fclose(gestor);
	printf("\n\n");

	return;
}

void guardarArchivo(){
    int i;

    if (!(gestor = fopen("Gestor.dat", "wb"))){
        printf("No se puede abrir el archivo\n");
        return (1);
    }

    for (i = 0; i <= contarCantidadContras(); i++){
        if(manager[i].ingreso == INGRESADO){
            fwrite(&manager[i], sizeof(manager[0]), 1, gestor);
        }
    }
    fclose(gestor);
    printf("\n");

    return;
}

void recibirValores(){
    int i, flag = 1, n;

    for(i = contarCantidadContras(); i<MAXIMO && flag == 1 ; i++){
        printf("Desea agregar una nueva contrase%ca? INGRESE: \n 1 SI \n 2 NO\n", ENIE_MIN);
        scanf("%i",&flag);
        printf("La opcion introducida es %i \n", flag);

        if(flag == 1){
            manager[i].ingreso = INGRESADO;

            printf("Ingrese el keyword (identificador).\n");
            while((getchar()!='\n')) {}
            gets(manager[i].keyword);
            printf("Genial! keyword ingresado con exito.\n");        //SE VIENE A ACA DE UNA
            printf("El keyword ingresado es: %s \n", manager[i].keyword);       //chequeo --> IMPRIME VACIO DESPUES DE :

            printf("Ingrese el usuario.\n");
            gets(manager[i].usuario);
            printf("Genial! Usuario ingresado con exito.\n");        //SE VIENE A ACA DE UNA
            printf("El usuario ingresado es: %s \n", manager[i].usuario);       //chequeo --> IMPRIME VACIO DESPUES DE :

            printf("Ingrese la password.\n");
            gets(manager[i].contra);
            printf("Genial! Password ingresada con exito.\n");        //SE VIENE A ACA DE UNA
            printf("La password ingresada es: %s \n", manager[i].contra);       //chequeo --> IMPRIME VACIO DESPUES DE :

            printf("Ingrese la url.\n");
            gets(manager[i].url);
            printf("Genial! Url ingresada con exito.\n");        //SE VIENE A ACA DE UNA
            printf("La url ingresada es: %s \n", manager[i].url);       //chequeo --> IMPRIME VACIO DESPUES DE :

        }

        if(flag == 2){
            printf("Ok, volviendo al menu! \n");

        }

    }

    return;
}

int contarCantidadContras(){
    int i, cantidad = 0;
    for(i=0; i<TAM; i++){
        if(manager[i].ingreso == INGRESADO){
            cantidad++;
        }
    }
    return cantidad;
}

int buscarContra(){
    int a, b, c = 0, i, flag;
    char keywordIngresado[TAM];

        printf("Ingrese el keyword de la contrase%ca que desea.\n", ENIE_MIN);

        while((getchar()!='\n')) {}
        gets(keywordIngresado);
        printf("Genial! keyword ingresado con exito.\n");        //SE VIENE A ACA DE UNA
        printf("El keyword ingresado es: %s \n", keywordIngresado);       //chequeo --> IMPRIME VACIO DESPUES DE :


        printf("Buscando lo que contenga %s... \n", keywordIngresado);

        for(i=0; i<TAM; i++){
            posCoincidencia[i] = -1;
        }

        for(a = 0; a<TAM; a++)                    //SUMO MIENTRAS HAYA ALGO INGRESADO
        {
            if(manager[a].ingreso == INGRESADO){
                if(strlen(manager[a].keyword) == strlen(keywordIngresado)){ //TIENEN EL MISMO TAMANO
                    if(strcmp(manager[a].keyword, keywordIngresado) == 0){   //SI SON IGUALES
                        //printf("Hay coincidencia\n");
                        flag = 1;
                        posCoincidencia[c] = a;                         //ME GUARDO LA POSICION DE LA COINCIDENCIA
                        c++;
                    }
                    /*if(strcmp(manager[a].keyword, keywordIngresado) != 0){
                        printf("No hay coincidencia\n");
                    }*/
                }
            }
        }



    return c;
}

void mostrarContra(int i){
    if(manager[i].ingreso == INGRESADO){
        printf("keyword: %s \n", manager[i].keyword);       //
        printf("Usuario: %s \n", manager[i].usuario);       //
        printf("Constrase%ca: %s \n", ENIE_MIN, manager[i].contra);       //
        printf("URL: %s \n", manager[i].url);       //
        printf("__________________________________\n");
    }
    return;
}

void mostrarTodasLasContras(){
    int i;

    if(contarCantidadContras() != 0){
        for(i = 0; i<MAXIMO; i++){
            mostrarContra(i);
        }
    }
    if(contarCantidadContras() == 0){
        printf("Todavia no hay contrase%cas guardadas.\nPor favor, ingrese sus contrase%cas.\n", ENIE_MIN, ENIE_MIN);
    }

    return;
}

void mostrarContraPorPos(int max){
    int i, j;

    if(contarCantidadContras() != 0){
        for(i = 0; i < max; i++){
                mostrarContra(posCoincidencia[i]);
        }
    }
    if(contarCantidadContras() == 0){
        printf("Todavia no hay contrase%cas guardadas.\nPor favor, ingrese sus contrase%cas.\n", ENIE_MIN, ENIE_MIN);
    }


    return;
}

void modificarContra(int max){
    int i, num;

    if(contarCantidadContras() != 0 && max>0){

        printf("Ingrese el numero de la contrase%ca que quiere modificar\n", ENIE_MIN);
        scanf("%i", &num);

        printf("Vamos a modificar la Opcion %i:\n", num);

        if(manager[posCoincidencia[num-1]].ingreso == INGRESADO){
            mostrarContra(posCoincidencia[num-1]);

            printf("Ingrese las modificaciones.\n");
            printf("keyword:\n");
            while((getchar()!='\n')) {}
            gets(manager[posCoincidencia[num-1]].keyword);
            printf("Usuario:\n");       //
            gets(manager[posCoincidencia[num-1]].usuario);
            printf("Constrase%ca:\n", ENIE_MIN);       //
            gets(manager[posCoincidencia[num-1]].contra);
            printf("URL:\n");       //
            gets(manager[posCoincidencia[num-1]].url);
            printf("__________________________________\n");

            printf("La modificacion:");
            printf("keyword: %s \n", manager[posCoincidencia[num-1]].keyword);       //
            printf("Usuario: %s \n", manager[posCoincidencia[num-1]].usuario);       //
            printf("Constrase%ca: %s \n", ENIE_MIN, manager[posCoincidencia[num-1]].contra);       //
            printf("URL: %s \n", manager[posCoincidencia[num-1]].url);       //
            printf("__________________________________\n");

        }
    }

    if(contarCantidadContras() == 0){
        printf("Todavia no hay contrase%cas guardadas.\nPor favor, ingrese sus contrase%cas.\n", ENIE_MIN, ENIE_MIN);
    }


    return;
}

void eliminarContra(int max){
    int i, num;

    if(contarCantidadContras() != 0 && max>0){

        printf("Ingrese el numero de la contrase%ca que quiere eliminar\n", ENIE_MIN);
        scanf("%i", &num);

        printf("Vamos a eliminar la Opcion %i:\n", num);

        if(manager[posCoincidencia[num-1]].ingreso == INGRESADO){
            mostrarContra(posCoincidencia[num-1]);

            manager[posCoincidencia[num-1]].ingreso = ELIMINADO;
            printf("La contrase%ca seleccionada sera eliminada al cerrar el programa.\n", ENIE_MIN);
        }
    }

    if(contarCantidadContras() == 0){
        printf("Todavia no hay contrase%cas guardadas.\nPor favor, ingrese sus contrase%cas.\n", ENIE_MIN, ENIE_MIN);
    }


    return;
}

