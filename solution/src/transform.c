#include "image.h"
#include "transform.h"
#include <stdio.h>
#include <stdlib.h>

struct image rotate_90(struct image const source)
{
    struct source out_image = { 0 };
    const uint32_t height = source.height;
    const uint32_t width = source.width;
    out_image.height = height;
    out_image.width = width;
    out_image.data = malloc(sizeof(struct pixel) * source.width * source.height);
    
    for (uint64_t row = 0; row < source.width; row++) {
        for (uint64_t column = 0; column < source.height; column++) {
            out_image.data[row * height + column] = source.data[(height - 1 - column) * width + row];
        }
    }

    return out_image;

    
}


void image_destroy(struct image* image)
{
    free(image->data);
    free(image);
}
