#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>


int read_file(char* word, FILE* file){
long count = 0;
    while (fscanf(file, "%255s", word)==1){
        printf("%s\n", word);
        count++;
    }

    printf("%ld", count);

    return 0;

}


long open_file(char *file_path) {

   FILE* file = fopen(file_path, "r");
   if (file == NULL) {
       printf("File not found: %s\n", file_path);
       return 1;
   }

    long count = 0;
    char word[512];

    while (read_file(word, file)){
        count++;
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
       word_count += open_file(file_path);
   }
  
   printf("The file contains %ld words.\n", word_count);


   return 0;
}
