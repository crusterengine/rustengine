#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>


int track_query(char *file_path, char *query, long *count, int *appear) {

   FILE *file = fopen(file_path, "r");
   if (file == NULL) {
       printf("File not found: %s\n", file_path);
       return 1;
   }

   char line[512];
   bool new_word = false;
   int line_no = 0;
   int page = 1; 
   bool new_page = true; 

   while (fgets(line, sizeof(line), file) != NULL) {
        line_no++;
    // Calculates the current page. 
       if (line_no >= 50){
        page += (line_no/50);
        line_no = 0; 
        new_page = true; 
       }

       
    //Tracks if the query appears in the current line.
        if (strstr(line, query) != NULL){
             *appear+=1;
             if (new_page){
                new_page = false; 
                printf("Found query '%s' appears in page: %d\n", query, page); // Later to be modified for a list/map. and then at last print all. 

             }
        }

    // for-loop countling the words of the .txt file. 
       for (int i = 0; line[i] != '\0'; i++) {
           if (isspace(line[i])) {
                   new_word = false; // Resets the word
           } else if (!new_word) {
                   new_word = true; //Indicates we're in a new word
                   *count+=1;
           }
       }

   }
    fclose(file);
    return 0;
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
