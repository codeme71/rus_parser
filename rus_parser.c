// codeme71 2025

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORD_LEN 100

// Приводим слово к нижнему регистру
void to_lower(char* str) {
    for (int i = 0; str[i]; i++) {
        str[i] = (char)tolower(str[i]);
    }
}

// Проверка окончания word на постфикс suffix
int has_suffix(const char* word, const char* suffix) {
    size_t wlen = strlen(word);
    size_t slen = strlen(suffix);
    if (wlen < slen) return 0;
    return strcmp(word + wlen - slen, suffix) == 0;
}

// Простые словари предлогов, союзов, местоимений
const char* get_part_of_speech(const char* word) {
    // Предлоги и союзы (пример)
    const char* prepositions[] = {"в", "на", "под", "из", "с", "к", "о"};
    const char* conjunctions[] = {"и", "а", "но", "что", "если"};
    const char* pronouns[] = {"я", "ты", "он", "она", "оно", "мы", "вы", "они"};

    for (int i = 0; i < sizeof(prepositions)/sizeof(prepositions[0]); i++) {
        if (strcmp(word, prepositions[i]) == 0) return "предлог";
    }
    for (int i = 0; i < sizeof(conjunctions)/sizeof(conjunctions[0]); i++) {
        if (strcmp(word, conjunctions[i]) == 0) return "союз";
    }
    for (int i = 0; i < sizeof(pronouns)/sizeof(pronouns[0]); i++) {
        if (strcmp(word, pronouns[i]) == 0) return "местоимение";
    }

    // Глагол: окончания и суффиксы
    if (has_suffix(word, "ить") ||
        has_suffix(word, "ать") ||
        has_suffix(word, "ять") ||
        has_suffix(word, "еть") ||
        has_suffix(word, "уть") ||
        has_suffix(word, "ться") ||
        has_suffix(word, "иться") ||
        has_suffix(word, "еть") ||
        has_suffix(word, "ать")) {
        return "глагол";
    }

    // Прилагательное: окончания
    if (has_suffix(word, "ый") || has_suffix(word, "ой") ||
        has_suffix(word, "ая") || has_suffix(word, "ое") || has_suffix(word, "ые")) {
        return "прилагательное";
    }

    // Наречие: часто заканчиваются на -о, -е
    if (has_suffix(word, "о") || has_suffix(word, "е")) {
        return "наречие";
    }

    // Существительное: суффиксы уменьшительно-ласкательные как пример
    if (has_suffix(word, "ка") || has_suffix(word, "ок") || has_suffix(word, "ик") ||
        has_suffix(word, "а") || has_suffix(word, "о") || has_suffix(word, "е") ||
        has_suffix(word, "ь") || has_suffix(word, "й")) {
        return "существительное";
    }

    // Если не подошло ни к одному, говорим "неизвестно"
    return "неизвестно";
}

int main() {
    char input[256];
    printf("Введите предложение: ");
    if (!fgets(input, sizeof(input), stdin)) {
        printf("Ошибка ввода\n");
        return 1;
    }
    // Уберём символ новой строки
    input[strcspn(input, "\n")] = 0;

    // Разбиваем по пробелу — простой разбор слов (без учёта пунктуации)
    char* word = strtok(input, " ,.?!;:-");
    while (word) {
        to_lower(word);
        printf("%s - %s\n", word, get_part_of_speech(word));
        word = strtok(NULL, " ,.?!;:-");
    }

    return 0;
}



















