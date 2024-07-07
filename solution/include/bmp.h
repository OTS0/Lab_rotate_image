#include  <stdint.h>
#include <stdio.h>
#include "image.h"
#pragma pack(push, 1)

/*  uint16_t bfType - 0x4d42 | 0x4349 | 0x5450
    uint32_t  bfileSize - размер файла
    uint32_t bfReserved - 0
    uint32_t bOffBits - смещение до поля данных,обычно 54 = 16 + biSize
    uint32_t biSize - размер струкуры в байтах
    uint32_t biWidth - ширина в точках
    uint32_t  biHeight - высота в точках
    uint16_t  biPlanes - 1
    uint16_t biBitCount 0 | 1 | 4 | 8 | 16 | 24 | 32
    uint32_t biCompression - BI_RGB
    uint32_t biSizeImage - Количество байт в поле данных.Обычно устанавливается в 0
    uint32_t biXPelsPerMeter - горизонтальное разрешение, точек на дюйм
    uint32_t biYPelsPerMeter -  вертикальное разрешение, точек на дюйм
    uint32_t biClrUsed - Количество используемых цветов
    uint32_t  biClrImportant - Количество существенных цветов*/

struct bmp_header
{
    uint16_t bfType;
    uint32_t  bfileSize;
    uint32_t bfReserved;
    uint32_t bOffBits;
    uint32_t biSize;
    uint32_t biWidth;
    uint32_t  biHeight;
    uint16_t  biPlanes;
    uint16_t biBitCount;
    uint32_t biCompression;
    uint32_t biSizeImage;
    uint32_t biXPelsPerMeter;
    uint32_t biYPelsPerMeter;
    uint32_t biClrUsed;
    uint32_t  biClrImportant;
};
#pragma pack(pop)
struct bmp_header create_header(struct image const* img);
//errors of reading
enum read_status {
    READ_OK = 0,
    READ_INVALID_SIGNATURE,
    READ_INVALID_BITS,
    READ_INVALID_HEADER,
    READ_INVALID_RESERVED,
    READ_INVALID_PLANES,
    READ_INVALID_WIDTH;

};

//writes image from file
enum read_status from_bmp(FILE* in, struct image* img);

//errors of writting
enum  write_status {
    WRITE_OK = 0,
    WRITE_ERROR
    WRITE_ERROR_COUNT_CHARS
};
//writes image to file
enum write_status to_bmp(FILE* out, struct image const* img);

//check file open
bool ability_open_file(const char* filename, FILE** in_file, struct bmp_header* header);

static bool read_header(FILE* f, struct bmp_header* header);
void  close_file(FILE* file);

//handles read errors
bool  is_successful_read(enum read_status read_status);

//handles write errors
bool  is_successful_writting(enum write_status  write_status);