
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <glib.h> //`pkg-config --cflags --libs glib-2.0`

typedef struct list
{
    GList *head;
    GList *tail;
} list;

void print_page(gpointer data, gpointer user_data)
{
    printf("%d, ", GPOINTER_TO_INT(data));
}

void print_query(GHashTable *word_index, char *query)
{
    list *page_list = (list *)g_hash_table_lookup(word_index, query);
    GList *list = page_list->head;

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
            list *page_list = (list *)value;
            g_list_free(page_list->head);
            free(page_list);
        }
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

    word[len - new_len] = '\0';
}

void process_word(char *word, long *word_count, GHashTable *word_index, int *linecount)
{
    if (strlen(word) > 0)
    {
        *word_count += 1;
    }

    trim_word(word);

    int page = *linecount / 50 + 1;

    list *page_list = (list *)g_hash_table_lookup(word_index, word);

    if (page_list == NULL)
    {
        list *new_page_list = (list *)g_malloc(sizeof(list));
        new_page_list->head = g_list_alloc();
        new_page_list->tail = new_page_list->head;
        new_page_list->head->next = NULL;
        new_page_list->head->data = GINT_TO_POINTER(page);
        g_hash_table_insert(word_index, g_strdup(word), new_page_list);
    }
    else
    {
        if (GPOINTER_TO_INT(page_list->tail->data) != page)
        {
            GList *new_page = g_list_alloc();
            new_page->data = GINT_TO_POINTER(page);

            GList *old_tail = page_list->tail;
            old_tail->next = new_page;
            page_list->tail = new_page;
        }
    }
}

void file_processing(FILE *file, long *word_count, GHashTable *word_index)
{
    char word[512];
    char line[512];
    int linecount = 0;

    while (fgets(line, sizeof(line), file) != NULL)
    {
        int char_index = 0;
        linecount++;

        for (int i = 0; line[i] != '\0'; i++)
        {
            if (!isspace(line[i]))
            {
                word[char_index++] = line[i];
            }
            else
            {
                if (char_index > 0)
                {
                    word[char_index] = '\0';
                    process_word(word, word_count, word_index, &linecount);
                    char_index = 0;
                }
            }
        }
        if (char_index > 0)
        {
            word[char_index] = '\0';
            process_word(word, word_count, word_index, &linecount);
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
    printf("C found the file contains %ld words.\n", word_count);

    print_query(word_index, query);

    free_linked(word_index);
    g_hash_table_destroy(word_index);
    fclose(file);
    return 0;
}