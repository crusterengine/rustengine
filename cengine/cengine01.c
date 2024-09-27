#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>


long count_words(char *file_path, char *query) {
   long count = 0;

   FILE *file = fopen(file_path, "r");
   if (file == NULL) {
       printf("File not found: %s\n", file_path);
       return 1;
   }

   char buffer[8192];
   setvbuf(file, buffer, _IOFBF, sizeof(buffer)); // Ensures that the buf size is equal to rust 

   char line[512];
   bool new_word = false;
   bool query_found = false; 

   while (fgets(line, sizeof(line), file) != NULL) {
        if (query != NULL && strstr(line, query) != NULL){
            query_found = true; 
            printf("Found query '%s' in line: %s", query, buffer);
        }
       for (int i = 0; line[i] != '\0'; i++) {
           if (isspace(line[i])) {
                   new_word = false; // Resets the word
           } else if (!new_word) {
                   new_word = true; //Indicates we're in a new word
                   count++;
           }
       }
   }

    fclose(file);

    if (!query_found){
        printf("Query '%s' not found", query);
    }

    return count;
}


int main(int argc, char *argv[]) {
   if (argc != 4) {
       printf("Missing argument, check file or counter\n");
       return 1;
   }

   char *file_path = argv[1];

   long word_count = 0;
   int number_of_iterations = (int)atoi(argv[2]);
   char *query = argv[3];

   for (int i = 0; i < number_of_iterations; i++) {
       word_count += count_words(file_path, query);
   }
  
   printf("The file contains %ld words.\n", word_count);


   return 0;
}
