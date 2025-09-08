/* =======================================================================
   Advent of Code 2015 — Day 1: Not Quite Lisp
   Part 1 -> answer1.txt
   Part 2 -> answer2.txt

   RU: Первая функция считает итоговый этаж и пишет в answer1.txt.
       Вторая функция ищет первую позицию входа в подвал (-1) и пишет
       в answer2.txt.
   IT: La prima funzione calcola il piano finale e scrive in answer1.txt.
       La seconda funzione trova la prima posizione del seminterrato (-1)
       e scrive in answer2.txt.
   ======================================================================= */

#include <stdio.h>    /* fopen, fclose, fgetc, fprintf, printf, puts    */
#include <stdlib.h>   /* EXIT_*                                         */

#ifdef _WIN32
  #include <windows.h> /* SetConsoleOutputCP, SetConsoleCP              */
#endif

/* RU: Переключаем консоль на UTF-8 (Windows). */
/* IT: Impostiamo la console su UTF-8 (Windows). */
static void set_utf8_console(void){
#ifdef _WIN32
    SetConsoleOutputCP(65001); /* CP_UTF8 */
    SetConsoleCP(65001);       /* CP_UTF8 */
#endif
}

/* RU: Печатаем линию для рамки. */
/* IT: Stampa una riga di cornice. */
static void print_line(char c, int w){
    int i;
    for (i = 0; i < w; ++i) putchar(c);
    putchar('\n');
}

/* =======================================================================
   Part 1
   RU: Считаем итоговый этаж, пишем в answer1.txt.
   IT: Calcoliamo il piano finale, scriviamo in answer1.txt.
   ======================================================================= */
static void solve_part1(void){
    const char *input_filename = "input.txt";
    const char *output_filename = "answer1.txt";
    FILE *input_file;
    FILE *output_file;
    int current_floor = 0;
    int final_floor = 0;
    int current_char;

    input_file = fopen(input_filename, "rb");
    if (!input_file){
        puts("Ошибка: не удалось открыть input.txt / Errore apertura input.txt");
        return;
    }

    while ((current_char = fgetc(input_file)) != EOF){
        if (current_char == '('){
            current_floor += 1;
        } else if (current_char == ')'){
            current_floor -= 1;
        }
    }
    fclose(input_file);
    final_floor = current_floor;

    output_file = fopen(output_filename, "wb");
    if (output_file){
        fprintf(output_file, "Part 1 (final floor): %d\n", final_floor);
        fclose(output_file);
    }

    print_line('-', 60);
    printf("Part 1 -> Итоговый этаж / Piano finale: %d\n", final_floor);
    printf("Записано в %s\n", output_filename);
}
/* =======================================================================
   Part 2
   RU: Ищем первую позицию, где этаж = -1, пишем в answer2.txt.
   IT: Troviamo la prima posizione in cui il piano = -1, scriviamo in answer2.txt.
   ======================================================================= */
static void solve_part2(void){
    const char *input_filename = "input.txt";
    const char *output_filename = "answer2.txt";
    FILE *input_file;
    FILE *output_file;
    int current_floor = 0;
    int current_position = 0;
    int first_basement_position = -1;
    int current_char;

    input_file = fopen(input_filename, "rb");
    if (!input_file){
        puts("Ошибка: не удалось открыть input.txt / Errore apertura input.txt");
        return;
    }

    while ((current_char = fgetc(input_file)) != EOF){
        if (current_char == '('){
            current_floor += 1;
            current_position++;
        } else if (current_char == ')'){
            current_floor -= 1;
            current_position++;
        } else {
            continue;
        }
        if (current_floor == -1 && first_basement_position == -1){
            first_basement_position = current_position;
            break;
        }
    }
    fclose(input_file);

    output_file = fopen(output_filename, "wb");
    if (output_file){
        fprintf(output_file, "Part 2 (first basement position): %d\n",
                first_basement_position);
        fclose(output_file);
    }

    print_line('-', 60);
    printf("Part 2 -> Первая позиция подвал / Prima posizione seminterrato: %d\n",
           first_basement_position);
    printf("Записано в %s\n", output_filename);
}

/* =======================================================================
   main
   ======================================================================= */
void main(void){
    set_utf8_console();

    print_line('=', 60);
    puts("Advent of Code 2015 — Day 1: Not Quite Lisp");

    solve_part1();
    solve_part2();

    print_line('=', 60);
    puts("Нажмите Enter для выхода...");
    puts("Premi Invio per uscire...");
    getchar();
}