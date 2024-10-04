#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void trim_word(char* word){
    int len = strlen(word);
    
    if (!isalpha(word[0])){
       for (size_t i = 0; i < len-1; i++)
       {
        word[i] = word[i+1];
       }
       word[len-1] = '\0';
    }

    if(!isalpha(word[len-1])){
       word[len-1] = '\0';
    }
    
}

int word_processing(FILE* file, char* word){
    char current;
    int index = 0;
    memset(word, '\0', 512);

    while((current = fgetc(file)) != EOF){

        if(!isspace(current)){
            word[index] = current;
            index++;
        } else if (index>0){ //checks that there is not multiple spaces. 
            trim_word(word); 
            return 1;
        }
    }
    //Ensure that the last word of the file is always handled eventhough we meet the EOF tag.  
    if (index>0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int file_processing(char* file_path){
    
    FILE *file = fopen(file_path, "r");
    if (file == NULL) {
       printf("File not found: %s\n", file_path);
       return 1;
   }

    int count = 0;
    char word[512];

   while(word_processing(file, word)){
    count++; 
    printf("%s\n", word); 
   }
   printf("%d\n", count);
  
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
        word_count += file_processing(file_path);
   }
  
   printf("The file contains %ld words.\n", word_count);
   return 0;
}