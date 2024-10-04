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


int word_processing(FILE* file, char* word, int* line){
    char current;
    int index = 0;
    memset(word, '\0', 512);

    while((current = fgetc(file)) != EOF){
        
        if (current == '\n'){
            *line += 1;
        }

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
        trim_word(word); 
        return 1;
    }
    else
    {
        return 0;
    }
}

int get_page(int* line){
    int page = *line/50;
    return page;
}

int file_processing(char* file_path){
    
    FILE *file = fopen(file_path, "r");
    if (file == NULL) {
       printf("File not found: %s\n", file_path);
       return 1;
   }

    int count = 0;
    char word[512];
    int line = 1; 
    

   while(word_processing(file, word, &line)){
    count++; 
    int page = get_page(&line);
    printf("%s is on page: %d\n", word, page); 
    //set up a datastructure
   }
   printf("%d\n", count);
  
   fclose(file);
   return count;
}

int main(int argc, char *argv[]) {
 if (argc != 2) {
       printf("Missing argument, check file or counter\n");
       return 1;
   }

   char *file_path = argv[1];
   long word_count = 0;

   file_processing(file_path);

   return 0;
}
