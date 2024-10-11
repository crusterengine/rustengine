
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
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

void process_word(char* word, long* wordcount, int page) {
    if (strlen(word) > 0) {
        trim_word(word);
        *wordcount += 1; //later to put word in index
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
                    addnode_index(word, index, page);
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
 if (argc != 4) {
       printf("Missing argument, check file or counter\n");
       return 1;
   }

   char* file_path = argv[1];

    FILE *file = fopen(file_path, "r");
    if (file == NULL) {
       printf("File not found: %s\n", file_path);
       return 1;
   }

   long word_count = 0;
   int itr = (int)atoi(argv[2]);
   char* query = argv[3];

   GHashTable *index = g_hash_table_new_full(g_str_hash, g_str_equal, g_free, NULL);

    for (size_t i = 0; i < itr; i++)
    {
        file_processing(file, &word_count, index);
        rewind(file);
    }

    printf("The file contains %ld words.\n", word_count);

    print_index(index);
    print_query(index, query);

    free_linked(index);
    g_hash_table_destroy(index);

    fclose(file);
   return 0;
}