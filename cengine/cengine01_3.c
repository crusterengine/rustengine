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

long count_words(char *file_path) {

   FILE* file = fopen(file_path, "r");
   if (file == NULL) {
       printf("File not found: %s\n", file_path);
       return 1;
   }

    long count = 0;
    char word[512];

    while (next_word(word, file)){
        count++;
        printf("%s\n", word);
    }

    fclose(file);

    return count;
}


int main(int argc, char *argv[]) {
   if (argc != 3) {
       printf("Missing argument, check file or counter\n");
       return 1;
   }

   char *file_path = argv[1];

   long word_count = 0;
   int number_of_iterations = (int)atoi(argv[2]);

   for (int i = 0; i < number_of_iterations; i++) {
       word_count += count_words(file_path);
   }
  
   printf("The file contains %ld words.\n", word_count);


   return 0;
}
