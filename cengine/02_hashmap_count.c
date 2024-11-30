#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <glib.h> //`pkg-config --cflags --libs glib-2.0`
#include <wctype.h>
#include <wchar.h>
#include <locale.h>

void free_values(GHashTable *word_index)
{
    GHashTableIter iter;
    gpointer key, value;

    g_hash_table_iter_init(&iter, word_index);
    while (g_hash_table_iter_next(&iter, &key, &value))
    {
       //g_free(key);
        g_free(value);
    }
    // g_hash_table_remove_all(word_index);
}

void find_most_frequent_word(GHashTable *word_index){

    GHashTableIter iter;
    gpointer key, value;
    int currently_highest = 0;
    char* word;

    g_hash_table_iter_init(&iter, word_index);
    while (g_hash_table_iter_next(&iter, &key, &value))
    {
        int* values = (int*) value;
        if(*values > currently_highest){
            currently_highest = *values;
            word = (char *)key;
        }
    }
    printf("The word appearing the most times is: '%s', it appeared %d times\n", word, currently_highest);
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

// void trim_word(char *word)
// {
//     int len = strlen(word);
//     int new_len = 0;
//     int first = 0;
//     int last = len - 1;

//     while (first < len && !isalpha(word[first]))
//     {
//         first++;
//         new_len++;
//     }

//     while (last >= first && !isalpha(word[last]))
//     {
//         last--;
//         new_len++;
//     }

//     for (int i = first; i <= last; i++)
//     {
//         word[i - first] = word[i];
//     }

//     word[len - new_len] = '\0';
// }


void trim_word(char *word) {
    gchar *start = word;  // Pointer to the first character
    gchar *end = word + strlen(word) - 1;  // Pointer to the last character

    // Skip leading non-alphabetic characters
    while (*start && !g_unichar_isalpha(g_utf8_get_char(start))) {
        start = g_utf8_next_char(start);  // Move to the next character
    }

    // Skip trailing non-alphabetic characters
    while (end > start && !g_unichar_isalpha(g_utf8_get_char(end))) {
        end = g_utf8_prev_char(end);  // Move to the previous character
    }

    // Copy the trimmed content back to the beginning of the string
    int final_len = end >= start ? (end - start + g_utf8_next_char(end) - end) : 0;
    for (int i = 0; i < final_len; i++) {
        word[i] = start[i];  // Copy character by character
    }

    word[final_len] = '\0';  // Null-terminate the trimmed word
}




void process_word(char *word, long *word_count, GHashTable *word_index)
{
    if (strlen(word) > 0)
    {
        *word_count += 1;
    }

    trim_word(word);

    printf("%s\n", word);

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

    while (fgets(line, sizeof(line), file) != NULL)
    {
        int char_index = 0;

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
                    process_word(word, word_count, word_index);
                    char_index = 0;
                }
            }
        }
        if (char_index > 0)
        {
            word[char_index] = '\0';
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

    //print_word_index(word_index);
    //printf("C found the file contains %ld words.\n", word_count);
    
    //find_most_frequent_word(word_index);
    
    //free_values(word_index);
    // print_word_index(word_index); // Illustrating dangling pointers
    //g_hash_table_destroy(word_index);

    fclose(file);
    return 0;
}
