#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>


long count_words(char *file_path) {
   int count = 0;

   FILE *file = fopen(file_path, "r");
   if (file == NULL) {
       printf("File not found: %s\n", file_path);
       return 1;
   }

   char buffer[8192];
   bool new_word = false;

   while (fgets(buffer, 8192, file) != NULL) {
       for (int i = 0; buffer[i] != '\0'; i++) {
           if (isspace(buffer[i])) {
                   new_word = false; // Resets the word
           } else if (!new_word) {
                   new_word = true; //Indicates we're in a new word
                   count++;
           }
       }
   }


   // while (fscanf(file, "%255s", word) == 1) {
   //     count++;
   // }
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
