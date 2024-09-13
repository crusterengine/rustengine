#include <stdio.h>
#include <stdlib.h>

int count_words(FILE *file){
    int count = 0; 
    char word[256];

    while (fscanf(file, "%255s", word)==1){
        // Somehow iterate over each word and trim all words. 
        count++; 
    }
    return count;
}

int main(){

    char file_path[256];
    FILE *file;

    printf("Enter the full filepath for the .txt file:");
    scanf("%255s", file_path);
    
    file = fopen(file_path, "r");
    if (file == NULL){
        printf("file not found\n");
        return 1;
    }

    int word_count = count_words(file); 

    printf("The file contains %d words. \n", word_count);

    fclose(file);
    
    return 0;

}

// gcc scanner.c -o scantest
// ./scantest
// /Users/annesofiedahl-petersen/Desktop/Thesis/Sandbox_Rust/rustengine/rustengine/target/Data/enwiki-tiny.txt