
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <glib.h> //`pkg-config --cflags --libs glib-2.0` 

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

void addpagenode_index(char* word, GHashTable* index, int page){
    PageNode* value = (PageNode*) g_hash_table_lookup(index, word);

    if(value != NULL){
        PageNode* newnode = createpagenode(page, value);
        g_hash_table_insert(index, g_strdup(word) , newnode);
    } else{
        PageNode* node = createpagenode(page, NULL);
        g_hash_table_insert(index, g_strdup(word) , node);
    }
}

void find_linked_q(GHashTable* index, char* query){
    gpointer value = g_hash_table_lookup(index, query);
    printf("%s: ", query);

    if (value != NULL){
        PageNode* current = (PageNode*)value;
        while (current != NULL) {
            printf("%d, ", current->page);
            current = current->next;
            // Modify to return a list
        }
    } else {
        printf(" not found.\n");
    }
    printf("\n");
}

void print_linked(GHashTable* index){
    GHashTableIter iter;
    gpointer key, value;

    g_hash_table_iter_init(&iter, index);
    while(g_hash_table_iter_next(&iter, &key, &value)){
        if(value != NULL){
            find_linked_q(index, key);
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

void free_linked(GHashTable* index){
    GHashTableIter iter;
    gpointer key, value;

    g_hash_table_iter_init(&iter, index);
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
    
    // if (!isalpha(word[0])){
    //    for (size_t i = 0; i < len-1; i++)
    //    {
    //     word[i] = word[i+1];
    //    }
    //    word[len-1] = '\0';
    // }

    // if(!isalpha(word[len-1])){
    //    word[len-1] = '\0';
    // }
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
    int page = 1; 
    page += *line/50;
    return page;
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
    int page = get_page(&line);
    //printf("%s is on page: %d\n", word, page); 
    //insert_index(word, index);
    addpagenode_index(word, index, page);
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
    }

    // print_linked(index);
    // find_linked_q(index, query);
    printf("main got: %ld\n", word_count);

    free_linked(index);
    g_hash_table_destroy(index);
   return 0;
}