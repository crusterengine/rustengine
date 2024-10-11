
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <glib.h> //`pkg-config --cflags --libs glib-2.0` 

void print_page (gpointer data, gpointer user_data){
    printf("%d, ", GPOINTER_TO_INT(data));
}

void print_query(GHashTable* index, char* query){
    GList* list = (GList*) g_hash_table_lookup(index, query); //hvilken type retur??
    printf("%s: ", query);

    if (list != NULL){
        g_list_foreach(list, print_page, NULL);
        printf("\n");
    } else {
        printf(" not found.\n");
    }
}

void print_index(GHashTable* index){
    GHashTableIter iter;
    gpointer key, value;

    g_hash_table_iter_init(&iter, index);
    while(g_hash_table_iter_next(&iter, &key, &value)){
        if(value != NULL){
            print_query(index, key);
        }
    }
}

void free_linked(GHashTable* index){
    GHashTableIter iter;
    gpointer key, value;

    g_hash_table_iter_init(&iter, index);
    while(g_hash_table_iter_next(&iter, &key, &value)){
        if(value != NULL){
            g_list_free(value);
        }
    }
}

GList* updatelist(int page, GList* list){
   return g_list_append(list, GINT_TO_POINTER(page));
   
}

void addnode_index(char* word, GHashTable* index, int page){
    GList* knownlist = (GList*) g_hash_table_lookup(index, word);
    if(knownlist != NULL){
        knownlist = updatelist(page, knownlist);
    } else{
        GList* list = NULL;
        list = updatelist(page, list);
        g_hash_table_insert(index, g_strdup(word) , list);
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

void word_processing(FILE* file, char* word, int* line){
    char line_buffer[512];
    int index = 0;
    memset(word, '\0', 512);
    *line = 0;

    bool new_word = false; 

    while (fgets(line_buffer, sizeof(line_buffer), file) != NULL) {
        (*line)++; 

        for (int i = 0; line_buffer[i] != '\0'; i++) {
            char current = line_buffer[i];

            if (isspace(current)) {
                new_word = false;
            } else {
                if (!new_word) {
                  
                    new_word = true;
                    index = 0;
                    while (current != '\0' && !isspace(current) && index < 511) {
                        word[index++] = current;
                        current = line_buffer[++i];
                    }
                    word[index] = '\0';
                    trim_word(word);
                }
            }
        }
    }
}

int file_processing(char* file_path, long* word_count, GHashTable* index){
    
    FILE *file = fopen(file_path, "r");
    if (file == NULL) {
       printf("File not found: %s\n", file_path);
       return 1;
   }

    char word[512];
    int line = 1; 
    
   while(word_processing(file, word, &line)){
    (*word_count)++; 
    int page = line/50 + 1; 
    addnode_index(word, index, page);
   }

   printf("file_processing found: %ld\n", *word_count);
  
   fclose(file);
   return 0;
}


int main(int argc, char *argv[]) {
 if (argc != 4) {
       printf("Missing argument, check file or counter\n");
       return 1;
   }

   char* file_path = argv[1];
   long word_count = 0;
   int itr = (int)atoi(argv[2]);
   char* query = argv[3];

   GHashTable *index = g_hash_table_new_full(g_str_hash, g_str_equal, g_free, NULL);

    for (size_t i = 0; i < itr; i++)
    {
        file_processing(file_path, &word_count, index);
        //rewind(file);
    }

    print_index(index);
    print_query(index, query);
    printf("main got: %ld\n", word_count);

    free_linked(index);
    g_hash_table_destroy(index);
   return 0;
}