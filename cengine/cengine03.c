
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <glib.h>  

typedef struct PageNode{
    int page; 
    struct PageNode* next;
} PageNode;

PageNode* createpagenode(int page, PageNode* prev){
    PageNode* newNode = (PageNode*)malloc(sizeof(PageNode));
    newNode -> page = page;
    newNode -> next = prev;
    return newNode; 
}

void addpagenode_hash_map(char* word, GHashTable* hash_map, int page){
    PageNode* value = (PageNode*) g_hash_table_lookup(hash_map, word);

    if(value != NULL){
        PageNode* newnode = createpagenode(page, value);
        g_hash_table_insert(hash_map, g_strdup(word) , newnode);
    } else{
        PageNode* node = createpagenode(page, NULL);
        g_hash_table_insert(hash_map, g_strdup(word) , node);
    }
}

void print_linked(GHashTable* hash_map){
    GHashTableIter iter;
    gpointer key, value;

    g_hash_table_iter_init(&iter, hash_map);
    while(g_hash_table_iter_next(&iter, &key, &value)){
        if(value != NULL){
            find_linked_q(hash_map, key);
        }
    }
}


void free_pagenode(PageNode* node) {
    PageNode* current = node;
    while (current != NULL) {
        PageNode* next = current->next;
        free(current);
        current = next;
    }
}

void free_linked(GHashTable* hash_map){
    GHashTableIter iter;
    gpointer key, value;

    g_hash_table_iter_init(&iter, hash_map);
    while(g_hash_table_iter_next(&iter, &key, &value)){
        if(value != NULL){
            free_pagenode(value);
        }
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

int word_processing(FILE* file, char* word, int* line){
    char current;
    int hash_map = 0;
    memset(word, '\0', 512);

    while((current = fgetc(file)) != EOF){
        
        if (current == '\n'){
            *line += 1;
        }

        if(!isspace(current)){
            word[hash_map] = current;
            hash_map++;
        } else if (hash_map>0){ //checks that there is not multiple spaces. 
            trim_word(word); 
            return 1;
        }
    }
    //Ensure that the last word of the file is always handled eventhough we meet the EOF tag.  
    if (hash_map>0)
    {
        trim_word(word); 
        return 1;
    }
    else
    {
        return 0;
    }
}

// int get_page(int* line){
//     int page = 1; 
//     page += *line/50;
//     return page;
// }

int file_processing(FILE* file, long* word_count, GHashTable* hash_map){

    char word[512];
    int line = 1; 
    int page = line/50;

   while(word_processing(file, word, &line)){
    *word_count += 1; 
    //int page = get_page(&line);
    addpagenode_hash_map(word, hash_map, page);
   }
  
   return 0;
}


int main(int argc, char *argv[]) {

 if (argc != 3) {
       printf("Missing argument, check file or counter\n");
       return 1;
   }

   char* file_path = argv[1];
   long word_count = 0;
   int itr = (int)atoi(argv[2]);

    FILE *file = fopen(file_path, "r");
    if (file == NULL) {
       printf("File not found: %s\n", file_path);
       return 1;
   }

   GHashTable *hash_map = g_hash_table_new_full(g_str_hash, g_str_equal, g_free, NULL);

    for (size_t i = 0; i < itr; i++)
    {
        file_processing(file, &word_count, hash_map);
        rewind(file);
    }

    print_linked(hash_map);

    printf("Total wordcount: %ld\n", word_count);

    free_linked(hash_map);
    g_hash_table_destroy(hash_map);

    fclose(file);
   return 0;
}