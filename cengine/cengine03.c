#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <glib.h>


bool next_word(FILE *file, char *word, int* line)
{
    char current_char;
    int array_index = 0;
    memset(word, '\0', 512);

    while ((current_char = fgetc(file)) != EOF)
    {
        if (current_char == '\n') {
            *line += 1;
        }
        if (!isspace(current_char)){
            word[array_index] = current_char;
            array_index++;
        } 

        else if (array_index > 0){
            return true;
        }
    }
    if (array_index > 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

int create_hashtable(GHashTable* hash_map, char* word){
    
    int* count = g_hash_table_lookup(hash_map, word);

    if (count == NULL)
    {
        int* count = malloc(sizeof(int));
        *count = 1;
        g_hash_table_insert(hash_map, g_strdup(word), (gpointer)(count));
        return 1;
    } else {
        *count += 1;
        return 1;
    }

    return 0;
}

int search_hashtable(GHashTable* hash_map, char* word) {

    if (g_hash_table_lookup(hash_map, word) == NULL)
    {
       printf("the word does not exist\n");
       return 1;
    } else {
        int* count = (int*) g_hash_table_lookup(hash_map, word);
        printf("The query is there: %d\n", *count);
        return 1;
    }
    
    return 0;

}

long track_query(char *file_path, char *query, long *total_word_count, int *total_appearances) {

   FILE* file = fopen(file_path, "r");
   if (file == NULL) {
       printf("File not found: %s\n", file_path);
       return 1;
   }

    char word[512];
    int line_no = 1;
    int page = 1;

    GHashTable *hash_map = g_hash_table_new(g_str_hash, g_str_equal);

    while (next_word(file, word, &line_no)){
        *total_word_count += 1;

    //     if (line_no == 50){
    //     page += 1;
    //     line_no = 0; 
    //    }

        create_hashtable(hash_map, word); 
        
        //printf("%s\n", word);
    }

    search_hashtable(hash_map, query);

    //printf("%d", line_no);
    
    g_hash_table_destroy(hash_map); 

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
  
    // if (total_appearances < 1){
    //     printf("The query '%s' was not found.\n", query);
    // } else{
    //     printf("The file contains the query '%s' %d times.\n", query, total_appearances);
    // }

    printf("The file contains %ld words.\n", total_word_count);

   return 0;
}
