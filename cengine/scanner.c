#include <stdlib.h>
#include <stdio.h>

long count_words(FILE *file){
    long count = 0; 
    char word[256];

    while (fscanf(file, "%255s", word)==1){
        // Somehow iterate over each word and trim all words. 
        count++; 
    }
    return count;
}

int main(int argc, char *argv[]){

    if (argc != 3) {
        printf("Not enough arguments %d", argc);
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (file == NULL){
        printf("file not found %s\n", argv[1]);
        return 1;
    }

    int number_of_iterations = (int) atoi(argv[2]);
    long word_count = 0;

    for (size_t i = 0; i < number_of_iterations; i++)
    {
        rewind(file);
        word_count += count_words(file);
    }
    
    
    printf("The file contains %ld words. \n", word_count);

    fclose(file);
    
    return 0;

}