#include <stdio.h>
#include <stdlib.h>

int count_words(File *file){
    int count = 0; 

    while (fget(file) != EOF){
        // Somehow iterate over each word and trim all words. 
        count++; 
    }
    return count;
}

int main(){

    char file_path[256];
    File *file;

    printf("Enter the full filepath for the .txt file:");
    scanf("%s", file_path);
    
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