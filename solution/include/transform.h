#include "image.h"
#include "transform.h"
#include <stdio.h>
#include <stdlib.h>

//creates an updated image that is rotated 90 degrees
struct image rotate_90(struct image const source);

//free memory
void image_destroy(struct image* image);