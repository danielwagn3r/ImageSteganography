#include <ctype.h>
#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include "ppm.h"

typedef struct _ppm_pixel
{
    uint8_t red;
    uint8_t green;
    uint8_t blue;
} ppm_pixel_t;

typedef struct _ppm_image
{
    uint32_t height;
    uint32_t widght;
    uint8_t colordepth;
    ppm_pixel_t *pixels;
} ppm_image_t;

const char *ppm_p3_header = "P3";
const char *ppm_p6_header = "P6";

bool ppm_load_p3_image(char *data, size_t data_sz, ppm_image_t *ppm_image);
bool ppm_load_p6_image(char *data, size_t data_sz, ppm_image_t *ppm_image);

bool ppm_load_image(const char *filename, ppm_image_t *ppm_image)
{
    struct stat st;
    if (stat(filename, &st))
    {
        return false;
    }

    FILE *file;

    file = fopen(filename, "rb");

    if (!file)
    {
        return false;
    }

    char *data = calloc(st.st_size, sizeof(char));

    if (fread(data, sizeof(char), st.st_size, file) != st.st_size)
    {
        return false;
    }

    if (!memcmp(data, ppm_p3_header, 2))
    {
        /* PPM P3 */
        puts("PPM P3\n");
        bool result = ppm_load_p3_image(data, st.st_size, ppm_image);
        return result;
    }
    else if (!memcmp(data, ppm_p6_header, 2))
    {
        /* PPM P6 */
        puts("PPM P6\n");
        bool result = ppm_load_p6_image(data, st.st_size, ppm_image);
        return result;
    }
    else
    {
        /* unknown file */
        return false;
    }

    fflush(stdout);
    fclose(file);

    return true;
}

bool ppm_load_p3_image(char *data, size_t data_sz, ppm_image_t *ppm_image)
{
    size_t i = 0;

    for (i = 2; isspace(data[i]); i++)
        ;

    printf("index: %u %c\n", i, data[i]);

    while (data[i] == '#')
    {
        size_t f = strcspn(data+i,"\n");

        if (f)
        {
            i += f;
            printf("index: %u %c\n", f, data[f]);
        }
        else
        {
            /* comment without further content */
            printf("end not found\n");
            return false;
        }
    }

    printf("index: %u %c\n", i, data[i]);

    return false;
}

bool ppm_load_p6_image(char *data, size_t data_sz, ppm_image_t *ppm_image)
{
    return false;
}

bool ppm_free_image(ppm_image_t *ppm_image)
{
    if (!ppm_image)
    {
        return false;
    }

    if (ppm_image->pixels)
    {
        free(ppm_image->pixels);
    }

    free(ppm_image);

    return true;
}
