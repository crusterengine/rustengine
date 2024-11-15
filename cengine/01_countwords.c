#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

void process_word(char *word, long *wordcount)
{
    if (strlen(word) > 0)
    {
        *wordcount += 1;
    }
}

void file_processing(FILE *file, long *word_count)
{
    char word[512];
    char line[512];

    while (fgets(line, 512, file) != NULL)
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
                    process_word(word, word_count);
                    char_index = 0;
                }
            }
        }
        if (char_index > 0)
        {
            word[char_index] = '\0';
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

    long word_count = 0;
    int itr = (int)atoi(argv[2]);

    for (int i = 0; i < itr; i++)
    {
        file_processing(file, &word_count);
        rewind(file);
    }

    printf("C found that the file contains %ld words.\n", word_count);

    // fclose(file);
    return 0;
}
