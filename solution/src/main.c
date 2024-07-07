#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include "solution\include\image.h"
#include "solution\include\bmp.h"
#include "solution\include\util.h"
#include "solution\include\transform.h"


int main( int argc, char** argv ) {

    (void) argc; (void) argv;
    util_usage(argc);

    FILE *in_file;
    FILE *out_file;
    struct bmp_header h = { 0 };

    //open files
    if (ability_open_file(argv[1], &in_file, &h)) {
        *in_file = fopen(argv[1], "rb");
    }
    else {
        util_err("Failed to open file for reading \n");
    }
    
    if (ability_open_file(argv[2], &out_file, &h)) {
        *in_file = fopen(argv[2], "wb");
    }
    else {
        util_err("Failed to open file for writing \n");
    }

    //work with images
    struct image image {0};
    struct image out_image { 0 };
    enum read_status read_status = from_bmp(in_file, image);
    if (is_successful_read(read_status)) 
    {
        out_image = rotate_90(image);
    }

    //write to file
    enum write_status write_status = to_bmp(out_file, out_image);
    if (is_successful_writting(write_status)) { printf("Writing to the file was successful"); }

    //close files
    close_file(in_file);
    close_file(out_file);

    //free memory
    image_destroy(image);
    image_destroy(out_image);

    return 0;
}
