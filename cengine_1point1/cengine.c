#include <stdlib.h>
#include <stdio.h>

long count_words(char* file_path){
    long count = 0; 

    FILE *file = fopen(file_path, "r");
    if (file == NULL){
        printf("file could not be found %s\n", file_path);
        return 1;
    }

    char word[256];

    while (fscanf(file, "%255s", word)==1){
        // Somehow iterate over each word and trim all words. 
        count++; 
    }

    fclose(file);

    return count;
}

int main(int argc, char *argv[]){

    if (argc != 3) {
        printf("Not enough arguments %d", argc);
        return 1;
    }

    char* file_path = argv[1];

    long word_count = 0;
    int number_of_iterations = (int) atoi(argv[2]);

    for (size_t i = 0; i < number_of_iterations; i++)
    {
        word_count += count_words(file_path);
    }
    
    printf("The file contains %ld words. \n", word_count);
    
    return 0;

}