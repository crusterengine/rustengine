
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <glib.h> //`pkg-config --cflags --libs glib-2.0`

typedef struct list
{
    GList* head; 
    GList* tail;
}list;


void print_page(gpointer data, gpointer user_data)
{
    printf("%d, ", GPOINTER_TO_INT(data));
}

void print_query(GHashTable *word_index, char *query)
{
    //GList *list = (GList *)g_hash_table_lookup(index, query); // hvilken type retur??
    
    list* page_list = (list*)g_hash_table_lookup(word_index, query);
    GList* list = page_list->head;

    printf("%s: ", query);

    if (list != NULL)
    {
        g_list_foreach(list, print_page, NULL);
        printf("\n");
    }
    else
    {
        printf(" not found.\n");
    }
}

void print_word_index(GHashTable *word_index)
{
    GHashTableIter iter;
    gpointer key, value;

    g_hash_table_iter_init(&iter, word_index);
    while (g_hash_table_iter_next(&iter, &key, &value))
    {
        if (value != NULL)
        {
            print_query(word_index, key);
        }
    }
}

void free_linked(GHashTable *word_index)
{
    GHashTableIter iter;
    gpointer key, value;

    g_hash_table_iter_init(&iter, word_index);
    while (g_hash_table_iter_next(&iter, &key, &value))
    {
        if (value != NULL)
        {
            g_list_free(value);
        }
    }
}

void update_word_index(GHashTable *word_index, char *word, int page)
{
    list* page_list = (list*)g_hash_table_lookup(word_index, word);
    
    if (page_list != NULL)
    {
        GList* new_page = g_list_alloc();
        new_page->data = GINT_TO_POINTER(page);

        GList* old_tail = page_list->tail;
        old_tail->next = new_page; //appends the new node to the list
        page_list->tail = new_page; //moves the tail pointer to the new node
    }
    else
    {
        list* new_page_list = (list*) malloc (sizeof(list));
        new_page_list->head = NULL;
        new_page_list->head = g_list_append(new_page_list->head, GINT_TO_POINTER(page));
        new_page_list->tail = new_page_list->head;
        g_hash_table_insert(word_index, g_strdup(word), new_page_list);
    }
}

void trim_word(char *word)
{
    int len = strlen(word);
    int new_len = 0; 
    int first = 0;
    int last = len - 1;

    while (first < len && !isalpha(word[first]))
    {
        first++;
        new_len++;
    }

    while (last >= first && !isalpha(word[last]))
    {
        last--;
        new_len++;
    }

    for (int i = first; i <= last; i++)
    {
        word[i - first] = word[i];
    }

    word[len-new_len] = '\0';

}

void process_word(char *word, long *wordcount)
{
    if (strlen(word) > 0)
    {
        trim_word(word);
        *wordcount += 1;
    }
}

void file_processing(FILE *file, long *word_count, GHashTable *word_index)
{
    char word[512];
    char line[512];
    int linecount = 0;

    while (fgets(line, 512, file) != NULL)
    {
        linecount++;
        bool new_word = false;
        int char_index = 0;

        for (int i = 0; line[i] != '\0'; i++)
        {
            if (isspace(line[i]))
            {
                if (new_word)
                {
                    // word[char_index] = '\0';
                    process_word(word, word_count);
                    int page = linecount/50 + 1;
                    update_word_index(word_index, word, page);
                    char_index = 0; // Nulstil for næste ord
                    new_word = false;
                    memset(word, '\0', 512);
                }
            }
            else
            {
                // Vi er midt i et ord
                word[char_index++] = line[i];
                new_word = true;
            }
        }
    }
}

int main(int argc, char *argv[])
{
    if (argc != 4)
    {
        printf("Missing argument, check file or counter\n");
        return 1;
    }

    char *file_path = argv[1];

    FILE *file = fopen(file_path, "r");
    if (file == NULL)
    {
        printf("File not found: %s\n", file_path);
        return 1;
    }

    long word_count = 0;
    int itr = (int)atoi(argv[2]);
    char *query = argv[3];

    GHashTable *word_index = g_hash_table_new_full(g_str_hash, g_str_equal, g_free, NULL);

    for (size_t i = 0; i < itr; i++)
    {
        file_processing(file, &word_count, word_index);
        rewind(file);
    }

    print_word_index(word_index);
    printf("The search found, ");
    print_query(word_index, query);
    printf("C found the file contains %ld words.\n", word_count);

    // free_linked(word_index);
    // g_hash_table_destroy(word_index);
    // fclose(file);
    return 0;
}