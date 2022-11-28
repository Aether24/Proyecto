// Proyecto.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <time.h>
#include <string.h>


void HideCursor();          // Ocultar el cursor
void gotoxy(int x, int y);  // Posicionamiento del cursor

#define R 26                // El valor máximo de la coordenada x aleatoria de la aeronave cada vez
#define N 20                // Puntuación aduanera

int ax[3] = { 0 };          // Tres coordenadas de la cola del avión, global
int y[3] = { 3,7,11 };      // Método de tabla de consulta global de tres ejes y para determinar la posición del eje y de la aeronave   
                            // Debido a que la distancia de vuelo de la bala de cañón es agregar dos cuadrículas a la vez, el eje y aquí debe ser par para correspondencia impar y par
int i;                      // Variables de ciclo
int fd[3];                  // Controla el tipo de aeronave

void cshcxhs()                              // función de inicialización
{
    system("título de Juegos de Aviones");           //título
    system("mode con cols=100 lines=30");   // Ancho 100, altura 30
    HideCursor();                           // Ocultar el cursor

    gotoxy(46, 12);                         // Introduce las reglas del juego
    printf("reglas del juego:");
    gotoxy(36, 14);
    printf("Wad key para controlar la dirección, barra espaciadora para lanzar proyectiles");
    gotoxy(26, 16);
    printf("Golpea un avión enemigo | --- 0> Agrega un punto, golpea un avión amigo >>>>>> Reduce un punto");
    gotoxy(40, 18);
    printf("Puntuación acumulativa% d final del juego", N);
    Sleep(2800);

    system("cls");

    int k;                                  // Variables de ciclo
    gotoxy(40, R);                          // Inicializa la batería
    for (k = 0; k < 17; k++)
        printf("_");

    gotoxy(46, R);
    printf("[_O_]");
    gotoxy(48, 25);                         // Medio x: 48
    printf("|");

    int f;
    srand((unsigned)time(NULL));            // Inicializar semilla aleatoria
    for (f = 0; f < 3; f++)                 // Inicializa la coordenada x inicial de la aeronave, escrita fuera del bucle
    {
        ax[f] = rand() % R;
        fd[f] = rand() % 2;
    }

    gotoxy(0, R);
    printf("  Puntuación:");                    // fracción x coordenada 9
}

void hcfjhs()                       // Dibuja la función de avión
{
    gotoxy(ax[i], y[i]);            // Primero da salida a la aeronave completa en la cola de la aeronave

    if (fd[i] == 1)
        printf("|---0>");
    else
        printf(">>>>>>");

    gotoxy(ax[i] - 1, y[i]);        // Eliminar rastros que quedan detrás del avión
    printf(" ");

    ax[i]++;                        // Luego, las coordenadas de la cola del avión aumentarán automáticamente, y la próxima vez saldrá todo el plano desde la cola del avión.
}

void dhpdxshs()                    // Dibuja el avión y deja que desaparezca al volar sobre x94
{
    for (i = 0; i < 3; i++)         // Cada avión da un paso
    {
        hcfjhs();

        if (ax[i] + 6 >= 94)        // Determine si cada cabeza de avión excede 94
        {
            gotoxy(94, y[i]);       // Cumple la condición de salida de espacios en 94 lugares de cada avión
            printf("      ");
            if (ax[i] + 6 > 100)      // La cabeza de cada avión supera los 100, luego restablece un número aleatorio
            {
                ax[i] = rand() % R; // Modificar a un número aleatorio menor que R
                fd[i] = rand() % 2;
            }
        }
    }
}

int da = 2;           // da = 1 es la dirección de fortaleza media predeterminada más a la izquierda, variable global
int yip = 0;          // Si disparar el arma, 0 no se dispara, 1, 2, 3 direcciones
int rtde = 1;         // Ya sea que se complete el lanzamiento, debe esperar el lanzamiento del shell


int shells_x;         // Coordenadas de bala de cañón
int shells_y;

void ckkzhs()
{
    char ch;
    ch = _getch();

    if (ch == 'd' || ch == 'D')
    {
        gotoxy(49, 25);
        printf("/");                // Gira a la derecha en la batería
        gotoxy(47, 25);
        printf("  ");
        da = 3;                     // Estado más a la derecha
    }
    if (ch == 'A' || ch == 'a')
    {
        gotoxy(47, 25);
        printf("\\");               // Escapar del personaje de escape
        gotoxy(48, 25);
        printf("  ");
        da = 1;                     // Estado más a la izquierda
    }
    if (ch == 'W' || ch == 'w')
    {
        gotoxy(48, 25);
        printf("|");
        gotoxy(47, 25);
        printf(" ");
        gotoxy(49, 25);
        printf(" ");
        da = 2;
    }

    if (ch == ' ' && rtde == 0)      // El cañón está en estado de finalización de lanzamiento y presiona la barra espaciadora
    {
        if (da == 2)                // Orientación de la batería media
            yip = 2;

        if (da == 1)                //izquierda
        {
            yip = 1;
            shells_x = 45;          // Inicializa las coordenadas del proyectil
        }
        if (da == 3)                //Derecha
        {
            yip = 3;
            shells_x = 51;
        }
        shells_y = 23;             // Inicializa las coordenadas del proyectil
    }
}

void dpfshs()                       // Proyectiles de fuego en tres direcciones diferentes
{
    rtde = 1;                       // Ciclo, cuando el proyectil se mueve, significa que no se dispara el arma.
    if (yip == 2)
    {
        shells_x = 48;
        gotoxy(shells_x, shells_y -= 2);
        printf("o");
        gotoxy(shells_x, shells_y + 2);
        printf(" ");
    }
    if (yip == 1)
    {
        gotoxy(shells_x -= 2, shells_y -= 2);
        printf("o");
        gotoxy(shells_x + 2, shells_y + 2);
        printf(" ");
    }
    if (yip == 3)
    {
        gotoxy(shells_x += 2, shells_y -= 2);
        printf("o");
        gotoxy(shells_x - 2, shells_y + 2);
        printf(" ");
    }

    if (shells_y <= 1)         // La bala de cañón cruza el límite y elimina la bala de cañón
    {
        yip = 0;               // El caparazón superó el límite, el caparazón se detuvo
        gotoxy(48, 1);         // Y eliminar
        printf(" ");
        gotoxy(23, 1);
        printf(" ");
        gotoxy(73, 1);
        printf(" ");
        rtde = 0;             // La bala de cañón cruza el límite, se completa el disparo y se puede llevar a cabo la siguiente ronda de disparos.
    }
}

int score;                  //Puntuación

void pdfsjzhs()             // determina si golpear y estadísticas
{

    for (i = 0; i < 3; i++)
    {
        if (shells_x >= ax[i] && shells_x <= ax[i] + 6 && shells_y == y[i])// Cuando se golpea
        {
            if (fd[i] == 1)
                score++;                        // Un golpe, más un puntaje
            else
            {
                score--;
                if (score <= 0)
                    score = 0;
            }

            rtde = 0;                       // Cuando golpeas, el disparo está completo

            gotoxy(ax[i] - 1, y[i]);          // Después de golpear, elimina el plano en la cola del plano original
            printf("      ");

            ax[i] = rand() % R;             // Modificar a un número aleatorio menor que 10
            fd[i] = rand() % 2;             // El tipo de aeronave ha cambiado

            gotoxy(shells_x, shells_y);     // Salida de un espacio donde el avión golpea para eliminar los proyectiles
            printf(" ");

            shells_x = 0, shells_y = 0;     // La bala de cañón golpea el avión, la bala de cañón cruza el límite, la próxima vez que el espacio inicialice automáticamente la bala de cañón
        }
    }

    gotoxy(9, R);
    printf("%d", score);

    if (score >= N)         //El juego ha terminado
    {
        system("cls");      //Pantalla clara
        gotoxy(39, 15);
        printf("Has despejado el nivel, la puntuación final:% d!", N);
        gotoxy(0, 29);
        exit(0);
    }

}

void process()              //Proceso
{
    while (1)
    {
        dhpdxshs();         // Función de animación de aeronave

        if (_kbhit())
        {
            ckkzhs();       // Función de operación
        }

        dpfshs();           // Función de efecto de cañón
        pdfsjzhs();         // determina si golpear y estadísticas

        Sleep(18);
    }
}

int main()
{
    cshcxhs();      // Programa inicial

    process();      //Proceso

    return 0;
}




void HideCursor()
{
    CONSOLE_CURSOR_INFO cursor_info = { 1, 0 };
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}

void gotoxy(int x, int y)
{
    COORD pos = { x,y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}


