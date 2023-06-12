#include <stdio.h>

#include <stdlib.h>
#include <time.h>


#define MAXRONDA    20
#define MENUPRINC   0
#define MENUNUM     1
#define MENUDOC     2
#define MENUFP      3
#define MENUCOLOR   4
#define MENUPAR     5
#define MENUCLM     6

#define     VERDE   0
#define     ROJO    1
#define     NEGRO   2

#define     FALSE   0
#define     FALTA   1
#define     PASA    2
#define     DOCENA1 1
#define     DOCENA2 2
#define     DOCENA3 3
#define     COLUMNA1 1
#define     COLUMNA2 2
#define     COLUMNA3 3
#define     IMPAR   1
#define     PAR     2

int lanzamiento(void);
int color_ronda(int num);
void suma_colores(int cc[], int ac[]);
int pasa_falta(int num);
int docenas(int num);
int columnas(int num);
int paridad(int num);
int pedirNrondas(void);
int num_primo(int numronda);
void imprimir_menues(int prin);
void inicio_array(int longitud, int a[]);
void seleccion_apuestas(int AA[],int n[]);
int apuestas(int ad[], int af[], int ac[], int ap[], int acol[],int mnum[37][6], int aa[], int n[], int cantcolor[]);
int perdidas_ronda(int numronda, int mnum[37][6], int ad[], int af[], int ac[], int ap[], int acol[]);
int ganancia_ronda(int numronda, int mnum[37][6], int ad[], int af[], int ac[], int ap[], int acol[]);

int main(){

    int cantRonda = 0;          // Cantidad de rondas que se jugaran en la mesa, ingresada por el usuario.
    int num_ronda = 0;          // Almacena el valor del numero que salio en la ronda.
    int perdida_parcial = 0;    // Almacena la perdida de la mesa por ronda.
    int ganancia_parcial = 0;   // Almacena la ganancia de la mesa por ronda.
    int perdida_total = 0;      // Almacena la perdida total de la mesa.
    int ganancia_total = 0;     // Almacena la ganancia total de la mesa.
    int total_apuestas = 0;     // Cantidad de apuestas realizadas durante todo el programa.
    float prom_apuestas = 0;    // Promedio de apuestas por ronda.
    int apuestaMax = 0;         // Guarda la apuesta de mayor valor.
    int apuestaMaxNum = 0;      // Numero de ronda en la que tuvo lugar la mayor apuesta.

    int sumatotalcolor = 0;     // Suma de todas las apuestas a los colores
    float porcentaje_negro=0;   // Porcentaje de apuetas al color negro.
    float porcentaje_rojo=0;    // Porcentaje de apuetas al color rojo.
    int color_cons=0;           // Cantidad de veces seguidas que salio un mismo color.
    int color_ant=-1;           // Representa el color que salio la ronda anterior.
    int coloresrepetidos = 0;   // Flag para indicar que se repitio un color mas de cinco veces.
    int multi_diez=0;           // Flag para indicar que en alguna ronda salio el 0 o un multiplo de 10.
    int cant_primos=0;          // Cantidad de veces que salieron numeros primos durante las rondas.
    int a_apuestas[8];          //Administra las casillas apostadas en la apuesta actual, y guarda la apuesta maxima.
    int a_docenas[18];
    /*  Array que contine las apuestas y fichas correspondiente a las docenas.
        a_docenas[0]= Cantidad de fichas de valor 1 para la Primer Docena.
        a_docenas[1]= Cantidad de fichas de valor 2 para la Primer Docena.
        a_docenas[2]= Cantidad de fichas de valor 5 para la Primer Docena.
        a_docenas[3]= Cantidad de fichas de valor 10 para la Primer Docena.
        a_docenas[4]= Cantidad de fichas de valor 50 para la Primer Docena.
        a_docenas[5]= Cantidad de fichas de valor 100 para la Primer Docena.
        a_docenas[6]= Cantidad de fichas de valor 1 para la Segunda Docena.
        a_docenas[7]= Cantidad de fichas de valor 2 para la Segunda Docena.
        a_docenas[8]= Cantidad de fichas de valor 5 para la Segunda Docena.
        a_docenas[9]= Cantidad de fichas de valor 10 para la Segunda Docena.
        a_docenas[10]= Cantidad de fichas de valor 50 para la Segunda Docena.
        a_docenas[11]= Cantidad de fichas de valor 100 para la Segunda Docena.
        a_docenas[12]= Cantidad de fichas de valor 1 para la Tercer Docena.
        a_docenas[13]= Cantidad de fichas de valor 2 para la Tercer Docena.
        a_docenas[14]= Cantidad de fichas de valor 5 para la Tercer Docena.
        a_docenas[15]= Cantidad de fichas de valor 10 para la Tercer Docena.
        a_docenas[16]= Cantidad de fichas de valor 50 para la Tercer Docena.
        a_docenas[17]= Cantidad de fichas de valor 100 para la Tercer Docena.*/

    int a_faltapasa[12];
    /*  Array que contine las apuestas y fichas correspondiente a la Falta-Pasa.
        a_faltapasa[0]= Cantidad de fichas de valor 1 para la Falta.
        a_faltapasa[1]= Cantidad de fichas de valor 2 para la Falta.
        a_faltapasa[2]= Cantidad de fichas de valor 5 para la Falta.
        a_faltapasa[3]= Cantidad de fichas de valor 10 para la Falta.
        a_faltapasa[4]= Cantidad de fichas de valor 50 para la Falta.
        a_faltapasa[5]= Cantidad de fichas de valor 100 para la Falta.
        a_faltapasa[6]= Cantidad de fichas de valor 1 para la Pasa.
        a_faltapasa[7]= Cantidad de fichas de valor 2 para la Pasa.
        a_faltapasa[8]= Cantidad de fichas de valor 5 para la Pasa.
        a_faltapasa[9]= Cantidad de fichas de valor 10 para la Pasa.
        a_faltapasa[10]= Cantidad de fichas de valor 50 para la Pasa.
        a_faltapasa[11]= Cantidad de fichas de valor 100 para la Pasa.*/

    int a_color[12];
    /*  Array que contine las apuestas y fichas correspondiente al Color.
        a_color[0]= Cantidad de fichas de valor 1 para color Rojo.
        a_color[1]= Cantidad de fichas de valor 2 para color Rojo.
        a_color[2]= Cantidad de fichas de valor 5 para color Rojo.
        a_color[3]= Cantidad de fichas de valor 10 para color Rojo.
        a_color[4]= Cantidad de fichas de valor 50 para color Rojo.
        a_color[5]= Cantidad de fichas de valor 100 para color Rojo.
        a_color[6]= Cantidad de fichas de valor 1 para color Negro.
        a_color[7]= Cantidad de fichas de valor 2 para color Negro.
        a_color[8]= Cantidad de fichas de valor 5 para color Negro.
        a_color[9]= Cantidad de fichas de valor 10 para color Negro.
        a_color[10]= Cantidad de fichas de valor 50 para color Negro.
        a_color[11]= Cantidad de fichas de valor 100 para color Negro.*/

    int a_paridad[12];
    /*  Array que contine las apuestas y fichas correspondiente a Par e Impar.
        a_paridad[0]= Cantidad de fichas de valor 1 para Par.
        a_paridad[1]= Cantidad de fichas de valor 2 para Par.
        a_paridad[2]= Cantidad de fichas de valor 5 para Par.
        a_paridad[3]= Cantidad de fichas de valor 10 para Par.
        a_paridad[4]= Cantidad de fichas de valor 50 para Par.
        a_paridad[5]= Cantidad de fichas de valor 100 para Par.
        a_paridad[6]= Cantidad de fichas de valor 1 para Impar.
        a_paridad[7]= Cantidad de fichas de valor 2 para Impar.
        a_paridad[8]= Cantidad de fichas de valor 5 para Impar.
        a_paridad[9]= Cantidad de fichas de valor 10 para Impar.
        a_paridad[10]= Cantidad de fichas de valor 50 para Impar.
        a_paridad[11]= Cantidad de fichas de valor 100 para Impar.*/

    int a_columnas[18];
        /*  Array que contine las apuestas y fichas correspondiente a las columnas.
        a_columnas[0]= Cantidad de fichas de valor 1 para la Columna del 1.
        a_columnas[1]= Cantidad de fichas de valor 2 para la Columna del 1.
        a_columnas[2]= Cantidad de fichas de valor 5 para la Columna del 1.
        a_columnas[3]= Cantidad de fichas de valor 10 para la Columna del 1.
        a_columnas[4]= Cantidad de fichas de valor 50 para la Columna del 1.
        a_columnas[5]= Cantidad de fichas de valor 100 para la Columna del 1.
        a_columnas[6]= Cantidad de fichas de valor 1 para la Columna del 2.
        a_columnas[7]= Cantidad de fichas de valor 2 para la Columna del 2.
        a_columnas[8]= Cantidad de fichas de valor 5 para la Columna del 2.
        a_columnas[9]= Cantidad de fichas de valor 10 para la Columna del 2.
        a_columnas[10]= Cantidad de fichas de valor 50 para la Columna del 2.
        a_columnas[11]= Cantidad de fichas de valor 100 para la Columna del 2.
        a_columnas[12]= Cantidad de fichas de valor 1 para la Columna del 3.
        a_columnas[13]= Cantidad de fichas de valor 2 para la Columna del 3.
        a_columnas[14]= Cantidad de fichas de valor 5 para la Columna del 3.
        a_columnas[15]= Cantidad de fichas de valor 10 para la Columna del 3.
        a_columnas[16]= Cantidad de fichas de valor 50 para la Columna del 3.
        a_columnas[17]= Cantidad de fichas de valor 100 para la Columna del 3.*/

    int cant_color[2];
        /*  Almacena la cantidad de apuestas al Rojo y al Negro.
        cant_color[0]= Cantidad de veces que se aposto al Rojo.
        cant_color[1]= Cantidad de veces que se aposto al Negro.*/

    int numeros[37];

    int m_numeros[37][6];
        /*  Matriz que contine las apuestas y fichas correspondiente a los numeros plenos.
            i representa a los numeros del 0 al 36.
        m_numeros[i][0]= Cantidad de fichas de valor 1 para el pleno en i.
        m_numeros[i][1]= Cantidad de fichas de valor 2 para el pleno en i.
        m_numeros[i][2]= Cantidad de fichas de valor 5 para el pleno en i.
        m_numeros[i][3]= Cantidad de fichas de valor 10 para el pleno en i.
        m_numeros[i][4]= Cantidad de fichas de valor 50 para el pleno en i.
        m_numeros[i][5]= Cantidad de fichas de valor 100 para el pleno en i.
        */

    /** Inicializacion de los arrays y matrices. */
    inicio_array(8, a_apuestas);
    inicio_array(37, numeros);
    inicio_array(18, a_docenas);
    inicio_array(12, a_faltapasa);
    inicio_array(12, a_color);
    inicio_array(12, a_paridad);
    inicio_array(18, a_columnas);
    inicio_array(2, cant_color);

    //Inicializacion de la matriz
    for(int i = 0; i<37; i++){
        for(int j = 0; j<6; j++){
            m_numeros[i][j] = 0;
        }
    }
    /*****************************/

    srand( time(NULL) ); //planta la semilla para que cambie con el tiempo

    printf("*************************************************************\n");
    printf("**** Bienvenido a la Ruleta del Taller de programacion 1 ****\n");
    printf("*************************************************************\n");
    printf("*************************************************************\n");
    printf("********* Avila, Ivan ********** Torrazza, Virginia *********\n");
    printf("*************************************************************\n");
    printf("\n");

    do{
        printf("Ingrese cuantas rondas desea jugar en esta mesa(Max. 20): \n");
        scanf("%d",&cantRonda);
        if(cantRonda > 20 || cantRonda < 0){
            printf("Recuerde que el valor debe estar entre 0 y 20.\n");
        }
    }while(cantRonda > 20 || cantRonda < 0);

    /* Bucle para jugar la cantidad de rondas seleccionadas */
    for(int i = 0; i < cantRonda; i++){
        /* La funcion apuestas devuelve la cantidad de apuestas que se realizaron
        y se iran sumando ronda a ronda. */
        total_apuestas +=  apuestas(a_docenas, a_faltapasa, a_color, a_paridad, a_columnas, m_numeros, a_apuestas, numeros, cant_color);
        /* Comparo si hay una nueva apuesta maxima.*/
        if(a_apuestas[7] > apuestaMax){
            apuestaMax = a_apuestas[7];
            apuestaMaxNum = i+1;
        }
        /* Simulamos el lanzamiento de la bola con la funcion lanzamiento
        y almacenamos el valor en num_ronda. */
        num_ronda = lanzamiento();

        printf("*************************************************************\n");
        printf("Salio la bola %d !!!\n",num_ronda);
        printf("*************************************************************\n");

        /* Simulamos el lanzamiento de la bola con la funcion lanzamiento
        y almacenamos el valor en num_ronda. */
        if( num_primo(num_ronda) == 1 ){
            cant_primos++;
        }

        /* Recorro el for haciendo j*10 para comparar si el
        numero que salio es igual a 0, 10, 20 o 30. */
        for(int j = 0; j < 4; j++){
            if(j*10 == num_ronda){
                multi_diez=1;
            }
        }

        /* Verifico segun el numero que salio si es del
        mismo color al de la ronda anterior y asi contar
        hasta superar cinco consecutivos. */
        if(color_ant == color_ronda(num_ronda)){
            color_cons++;
        }else{
            color_cons = 1;
            color_ant = color_ronda(num_ronda);
        }
        if(color_cons >= 5){
            coloresrepetidos=1;
        }

        /* Almacenamos las perdidas generadas en la ultima ronda. */
        perdida_parcial = perdidas_ronda(num_ronda, m_numeros, a_docenas, a_faltapasa, a_color, a_paridad, a_columnas);
        /* Almacenamos las ganancias generadas en la ultima ronda. */
        ganancia_parcial = ganancia_ronda(num_ronda, m_numeros, a_docenas, a_faltapasa, a_color, a_paridad, a_columnas);
        /* Almacenamos las perdidas totales generadas en la totalidad de las rondas. */
        perdida_total = perdida_total + perdida_parcial;
        /* Almacenamos las ganancias totales generadas en la totalidad de las rondas. */
        ganancia_total = ganancia_total + ganancia_parcial;

        printf("La ganancia de esta ronda es: %d \n",ganancia_parcial);
        printf("La perdida de esta ronda es: %d \n",perdida_parcial);

        /* Blanqueo de arrays y matriz para realizar la siguientes ronda.*/
        inicio_array(7, a_apuestas);
        inicio_array(18, a_docenas);
        inicio_array(12, a_faltapasa);
        inicio_array(12, a_color);
        inicio_array(12, a_paridad);
        inicio_array(18, a_columnas);
        inicio_array(37, numeros);

        for(int i = 0; i<37; i++){
            for(int j = 0; j<6; j++){
                m_numeros[i][j] = 0;
            }
        }
    }

    /* Calculo del promedio de apuestas por ronda. */
    prom_apuestas = total_apuestas/cantRonda;

    /* Calculo del porcentaje de apuestas por color*/
    sumatotalcolor= cant_color[0] + cant_color[1];
    if(sumatotalcolor == 0){
        cant_color[0] = 0;
        cant_color[1] = 0;
    }else{
        porcentaje_rojo = (float)(cant_color[0]*100)/sumatotalcolor;
        porcentaje_negro=100 - porcentaje_rojo;
    }

    printf("*************************************************************\n");
    printf(" Las rondas de esta mesa han terminado. \n");
    printf("*************************************************************\n");
    printf("Estadisticas: \n");
    printf("Ganancias Totales: %d\n",ganancia_total);
    printf("Perdidas Totales: %d\n",perdida_total);
    printf("*************************************************************\n");

    if(ganancia_total > perdida_total){
        printf("Mesa Ganadora!!!\n");
    }else{
        if(ganancia_total == perdida_total){
            printf("Mesa No Conforme\n");
        }else{
            printf("Mesa En Problemas ;)\n");
        }
    }

    printf("El promedio de apuestas por ronda es: %.2f\n",prom_apuestas);
    printf("La Mayor apuesta monetaria fue de %d en la ronda %d \n",apuestaMax,apuestaMaxNum);
    printf("El porcentaje de apuestas al rojo es de un %.2f mientras que el de negro es un %.2f\n",porcentaje_rojo,porcentaje_negro);
    if(coloresrepetidos==1){
        printf("Hubo mas de 5 ocasiones donde la bola cayo en el mismo color\n");
    }else{
        printf("No hubo mas de 5 ocasiones donde la bola cayo en el mismo color\n");
    }
    if(multi_diez==1){
        printf("Salio en las rondas el 0 (cero) o numeros multiplos de 10 (diez)\n");
    }else{
        printf("Nunca salio en las rondas el 0 (cero) o numeros multiplos de 10 (diez).\n");
    }
    printf("La cantidad de veces que la bola cayo en un numero primo es: %d\n",cant_primos);

    return 0;
}

/* Se utiliza para poner en 0 a un array.       */
/* Argumento:   int longitud: Tamaño del array. */
/*              int a[]: Array a blanquear.     */
/* Retorna:     void                            */
void inicio_array(int longitud, int a[]){

    for(int i = 0; i< longitud; i++){
        a[i]=0;
    }
}

/* Se utiliza para simular el lanzamiento       */
/* de la bola.                                  */
/* Argumento:   void                            */
/* Retorna:     Entero entre 0 y 36             */
int lanzamiento(void){
    return rand()%37;
}

/* Se utiliza para saber el color en el paño    */
/* del numero que se le paso como argumento.    */
/* Argumento:   Entero numero que salio.        */
/* Retorna:     0=VERDE, 1=ROJO, 2=NEGRO        */
int color_ronda(int num){
    int aux_u = 0;
    int aux_d = 0;

    if(num == 0) return VERDE;

    if(num == 10 || num == 28){
        return NEGRO;
    }

    while(num > 9){
        aux_d = num/10;
        num = aux_d + aux_u;
    }

    if(num%2==0){
        return NEGRO;
    }else{
        return ROJO;
    }
}

/* Se utiliza para saber el numero corresponde  */
/* a falta o pasa.                              */
/* Argumento:   Entero numero que salio.        */
/* Retorna:     0=False, 1=Falta, 2=Pasa        */
int pasa_falta(int num){

    if(num > 0 && num < 19){
        return FALTA;
    }else{
        if(num > 18 && num < 37){
            return PASA;
        }
    }

    return FALSE;
}

/* Se utiliza para saber el numero corresponde  */
/* a las docenas 1, 2 y 3.                      */
/* Argumento:   Entero numero que salio.        */
/* Retorna:     0= 1 Doc, 1= 2 Doc, 2= 3 Doc.   */
int docenas(int num){

    if(num > 0 && num < 13){
        return DOCENA1;
    }else{
        if(num > 12 && num < 25){
            return DOCENA2;
        }else{
            if(num > 24 && num < 37){
                return DOCENA3;
            }
        }
    }

    return FALSE;
}

/* Se utiliza para saber el numero corresponde  */
/* a las columnas 1, 2 y 3.                     */
/* Argumento:   Entero numero que salio.        */
/* Retorna:     0= 1 Doc, 1= 2 Doc, 2= 3 Doc.   */
int columnas(int num){

    int col1 = 0;
    int col2 = 0;
    int col3 = 0;

    for(int col1 = 1; col1 < 37; col1=col1+3){

        col2 = col1 + 1;
        col3 = col1 + 2;

        if(num == col1){
            return COLUMNA1;
        }else{
            if(num == col2){
                return COLUMNA2;
            }else{
                if(num == col3){
                    return COLUMNA3;
                }
            }
        }
    }

    return FALSE;
}

/* Se utiliza para saber el numero corresponde  */
/* a los pares e impares.                       */
/* Argumento:   Entero numero que salio.        */
/* Retorna:     0= False, 1= Impar, 2= Par.     */
int paridad(int num){

    int aux = num % 2;

    if(num == 0){
        return FALSE;
    }else{
        if(aux == 0){
            return PAR;
        }else{
            return IMPAR;
        }
    }
}

/* Se utiliza para saber si el numero es primo  */
/* Argumento:   Entero numero que salio.        */
/* Retorna:     0= No primo, 1= Primo.          */
int num_primo(int numronda){
    int aux= numronda-1;
    while(aux > 1){
        if((numronda%aux) == 0){
            return 0;
        }
        aux--;
    }
    return 1;
}

/* Se utiliza para mostrar los diferentes menues.   */
/* Argumento:   Entero numero de menu.              */
/* Retorna:     void                                */
void imprimir_menues(int prin){

    switch(prin){
    case 0:
        printf("\n");
        printf("Seleccione apuesta:");
        printf("\n");
        printf("1-Numeros Plenos");
        printf("\n");
        printf("2-Docenas");
        printf("\n");
        printf("3-Falta/Pasa");
        printf("\n");
        printf("4-Color");
        printf("\n");
        printf("5-Pares e Impares");
        printf("\n");
        printf("6-Columnas");
        printf("\n");
        printf("7-Finalizar Apuesta");
        printf("\n");
        printf("Ingrese el tipo de apuesta a realizar: ");
        printf("\n");
        break;

    case 1:
        printf("\n");
        printf("Numeros Plenos");
        printf("\n");
        printf("Ingrese el numero a apostar: ");
        printf("\n");
        break;
    case 2:
        printf("\n");
        printf("Docenas");
        printf("\n");
        printf("1-Primera docena");
        printf("\n");
        printf("2-Segunda docena");
        printf("\n");
        printf("3-Tercera docena");
        printf("\n");
        printf("Ingrese la docena a apostar: ");
        printf("\n");
        break;
    case 3:
        printf("\n");
        printf("Falta/Pasa");
        printf("\n");
        printf("1-Falta");
        printf("\n");
        printf("2-Pasa");
        printf("\n");
        printf("Ingrese el valor correspondiente: ");
        printf("\n");
        break;
    case 4:
        printf("\n");
        printf("Color");
        printf("\n");
        printf("1-Rojo");
        printf("\n");
        printf("2-Negro");
        printf("\n");
        break;
    case 5:
        printf("\n");
        printf("Paridad");
        printf("\n");
        printf("1-Par");
        printf("\n");
        printf("2-Impar");
        printf("\n");
        break;
    case 6:
        printf("\n");
        printf("Columnas");
        printf("\n");
        printf("1-Columna del 1");
        printf("\n");
        printf("2-Columna del 2");
        printf("\n");
        printf("3-Columna del 3");
        printf("\n");
        break;

    case 7:
        printf("Ingrese la cantidad de fichas a apostar: ");
        printf("\n");
        break;

    case 8:
        printf("Ingrese el valor de cada ficha: ");
        printf("\n");
        printf("1-Ficha de valor 1");
        printf("\n");
        printf("2-Ficha de valor 2");
        printf("\n");
        printf("3-Ficha de valor 5");
        printf("\n");
        printf("4-Ficha de valor 10");
        printf("\n");
        printf("5-Ficha de valor 50");
        printf("\n");
        printf("6-Ficha de valor 100");
        printf("\n");
        break;
    }
}

/* Se utiliza armar el array de apuestas para   */
/* saber con que casilla trabajamos.            */
/* Argumento:   int AA[] ,int n[]               */
/* Retorna:     void.                           */
void seleccion_apuestas(int AA[],int n[]){
    int aux=-1;
    int aux_ap=0;

        do{
            imprimir_menues(MENUPRINC);
            scanf("%d",&aux);
            if((aux<1) || (aux>7) ){
                printf("\nIngrese un valor comprendido entre 1 y 7.\n");
            }
        }while((aux<1) || (aux>7));

        switch(aux){
            case 1:
                do{
                    imprimir_menues(MENUNUM);
                    scanf("%d",&AA[1]);
                }while((AA[1]<0) || (AA[1]>36));

                if((AA[1]<0) || (AA[1]>36)){
                    printf("\n");
                    printf("Al estar fuera de rango, su apuesta no sera tomada en cuenta");
                    printf("\n");
                }else{
                    n[AA[1]]= 1;
                    AA[0]= 1;
                }
            break;

            case 2:
                do{
                    imprimir_menues(MENUDOC);
                    scanf("%d",&aux_ap);
                    if((aux_ap<0)|| (aux_ap>3)){
                        printf("\nPor favor, ingrese un valor dentro del rango\n");
                    }else{

                        AA[2] = aux_ap; // acumulo el valor ingresado a la apuesta de docenas
                        AA[0]= 2;
                    }

                }while((aux_ap<0)|| (aux_ap>3));
                break;
            case 3:
                do{
                    imprimir_menues(MENUFP);
                    scanf("%d",&aux_ap);
                    if((aux_ap<0)|| (aux_ap>2)){
                        printf("\nPor favor, ingrese un valor dentro del rango\n");
                    }else{
                        AA[3] = aux_ap;
                        AA[0]= 3;
                    }
                }while((aux_ap<0)|| (aux_ap>2));
                break;
            case 4:
                do{
                    imprimir_menues(MENUCOLOR);
                    scanf("%d",&aux_ap);
                    if((aux_ap<0)|| (aux_ap>2)){
                        printf("\nPor favor, ingrese un valor dentro del rango\n");
                    }else{
                        AA[4]= aux_ap;
                        AA[0]= 4;
                    }
                }while((aux_ap<0)|| (aux_ap>2));
                break;
            case 5:
                do{
                    imprimir_menues(MENUPAR);
                    scanf("%d",&aux_ap);
                    if((aux_ap<0)|| (aux_ap>2)){
                        printf("\nPor favor, ingrese un valor dentro del rango\n");
                    }else{
                        AA[5]= aux_ap;
                        AA[0]= 5;
                    }
                }while((aux_ap<0)|| (aux_ap>2));
                break;
            case 6:
                do{
                    imprimir_menues(MENUCLM);
                    scanf("%d",&aux_ap);
                    if((aux_ap<0)|| (aux_ap>3)){
                        printf("\nPor favor, ingrese un valor dentro del rango\n");
                    }else{

                        AA[6]= aux_ap;
                        AA[0]= 6;

                    }
                }while((aux_ap<0)|| (aux_ap>3));
                break;

            case 7:
                AA[0] = 0;
                break;
        }
}

/* Se utiliza saber si hay apuestas dobles con  */
/* el mismo valor monetario.                    */
/* Argumento:   int af[] ,int ac[] int ap[]     */
/* Retorna:     1 = Hay mismo valor, 0= Falso   */
int comp_apuestas_doble(int af[], int ac[], int ap[]){

    int dinero_falta = 0;
    int dinero_color = 0;
    int dinero_paridad = 0;

    for(int i = 0; i < 12; i++){

        switch(i){
            case 0:
            case 6:
                dinero_falta = dinero_falta + af[i];
                dinero_color = dinero_color + ac[i];
                dinero_paridad = dinero_paridad + ap[i];
            break;

            case 1:
            case 7:
                dinero_falta = dinero_falta + af[i]*2;
                dinero_color = dinero_color + ac[i]*2;
                dinero_paridad = dinero_paridad + ap[i]*2;
            break;

            case 2:
            case 8:
                dinero_falta = dinero_falta + af[i]*5;
                dinero_color = dinero_color + ac[i]*5;
                dinero_paridad = dinero_paridad + ap[i]*5;
            break;

            case 3:
            case 9:
                dinero_falta = dinero_falta + af[i]*10;
                dinero_color = dinero_color + ac[i]*10;
                dinero_paridad = dinero_paridad + ap[i]*10;
            break;

            case 4:
            case 10:
                dinero_falta = dinero_falta + af[i]*50;
                dinero_color = dinero_color + ac[i]*50;
                dinero_paridad = dinero_paridad + ap[i]*50;
            break;

            case 5:
            case 11:
                dinero_falta = dinero_falta + af[i]*100;
                dinero_color = dinero_color + ac[i]*100;
                dinero_paridad = dinero_paridad + ap[i]*100;
            break;
        }

    }

    if(dinero_falta == dinero_color && dinero_falta != 0 && dinero_color != 0){
        return 1;
    }else{
        if(dinero_falta == dinero_paridad && dinero_falta != 0 && dinero_paridad != 0){
            return 1;
        }else{
            if(dinero_color == dinero_paridad && dinero_color != 0 && dinero_paridad != 0){
                return 1;
            }
        }
    }

    return 0;
}

/* Se utiliza para cargar las fichas y valores, */
/* en las casillas correspondientes.            */
/* Argumento:   int indice, int aa[],int ad[18], int af[12], int ac[12], int ap[12], int acol[18],int mnum[37][6], int cantcolor[] */
/* Retorna:     void                            */
void seleccionfichas(int indice, int aa[],int ad[18], int af[12], int ac[12], int ap[12], int acol[18],int mnum[37][6], int cantcolor[]){

    int aux = 0;
    int aux_ficha=0;
    int aux_comp =0;

    switch(aa[0]){
        case 1: //números
            do{
                imprimir_menues(7);
                scanf("%d", &aux);
                if(aux<0){
                    printf("Ingrese un valor positivo\n");
                }
            }while(aux<0);

            do{
                imprimir_menues(8);
                scanf("%d", &aux_ficha);
            }while(aux_ficha < 1 || aux_ficha > 6);
            mnum[aa[1]][aux_ficha-1] = mnum[aa[1]][aux_ficha-1] + aux;
        break;

        case 2: //Docenas
            do{
                imprimir_menues(7);
                scanf("%d", &aux);
                if(aux<0){
                    printf("Ingrese un valor positivo\n");
                }
            }while(aux<0);
            do{
                imprimir_menues(8);
                scanf("%d", &aux_ficha);
            }while(aux_ficha < 1 || aux_ficha > 6);

            if(aa[2] == 1){
                ad[aux_ficha-1] = ad[aux_ficha-1] + aux;
            }else{
                if(aa[2] == 2){
                    ad[aux_ficha+6-1] = ad[aux_ficha+6-1] + aux;
                }else{
                    if(aa[2]== 3){
                        ad[aux_ficha+12-1] = ad[aux_ficha+12-1] + aux;
                    }
                }
            }
        break;

        case 3: //Falta Pasa
            do{
                imprimir_menues(7);
                scanf("%d", &aux);
                if(aux<0){
                    printf("Ingrese un valor positivo\n");
                }
            }while(aux<0);
            do{
                imprimir_menues(8);
                scanf("%d", &aux_ficha);
            }while(aux_ficha < 1 || aux_ficha > 6);
            //compara apuestas dobles para saber si existen dos con el mismo valor monetario
            aux_comp = comp_apuestas_doble(af, ac, ap);
            if(aux_comp == 1){
                printf("Esta apuesta no sera tomada en cuenta.\n");
                printf("Porque no se permite apostar la misma cantidad de dinero a apuestas que pagan doble.\n");
            }else{
                if(aa[3] == 1){
                    af[aux_ficha-1] = af[aux_ficha-1] + aux;
                }else{
                    if(aa[3] == 2){
                        af[aux_ficha+6-1] = af[aux_ficha+6-1] + aux;
                    }
                }
            }

        break;

        case 4: //Color
            do{
                imprimir_menues(7);
                scanf("%d", &aux);
                if(aux<0){
                    printf("Ingrese un valor positivo\n");
                }
            }while(aux<0);
            do{
                imprimir_menues(8);
                scanf("%d", &aux_ficha);
            }while(aux_ficha < 1 || aux_ficha > 6);

            aux_comp = comp_apuestas_doble(af, ac, ap);
            if(aux_comp == 1){
                printf("Esta apuesta no sera tomada en cuenta.\n");
                printf("Porque no se permite apostar la misma cantidad de dinero a apuestas que pagan doble.\n");
            }else{

                if(aa[4] == 1){ //rojo
                    ac[aux_ficha-1] = ac[aux_ficha-1] + aux;
                    cantcolor[0]++;
                }else{
                    if(aa[4]==2){ //negro
                        ac[aux_ficha+6-1] = ac[aux_ficha+6-1] + aux;
                        cantcolor[1]++;
                    }
                }
            }

        break;

        case 5: //Paridad
            do{
                imprimir_menues(7);
                scanf("%d", &aux);
                if(aux<0){
                    printf("Ingrese un valor positivo\n");
                }
            }while(aux<0);
            do{
                imprimir_menues(8);
                scanf("%d", &aux_ficha);
            }while(aux_ficha < 1 || aux_ficha > 6);
            aux_comp = comp_apuestas_doble(af, ac, ap);
            if(aux_comp == 1){
                printf("Esta apuesta no sera tomada en cuenta.\n");
                printf("Porque no se permite apostar la misma cantidad de dinero a apuestas que pagan doble.\n");
            }else{

                if(aa[5] == 1){ //impar
                    ap[aux_ficha-1] = ap[aux_ficha-1] + aux;
                }else{
                    if(aa[5]==2){ //par
                        ap[aux_ficha+6-1] = ap[aux_ficha+6-1] + aux;
                    }
                }
            }
        break;

        case 6: //Columnas
            do{
                imprimir_menues(7);
                scanf("%d", &aux);
                if(aux<0){
                    printf("Ingrese un valor positivo\n");
                }
            }while(aux<0);
            do{
                imprimir_menues(8);
                scanf("%d", &aux_ficha);
            }while(aux_ficha < 1 || aux_ficha > 6);

            if(aa[6] == 1){
                acol[aux_ficha-1] = acol[aux_ficha-1] + aux;
            }else{
                if(aa[6] == 2){
                    acol[aux_ficha+6-1] = acol[aux_ficha+6-1] + aux;
                }else{
                    if(aa[6]== 3){
                        acol[aux_ficha+12-1] = acol[aux_ficha+12-1] + aux;
                    }
                }
            }
        break;

    }

}

/* Se utiliza para sumar las apuestas de        */
/* la ronda.                                    */
/* Argumento:   int ad[], int af[], int ac[], int ap[], int acol[],int mnum[37][6] */
/* Retorna:     la suma de las apuestas         */
int suma_apuesta(int ad[], int af[], int ac[], int ap[], int acol[],int mnum[37][6]){
    int aux_total=0;
    for(int i = 0; i<18; i++){
        switch(i){
            case 0:
            case 6:
            case 12:
                aux_total = aux_total + ad[i];
                aux_total = aux_total + acol[i];
            break;

            case 1:
            case 7:
            case 13:
                aux_total = aux_total + ad[i]*2;
                aux_total = aux_total + acol[i]*2;
            break;

            case 2:
            case 8:
            case 14:
                aux_total = aux_total + ad[i]*5;
                aux_total = aux_total + acol[i]*5;
            break;

            case 3:
            case 9:
            case 15:
                aux_total = aux_total + ad[i]*10;
                aux_total = aux_total + acol[i]*10;
            break;

            case 4:
            case 10:
            case 16:
                aux_total = aux_total + ad[i]*50;
                aux_total = aux_total + acol[i]*50;
            break;

            case 5:
            case 11:
            case 17:
                aux_total = aux_total + ad[i]*100;
                aux_total = aux_total + acol[i]*100;
            break;
        }
    }

    for(int i = 0; i<12; i++){
        switch(i){
            case 0:
            case 6:
                aux_total = aux_total + af[i];
                aux_total = aux_total + ac[i];
                aux_total = aux_total + ap[i];
            break;

            case 1:
            case 7:
                aux_total = aux_total + af[i]*2;
                aux_total = aux_total + ac[i]*2;
                aux_total = aux_total + ap[i]*2;
            break;

            case 2:
            case 8:
                aux_total = aux_total + af[i]*5;
                aux_total = aux_total + ac[i]*5;
                aux_total = aux_total + ap[i]*5;
            break;

            case 3:
            case 9:
                aux_total = aux_total + af[i]*10;
                aux_total = aux_total + ac[i]*10;
                aux_total = aux_total + ap[i]*10;
            break;

            case 4:
            case 10:
                aux_total = aux_total + af[i]*50;
                aux_total = aux_total + ac[i]*50;
                aux_total = aux_total + ap[i]*50;
            break;

            case 5:
            case 11:
                aux_total = aux_total + af[i]*100;
                aux_total = aux_total + ac[i]*100;
                aux_total = aux_total + ap[i]*100;
            break;
        }
    }

    for(int i = 0; i < 37; i++){
        for(int j = 0; j < 6; j++){

            switch(j){
                case 0:
                    aux_total = aux_total + mnum[i][j];
                break;

                case 1:
                    aux_total = aux_total + mnum[i][j]*2;
                break;

                case 2:
                    aux_total = aux_total + mnum[i][j]*5;
                break;

                case 3:
                    aux_total = aux_total + mnum[i][j]*10;
                break;

                case 4:
                    aux_total = aux_total + mnum[i][j]*50;
                break;

                case 5:
                    aux_total = aux_total + mnum[i][j]*100;
                break;
            }

        }
    }

    return aux_total;
}

/* Se utiliza para administrar las apuestas.        */
/* Argumento:   los arrays de cada apuesta          */
/* Retorna:     la cantidad de apuestas por ronda   */
int apuestas(int ad[], int af[], int ac[], int ap[], int acol[],int mnum[37][6], int aa[], int n[], int cantcolor[]){
    //posicion 7 de aa es la apuesta mas grande hasta el momento
    char flag = ' ';
    int cant_ap = 0;
    int aux_t_apuestas = 0;
    int max_apuesta =0;

    do{
        do{
            seleccion_apuestas(aa,n);
            if(aa[0]!=0){
                seleccionfichas(cant_ap, aa, ad, af, ac, ap, acol, mnum, cantcolor);
            }
        }while(aa[0]!=0);

        aux_t_apuestas = suma_apuesta(ad, af, ac, ap, acol,mnum);
        max_apuesta = aux_t_apuestas - max_apuesta;
        if(max_apuesta > aa[7]){
            aa[7] = max_apuesta;
        }

        cant_ap++;
        printf("Le restan %d apuestas de 10\n", (10-cant_ap));
        if(cant_ap == 10){
            printf("No quedan apuestas por realizar, comenzara la ronda\n");
            do{
                printf("Presione la tecla C para continuar...\n");
                scanf("%s",&flag);
            }while(flag != 'c' || flag != 'C');
        }else{
            printf("Desea realizar otra apuesta? S/N\n");
            scanf("%s",&flag);
        }

    }while((flag == 's' || flag == 'S') && cant_ap < 10);

    return cant_ap;
}

/* Se utiliza para contar las perdidas                 */
/* correspondientes a las docenas.                     */
/* Argumento:   numero de ronda y array de docenas     */
/* Retorna:     perdidas de docenas                    */
int perdidas_doc(int numronda, int ad[]){

    int perdidas = 0;
    int docena = docenas(numronda);

    for(int i = 0; i<6; i++){

        if(docena == 1){

            if(ad[i]!=0 ){
                switch(i){
                    case 0:
                        perdidas = perdidas + ad[i]*3;
                    break;
                    case 1:
                        perdidas = perdidas + ad[i]*2*3;
                    break;
                    case 2:
                        perdidas = perdidas + ad[i]*5*3;
                    break;
                    case 3:
                        perdidas = perdidas + ad[i]*10*3;
                    break;
                    case 4:
                        perdidas = perdidas + ad[i]*50*3;
                    break;
                    case 5:
                        perdidas = perdidas + ad[i]*100*3;
                    break;
                }

            }

        }

        if(docena == 2){
            int i_aux = i+6;
            if(ad[i_aux]!=0 ){
                switch(i){
                    case 0:
                        perdidas = perdidas + ad[i_aux]*3;
                    break;
                    case 1:
                        perdidas = perdidas + ad[i_aux]*2*3;
                    break;
                    case 2:
                        perdidas = perdidas + ad[i_aux]*5*3;
                    break;
                    case 3:
                        perdidas = perdidas + ad[i_aux]*10*3;
                    break;
                    case 4:
                        perdidas = perdidas + ad[i_aux]*50*3;
                    break;
                    case 5:
                        perdidas = perdidas + ad[i_aux]*100*3;
                    break;
                }

            }

        }

        if(docena == 3){
            int i_aux = i+12;

            //printf("el valor de i_aux es %d y el valor ad[i_aux] %d",i_aux,ad[i_aux]);
            if(ad[i_aux]!=0 ){
                switch(i){
                    case 0:
                        perdidas = perdidas + ad[i_aux]*3;
                    break;
                    case 1:
                        perdidas = perdidas + ad[i_aux]*2*3;
                    break;
                    case 2:
                        perdidas = perdidas + ad[i_aux]*5*3;
                    break;
                    case 3:
                        perdidas = perdidas + ad[i_aux]*10*3;
                    break;
                    case 4:
                        perdidas = perdidas + ad[i_aux]*50*3;
                    break;
                    case 5:
                        perdidas = perdidas + ad[i_aux]*100*3;
                    break;
                }

            }
        }
    }

    return perdidas;

}

/* Se utiliza para contar las perdidas                 */
/* correspondientes a las falta pasa.                  */
/* Argumento:   numero de ronda y array de falta pasa  */
/* Retorna:     perdidas de falta pasa                 */
int perdidas_falta_pasa(int numronda, int af[]){

    int perdidas = 0;
    int falta_pasa = pasa_falta(numronda);

    for(int i = 0; i<6; i++){

        if(falta_pasa == 1){

            if(af[i]!=0 ){
                switch(i){
                    case 0:
                        perdidas = perdidas + af[i]*2;
                    break;
                    case 1:
                        perdidas = perdidas + af[i]*2*2;
                    break;
                    case 2:
                        perdidas = perdidas + af[i]*5*2;
                    break;
                    case 3:
                        perdidas = perdidas + af[i]*10*2;
                    break;
                    case 4:
                        perdidas = perdidas + af[i]*50*2;
                    break;
                    case 5:
                        perdidas = perdidas + af[i]*100*2;
                    break;
                }
            }
        }

        if(falta_pasa == 2){
            int i_aux = i+6;
            if(af[i_aux]!=0 ){
                switch(i){
                    case 0:
                        perdidas = perdidas + af[i_aux]*2;
                    break;
                    case 1:
                        perdidas = perdidas + af[i_aux]*2*2;
                    break;
                    case 2:
                        perdidas = perdidas + af[i_aux]*5*2;
                    break;
                    case 3:
                        perdidas = perdidas + af[i_aux]*10*2;
                    break;
                    case 4:
                        perdidas = perdidas + af[i_aux]*50*2;
                    break;
                    case 5:
                        perdidas = perdidas + af[i_aux]*100*2;
                    break;
                }

            }

        }

    }

    return perdidas;

}

/* Se utiliza para contar las perdidas                 */
/* correspondientes a color.                           */
/* Argumento:   numero de ronda y array de color       */
/* Retorna:     perdidas de color                      */
int perdidas_color(int numronda, int ac[]){

    int perdidas = 0;
    int color = color_ronda(numronda);

    for(int i = 0; i<6; i++){
        //for(int k = 0; k<12; k++){
        //    printf("\nac[i]= %d y i es %d \n",ac[k],k);
        //}
        if(color == 1){

            if(ac[i]!=0 ){

                switch(i){
                    case 0:
                        perdidas = perdidas + ac[i]*2;
                    break;
                    case 1:
                        perdidas = perdidas + ac[i]*2*2;
                    break;
                    case 2:
                        perdidas = perdidas + ac[i]*5*2;
                    break;
                    case 3:
                        perdidas = perdidas + ac[i]*10*2;
                    break;
                    case 4:
                        perdidas = perdidas + ac[i]*50*2;
                    break;
                    case 5:
                        perdidas = perdidas + ac[i]*100*2;
                    break;
                }

            }

        }

        if(color == 2){
            int i_aux = i+6;
            if(ac[i_aux]!=0 ){
                switch(i){
                    case 0:
                        perdidas = perdidas + ac[i_aux]*2;
                    break;
                    case 1:
                        perdidas = perdidas + ac[i_aux]*2*2;
                    break;
                    case 2:
                        perdidas = perdidas + ac[i_aux]*5*2;
                    break;
                    case 3:
                        perdidas = perdidas + ac[i_aux]*10*2;
                    break;
                    case 4:
                        perdidas = perdidas + ac[i_aux]*50*2;
                    break;
                    case 5:
                        perdidas = perdidas + ac[i_aux]*100*2;
                    break;
                }

            }

        }

    }

    return perdidas;

}

/* Se utiliza para contar las perdidas                 */
/* correspondientes a par o impar.                     */
/* Argumento:   numero de ronda y array de paridad     */
/* Retorna:     perdidas de par o impar                */
int perdidas_paridad(int numronda, int ap[]){

    int perdidas = 0;
    int par = paridad(numronda);

    for(int i = 0; i<6; i++){

        if(par == 1){

            if(ap[i]!=0 ){
                switch(i){
                    case 0:
                        perdidas = perdidas + ap[i]*2;
                    break;
                    case 1:
                        perdidas = perdidas + ap[i]*2*2;
                    break;
                    case 2:
                        perdidas = perdidas + ap[i]*5*2;
                    break;
                    case 3:
                        perdidas = perdidas + ap[i]*10*2;
                    break;
                    case 4:
                        perdidas = perdidas + ap[i]*50*2;
                    break;
                    case 5:
                        perdidas = perdidas + ap[i]*100*2;
                    break;
                }

            }

        }

        if(par == 2){
            int i_aux = i+6;
            if(ap[i_aux]!=0 ){
                switch(i){
                    case 0:
                        perdidas = perdidas + ap[i_aux]*2;
                    break;
                    case 1:
                        perdidas = perdidas + ap[i_aux]*2*2;
                    break;
                    case 2:
                        perdidas = perdidas + ap[i_aux]*5*2;
                    break;
                    case 3:
                        perdidas = perdidas + ap[i_aux]*10*2;
                    break;
                    case 4:
                        perdidas = perdidas + ap[i_aux]*50*2;
                    break;
                    case 5:
                        perdidas = perdidas + ap[i_aux]*100*2;
                    break;
                }

            }

        }


    }

    return perdidas;

}

/* Se utiliza para contar las perdidas                 */
/* correspondientes a las columnas.                    */
/* Argumento:   numero de ronda y array de columnas    */
/* Retorna:     perdidas de columnas                   */
int perdidas_columnas(int numronda, int acol[]){

    int perdidas = 0;
    int columna = columnas(numronda);

    for(int i = 0; i<6; i++){

        if(columna == 1){

            if(acol[i]!=0 ){
                switch(i){
                    case 0:
                        perdidas = perdidas + acol[i]*3;
                    break;
                    case 1:
                        perdidas = perdidas + acol[i]*2*3;
                    break;
                    case 2:
                        perdidas = perdidas + acol[i]*5*3;
                    break;
                    case 3:
                        perdidas = perdidas + acol[i]*10*3;
                    break;
                    case 4:
                        perdidas = perdidas + acol[i]*50*3;
                    break;
                    case 5:
                        perdidas = perdidas + acol[i]*100*3;
                    break;
                }

            }

        }

        if(columna == 2){
            int i_aux = i+6;
            if(acol[i_aux]!=0 ){
                switch(i){
                    case 0:
                        perdidas = perdidas + acol[i_aux]*3;
                    break;
                    case 1:
                        perdidas = perdidas + acol[i_aux]*2*3;
                    break;
                    case 2:
                        perdidas = perdidas + acol[i_aux]*5*3;
                    break;
                    case 3:
                        perdidas = perdidas + acol[i_aux]*10*3;
                    break;
                    case 4:
                        perdidas = perdidas + acol[i_aux]*50*3;
                    break;
                    case 5:
                        perdidas = perdidas + acol[i_aux]*100*3;
                    break;
                }

            }

        }

        if(columna == 3){
            int i_aux = i+12;
            if(acol[i_aux]!=0 ){
                switch(i){
                    case 0:
                        perdidas = perdidas + acol[i_aux]*3;
                    break;
                    case 1:
                        perdidas = perdidas + acol[i_aux]*2*3;
                    break;
                    case 2:
                        perdidas = perdidas + acol[i_aux]*5*3;
                    break;
                    case 3:
                        perdidas = perdidas + acol[i_aux]*10*3;
                    break;
                    case 4:
                        perdidas = perdidas + acol[i_aux]*50*3;
                    break;
                    case 5:
                        perdidas = perdidas + acol[i_aux]*100*3;
                    break;
                }

            }

        }

    }

    return perdidas;

}

/* Se utiliza para contar las perdidas                 */
/* correspondientes a los numeros.                     */
/* Argumento:   numero de ronda y matriz numeros       */
/* Retorna:     perdidas de numeros                    */
int perdidas_numeros(int numronda, int mnum[37][6]){

    int perdidas = 0;

    for(int i = 0; i < 37; i++){
        for(int j = 0; j < 6; j++){
            //printf("bola: %d ",numronda);
            if(mnum[i][j]!=0 && i==numronda){
                switch(j){
                    case 0:
                        perdidas = perdidas + mnum[i][j]*35;
                    break;
                    case 1:
                        perdidas = perdidas + mnum[i][j]*2*35;
                    break;
                    case 2:
                        perdidas = perdidas + mnum[i][j]*5*35;
                    break;
                    case 3:
                        perdidas = perdidas + mnum[i][j]*10*35;
                    break;
                    case 4:
                        perdidas = perdidas + mnum[i][j]*50*35;
                    break;
                    case 5:
                        perdidas = perdidas + mnum[i][j]*100*35;
                    break;
                }
            }
        }
    }
    return perdidas;
}

/* Se utiliza para contar las perdidas                      */
/* totales a la ronda.                                      */
/* Argumento:   num de bola y las arrays de las apuestas    */
/* Retorna:     perdidas totales de la ronda                */
int perdidas_ronda(int numronda, int mnum[37][6], int ad[], int af[], int ac[], int ap[], int acol[]){

    int perdidas = 0;

    perdidas = perdidas + perdidas_numeros(numronda, mnum);
    perdidas = perdidas + perdidas_doc(numronda, ad);
    perdidas = perdidas + perdidas_falta_pasa(numronda, af);
    perdidas = perdidas + perdidas_color(numronda, ac);
    perdidas = perdidas + perdidas_paridad(numronda, ap);
    perdidas = perdidas + perdidas_columnas(numronda, acol);

    return perdidas;
}

/* Se utiliza para contar las ganancias                     */
/* por casilla y la retorna.                                */
/* Argumento:   tipo:   1:  docena
                        2:  falta pasa
                        3:  color
                        4:  par
                        5:  columna
                        6:  numero
                numero de bola, array correspondiente a la
                apuesta a evaluar, matriz de numeros        */
/* Retorna:     ganancia de la casilla                      */
int ganancia_apuesta(int tipo, int numronda, int array[], int mnum[37][6]){

    int apuesta = 0;
    int subcant = 0;
    int ganancia = 0;

    if(tipo == 1){
        apuesta = docenas(numronda);
        subcant = 3;
    }

    if(tipo == 2){
        apuesta = pasa_falta(numronda);
        subcant = 2;
    }

    if(tipo == 3){
        apuesta = color_ronda(numronda);
        subcant = 2;
    }

    if(tipo == 4){
        apuesta = paridad(numronda);
        subcant = 2;
    }
    if(tipo == 5){
        apuesta = columnas(numronda);
        subcant = 3;
    }

    if(tipo == 6){
        for(int i = 0; i<37; i++){
            for(int j = 0; j<6; j++){
                if(i != numronda){
                    if(mnum[i][j]!=0){
                        switch(j){
                            case 0:
                                ganancia = ganancia + mnum[i][j];
                            break;
                            case 1:
                                ganancia = ganancia + mnum[i][j]*2;
                            break;
                            case 2:
                                ganancia = ganancia + mnum[i][j]*5;
                            break;
                            case 3:
                                ganancia = ganancia + mnum[i][j]*10;
                            break;
                            case 4:
                                ganancia = ganancia + mnum[i][j]*50;
                            break;
                            case 5:
                                ganancia = ganancia + mnum[i][j]*100;
                            break;
                        }
                    }
                }
            }
        }
    }

    if(subcant == 3){//

        for(int i = 0; i<6; i++){

            if(apuesta != 1){

                if(array[i]!=0 ){
                    switch(i){
                        case 0:
                            ganancia = ganancia + array[i];
                        break;
                        case 1:
                            ganancia = ganancia + array[i]*2;
                        break;
                        case 2:
                            ganancia = ganancia + array[i]*5;
                        break;
                        case 3:
                            ganancia = ganancia + array[i]*10;
                        break;
                        case 4:
                            ganancia = ganancia + array[i]*50;
                        break;
                        case 5:
                            ganancia = ganancia + array[i]*100;
                        break;
                    }

                }

            }

            if(apuesta != 2){
                int i_aux = i+6;
                if(array[i_aux]!=0 ){
                    switch(i){
                        case 0:
                            ganancia = ganancia + array[i_aux];
                        break;
                        case 1:
                            ganancia = ganancia + array[i_aux]*2;
                        break;
                        case 2:
                            ganancia = ganancia + array[i_aux]*5;
                        break;
                        case 3:
                            ganancia = ganancia + array[i_aux]*10;
                        break;
                        case 4:
                            ganancia = ganancia + array[i_aux]*50;
                        break;
                        case 5:
                            ganancia = ganancia + array[i_aux]*100;
                        break;
                    }
                }
            }

            if(apuesta != 3){
                int i_aux = i+12;
                if(array[i_aux]!=0 ){
                    switch(i){
                        case 0:
                            ganancia = ganancia + array[i_aux];
                        break;
                        case 1:
                            ganancia = ganancia + array[i_aux]*2;
                        break;
                        case 2:
                            ganancia = ganancia + array[i_aux]*5;
                        break;
                        case 3:
                            ganancia = ganancia + array[i_aux]*10;
                        break;
                        case 4:
                            ganancia = ganancia + array[i_aux]*50;
                        break;
                        case 5:
                            ganancia = ganancia + array[i_aux]*100;
                        break;
                    }

                }

            }

        }

    }

    if(subcant == 2){//

        for(int i = 0; i<6; i++){

            if(apuesta != 1){

                if(array[i]!=0 ){
                    switch(i){
                        case 0:
                            ganancia = ganancia + array[i];
                        break;
                        case 1:
                            ganancia = ganancia + array[i]*2;
                        break;
                        case 2:
                            ganancia = ganancia + array[i]*5;
                        break;
                        case 3:
                            ganancia = ganancia + array[i]*10;
                        break;
                        case 4:
                            ganancia = ganancia + array[i]*50;
                        break;
                        case 5:
                            ganancia = ganancia + array[i]*100;
                        break;
                    }

                }

            }

            if(apuesta != 2){
                int i_aux = i+6;
                if(array[i_aux]!=0 ){
                    switch(i){
                        case 0:
                            ganancia = ganancia + array[i_aux];
                        break;
                        case 1:
                            ganancia = ganancia + array[i_aux]*2;
                        break;
                        case 2:
                            ganancia = ganancia + array[i_aux]*5;
                        break;
                        case 3:
                            ganancia = ganancia + array[i_aux]*10;
                        break;
                        case 4:
                            ganancia = ganancia + array[i_aux]*50;
                        break;
                        case 5:
                            ganancia = ganancia + array[i_aux]*100;
                        break;
                    }
                }
            }
        }
    }
    return ganancia;
}

/* Se utiliza para contar las ganancias                     */
/* totales por ronda.                                       */
/* Argumento:   numero de bola, matriz de numeros
                array correspondiente a la
                apuesta a evaluar.                          */
/* Retorna:     ganancia total de la ronda                  */
int ganancia_ronda(int numronda, int mnum[37][6], int ad[], int af[], int ac[], int ap[], int acol[]){

    int ganancia = 0;
    ganancia = ganancia + ganancia_apuesta(1, numronda, ad, mnum);
    ganancia = ganancia + ganancia_apuesta(2, numronda, af, mnum);
    ganancia = ganancia + ganancia_apuesta(3, numronda, ac, mnum);
    ganancia = ganancia + ganancia_apuesta(4, numronda, ap, mnum);
    ganancia = ganancia + ganancia_apuesta(5, numronda, acol, mnum);
    ganancia = ganancia + ganancia_apuesta(6, numronda, ad, mnum);

    return ganancia;
}
