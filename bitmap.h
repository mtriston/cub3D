
#ifndef CUB3D_BITMAP_H
#define CUB3D_BITMAP_H

# include <stdint.h>
# pragma pack(1)

typedef struct  s_bmp_file_header
{
	uint16_t    type;
	uint32_t    size;
	uint16_t    reserved1;
	uint16_t    reserved2;
	uint32_t    off_bits;
}               t_bmp_file_header;

typedef struct  s_bmp_info_header
{
	uint32_t    size;
	int32_t     width;
	int32_t     height;
	uint16_t    planes;
	uint16_t    bit_count;
	uint32_t    compression;
	uint32_t    size_image;
	int16_t     x_pels_per_meter;
	int16_t     y_pels_per_meter;
	uint32_t    clr_used;
	uint32_t    clr_important;
}               t_bmp_info_header;
#pragma pack()
#endif
