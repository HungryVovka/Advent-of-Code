#include <stdio.h>
#include <stdlib.h>

#ifdef _WIN32
#include <windows.h> // Для установки кодировки на Windows 
                     // / For setting console encoding on Windows 
                     // / Per impostare la codifica su Windows
#endif

// Цветовые коды ANSI для форматирования текста / ANSI color codes 
// for text formatting / Codici colore ANSI per la formattazione del testo
#define RESET "\x1b[0m"          // Сброс к цвету по умолчанию 
                                 // / Reset to default color 
                                 // / Ripristina colore predefinito
#define RED "\x1b[31m"           // Красный текст / Red text / Testo rosso
#define GREEN "\x1b[32m"         // Зеленый текст / Green text / Testo verde
#define CYAN "\x1b[36m"          // Голубой текст / Cyan text / Testo ciano

#define MAX_SIZE 100000 // Максимальный размер массива / Maximum array size 
                        // / Dimensione massima dell'array

// Функция для чтения чисел из файла / Function to read numbers from a file 
// / Funzione per leggere i numeri da un file
int readNumbersFromFile(
    const char *filename, 
    int list1[], 
    int list2[], 
    int *size
) {
    FILE *file; // Указатель на файл / File pointer / Puntatore al file
    int num1, num2, count;

    file = fopen(filename, "r"); // Открываем файл / Open the file 
                                 // / Aprire il file
    if (file == NULL) {
        // Если файл не открылся, возвращаем ошибку / Return an error 
        // if file cannot be opened / Restituire un errore se il file 
        // non può essere aperto
        printf(RED "Ошибка: Невозможно открыть файл %s\n" RESET, filename);
        printf(RED "Error: Cannot open file %s\n" RESET, filename);
        printf(RED "Errore: Impossibile aprire il file %s\n" RESET, filename);
        return 0;
    }

    count = 0; // Инициализируем счетчик / Initialize counter 
               // / Inizializzare il contatore
    while (fscanf(file, "%d %d", &num1, &num2) == 2) {
        if (count >= MAX_SIZE) {
            // Проверка на переполнение массива / Check for array overflow 
            // / Verifica del superamento dell'array
            printf(RED "Ошибка: Превышен лимит массива (%d строк).\n" RESET, 
                   MAX_SIZE);
            break;
        }
        list1[count] = num1; // Записываем числа в массивы 
                             // / Store numbers in arrays 
                             // / Memorizza i numeri negli array
        list2[count] = num2;
        count++;
    }

    if (count == 0) {
        // Проверка на пустой файл / Check for empty file 
        // / Verifica se il file è vuoto
        printf(RED "Ошибка: Файл пуст или имеет неверный формат.\n" RESET);
        printf(RED "Error: File is empty or has incorrect format.\n" RESET);
        printf(RED "Errore: Il file è vuoto o ha un formato errato.\n" RESET);
    }

    fclose(file); // Закрываем файл / Close the file / Chiudere il file
    *size = count; // Передаём количество элементов через указатель 
                   // / Pass number of elements via pointer 
                   // / Passare il numero di elementi tramite puntatore
    return (count > 0);
}

// Функция для сравнения чисел (используется для сортировки)
// Function for comparing numbers (used for sorting)
// Funzione per confrontare i numeri (utilizzata per l'ordinamento)
int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b); // Простая разность чисел 
                                    // / Simple difference of numbers 
                                    // / Semplice differenza tra numeri
}

// Функция для подсчёта Similarity Score
// Function to calculate the Similarity Score
// Funzione per calcolare il punteggio di similarità
int calculateSimilarityScore(int list1[], int list2[], int size1, int size2) {
    int similarityScore = 0; // Итоговый результат / Final result / Risultato finale
    int i, j;

    for (i = 0; i < size1; i++) {
        int count = 0;
        for (j = 0; j < size2; j++) {
            if (list1[i] == list2[j]) {
                count++; // Увеличиваем количество совпадений
                          // Increment match count
                          // Incrementa il conteggio delle corrispondenze
            }
        }
        similarityScore += list1[i] * count; // Увеличиваем итоговый результат
                                             // Add to final result
                                             // Aggiungi al risultato finale
    }
    return similarityScore; // Возвращаем итоговое значение / Return final value
                            // Restituisci il valore finale
}

// Основная программа / Main program / Programma principale
int main() {
    #ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8); // Устанавливаем кодировку UTF-8 для вывода
                                 // / Set UTF-8 encoding for output
                                 // / Imposta la codifica UTF-8 per l'output
    #endif

    int list1[MAX_SIZE], list2[MAX_SIZE]; // Два массива для чисел
                                          // / Two arrays for numbers
                                          // / Due array per numeri
    int size, i, totalDistance;           // Общие переменные программы
                                          // / Common variables of the program
                                          // / Variabili comuni del programma

    // Считать данные из файла / Read data from file / Leggere i dati dal file
    if (!readNumbersFromFile("input.txt", list1, list2, &size)) {
        return 1; // Завершаем программу в случае ошибки
                  // / Terminate the program in case of an error
                  // / Termina il programma in caso di errore
    }

    // Сортировка списков / Sort lists / Ordinare le liste
    qsort(list1, size, sizeof(int), compare); // Сортируем первый список
                                              // / Sort the first list
                                              // / Ordinare la prima lista
    qsort(list2, size, sizeof(int), compare); // Сортируем второй список
                                              // / Sort the second list
                                              // / Ordinare la seconda lista

    // Вычисление общей суммы расстояний для Part One
    // Calculate total distance for Part One
    // Calcolare la distanza totale per Part One
    totalDistance = 0; // Инициализируем сумму / Initialize the sum
                       // / Inizializza la somma
    for (i = 0; i < size; i++) {
        totalDistance += abs(list1[i] - list2[i]); // Суммируем расстояния
                                                  // / Sum distances
                                                  // / Somma le distanze
    }

    // Вывод результатов для Part One
    // Print results for Part One
    // Stampa i risultati per Part One
    printf(GREEN "Part One\n" RESET);
    printf(GREEN "Общая сумма расстояний: %d\n" RESET, totalDistance);
    printf(GREEN "Total distance: %d\n" RESET, totalDistance);
    printf(GREEN "Distanza totale: %d\n\n" RESET, totalDistance);

    // Вычисление Similarity Score для Part Two
    // Calculate Similarity Score for Part Two
    // Calcola il punteggio di similarità per Part Two
    int similarityScore = calculateSimilarityScore(list1, list2, size, size);

    // Вывод результатов для Part Two
    // Print results for Part Two
    // Stampa i risultati per Part Two
    printf(GREEN "Part Two\n" RESET);
    printf(GREEN "Сумма совпадений: %d\n" RESET, similarityScore);
    printf(GREEN "Similarity score: %d\n" RESET, similarityScore);
    printf(GREEN "Punteggio di similarità: %d\n\n" RESET, similarityScore);

    // Ожидание ввода пользователя для выхода
    // Wait for user input to exit
    // Attendi l'input dell'utente per uscire
    int exitCode;
    printf(CYAN "Нажмите 0, чтобы выйти...\n" RESET);
    printf(CYAN "Press 0 to exit...\n" RESET);
    printf(CYAN "Premere 0 per uscire...\n" RESET);
    do {
        scanf("%d", &exitCode); // Ждём ввод пользователя
                                // / Wait for user input
                                // / Aspetta l'input dell'utente
    } while (exitCode != 0);

    return 0; // Успешное завершение программы
              // / Successful program termination
              // / Terminazione con successo del programma
}