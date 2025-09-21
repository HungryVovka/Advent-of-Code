/* =======================================================================
   Advent of Code 2015 — Day 2: I Was Told There Would Be No Math
   Part 1 -> answer1.txt
   Part 2 -> answer2.txt

   - Часть 1: Считаем, сколько всего квадратных футов обёрточной бумаги нужно.
     Для каждой коробки: площадь поверхности + площадь самой маленькой грани.
   - Часть 2: Считаем общую длину ленты. Для каждой коробки:
     минимальный периметр из двух сторон + объём.

   - Parte 1: Calcoliamo il totale della carta da regalo necessaria.
     Per ogni scatola: superficie totale + area del lato più piccolo.
   - Parte 2: Calcoliamo la lunghezza totale del nastro. Per ogni scatola:
     perimetro minimo di due lati + volume.
   ======================================================================= */

#include <stdio.h>   /* fopen, fclose, fgets, sscanf, fprintf, printf   */
#include <stdlib.h>  /* EXIT_*                                          */
#include <string.h>  /* strlen, strtok (se servisse)                    */

#ifdef _WIN32
  #include <windows.h> /* SetConsoleOutputCP, SetConsoleCP              */
#endif

/* RU: Переключаем консоль на UTF-8 (Windows).
   IT: Impostiamo la console su UTF-8 (Windows). */
static void set_utf8_console(void){
#ifdef _WIN32
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);
#endif
}

/* Печатаем разделительную линию.
   Stampa una riga di separazione. */
static void print_line(char c, int width){
    int i;
    for (i = 0; i < width; ++i) putchar(c);
    putchar('\n');
}

/* =======================================================================
   Part 1
   Считаем бумагу для всех коробок из input.txt.
   Calcoliamo la carta per tutte le scatole da input.txt.
   ======================================================================= */
static void solve_wrapping_paper_part1(void){
    const char *input_filename = "input.txt";
    const char *output_filename = "answer1.txt";
    FILE *input_file;
    FILE *output_file;

    /* Переменные для размеров коробки и итоговой суммы.
       Variabili per le dimensioni e il totale. */
    int length, width, height;
    int side1, side2, side3;
    int smallest_side;
    long long total_paper = 0;  /* RU: итог | IT: totale */
    char line[128];

    input_file = fopen(input_filename, "r");
    if (!input_file){
        puts("Ошибка: не удалось открыть input.txt / Errore apertura input.txt");
        return;
    }

    /* Читаем файл построчно, парсим l,w,h.
       Leggiamo il file riga per riga, estraiamo l,w,h. */
    while (fgets(line, sizeof(line), input_file)){
        if (sscanf(line, "%dx%dx%d", &length, &width, &height) == 3){
            side1 = length * width;
            side2 = width * height;
            side3 = height * length;

            /* находим минимальную грань
               troviamo il lato minimo */
            smallest_side = side1;
            if (side2 < smallest_side) smallest_side = side2;
            if (side3 < smallest_side) smallest_side = side3;

            /* RU: площадь поверхности + запас
               IT: superficie totale + extra */
            total_paper += 2*side1 + 2*side2 + 2*side3 + smallest_side;
        }
    }
    fclose(input_file);

    /* Записываем результат в answer1.txt
       Scriviamo il risultato in answer1.txt */
    output_file = fopen(output_filename, "wb");
    if (output_file){
        fprintf(output_file, "Part 1 (total wrapping paper): %lld\n", total_paper);
        fclose(output_file);
    }

    print_line('-', 65);
    printf("Part 1 -> Общая бумага / Carta totale: %lld\n", total_paper);
    printf("Записано в %s\n", output_filename);
}

/* =======================================================================
   Part 2
   Считаем общую длину ленты: минимальный периметр + объём коробки.
   Calcoliamo il nastro totale: perimetro minimo + volume della scatola.
   Результат пишем в answer2.txt.
   ======================================================================= */
static void solve_wrapping_ribbon_part2(void){
    const char *input_filename = "input.txt";
    const char *output_filename = "answer2.txt";
    FILE *input_file;
    FILE *output_file;

    int length, width, height;
    int perim1, perim2, perim3;
    int min_perimeter;
    long long total_ribbon = 0;
    char line[128];

    input_file = fopen(input_filename, "r");
    if (!input_file){
        puts("Ошибка: не удалось открыть input.txt / Errore apertura input.txt");
        return;
    }

    while (fgets(line, sizeof(line), input_file)){
        if (sscanf(line, "%dx%dx%d", &length, &width, &height) == 3){
            perim1 = 2 * (length + width);
            perim2 = 2 * (width + height);
            perim3 = 2 * (height + length);

            min_perimeter = perim1;
            if (perim2 < min_perimeter) min_perimeter = perim2;
            if (perim3 < min_perimeter) min_perimeter = perim3;

            total_ribbon += min_perimeter + (length * width * height);
        }
    }
    fclose(input_file);

    output_file = fopen(output_filename, "wb");
    if (output_file){
        fprintf(output_file, "Part 2 (total ribbon length): %lld\n", total_ribbon);
        fclose(output_file);
    }

    print_line('-', 65);
    printf("Part 2 -> Общая лента / Nastro totale: %lld\n", total_ribbon);
    printf("Записано в %s\n", output_filename);
}

/* =======================================================================
   main
   ======================================================================= */
void main(void){
    set_utf8_console();

    print_line('=', 65);
    puts("Advent of Code 2015 — Day 2: I Was Told There Would Be No Math");

    solve_wrapping_paper_part1();
    solve_wrapping_ribbon_part2();

    print_line('=', 65);
    puts("Нажмите Enter для выхода...");
    puts("Premi Invio per uscire...");
    getchar();
}