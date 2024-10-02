#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>


bool next_word(char* word, FILE* file){
    if (feof(file)) {
        return false;
    } else {
        fscanf(file, "%512s", word);
    return true;
    }
}

long track_query(char *file_path, char *query, long *total_word_count, int *total_appearances) {

   FILE* file = fopen(file_path, "r");
   if (file == NULL) {
       printf("File not found: %s\n", file_path);
       return 1;
   }

    long count = 0;
    char word[512];
    int page = 1;

    while (next_word(word, file)){
        *total_word_count += 1;

        //This does not work, we don't get the new lines as words!!
        // if (strcmp(word, "\n") == 0)
        // {
        //    page++;
        // }

        char trimmed_word[512];
        int array_index = 0;

        for (size_t i = 0; i < 512; i++) {
            char current_char = word[i];
            if (isalpha(current_char)) {
                trimmed_word[array_index] = current_char;
                array_index++;
            } else {
                trimmed_word[array_index] = '\0';
                array_index++;
            }
        }

        if(strcmp(trimmed_word, query) == 0){
            *total_appearances += 1;
            int array_index = 0;
            memset(trimmed_word, '\0', 512);   
        }

    }

    fclose(file);

    return count;
}


int main(int argc, char *argv[]) {
   if (argc != 4) {
       printf("Missing argument, check file or counter\n");
       return 1;
   }

    char *file_path = argv[1];
    char *query = argv[3];

    int number_of_iterations = (int)atoi(argv[2]);
    long total_word_count = 0;
    int total_appearances = 0;

   for (int i = 0; i < number_of_iterations; i++) {
        track_query(file_path, query, &total_word_count, &total_appearances);
   }
  
    if (total_appearances < 1){
        printf("The query '%s' was not found.\n", query);
    } else{
        printf("The file contains the query '%s' %d times.\n", query, total_appearances);
    }

    printf("The file contains %ld words.\n", total_word_count);

   return 0;
}
