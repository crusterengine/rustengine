#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

void process_word(char *word, long *wordcount)
{
    if (strlen(word) > 0)
    {
        *wordcount += 1; // later to put word in index
    }
}

void file_processing(FILE *file, long *word_count)
{
    char word[512];
    char line[512];

    while (fgets(line, 512, file) != NULL)
    {
        bool new_word = false;
        int word_index = 0;

        for (int i = 0; line[i] != '\0'; i++)
        {
            if (isspace(line[i]))
            {
                if (new_word)
                {
                    process_word(word, word_count);
                    //printf("word: %s \n", word);
                    word_index = 0; // Nulstil for næste ord
                    new_word = false;
                    memset(word, '\0', word_index);
                }
            }
            else
            {
                // Vi er midt i et ord
                word[word_index++] = line[i];
                new_word = true;
            }
        }
        if (new_word)
        {
            process_word(word, word_count);
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

    // char buffer[8192];
    // setvbuf(file, buffer, _IOFBF, 8192);

    long word_count = 0;
    //printf("Before processing: %ld\n", &word_count);
    //printf("Before processing: %ld\n", word_count);

    int itr = (int)atoi(argv[2]);

    for (int i = 0; i < itr; i++)
    {
        file_processing(file, &word_count);
        rewind(file);
    }

    //printf("The file contains %ld words.\n", word_count);

    // fclose(file);
    return 0;
}
