#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

void process_word(char* word, long* wordcount) {
    if (strlen(word) > 0) {
        printf("Processed word: %s\n", word);
        (*wordcount)++; //later to put word in index
    }
}

void file_processing(FILE* file, long* word_count){
    char word[512];
    char line[512];
    int linecount = 0;

    while (fgets(line, 512, file) != NULL){
        linecount++;
        bool new_word =false;
        int word_index = 0;

            for (int i = 0; line[i] != '\0'; i++) {
            if (isspace(line[i])) {
                if (new_word) {
                    //word[word_index] = '\0';
                    process_word(word, word_count);
                    word_index = 0; // Nulstil for næste ord
                    new_word = false;
                    memset(word, '\0', 512);
                }
            } else {
                // Vi er midt i et ord
                word[word_index++] = line[i];
                new_word = true;
            }
        }
    }
}

int main(int argc, char *argv[]) {
    
 if (argc != 3) {
       printf("Missing argument, check file or counter\n");
       return 1;
   }

   char *file_path = argv[1];

    FILE *file = fopen(file_path, "r");
    if (file == NULL) {
       printf("File not found: %s\n", file_path);
       return 1;
   }

   long word_count = 0;
   int number_of_iterations = (int)atoi(argv[2]);

   for (int i = 0; i < number_of_iterations; i++) {
        file_processing(file, &word_count);
        rewind(file);
   }
  
   printf("The file contains %ld words.\n", word_count);
    
    fclose(file);
   return 0;
}
