#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <glib.h> //`pkg-config --cflags --libs glib-2.0`

// void free_values_word_index(GHashTable *word_index)
// {

//     GHashTableIter iter;
//     gpointer key, value;

//     g_hash_table_iter_init(&iter, word_index);
//     while (g_hash_table_iter_next(&iter, &key, &value))
//     {
//             int *count = (int *)g_hash_table_lookup(word_index, key);
//             //printf("%d\n", *count);
//             free(count);
//             //printf("%d\n", *count);

//     }
// }

// void free_keys_word_index(GHashTable *word_index)
// {
//     // Get a list of all keys
//     GList *keys = g_hash_table_get_keys(word_index);
//     GList *iterator = keys;

//     // Iterate through each key and free its memory
//     while (iterator != NULL)
//     {
//         free(iterator->data);  // Free the actual string data of the key
//         iterator = iterator->next;
//     }

//     // Free the GList container itself
//     //g_list_free(keys);
// }

// void free_keys_word_index(GHashTable *word_index)
// {
//     // Get all keys from the hash table without modifying the table
//     GList *keys = g_hash_table_get_keys(word_index);
    
//     // Iterate through each key
//     for (GList *iterator = keys; iterator != NULL; iterator = iterator->next)
//     {
//         char *key_string = (char *)iterator->data; // Get the key string
//         g_free(key_string); // Free the actual memory for the string
//     }
    
//     // Free the GList container itself after freeing each key string
//     //g_list_free(keys);
// }


// void print_word_index(GHashTable *word_index)
// {

//     GHashTableIter iter;
//     gpointer key, value;

//     g_hash_table_iter_init(&iter, word_index);
//     while (g_hash_table_iter_next(&iter, &key, &value))
//     {
//             int *count = (int *)g_hash_table_lookup(word_index, key);
//             char *word = (char *)key;
//             printf("%s: %d\n", word, *count);
//     }
// }


void print_word_index(GHashTable *word_index)
{

    GHashTableIter iter;
    gpointer key, value;

    g_hash_table_iter_init(&iter, word_index);
    while (g_hash_table_iter_next(&iter, &key, &value))
    {
            long count = (long)(char *)g_hash_table_lookup(word_index, key);
            char *word = (char *)key;
            printf("%s: %ld\n", word, count);
    }
}

//Peters version 4:
// void update_word_index(GHashTable *word_index, char *word, long *map_word_count)
// {
//     void* p = g_hash_table_lookup(word_index, word);

//     if (p != NULL)
//     {
//         p = (void*)((char*)p + 1);
//         g_hash_table_replace(word_index, (gchar *)word, p);

//     }
//     else
//     {
//         g_hash_table_insert(word_index, g_strdup(word), GINT_TO_POINTER(1));
//     }
// }

// void print_word_index(GHashTable *word_index)
// {
//     GHashTableIter iter;
//     gpointer key, value;

//     g_hash_table_iter_init(&iter, word_index);
//     while (g_hash_table_iter_next(&iter, &key, &value))
//     {
//         char *word = (char *)key;
//         int count = GPOINTER_TO_INT(value);  // Decode pointer as integer
//         printf("%s: %d\n", word, count);
//     }
// }

// void print_word_index(GHashTable *word_index)
// {
//     GHashTableIter iter;
//     gpointer key, value;

//     g_hash_table_iter_init(&iter, word_index);
//     while (g_hash_table_iter_next(&iter, &key, &value))
//     {
//         char *word = (char *)key;
//         int count = GPOINTER_TO_INT(value);
//         printf("%s: %d\n", word, count);
//     }
// }


// void update_word_index(GHashTable *word_index, char *word, long *map_word_count)
// {
//     // Check if the word is already in the hash table
//     gpointer current_value = g_hash_table_lookup(word_index, word);
//     int count = current_value ? GPOINTER_TO_INT(current_value) : 0;

//     *map_word_count += 1;

//     if (count > 0) {
//         // Update existing entry: replace word with updated count
//         g_hash_table_insert(word_index,  g_strdup(word),  GINT_TO_POINTER(count + 1));
//     } else {
//         // Insert new word with initial count of 1
//         g_hash_table_insert(word_index, g_strdup(word), GINT_TO_POINTER(1));
//     }
// }

// void update_word_index(GHashTable *word_index, char *word, long *map_word_count)
// {
//     // Check if the word is already in the hash table
//     gpointer current_value = g_hash_table_lookup(word_index, word);
//     int count = current_value ? GPOINTER_TO_INT(current_value) : 0;

//     *map_word_count += 1;

//     if (count > 0) {
//         // Update existing entry: replace word with updated count
//         g_hash_table_replace(word_index, g_strdup(word), GINT_TO_POINTER(count + 1));
//     } else {
//         // Insert new word with initial count of 1
//         g_hash_table_insert(word_index, g_strdup(word), GINT_TO_POINTER(1));
//     }
// }

// void update_word_index(GHashTable *word_index, const char *word, long *map_word_count)
// {
//     // Check if the word is already in the hash table
//     gpointer current_value = g_hash_table_lookup(word_index, word);
//     int count = current_value ? GPOINTER_TO_INT(current_value) : 0;

//     *map_word_count += 1;

//     if (count > 0) {
//         // Update the count for an existing key
//         g_hash_table_insert(word_index, word, GINT_TO_POINTER(count + 1));
//     } else {
//         // Insert a new key (duplicate the key to ensure it's owned by the hash table)
//         g_hash_table_insert(word_index, g_strdup(word), GINT_TO_POINTER(1));
//     }
// }

// Peters version 1 - nævn at det er lavet om til g_malloc for at holde os til at bruge biblioteket, og denne sikre mod visse fejl:
//  void update_word_index(GHashTable *word_index, char *word, long* map_word_count)
//  {
//      int *count = (int *)g_hash_table_lookup(word_index, word);
//      *map_word_count += 1;
//      if (count != NULL)
//      {
//          *count += 1;
//      }
//      else
//      {
//          int *new_value = g_malloc(sizeof(int));
//          *new_value = 1;
//          g_hash_table_insert(word_index, g_strdup(word), new_value);
//      }
//  }


//Peters version 2:
// void update_word_index(GHashTable *word_index, char *word, long *map_word_count)
// {
//     gpointer current_value = g_hash_table_lookup(word_index, word);

//     if (current_value != NULL)
//     {
//         int count = GPOINTER_TO_INT(current_value);
//         g_hash_table_insert(word_index, (gchar *)word, GINT_TO_POINTER(count + 1));
//     }
//     else
//     {
//         g_hash_table_insert(word_index, g_strdup(word), GINT_TO_POINTER(1));
//     }
// }

// const int N = 100;
// // Peters version 3
// void update_word_index(GHashTable *word_index, char *word, long *map_word_count)
// {
//     static int next = N; // next is an index into an array ints[0..N-1]; when next>=N the old array is full and a new one must be allocated
//     static int *ints = NULL; //

//     gpointer p = g_hash_table_lookup(word_index, word);
//     if (p == NULL)
//     {
//         if (next >= N)
//         {
//             next = 0;
//             ints = (int *)malloc(N * sizeof(int));
//         }
//         p = &ints[next++];
//         *(int *)p = 1;
//         //g_hash_table_lookup(word_index, word, p);
//         g_hash_table_insert(word_index, g_strdup(word), p);
//     }
//     else
//     {
//         *(int *)p += 1;
//     }
// }

//Peters version 4:
// void update_word_index(GHashTable *word_index, char *word, long *map_word_count)
// {
//     void* p = g_hash_table_lookup(word_index, word);

//     if (p != NULL)
//     {
//         p = (void*)((char*)p + 1);
//         g_hash_table_replace(word_index, (gchar *)word, p);

//     }
//     else
//     {
//         g_hash_table_insert(word_index, g_strdup(word), GINT_TO_POINTER(1));
//     }
// }

//Peters version 5:
void update_word_index(GHashTable *word_index, char *word, long *map_word_count)
{
    void* p = g_hash_table_lookup(word_index, word);

        p = (void*)((char*)p + 1);
        g_hash_table_replace(word_index, g_strdup(word), p);
    
}


// void update_word_index(GHashTable *word_index, const char *word, long *map_word_count)
// {
//     // Check if the word is already in the hash table
//     gpointer current_value = g_hash_table_lookup(word_index, word);
//     int count = current_value ? GPOINTER_TO_INT(current_value) : 0;

//     *map_word_count += 1;

//     if (count > 0) {
//         // Update the count for an existing key
//         g_hash_table_insert(word_index, g_strdup(word), GINT_TO_POINTER(count + 1));
//     } else {
//         // Insert a new key (duplicate the key only once for first insertion)
//         g_hash_table_insert(word_index, g_strdup(word), GINT_TO_POINTER(1));
//     }
// }

// void update_word_index(GHashTable *word_index, const char *word, long *map_word_count)
// {
//     // Check if the word is already in the hash table
//     gpointer current_value = g_hash_table_lookup(word_index, word);
//     gpointer current_key = g_strdup(word);

//     if (current_value != NULL) {
//         int count = GPOINTER_TO_INT(current_value);
//         count += 1;

//     } else {
//         // Insert a new key (duplicate the key only once for first insertion)
//         g_hash_table_insert(word_index, g_strdup(word), GINT_TO_POINTER(1));
//     }
// }

void trim_word(char *word)
{
    int len = strlen(word); // Can this be done different??
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

void file_processing(FILE *file, long *word_count, long *map_word_count, GHashTable *word_index)
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
                    *word_count += 1;
                    trim_word(word);
                    update_word_index(word_index, word, map_word_count);
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
        if (new_word)
        {
            *word_count += 1;
            trim_word(word);
            update_word_index(word_index, word, map_word_count);
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
    long map_word_count = 0;
    int itr = (int)atoi(argv[2]);

    //GHashTable *word_index = g_hash_table_new_full(g_str_hash, g_str_equal, g_free,  g_free); //used for our own workaround with malloc

    // GHashTable *word_index = g_hash_table_new_full(g_str_hash, g_str_equal, g_free, NULL);
    // GHashTable *word_index = g_hash_table_new_full(g_str_hash, g_str_equal, NULL, NULL);

    GHashTable *word_index = g_hash_table_new(g_str_hash, g_str_equal);

    for (int i = 0; i < itr; i++)
    {
        file_processing(file, &word_count, &map_word_count, word_index);
        rewind(file);
    }

    //free_values_word_index(word_index);
    //free_keys_word_index(word_index);
    //print_word_index(word_index);

    // int map_size = g_hash_table_size(word_index);
    // printf("The size of the map is: %d\n", map_size);
    // printf("The map contains: %ld elements\n", map_word_count);
    // printf("C found the file contains %ld words.\n", word_count);

    // g_hash_table_destroy(word_index);
    // fclose(file);
    return 0;
}
