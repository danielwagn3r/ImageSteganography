#ifndef __PPM_H__
#define __PPM_H__

#include <stdbool.h>
#include <stdint.h>

typedef struct _ppm_pixel ppm_pixel_t;

typedef struct _ppm_image ppm_image_t;

bool ppm_load_image(const char *filename, ppm_image_t *ppm_image);

bool ppm_free_image(ppm_image_t *ppm_image);

#endif