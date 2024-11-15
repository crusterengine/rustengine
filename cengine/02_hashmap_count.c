#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <glib.h> //`pkg-config --cflags --libs glib-2.0`

void free_values(GHashTable *word_index){
    GHashTableIter iter;
    gpointer key, value;

    g_hash_table_iter_init(&iter, word_index);
    while (g_hash_table_iter_next(&iter, &key, &value))
    {
            g_free(key);
            g_free(value);
    }
   //g_hash_table_remove_all(word_index);
}

void print_word_index(GHashTable *word_index)
{

    GHashTableIter iter;
    gpointer key, value;

    g_hash_table_iter_init(&iter, word_index);
    while (g_hash_table_iter_next(&iter, &key, &value))
    {
            int *count = (int *)g_hash_table_lookup(word_index, key);
            char *word = (char *)key;
            printf("%s: %d\n", word, *count);
    }
}

void trim_word(char *word)
{
    int len = strlen(word); //Can this be done different??
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

void process_word(char *word, long *word_count, GHashTable *word_index)
{
    if (strlen(word) > 0)
    {
        *word_count += 1;
    }

    trim_word(word);

    int *count = (int *)g_hash_table_lookup(word_index, word);
    if (count == NULL)
    {
        int *new_value = g_malloc(sizeof(int));
        *new_value = 1;
        g_hash_table_insert(word_index, g_strdup(word), new_value);
    }
    else
    {
        *count += 1;
    }
}

void file_processing(FILE *file, long *word_count, GHashTable *word_index)
{
    char word[512];
    char line[512];

    while (fgets(line, 512, file) != NULL)
    {
        bool new_word = false;
        int char_index = 0;

        for (int i = 0; line[i] != '\0'; i++)
        {
            if (isspace(line[i]))
            {
                if (new_word)
                {
                    process_word(word, word_count, word_index);
                    char_index = 0; // Nulstil for næste ord
                    new_word = false;
                    memset(word, '\0', 512);
                }
            }
            else
            {
                word[char_index++] = line[i];
                new_word = true;
            }
        }
        if (new_word)
        {         
            process_word(word, word_count, word_index);
        }
    }
}

int main(int argc, char *argv[])
{

    if (argc != 3)
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

    GHashTable *word_index = g_hash_table_new(g_str_hash, g_str_equal);

    for (int i = 0; i < itr; i++)
    {
        file_processing(file, &word_count, word_index);
        rewind(file);
    }

    print_word_index(word_index);
    printf("C found the file contains %ld words.\n", word_count);
    free_values(word_index);
    print_word_index(word_index);
    g_hash_table_destroy(word_index);
    
    // fclose(file);
    return 0;
}
