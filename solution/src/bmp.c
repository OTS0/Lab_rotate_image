#include "solution\include\bmp.h"
#include "solution\include\image.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

struct bmp_header create_header(struct image const* img) {
    struct bmp_header bmp_header = {
            .bfType = 0x4D42,
            .bfileSize = (sizeof(struct bmp_header) + img->height * img->width * sizeof(struct pixel)
                          + img->height * ((img->width) % 4)),

            .bfReserved = 0,
            .bOffBits = sizeof(struct bmp_header),
            .biSize = 40,
            .biWidth = img->width,
            .biHeight = img->height,
            .biPlanes = 1,
            .biBitCount = 24,
            .biCompression = 0,
            .biSizeImage = img->height * img->width * sizeof(struct pixel) + (img->width % 4) * img->height,
            .biXPelsPerMeter = 0,
            .biYPelsPerMeter = 0,
            .biClrUsed = 0,
            .biClrImportant = 0 };
    return bmp_header;
}

static bool read_header(FILE* f, struct bmp_header* header) {
    return fread(header, sizeof(struct bmp_header), 1, f);
}

bool ability_open_file(const char* filename, FILE** in_file, struct bmp_header* header);
{
    if (!filename) return false;
    *in_file = fopen(filename, "rb");
    if (!*in_file) return false;
    if (read_header(*in_file, header)) {
        fclose(*in_file);
        return true;
    }

    fclose(*in_file);
    return false;

}
/*  uint16_t bfType - 0x4d42 | 0x4349 | 0x5450
    uint32_t  bfileSize - размер файла
    uint32_t bfReserved - 0
    uint32_t bOffBits - смещение до поля данных,обычно 54 = 16 + biSize
    uint32_t biSize - размер струкуры в байтах
    uint32_t biWidth - ширина в точках
    uint32_t  biHeight - высота в точках
    uint16_t  biPlanes - 1
    uint16_t biBitCount  24 
    uint32_t biCompression - BI_RGB
    uint32_t biSizeImage - Количество байт в поле данных.Обычно устанавливается в 0
    uint32_t biXPelsPerMeter - горизонтальное разрешение, точек на дюйм
    uint32_t biYPelsPerMeter -  вертикальное разрешение, точек на дюйм
    uint32_t biClrUsed - Количество используемых цветов
    uint32_t  biClrImportant - Количество существенных цветов*/

    enum read_status from_bmp(FILE* in, struct image* img) 
    {
        struct bmp_header* bmp_header = malloc(sizeof(struct bmp_header));
        read_header(in, bmp_header);

        if (bmp_header->bfType != 0x4d42 ) { return READ_INVALID_SIGNATURE; }
        if (bmp_header->biBitCount != 24) { return READ_INVALID_BITS };
        if (bmp_header->bfReserved != 0) { return READ_INVALID_RESERVED; }
        if (bmp_header->biPlanes != 0) { return READ_INVALID_PLANES; }

        struct pixel* data = malloc(sizeof(struct pixel) * bmp_header->biWidth * bmp_header->biHeight);
        img->data = data;

        if ((bmp_header->biWidth) > 0 && (bmp_header->biHeight) > 0)
        {
            img->width = bmp_header->biWidth;
            img->height = bmp_header->biHeight;
        }
        else return READ_INVALID_WIDTH;
        uint32_t i=0;
        while (i < bmp_header->biHeight) 
        {
            if (!(fread(&(img->data[i * img->width]), sizeof(struct pixel), image->width, in))) {
                return READ_INVALID_HEADER;
            }
            fseek(in, bmp_header -> biWidth%4, 1);
            // if don't work to change 1 to SEEK_CUR
            //means current position in the file
            i++;
        }
        free(bmp_header);
        return READ_OK;
    }

    enum write_status to_bmp(FILE* out, struct image const* img)
    {
        const size_t size = 0;
        struct bmp_header bmp_header = create_header(img);
        if (!fwrite(&bmp_header, sizeof(struct bmp_header), 1, out))
        {
            return WRITE_ERROR_COUNT_CHARS;
        }
        uint32_t i = 0;
        while (i < bmp_header->biHeight)
        {
            if (!(fwrite(&(img->data[i * img->width]), sizeof(struct pixel), image->width, out))) {
                return WRITE_ERROR;
            }

            if (!(fwrite(&size, 1, (img->width) % 4, out))) { return WRITE_ERROR; }
        }
        return WRITE_OK;
    }
    
    bool  is_successful_read(enum read_status read_status)
    {
        switch (read_status) {
        case READ_INVALID_SIGNATURE:
            error_("Invalid signature\n");
            break;
        case READ_INVALID_BITS:
            error_("Invalid bits\n");
            break;
        case READ_INVALID_HEADER:
            error_("Invalid header\n");
            break;
        case READ_INVALID_RESERVED:
            error_("Invalid reserved, always 0 \n");
            break;
        case READ_INVALID_PLANES:
            error_("Invalid planes, always 1 \n");
            break;
        case READ_INVALID_WIDTH:
            error_("Invalid width or height\n");
            break;
        case READ_OK:
            return true;
        }
        return false;

    }
    
    bool  is_successful_writting(enum write_status  write_status)
    {
        switch (write_status) {
        case WRITE_ERROR:
            error_("Write error \n");
            break;
        case WRITE_ERROR_COUNT_CHARS:
            error_("Write error, problems with header\n");
            break;
        case WRITE_OK:
            return true;
        }
        return false;
    }

    void  close_file(FILE* file) {
        bool close = fclose(file);
        if (close == false) { err("close error\n"); }
    }
