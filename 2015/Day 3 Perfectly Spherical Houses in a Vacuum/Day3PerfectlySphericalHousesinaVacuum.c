/* =======================================================================
   Advent of Code 2015 — Day 3: Perfectly Spherical Houses in a Vacuum
   Part 1 -> answer1.txt
   Part 2 -> answer2.txt

   - Часть 1: Считаем, сколько уникальных домов получили хотя бы один подарок.
   - Часть 2: Санта и Робо-Санта идут по очереди и вместе разносят подарки.
     Считаем, сколько уникальных домов получили хотя бы один подарок.

   - Parte 1: Calcoliamo quante case uniche hanno ricevuto almeno un regalo.
   - Parte 2: Babbo Natale e Robo-Babbo si muovono a turni e consegnano insieme.
     Calcoliamo quante case uniche hanno ricevuto almeno un regalo.
   ======================================================================= */

#include <stdio.h>    /* fopen, fclose, fgetc, fprintf, printf, puts    */
#include <stdlib.h>   /* malloc, free                                   */

#ifdef _WIN32
  #include <windows.h> /* SetConsoleOutputCP, SetConsoleCP              */
#endif

/* Включаем UTF-8 для Windows. */
/* Abilitiamo UTF-8 su Windows. */
static void set_utf8_console(void){
#ifdef _WIN32
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);
#endif
}

/* Печать разделительной линии. */
/* Stampa una linea di separazione. */
static void print_line(char c, int width){
    int i;
    for (i = 0; i < width; i++) putchar(c);
    putchar('\n');
}

/* Структура для хранения координат / Struttura per memorizzare coordinate */
typedef struct {
    int x;
    int y;
} Point;

/* Проверяем уникальность */ 
/* Controlliamo l'unicità */
static int is_unique(Point *visited, int count, int x, int y){
    int i;
    for (i = 0; i < count; i++){
        if (visited[i].x == x && visited[i].y == y){
            return 0; /* RU: уже был | IT: già visitato */
        }
    }
    return 1; /* RU: новый дом | IT: nuova casa */
}

/* =======================================================================
   Part 1
   Считаем уникальные дома из input.txt.
   Calcoliamo le case uniche da input.txt.
   ======================================================================= */
static void solve_houses_part1(void){
    const char *input_filename = "input.txt";
    const char *output_filename = "answer1.txt";
    FILE *input_file;
    FILE *output_file;

    /* RU: Предполагаем до миллиона шагов.  
       IT: Supponiamo fino a un milione di passi. */
    long long max_steps = 1000000;
    Point *visited = (Point*)malloc(max_steps * sizeof(Point));
    if (!visited){
        puts("Ошибка: не удалось выделить память / Errore: memoria insufficiente");
        return;
    }

    int x = 0, y = 0;                 /* текущие координаты | coordinate attuali */
    long long unique_count = 0;       /* уникальные дома    | case uniche        */
    int current_char;

    /* стартовая точка (0,0) | punto iniziale (0,0) */
    visited[0].x = 0;
    visited[0].y = 0;
    unique_count = 1;

    input_file = fopen(input_filename, "rb");
    if (!input_file){
        puts("Ошибка: не удалось открыть input.txt / Errore apertura input.txt");
        free(visited);
        return;
    }

    /* Читаем все шаги / Leggiamo tutti i passi */
    while ((current_char = fgetc(input_file)) != EOF){
        if (current_char == '^'){
            y += 1;
        } else if (current_char == 'v'){
            y -= 1;
        } else if (current_char == '>'){
            x += 1;
        } else if (current_char == '<'){
            x -= 1;
        } else {
            continue; /* игнорируем мусор | ignoriamo caratteri inutili */
        }

        if (is_unique(visited, unique_count, x, y)){
            visited[unique_count].x = x;
            visited[unique_count].y = y;
            unique_count++;
        }
    }
    fclose(input_file);

    /* Записываем результат / Scriviamo il risultato */
    output_file = fopen(output_filename, "wb");
    if (output_file){
        fprintf(output_file, "Part 1 (unique houses): %lld\n", unique_count);
        fclose(output_file);
    }

    print_line('-', 65);
    printf("Part 1 -> Уникальных домов / Case uniche: %lld\n", unique_count);
    printf("Записано в %s\n", output_filename);

    free(visited);
}

/* =======================================================================
   Part 2
   Санта и Робо-Санта идут по очереди, считаем уникальные дома.
   Babbo Natale e Robo-Babbo si muovono a turni, contiamo le case uniche.
   ======================================================================= */
static void solve_houses_part2(void){
    const char *input_filename = "input.txt";
    const char *output_filename = "answer2.txt";
    FILE *input_file;
    FILE *output_file;

    long long max_steps = 1000000;
    Point *visited = (Point*)malloc(max_steps * sizeof(Point));
    if (!visited){
        puts("Ошибка: не удалось выделить память / Errore: memoria insufficiente");
        return;
    }

    /* Координаты Санты и Робо-Санты / Coordinate di Babbo e Robo-Babbo */
    int santa_x = 0, santa_y = 0;
    int robo_x = 0, robo_y = 0;
    long long unique_count = 0;
    int current_char;
    long long step_index = 0;

    /* Стартовая точка (0,0) / Punto iniziale (0,0) */
    visited[0].x = 0;
    visited[0].y = 0;
    unique_count = 1;

    input_file = fopen(input_filename, "rb");
    if (!input_file){
        puts("Ошибка: не удалось открыть input.txt / Errore apertura input.txt");
        free(visited);
        return;
    }

    /* Читаем все шаги / Leggiamo tutti i passi */
    while ((current_char = fgetc(input_file)) != EOF){
        int *x, *y;

        /* Чередуем: чётные шаги → Санта, нечётные → Робо-Санта */
        /* Alternativo: passi pari → Santa, passi dispari → Robo-Santa */
        if (step_index % 2 == 0){
            x = &santa_x; y = &santa_y;
        } else {
            x = &robo_x; y = &robo_y;
        }

        if (current_char == '^'){
            (*y)++;
        } else if (current_char == 'v'){
            (*y)--;
        } else if (current_char == '>'){
            (*x)++;
        } else if (current_char == '<'){
            (*x)--;
        } else {
            step_index++;
            continue;
        }

        if (is_unique(visited, unique_count, *x, *y)){
            visited[unique_count].x = *x;
            visited[unique_count].y = *y;
            unique_count++;
        }

        step_index++;
    }
    fclose(input_file);

    output_file = fopen(output_filename, "wb");
    if (output_file){
        fprintf(output_file, "Part 2 (unique houses with Robo-Santa): %lld\n",
                unique_count);
        fclose(output_file);
    }

    print_line('-', 65);
    printf("Part 2 -> Уникальных домов (Санта+Робо) / Case uniche (Babbo+Robo): %lld\n",
           unique_count);
    printf("Записано в %s\n", output_filename);

    free(visited);
}

/* =======================================================================
   main
   ======================================================================= */
void main(void){
    set_utf8_console();

    print_line('=', 65);
    puts("Advent of Code 2015 — Day 3: Perfectly Spherical Houses in a Vacuum");

    solve_houses_part1();
    solve_houses_part2();

    print_line('=', 65);
    puts("Нажмите Enter для выхода...");
    puts("Premi Invio per uscire...");
    getchar();
}