#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

void process_word(char *word, long *word_count) {
    if (strlen(word) > 0) {
        (*word_count)++;
    }
}

void file_processing(FILE *file, long *word_count) {
    size_t line_buffer_size = 512;  // Initial buffer size for each line
    char *line = malloc(line_buffer_size);
    if (!line) {
        perror("Failed to allocate memory for line buffer");
        return;
    }

    while (getline(&line, &line_buffer_size, file) != -1) {
        bool new_word = false;
        int word_index = 0;
        char word[512] = {0};  // Word buffer

        for (int i = 0; line[i] != '\0'; i++) {
            if (isspace(line[i])) {
                if (new_word) {
                    word[word_index] = '\0';  // Null-terminate the word
                    process_word(word, word_count);
                    word_index = 0;  // Reset for the next word
                    new_word = false;
                    memset(word, '\0', sizeof(word));  // Clear word buffer
                }
            } else {
                word[word_index++] = line[i];
                new_word = true;
            }
        }
        if (new_word) {  // Handle last word in line
            word[word_index] = '\0';
            process_word(word, word_count);
        }
    }

    free(line);  // Free allocated line buffer
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Missing argument, check file or counter\n");
        return 1;
    }

    char *file_path = argv[1];
    FILE *file = fopen(file_path, "r");
    if (file == NULL) {
        perror("File not found");
        return 1;
    }

    char buffer[8192];
    setvbuf(file, buffer, _IOFBF, 8192);

    long word_count = 0;
    int itr = atoi(argv[2]);

    for (int i = 0; i < itr; i++) {
        file_processing(file, &word_count);
        rewind(file);
    }

    printf("The file contains %ld words.\n", word_count);

    fclose(file);
    return 0;
}
