/*
    PASSWORD MANAGER
    REALIZADO POR:
        HINARA RAMIREZ
        SOFIA IGLESIAS
    INFORMATICA - 1C 2023
    INGENIERIA BIOMEDICA - UNIVERSIDAD NACIONAL DE SAN MARTIN
*/

#include <stdio.h>
#include <string.h>

/*ESTADOS MAQUINA MENU OPERACIONES*/
#define OPCIONES                    0
#define INGRESAR_DATOS              1
#define MOSTRAR_CONTRASENA          2
#define BUSCAR_CONTRASENA           3
#define MODIFICAR_CONTRASENA        4
#define ELIMINAR_CONTRASENA         5
#define LEVANTAR_ARCHIVO_USUARIOS   6
#define INGRESAR_PERFIL             7
#define SALIR                       10

/*ESTADOS DE INGRESO*/
#define INGRESADO       1
#define NO_INGRESADO    0               //NO SE GUARDA EN ARCHIVO
#define ELIMINADO       -1              //NO SE GUARDA EN ARCHIVO

/*DEFINES DE TAMANOS DE VECTORES*/
#define MAXIMO          100
#define TAM             100             //VECTORES INTERNOS DE ESTRUCTURA
#define DOSCINCOCINCO   255             //VECTORES INTERNOS DE ESTRUCTURA

/*ASCII DE Ņ*/
#define ENIE_MIN    164                 //MINUSCULA
#define ENIE_MAY    165                 //MAYUSCULA


/*ESTRUCTURAS*/
typedef struct password
{
    int ingreso;
    char keyword[TAM];
    char usuario[TAM];
    char contra[TAM];
    char url[DOSCINCOCINCO];              //QUE TAN LARGO PUEDE SER UN LINK?

}password;

typedef struct user
{
    int ingreso;
    char usuario[TAM];
    char contra[TAM];
    char nombreArchivo[TAM];

}user;


/*PROTOTIPOS DE FUNCIONES*/
/*FUNCIONES GENERALES*/
//void maquinaMenu(void);                 //FUNCION GENERAL DE LA MAQUINA DE ESTADOS
void inicializar(char usu[], char con[], password manager[], user perfil[]);                 //INICIALIZA LO QUE TIENE ADENTRO LA ESTRUCTURA --> TODO EN NO_INGRESADO O \0 (VACIO)
void resumen(password manager[]);
void guardarArchivo(int posUsuario, user perfil[], password manager[]);              //ESCRIBE EL ARCHIVO EN EL QUE SE GUARDAN LAS CONTRASEŅAS (MISMO ARCHIVO DE DONDE LEVANTA LOS DATOS)

/*FUNCIONES DE USUARIOS*/
void ingresoPerfil(char usu[], char con[]);
void levantarArchivoPerfiles(user perfil[]);
int buscarPerfil(char *usu, char *con, int posPerfil, user perfil[]);
int crearNuevoPerfil(char *usu, char *con, int posPerfil, user perfil[]);
int contarCantidadPerfiles(user perfil[]);

/*FUNCIONES DE CONTRAS*/
void levantarArchivoContras(int pos, user perfil[], password manager[]);      //AGARRA LO QUE TENGA ADENTRO EL ARCHIVO Y LO GUARDA EN EL VECTOR DE ESTRUCTURAS (manager)
void recibirValores(password manager[]);              //RECIBE VALORES INGRESADOS POR EL USUARIO POR CONSOLA
int contarCantidadContras(int estado, password manager[]);        //CUENTA LA CANTIDAD DE CONTRASEŅAS QUE TIENEN ingreso = INGRESADO
int buscarContra(int posCoincidencia[], password manager[]);                 //RECORRE EL VECTOR manager Y SE FIJA SI ENCUENTRA UNA COINCIDENCIA CON LAS KEYWORD --> ES COMO LA FUNCION SAME
void mostrarContra(int i, password manager[]);              //MUESTRA CONTRASEŅA
void mostrarTodasLasContras(password manager[]);      //MUESTRA TODAS LAS CONTRASEŅAS INGRESADAS (ingreso = INGRESADO) EN FORMA DE LISTA. LO HACE USANDO mostarContra
void mostrarContraPorPos(int posCoincidencia[], int max, password manager[]);      //MUESTRA CONTRASEŅAS CON LA POSICION
void modificarContra(int posCoincidencia[], int max, password manager[]);          //BUSCA LA CONTRASEŅA CON buscarContra Y TE OFRECE PARA CARGARLE LOS NUEVOS DATOS
void eliminarContra(int posCoincidencia[], int max, password manager[]);           //BUSCA LA CONTRASEŅA CON buscarContra Y PONE ingreso = ELIMINADO


/*PUNTEROS ARCHIVOS*/
FILE *gestorContras, *gestorPerfil;                                   //DECLARO VARIBALE DE ARCHIVO


void main(){

    /*VARIABLES*/
    password manager[MAXIMO];                       //DECLARO EL VECTOR manager DEL TIPO password --> ES UN VECTOR DE LA ESTRUCTURA password
    user perfil[MAXIMO];
    int estadoMaquinaMenu = LEVANTAR_ARCHIVO_USUARIOS;       //VARIABLE DE CAMBIO DEL SWITCH CASE --> TIENE QUE SER UNA VARIABLE GLOBAL    //INICIA EN UN ESTADO


    while(1){                                   //LA CONDICION SIEMPRE ES VERDADERA --> ASI LO HAGO LOOP (BUCLE)

        /*VARIABLES*/
        int posPerfil = 0;
        int posCoincidencia[MAXIMO];                    //VECTOR QUE LO USO PARA GUARDAR LAS POSICIONES DONDE HAYA COINCIDENCIAS
        char usu[TAM], con[TAM];

        int numOperacion;

        switch(estadoMaquinaMenu)
        {
            case LEVANTAR_ARCHIVO_USUARIOS:                  //INICIO EN ESTE ESTADO
                printf("Hola!\n");                  //SALUDO AL USUARIO PORQUE SOMOS AMABLES

                inicializar(usu, con, manager, perfil);                      //INICIALIZA LO QUE TIENE ADENTRO LA ESTRUCTURA --> TODO EN NO_INGRESADO O \0 (VACIO)

                printf("Ok, levantando archivo de usuarios!\n");    //AVISO QUE LEVANTO EL ARCHIVO --> BORRABLE --> LO USO PARA CHEQUEAR QUE FUNCIONE TODO OK
                levantarArchivoPerfiles(perfil);
                printf("Archivo levantado!\n");       //AVISO QUE YA LEVANTE EL ARCHIVO --> BORRABLE --> LO USO PARA CHEQUEAR QUE FUNCIONE TODO OK


                estadoMaquinaMenu = INGRESAR_PERFIL;       //VOY A ESTADO INGRESAR_PERFIL
            break;

            case INGRESAR_PERFIL:
                ingresoPerfil(usu, con);                    //EL USUARIO INGRESA DATOS POR CONSOLA

                int p = -1, q = -1;
                p = buscarPerfil(usu, con, posPerfil, perfil);
                //printf("Coincidencia en pos %i", p);

                if(p >= 0){                                                      //SI LO QUE DEVUELVE ES POSITIVO Y DISTINTO DE 0
                    //printf("Hay coincidencia\n");           //AVISA QUE SE ENCONTRARON UNA CANTIDAD DE COINCIDENCIAS
                    printf("Levantando archivo de contrase%cas...\n", ENIE_MIN);    //AVISO QUE LEVANTO EL ARCHIVO --> BORRABLE --> LO USO PARA CHEQUEAR QUE FUNCIONE TODO OK
                    levantarArchivoContras(p, perfil, manager);
                    printf("\nArchivo levantado!\n");       //AVISO QUE YA LEVANTE EL ARCHIVO --> BORRABLE --> LO USO PARA CHEQUEAR QUE FUNCIONE TODO OK
                }
                if(p < 0){
                    printf("\nNo existe ningun perfil que coincida con los datos ingresados.\nSe va a crear un nuevo archivo para este perfil.\n\n");
                    q = crearNuevoPerfil(usu, con, posPerfil, perfil);
                    printf("Levantando archivo de contrase%cas...\n", ENIE_MIN);    //AVISO QUE LEVANTO EL ARCHIVO --> BORRABLE --> LO USO PARA CHEQUEAR QUE FUNCIONE TODO OK
                    levantarArchivoContras(q, perfil, manager);
                    printf("\nArchivo levantado!\n");       //AVISO QUE YA LEVANTE EL ARCHIVO --> BORRABLE --> LO USO PARA CHEQUEAR QUE FUNCIONE TODO OK

                }

                printf("\nPARA CAMBIAR DE PERFIL, DEBE CERRAR EL PROGRAMA Y VOLVER A INGRESAR!\n");
                estadoMaquinaMenu = OPCIONES;       //VOY A ESTADO OPCIONES --> ES EL DEL MENU

            break;

            case OPCIONES:                          //ACA MUESTRO EL MENU

                printf("\nIntroduzca el numero de la operacion que desea realizar. \n 1 INGRESAR NUEVA CONTRASE%cA \n 2 MOSTRAR CONTRASE%cAS \n 3 BUSCAR CONTRASE%cAS \n 4 MODIFICAR CONTRASE%cAS \n 5 ELIMINAR CONTRASE%cAS \n 7 SALIR \n", ENIE_MAY, ENIE_MAY, ENIE_MAY, ENIE_MAY, ENIE_MAY);
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

            case INGRESAR_DATOS:        //ACA EL USUARIO INTRODUCE LOS DATOS DE LAS CONTRASEŅAS

                printf("Ok, vamos a ingresar contrase%cas!\n", ENIE_MIN);
                recibirValores(manager);                                               //LLAMO A LA FUNCION

                estadoMaquinaMenu = OPCIONES;                                   //CUANDO TERMINA VUELVE A OPCIONES

            break;

            case MOSTRAR_CONTRASENA:    //ACA SE MUESTRAN TODAS LAS CONTRASEŅAS

                printf("Ok, vamos a mostrar todas las contrase%cas!\n", ENIE_MIN);
                mostrarTodasLasContras(manager);                                       //LLAMO A LA FUNCION


                estadoMaquinaMenu = OPCIONES;                                   //CUANDO TERMINA VUELVE A OPCIONES

            break;

            case BUSCAR_CONTRASENA:         //ACA EL USUARIO PUEDE BUSACR CONTRASEŅAS POR KEYWORD

                printf("Ok, vamos a buscar contrase%cas!\n", ENIE_MIN);
                int nro = buscarContra(posCoincidencia, manager), i;                                    //LLAMO A LA FUNCION Y GUARDO LO QUE DEVUELVE EN LA VARIABLE nro

                if(nro>0){                                                      //SI LO QUE DEVUELVE ES POSITIVO Y DISTINTO DE 0
                    printf("Se encontraron %i coincidencias\n", nro);           //AVISA QUE SE ENCONTRARON UNA CANTIDAD DE COINCIDENCIAS
                    mostrarContraPorPos(posCoincidencia, nro, manager);                                   //MUESTRO LAS CONTRASEŅAS SEGUN LA POSICION QUE TENGAN EN EL VECTOR
                }
                else{
                    printf("No se encontraron coincidencias\n");                //SI NO HAY COINCIDENCIAS IMPRIMO ESTE AVISO
                }

                estadoMaquinaMenu = OPCIONES;                                   //CUANDO TERMINA VUELVE A OPCIONES

            break;

            case MODIFICAR_CONTRASENA:      //ACA EL USUARIO PUEDE MODIFICAR LA CONTRASEŅA Y LA IDENTIFICA CON LA KEYWORD

                printf("Ok, vamos a modificar contrase%cas!\n", ENIE_MIN);
                int nro1 = buscarContra(posCoincidencia, manager);                                      //LLAMO A LA FUNCION Y GUARDO LO QUE DEVUELVE EN LA VARIABLE nro1
                if(nro1>0){                                                     //SI LO QUE DEVUELVE ES POSITIVO Y DISTINTO DE 0
                    printf("Se encontraron %i coincidencias\n", nro1);          //AVISA QUE SE ENCONTRARON UNA CANTIDAD DE COINCIDENCIAS
                    mostrarContraPorPos(posCoincidencia, nro1, manager);                                  //MUESTRO LAS CONTRASEŅAS SEGUN LA POSICION QUE TENGAN EN EL VECTOR
                    modificarContra(posCoincidencia, nro1, manager);                                      //LLAMO A LA FUNCION Y EL USUARIO INGRESA LOS CAMBIOS
                }
                else{
                    printf("No se encontraron coincidencias\n");                //SI NO HAY COINCIDENCIAS IMPRIMO ESTE AVISO
                }

                estadoMaquinaMenu = OPCIONES;                                   //CUANDO TERMINA VUELVE A OPCIONES

            break;

            case ELIMINAR_CONTRASENA:       //ACA EL USUARIO PUEDE ELIMINAR CONTRASEŅAS Y LA IDENTIFICA CON LA KEYWORD

                printf("Ok, vamos a eliminar contrase%cas!\n", ENIE_MIN);
                int nro2 = buscarContra(posCoincidencia, manager);                                      //LLAMO A LA FUNCION Y GUARDO LO QUE DEVUELVE EN LA VARIABLE nro1
                if(nro2>0){                                                     //SI LO QUE DEVUELVE ES POSITIVO Y DISTINTO DE 0
                    printf("Se encontraron %i coincidencias\n", nro2);          //AVISA QUE SE ENCONTRARON UNA CANTIDAD DE COINCIDENCIAS
                    mostrarContraPorPos(posCoincidencia, nro2, manager);                                  //MUESTRO LAS CONTRASEŅAS SEGUN LA POSICION QUE TENGAN EN EL VECTOR
                    eliminarContra(posCoincidencia, nro2, manager);                                       //LLAMO A LA FUNCION Y EL USUARIO DECIDE CUAL ELIMINAR
                }
                else{
                    printf("No se encontraron coincidencias\n");                //SI NO HAY COINCIDENCIAS IMPRIMO ESTE AVISO
                }

                estadoMaquinaMenu = OPCIONES;                                   //CUANDO TERMINA VUELVE A OPCIONES

            break;

            case SALIR:         //ACA SE TERMINA EL PROGRAMA --> SI LA PERSONA NO SALE POR ACA, NO SE GUARDAN LOS CAMBIOS QUE REALICE
                system("cls");                                        //ESTA COSA LIMPIA LO QUE HAYA EN LA CONSOLA
                printf("Guardando archivos...\n\n");                               //AVISA QUE ESTA GUARDANDO EL ARCHIVO
                resumen(manager);
                guardarArchivo(posPerfil, perfil, manager);                                               //LLAM0 A LA FUNCION QUE GUARDA
                printf("Saliendo del programa. Nos vemos!\n");                  //CUANDO TERMINA, TE DICE CHAU PORQUE SOMOS EDUCADAS
                exit(0);
            break;

        }




    }
    return;
}

void inicializar(char usu[], char con[], password manager[], user perfil[]){                 //INICIALIZA LO QUE TIENE ADENTRO LA ESTRUCTURA --> TODO EN NO_INGRESADO O \0 (VACIO)
    int i;

    printf("inicializando... \n");
    for(i = 0; i<MAXIMO; i++){                                                  //SUMO HASTA QUE LLEGO AL MAXIMO
        manager[i].ingreso = NO_INGRESADO;                                      //INICIALIZO COMO NO_INGRESADO
        strcpy(manager[i].keyword, "\0");                                       //INICIALIZO CON \0
        strcpy(manager[i].usuario, "\0");                                       //INICIALIZO CON \0
        strcpy(manager[i].contra, "\0");                                        //INICIALIZO CON \0
        strcpy(manager[i].url, "\0");                                           //INICIALIZO CON \0

        perfil[i].ingreso = NO_INGRESADO;                                      //INICIALIZO COMO NO_INGRESADO
        strcpy(perfil[i].usuario, "\0");                                       //INICIALIZO CON \0
        strcpy(perfil[i].contra, "\0");                                        //INICIALIZO CON \0
        strcpy(perfil[i].nombreArchivo, "\0");                                 //INICIALIZO CON \0

        strcpy(usu, "\0");
        strcpy(con, "\0");

    }
    printf("terminando... \n");
    return;
}

void levantarArchivoPerfiles(user perfil[]){             //AGARRA LO QUE TENGA ADENTRO EL ARCHIVO Y LO GUARDA EN EL VECTOR DE ESTRUCTURAS (usuarios)
    int i;

    if (!(gestorPerfil = fopen("Usuarios.dat", "rb"))){             //SI NO SE PUEDE ABRIR EL ARCHIVO
        //printf("No se puede abrir el archivo\n");           //AVISA
		return (1);                                         //DEVUELVE 1
	}

	for (i = 0; i <= MAXIMO; i++){         //LLAMA A LA FUNCION Y SUMA HASTA QUE SEA IGUAL A LA CANTIDAD DE CONTRASEŅAS CON ingreso = INGRESADO --> DEBERIA HABER 0
        fread(&perfil[i], sizeof(perfil[0]), 1, gestorPerfil);  //LEE EL ARCHIVO
    }

	while (!feof(gestorPerfil)){                                  //MIENTRAS NO HAYA LLEGADO AL FINAL DEL ARCHIVO gestorContras (end of file -> eof)
		//printf("\n%100i%100i%100s%100s%100s%255s", manager[i].ingreso, manager[i].id, manager[i].keyword, manager[i].usuario, manager[i].contra, manager[i].url);
		fread(&perfil[i], sizeof(perfil[0]), 1, gestorPerfil);  //LEE EL ARCHIVO Y LO VA GUARDANDO EN EL VECTOR manager
	}
	printf("Hay %i perfiles.\n", contarCantidadPerfiles(perfil));
	fclose(gestorPerfil);                                         //CIERRA EL ARCHIVO gestorContras
	printf("\n\n");                                         //PRINTEA ESTO PARA SEPARAR

	return;
}

void ingresoPerfil(char usu[], char con[]){
    int flag2 = 1;
    printf("Para poder visualizar sus contrase%cas, debe identificarse con su usuario y contrase%ca.\n", ENIE_MIN, ENIE_MIN);
    printf("Usuario:\n");
    //while((getchar()!='\n')) {}
    gets(usu);                                                  //ACA PUEDE CAMBIAR LO QUE VALE FLAG --> DEPENDE DE LO QUE INGRESA EL USUARIO
    while (strcmp(usu, "\n") != flag2){
        printf("El usuario no puede quedar vacio.\n Por favor, ingresar un usuario valido\n");
        gets(usu);
    }
    printf("El usuario introducido es %s \n", usu);                     //CHEQUEO INGRESO
    printf("Contrase%ca:\n", ENIE_MIN);
    gets(con);                                                  //ACA PUEDE CAMBIAR LO QUE VALE FLAG --> DEPENDE DE LO QUE INGRESA EL USUARIO
    while (strcmp(con, "\n") != flag2){
        printf("La contrase%ca no puede quedar vacio.\n Por favor, ingresar una contrase%ca valida\n", ENIE_MIN, ENIE_MIN);
        gets(con);
    }
    printf("La contrase%ca introducida es %s \n", ENIE_MIN, con);                     //CHEQUEO INGRESO

    return;
}

int buscarPerfil(char usu[], char con[], int posPerfil, user perfil[]){
    int a, i;

    posPerfil = -1;

    for(i=0; i<MAXIMO ; i++){
        if(perfil[i].ingreso == INGRESADO){
            if(strlen(perfil[i].usuario) == strlen(usu) && strlen(perfil[i].contra) == strlen(con)){     //USO SRTLEN (funcion de libreria) PARA VER SI TIENEN EL MISMO TAMAŅO
                if(strcmp(perfil[i].usuario, usu) == 0 && strcmp(perfil[i].contra, con) == 0){      //USO STRCMP (funcion de libreria) PARA VER SI SON IGUALES
                    printf("\nExiste un perfil que coincide con los datos ingresados.\n\n");                         //ESTO LO USO PARA DEBUGGEAR PERO AHORA NO
                    posPerfil = i;
                }
            }
        }
    }

    return posPerfil;
}

int crearNuevoPerfil(char usu[], char con[], int posPerfil, user perfil[]){
    int i, a;

    posPerfil = -1;
    i = contarCantidadPerfiles(perfil);

    if(perfil[i].ingreso == NO_INGRESADO){
        perfil[i].ingreso = 1;
        strcpy(perfil[i].usuario, usu);                   //LE COPIO usu A USUARIO EN LA POSICION DEL STRUCT
        strcpy(perfil[i].contra, con);                    //IDEM PERO CON con y CONTRA
        strcpy(perfil[i].nombreArchivo, usu);             //ASIGNO EL USUARIO COMO NOMBRE DE ARCHIVO
        strcat(perfil[i].nombreArchivo,".dat");
        posPerfil = i;
    }
    printf("Nuevo perfil creado!\nAhora hay %i perfiles.\n\n", contarCantidadPerfiles(perfil));

    return posPerfil;
}

int contarCantidadPerfiles(user perfil[]){        //CUENTA LA CANTIDAD DE CONTRASEŅAS QUE TIENEN ingreso = INGRESADO
    int i, cantidad = 0;
    for(i=0; i<TAM; i++){                                   //CUENTA HASTA EL FINAL DEL VECTOR
        if(perfil[i].ingreso){                //SI ingreso = INGRESADO
            cantidad++;                                     //CUENTO CONTRASEŅA
        }
    }
    return cantidad;                                        //DEVUELVE LA CANTIDAD DE CONTRASEŅAS INGRESADAS --> OSEA HASTA QUE POSICION DEL VECTOR ESTA OCUPADO CON INFORMACION Y NO ESTA VACIO
}

void levantarArchivoContras(int pos, user perfil[], password manager[]){             //AGARRA LO QUE TENGA ADENTRO EL ARCHIVO Y LO GUARDA EN EL VECTOR DE ESTRUCTURAS (manager)
    int i;

    //system("cls");
	if (!(gestorContras = fopen(perfil[pos].nombreArchivo, "rb"))){             //SI NO SE PUEDE ABRIR EL ARCHIVO
        //printf("No se puede abrir el archivo\n");           //AVISA
		return (1);                                         //DEVUELVE 1
	}

	for (i = 0; i <= MAXIMO; i++){         //LLAMA A LA FUNCION Y SUMA HASTA QUE SEA IGUAL A LA CANTIDAD DE CONTRASEŅAS CON ingreso = INGRESADO --> DEBERIA HABER 0
        fread(&manager[i], sizeof(manager[0]), 1, gestorContras);  //LEE EL ARCHIVO
    }

	while (!feof(gestorContras)){                                  //MIENTRAS NO HAYA LLEGADO AL FINAL DEL ARCHIVO gestorContras (end of file -> eof)
		//printf("\n%100i%100i%100s%100s%100s%255s", manager[i].ingreso, manager[i].id, manager[i].keyword, manager[i].usuario, manager[i].contra, manager[i].url);
		fread(&manager[i], sizeof(manager[0]), 1, gestorContras);  //LEE EL ARCHIVO Y LO VA GUARDANDO EN EL VECTOR manager
	}
	fclose(gestorContras);                                         //CIERRA EL ARCHIVO gestorContras
	printf("\n\n");                                         //PRINTEA ESTO PARA SEPARAR

	return;
}

void recibirValores(password manager[]){              //RECIBE VALORES INGRESADOS POR EL USUARIO POR CONSOLA
    int i, flag = 1, flag2 = 1, n;

    for(i = contarCantidadContras(INGRESADO, manager); i<MAXIMO && flag == 1 ; i++){          //SUMA DESDE LA ULTIMA POSICION QUE HAYA DE CONTRASEŅA CARGADA HASTA LLEGAR A MAXIMO
        printf("Desea agregar una nueva contrase%ca? INGRESE: \n 1 SI \n 2 NO\n", ENIE_MIN);
        scanf("%i",&flag);                                                  //ACA PUEDE CAMBIAR LO QUE VALE FLAG --> DEPENDE DE LO QUE INGRESA EL USUARIO
        printf("La opcion introducida es %i \n", flag);                     //CHEQUEO INGRESO

        if(flag == 1){                                                      //SI EL USUARIO INGRESA 1
            manager[i].ingreso = INGRESADO;                                 //CAMBIO LO QUE TIENE ingreso a INGRESADO

            printf("Ingrese el keyword (identificador).\n");
            while((getchar()!='\n')) {}                                     //ESTO ES PARA QUE ELIMINE UN \n SI LE QUEDO EN EL BUFFER
            gets(manager[i].keyword);                                       //GETTEO LO QUE INGRESA COMO KEYWORD Y LO GUARDO
            while (strcmp(manager[i].keyword, "\n") != flag2){
                    printf("El keyword no puede quedar vacio.\n Por favor, ingresar un keyword valido\n");
                    gets(manager[i].keyword);
            }
            printf("Genial! keyword ingresado con exito.\n");
            printf("El keyword ingresado es: %s \n", manager[i].keyword);   //CHEQUEO INGRESO

            printf("Ingrese el usuario.\n");                                //IDEM A KEYWORD
            gets(manager[i].usuario);
            printf("Genial! Usuario ingresado con exito.\n");
            printf("El usuario ingresado es: %s \n", manager[i].usuario);

            printf("Ingrese la password.\n");                               //IDEM A KEYWORD
            gets(manager[i].contra);
            while (strcmp(manager[i].contra, "\n") != flag2){
                    printf("El keyword no puede quedar vacio.\n Por favor, ingresar un keyword valido\n");
                    gets(manager[i].contra);
            }
            printf("Genial! Password ingresada con exito.\n");
            printf("La password ingresada es: %s \n", manager[i].contra);

            printf("Ingrese la url.\n");                                   //IDEM A KEYWORD
            gets(manager[i].url);
            printf("Genial! Url ingresada con exito.\n");
            printf("La url ingresada es: %s \n", manager[i].url);

        }

        if(flag == 2){                                                     //SI EL USUARIO INGRESA 2 --> SE DEJA DE CUMPLIR CONDICION DEL FOR
            printf("Ok, volviendo al menu! \n");                           //SALE DEL FOR Y VUELVE AL MENU
        }
    }

    return;
}

int contarCantidadContras(int estado, password manager[]){        //CUENTA LA CANTIDAD DE CONTRASEŅAS QUE TIENEN ingreso = INGRESADO
    int i, cantidad = 0;
    for(i=0; i<TAM; i++){                                   //CUENTA HASTA EL FINAL DEL VECTOR
        if(manager[i].ingreso == estado){                //SI ingreso = INGRESADO
            cantidad++;                                     //CUENTO CONTRASEŅA
        }
    }
    //printf("Hay %i contras\n", cantidad);
    return cantidad;                                        //DEVUELVE LA CANTIDAD DE CONTRASEŅAS INGRESADAS --> OSEA HASTA QUE POSICION DEL VECTOR ESTA OCUPADO CON INFORMACION Y NO ESTA VACIO
}

int buscarContra(int posCoincidencia[], password manager[]){                 //RECORRE EL VECTOR manager Y SE FIJA SI ENCUENTRA UNA COINCIDENCIA CON LAS KEYWORD --> ES COMO LA FUNCION SAME
    int a, b, c = 0, i, flag2 = 1;
    char keywordIngresado[TAM];                                                 //CREO UN VECTOR DE CHAR (string) PARA GUARDAR LA KEYWORD QUE INGRESE EL USUARIO

        printf("Ingrese el keyword de la contrase%ca que desea.\n", ENIE_MIN);

        while((getchar()!='\n')) {}                                             //ESTO ES PARA QUE ELIMINE UN \n SI LE QUEDO EN EL BUFFER
        gets(keywordIngresado);                                                 //GETTEO Y GUARDO
        while (strcmp(keywordIngresado, "\n") != flag2){
            printf("El keyword no puede quedar vacio.\n Por favor, ingresar un keyword valido\n");
            gets(keywordIngresado);
        }
        printf("Genial! keyword ingresado con exito.\n");
        printf("El keyword ingresado es: %s \n", keywordIngresado);             //CHEQUEO


        printf("Buscando lo que contenga %s... \n", keywordIngresado);

        for(i=0; i<TAM; i++){                                                   //PONGO EL VECTOR EN -1 Y LE "BORRO" LO QUE SEA QUE TENGA ANTES PARA QUE NO SE PISE NADA
            posCoincidencia[i] = -1;
        }

        for(a = 0; a<TAM; a++){                                                 //SUMO HASTA LLEGAR AL FINAL DEL VECTOR

            if(manager[a].ingreso == INGRESADO){                                //SI ignresado = INGRESO
                if(strlen(manager[a].keyword) == strlen(keywordIngresado)){     //USO SRTLEN (funcion de libreria) PARA VER SI TIENEN EL MISMO TAMAŅO
                    if(strcmp(manager[a].keyword, keywordIngresado) == 0){      //USO STRCMP (funcion de libreria) PARA VER SI SON IGUALES
                        //printf("Hay coincidencia\n");                         //ESTO LO USO PARA DEBUGGEAR PERO AHORA NO
                        posCoincidencia[c] = a;                                 //ME GUARDO LA POSICION DE LA COINCIDENCIA
                        c++;                                                    //INCREMENTO LA VARIABLE --> ESTO CUENTA LA CANTIDAD DE COINCIDENCIAS
                    }
                }
            }
        }

    return c;                                                                   //DEVUELVE LA VARIABLE --> LA CANTIDAD DE COINCIDENCIAS
}

void mostrarContra(int i, password manager[]){          //MUESTRA CONTRASEŅA
    if(manager[i].ingreso == INGRESADO){                                        //SI ingreso = INGRESADO EN ESA POSICION DEL VECTOR
        printf("keyword: %s \n", manager[i].keyword);                           //PRINTEO
        printf("Usuario: %s \n", manager[i].usuario);
        printf("Constrase%ca: %s \n", ENIE_MIN, manager[i].contra);
        printf("URL: %s \n", manager[i].url);
        printf("__________________________________\n");
    }
    return;
}

void mostrarTodasLasContras(password manager[]){      //MUESTRA TODAS LAS CONTRASEŅAS INGRESADAS (ingreso = INGRESADO) EN FORMA DE LISTA. LO HACE USANDO mostarContra
    int i;

    if(contarCantidadContras(INGRESADO, manager) != 0){                                           //SI HAY CONTRASEŅAS GUARDADAS
        for(i = 0; i<MAXIMO; i++){                                              //INCREMENTO i
            mostrarContra(i, manager);                                                   //LE VOY MANDANDO i PARA QUE EN LA FUNCION RECORRA EL VECTOR
        }
    }
    if(contarCantidadContras(INGRESADO, manager) == 0){                                           //SI NO HAY CONTRASEŅAS GUARDADAS
        printf("Todavia no hay contrase%cas guardadas.\nPor favor, ingrese sus contrase%cas.\n", ENIE_MIN, ENIE_MIN);   //AVISO
    }

    return;
}

void mostrarContraPorPos(int posCoincidencia[], int max, password manager[]){  //MUESTRA CONTRASEŅAS CON LA POSICION
    int i, j;

    if(contarCantidadContras(INGRESADO, manager) != 0){                                           //SI HAY CONTRASEŅAS GUARDADAS
        for(i = 0; i < max; i++){                                               //INCREMENTO i HASTA LLEGAR A LA CANTIDAD DE COINCIDENCIAS
                mostrarContra(posCoincidencia[i], manager);                              //LLAMO A posCoincidencia  Y LE PASO i, Y A mostrarContra LE PASO LO QUE DEVUELVE posCoincidencia --> LE MANDO SOLO LAS POSICIONES DONDE HAY COINCIDENCIA
        }
    }
    if(contarCantidadContras(INGRESADO, manager) == 0){                                           //SI NO HAY CONTRASEŅAS GUARDADAS
        printf("Todavia no hay contrase%cas guardadas.\nPor favor, ingrese sus contrase%cas.\n", ENIE_MIN, ENIE_MIN);   //AVISO
    }


    return;
}

void modificarContra(int posCoincidencia[], int max, password manager[]){      //BUSCA LA CONTRASEŅA CON buscarContra Y TE OFRECE PARA CARGARLE LOS NUEVOS DATOS
    int i, num, flag2 = 1;

    if(contarCantidadContras(INGRESADO, manager) != 0 && max>0){                                  //SI HAY CONTRASEŅAS GUARDADAS Y LO QUE DEVUELVE buscarContra ES > 0

        printf("Ingrese el numero de la contrase%ca que quiere modificar\n", ENIE_MIN); //PIDO QUE INGRESE CUAL QUIERE MODIFICAR
        scanf("%i", &num);                                                      //LO RECIBO Y GUARDO

        printf("Vamos a modificar la Opcion %i:\n", num);                       // --> HAY QUE AGREGARLE UN NUMERO DE OPCION A LO QUE SE PRINTEA <--

        if(manager[posCoincidencia[num-1]].ingreso == INGRESADO){               //SI ingreso = INGRESADO EN ESA POSICION
            mostrarContra(posCoincidencia[num-1], manager);                              //MUESTRO LA CONTRASEŅA DE ESA POSICION

            printf("Ingrese las modificaciones.\n");                            //RECIBO DATOS Y LOS GUARDO --> PISO LOS ANTERIORES

            printf("keyword:\n");
            while((getchar()!='\n')) {}
            gets(manager[posCoincidencia[num-1]].keyword);
            while(strcmp(manager[posCoincidencia[num-1]].keyword, "\n") != flag2){
                printf("El keyword no puede quedar vacio.\n Por favor, ingresar un keyword valido\n");
                gets(manager[posCoincidencia[num-1]].keyword);
            }

            printf("Usuario:\n");
            gets(manager[posCoincidencia[num-1]].usuario);

            printf("Constrase%ca:\n", ENIE_MIN);
            gets(manager[posCoincidencia[num-1]].contra);
            while(strcmp(manager[posCoincidencia[num-1]].contra, "\n") != flag2){
                printf("El keyword no puede quedar vacio.\n Por favor, ingresar un keyword valido\n");
                gets(manager[posCoincidencia[num-1]].contra);
            }

            printf("URL:\n");
            gets(manager[posCoincidencia[num-1]].url);
            printf("__________________________________\n");

            printf("La modificacion:\n");                                         //IMPRIMO CON LOS CAMBIOS FINALES
            printf("keyword: %s \n", manager[posCoincidencia[num-1]].keyword);
            printf("Usuario: %s \n", manager[posCoincidencia[num-1]].usuario);
            printf("Constrase%ca: %s \n", ENIE_MIN, manager[posCoincidencia[num-1]].contra);
            printf("URL: %s \n", manager[posCoincidencia[num-1]].url);          //HAGO num-1 PORQUE NECESITO CONSIDERAR QUE EL VECTOR EMPIEZA EN 0
            printf("__________________________________\n");

        }
    }

    if(contarCantidadContras(INGRESADO, manager) == 0){                                           //SI NO HAY CONTRASEŅAS GUARDADAS
        printf("Todavia no hay contrase%cas guardadas.\nPor favor, ingrese sus contrase%cas.\n", ENIE_MIN, ENIE_MIN);   //AVISO
    }


    return;
}

void eliminarContra(int posCoincidencia[], int max, password manager[]){       //BUSCA LA CONTRASEŅA CON buscarContra Y PONE ingreso = ELIMINADO
    int i, num, flag2 = 1;

    if(contarCantidadContras(INGRESADO, manager) != 0 && max>0){                                  //SI HAY CONTRASEŅAS GUARDADAS Y LO QUE DEVUELVE buscarContra ES > 0

        printf("Ingrese el numero de la contrase%ca que quiere eliminar\n", ENIE_MIN); //PIDO QUE INGRESE CUAL QUIERE MODIFICAR
        scanf("%i", &num);                                                      //LO RECIBO Y GUARDO

        printf("Vamos a eliminar la Opcion %i:\n", num);                        // --> HAY QUE AGREGARLE UN NUMERO DE OPCION A LO QUE SE PRINTEA <--

        if(manager[posCoincidencia[num-1]].ingreso == INGRESADO){               //SI ingreso = INGRESADO EN ESA POSICION
            mostrarContra(posCoincidencia[num-1], manager);                              //MUESTRO LA CONTRASEŅA DE ESA POSICION

            manager[posCoincidencia[num-1]].ingreso = ELIMINADO;                //CAMBIO ingreso = INGRESADO A ingreso = ELIMINADO --> DESPUES NO GUARDO LOS QUE TIENEN ELIMINADO
            printf("La contrase%ca seleccionada sera eliminada al cerrar el programa.\n", ENIE_MIN);    //AVISO
        }
    }

    if(contarCantidadContras(INGRESADO, manager) == 0){                                           //SI NO HAY CONTRASEŅAS GUARDADAS
        printf("Todavia no hay contrase%cas guardadas.\nPor favor, ingrese sus contrase%cas.\n", ENIE_MIN, ENIE_MIN);   //AVISO
    }

    return;
}

void resumen(password manager[]){
    printf("\n\nRESUMEN\n");
    printf("\t%i CONTRAE%cAS INGRESADAS\n\t%i CONTRAE%cAS ELIMINADAS\n\n", contarCantidadContras(INGRESADO, manager), ENIE_MAY, contarCantidadContras(ELIMINADO, manager), ENIE_MAY);
    return;
}

void guardarArchivo(int posPerfil, user perfil[], password manager[]){
    int i,j = 0;

    if (!(gestorContras = fopen(perfil[posPerfil].nombreArchivo, "wb"))){                                 //SI NO SE PUEDE ABRIR EL ARCHIVO
        printf("No se puede abrir el archivo\n");                               //AVISA
        return (1);                                                             //DEVUELVE 1
    }

    if (!(gestorPerfil = fopen("Usuarios.dat", "wb"))){                                 //SI NO SE PUEDE ABRIR EL ARCHIVO
        printf("No se puede abrir el archivo Usuarios\n");                               //AVISA
        return (1);                                                             //DEVUELVE 1
    }

    printf("Guardando contrase%cas...\n", ENIE_MIN);
    for (i = 0; i <= contarCantidadContras(INGRESADO, manager); i++){                             //INCREMENTA HASTA QUE LLEGA A LA CANTIDAD DE CONTRASEŅAS INGRESADAS
        if(manager[i].ingreso == INGRESADO){                                    //SI ingreso = INGRESADO
            fwrite(&manager[i], sizeof(manager[0]), 1, gestorContras);                 //ESCRIBE LA CONTRASEŅA EN EL ARCHIVO
        }
    }

    printf("Guardando perfil...\n");
    for (j = 0; j <= contarCantidadPerfiles(perfil); j++){                             //INCREMENTA HASTA QUE LLEGA A LA CANTIDAD DE CONTRASEŅAS INGRESADAS
        if(perfil[j].ingreso == INGRESADO){                                    //SI ingreso = INGRESADO
            //printf("Usuarios:\n");
            //printf("%s\n", perfil[j].usuario);
            fwrite(&perfil[j], sizeof(perfil[0]), 1, gestorPerfil);                 //ESCRIBE LA CONTRASEŅA EN EL ARCHIVO
        }
    }

    fclose(gestorContras);                                                             //CIERRO EL ARCHIVO
    fclose(gestorPerfil);                                                             //CIERRO EL ARCHIVO
    printf("\n");                                                               //PRINTEA ESTO DE ONDA

    return;
}
