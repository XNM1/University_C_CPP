// Lab06_2.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"

#pragma pack(push, 1)
typedef struct _WAVHEADER {
	char riff[4];
	unsigned long size;
	char format[4];
	char formatchunk[4];
	unsigned long chunk_size;
	unsigned short audio_format;
	unsigned short channels;
	unsigned long srate;
	unsigned long brate;
	unsigned short sample_block;
	unsigned short bits_per_sample;
	char data[4];
	unsigned long fsize;
} WAVHEADER;
#pragma pack(pop)


int main(int argc, char *argv[])
{
	WAVHEADER header;
	FILE *f;
	if (!(f = fopen(argv[1], "rb"))) {
		perror("Invalid filename");
	}
	fread(&header, sizeof(WAVHEADER), sizeof(WAVHEADER), f);
	printf("%s\n%u\n%s\n%s\n%u\n%u\n%u\n%u\n%u\n%u\n%u\n%s\n%u", header.riff, header.size, header.format,
		header.formatchunk, header.chunk_size, header.audio_format,
		header.channels, header.srate, header.brate, header.sample_block,
		header.bits_per_sample, header.data, header.fsize);
    return 0;
}

