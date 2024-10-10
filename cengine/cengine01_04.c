#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int word_processing(FILE *file, char *word)
{
    char current;
    int index = 0;
    memset(word, '\0', 512);

    while ((current = fgetc(file)) != EOF)
    {

        if (!isspace(current))
        {
            word[index] = current;
            index++;
        }
        else if (index > 0)
        { // checks that there is not multiple spaces.
            return 1;
        }
    }
    // Ensure that the last word of the file is always handled eventhough we meet the EOF tag.
    if (index > 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int file_processing(char *file_path, long *word_count)
{

    FILE *file = fopen(file_path, "r");
    if (file == NULL)
    {
        printf("File not found: %s\n", file_path);
        return 1;
    }

    char word[512];

    while (word_processing(file, word))
    {
        *word_count += 1;
    }

    fclose(file);
    return 0;
}

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("Missing argument, check file or counter\n");
        return 1;
    }

    char *file_path = argv[1];

    long word_count = 0;
    int itr = (int)atoi(argv[2]);

    for (int i = 0; i < itr; i++)
    {
        file_processing(file_path, &word_count);
    }

    printf("The file contains %ld words.\n", word_count);
    return 0;
}
