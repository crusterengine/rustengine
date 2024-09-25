#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>


long count_words(char *file_path) {


   FILE *file = fopen(file_path, "r");
   if (file == NULL) {
       printf("File not found: %s\n", file_path);
       return 1;
   }


   char buffer[8192];
   int word_count = 0;
   // Reset for each line read
   bool new_word = false;


   while (fgets(buffer, 8192, file) != NULL) {
       for (int i = 0; buffer[i] != '\0'; i++) {
           if (isspace(buffer[i])) {
                   new_word = false; // Resets the word
           } else if (!new_word) {
                   new_word = true; //Indicates we're in a new word
                   word_count++;
           }
       }
   }


   // while (fscanf(file, "%255s", word) == 1) {
   //     count++;
   // }
       fclose(file);
    return word_count;
}


int main(int argc, char *argv[]) {
   if (argc != 3) {
       printf("Missing argument, check file or counter\n");
       return 1;
   }


   long word_count = 0;
   char *file = argv[1];


   for (int i = 0; i < (int)atoi(argv[2]); i++)
   {
       word_count += count_words(file);
   }
  
   printf("The file contains %ld words.\n", word_count);


   return 0;
}
