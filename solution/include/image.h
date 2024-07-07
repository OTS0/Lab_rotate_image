#include <stdio.h>
struct pixel {
	uint8_t a,b,c;
};

struct image {
	uint64_t width, height;
	struct pixel* data;
};


