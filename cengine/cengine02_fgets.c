#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <glib.h> //`pkg-config --cflags --libs glib-2.0`

void update_index(GHashTable* index, char* word, int page){
    int* value = (int*) g_hash_table_lookup(index, word);

    if (value != NULL) {
        (*value) += 1; 
        printf("Updated value for '%s': %d\n", word, *value);
    } else {
        int* new_value = malloc(sizeof(int));
        *new_value = 1;
        g_hash_table_insert(index, g_strdup(word) , new_value);
        printf("this '%s' word is on the way to the index\n", word);
    }
}

void trim_word(char* word){
    int len = strlen(word);
    int first = 0; 
    int last = len-1; 

    while (first < len && !isalpha(word[first])) {
        first++;
    }

    while (last >= first && !isalpha(word[last])){
        last--;
    }

    for (int i = first; i <= last; i++) {
        word[i - first] = word[i];
    }

    for (int i = last+1; i < len; i++)
    {
        word[i] = '\0';
    }
}

void process_word(char* word, long* wordcount, int page) {
    if (strlen(word) > 0) {
        trim_word(word);
        (*wordcount)++; //later to put word in index
    }
}

void file_processing(FILE* file, long* word_count, GHashTable* index){
    char word[512];
    char line[512];
    int linecount = 0;

    while (fgets(line, 512, file) != NULL){
        linecount++;
        bool new_word =false;
        int word_index = 0;

            for (int i = 0; line[i] != '\0'; i++) {
            if (isspace(line[i])) {
                if (new_word) {
                    //word[word_index] = '\0';
                    int page = linecount/50 + 1;
                    process_word(word, word_count, page);
                    update_index(index, word, page);
                    word_index = 0; // Nulstil for næste ord
                    new_word = false;
                    memset(word, '\0', 512);
                }
            } else {
                // Vi er midt i et ord
                word[word_index++] = line[i];
                new_word = true;
            }
        }
    }
}

int main(int argc, char *argv[]) {
    
 if (argc != 3) {
       printf("Missing argument, check file or counter\n");
       return 1;
   }

   char *file_path = argv[1];

    FILE *file = fopen(file_path, "r");
    if (file == NULL) {
       printf("File not found: %s\n", file_path);
       return 1;
   }

   long word_count = 0;
   int itr = (int)atoi(argv[2]);
   GHashTable *index = g_hash_table_new_full(g_str_hash, g_str_equal, g_free, g_free);

   for (int i = 0; i < itr; i++) {
        file_processing(file, &word_count, index);
        rewind(file);
   }
  
   printf("The file contains %ld words.\n", word_count);

    g_hash_table_destroy(index);
    fclose(file);
    return 0;
}
