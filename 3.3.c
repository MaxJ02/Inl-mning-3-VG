/***************************************************************************

Detta är en uppdaterad version av den bifogade koden i 3.3.c på google classroom.
Den ska följa modern c99 standard och jag hoppas att jag inte glömde ändra på något.
Koden fungerar och skriver ut den bubble sorterade arrayen till både terminalen och data.txt
****************************************************************************/



#include <stdio.h>
#include <stdlib.h>

#define SIZE 20

static inline size_t* uint_ptr_new(size_t size) 
{
    return (size_t*)malloc(sizeof(size_t) * size);
}

static inline size_t get_random(size_t min, size_t max) 
{
    return rand() % (max + 1 - min) + min;
}

static inline void assign(size_t* data, size_t size, size_t min, size_t max) 
{
    for (size_t i = 0; i < size; i++) 
    {
        data[i] = get_random(min, max);
    }
}

static inline void sort(size_t* data, size_t size) 
{
    for (size_t i = 0; i < size - 1; i++) 
    {
        for (size_t j = 0; j < size - i - 1; j++) 
        {
            if (data[j] > data[j + 1]) 
            {
                size_t temp = data[j];
                data[j] = data[j + 1];
                data[j + 1] = temp;
            }
        }
    }
}

static inline void print(const size_t* data, size_t size, FILE* stream) 
{
    if (size) 
    {
        if (!stream) stream = stdout;
        fprintf(stream, "--------------------------------------------------------------------------\n");
        for (size_t i = 0; i < size; i++) 
        {
            fprintf(stream, "%lu\n", (unsigned long)data[i]);
        }
        fprintf(stream, "--------------------------------------------------------------------------\n\n");
    }
}

static inline void file_read(const char* filepath, FILE* stream) 
{
    if (!stream) stream = stdout;

    FILE* fp = fopen(filepath, "r");
    if (!fp) 
    {
        fprintf(stderr, "Could not open file at path %s!\n\n", filepath);
    }
    else 
    {
        char s[100] = { '\0' };
        while (fgets(s, (int)sizeof(s), fp)) 
        {
            fprintf(stream, "%s", s);
        }
        fclose(fp);
    }
}

int main(void) 
{
    size_t* data = uint_ptr_new(SIZE);
    assign(data, SIZE, 5, 15);
    sort(data, SIZE);

    FILE* fp = fopen("data.txt", "w");
    print(data, SIZE, fp);
    fclose(fp);

    file_read("data.txt", stdout);
    free(data);
    return 0;
}
