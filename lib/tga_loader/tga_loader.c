/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tga_loader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcojan <dcojan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/16 11:42:27 by dcojan            #+#    #+#             */
/*   Updated: 2016/03/16 11:52:01 by dcojan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tga_loader.h"

// t_tga_tex	*load_tga(const char* filename)
// {
// 	t_tga_header		tgaheader;
// 	t_tga_tex			*t;
// 	FILE				*f;
//
// 	printf("loading %s\n", filename);
// 	f = fopen(filename, "rb");
// 	if (f == NULL)
// 	{
// 		perror(filename);
// 		return (NULL);
// 	}
// 	t = (t_tga_tex*)malloc(sizeof(t_tga_tex));
//
// 	// read TGA header
// 	// fread((char*) &tgaheader , sizeof(struct tga_header));			// Read tga header. For more information: see tga.h and link above
// 	fread(&tgaheader, sizeof(t_tga_header), 1, f);
// 	// printf("image type: %i n", tgaheader.imageTypeCode);
// 	// read pixel data
// 	int imageSize = tgaheader.width * tgaheader.height * tgaheader.PixelDepth;		// Calculate image size
// 	t->width = tgaheader.width;
// 	t->height = tgaheader.height;
//  	t->data = (unsigned char*) malloc(imageSize);							// Reserve space in the memory to store our image data
// 	fread(&(t->data), imageSize, 1, f);						// Read image data from file, into the reserved memory place
// 	/*
//  	* TGA is stored in BGR (Blue-Green-Red) format,
//  	* we need to convert this to Red-Green-Blue (RGB).
//  	* The following section does BGR to RGB conversion
//  	*/
//  	// if (tgaheader.bpp == 24)
// 	// {
// 	// 	for (int i = 0; i < imageSize; i+=3)
// 	// 	{
// 	// 		char c = imageData[i];
// 	// 		imageData[i] = imageData[i+2];
// 	// 		imageData[i+2] = c;
// 	// 	}
// 	// }
// 	// else
// 	// if (tgaheader.bpp == 32)
// 	// {
// 	// 	for (int i = 0; i < imageSize; i+=4)
// 	// 	{
// 	// 		// 32 bits per pixel   =  4 byte per pixel
// 	// 		char c = imageData[i];
// 	// 		imageData[i] = imageData[i+2];
// 	// 		imageData[i+2] = c;
// 	// 	}
// 	// }
// 	fclose(f);
// 	printf("done\n");
// 	return (t);
// }

t_tga_tex	*load_tga(const char *filename)
{
	t_tga_tex		*tgaFile;
	FILE			*filePtr;
	unsigned char	ucharBad;
	short int		sintBad;
	long			imageSize;
	int				colorMode;
	unsigned char	colorSwap;
	unsigned char	imageTypeCode;
	unsigned char	bitCount;

	printf("loading %s\n", filename);
	filePtr = fopen(filename, "rb");
	if (filePtr == NULL)
	{
		perror(filename);
		return (NULL);
	}
	tgaFile = (t_tga_tex*)malloc(sizeof(t_tga_tex));
	// Read the two first bytes we don't need.
	fread(&ucharBad, sizeof(unsigned char), 1, filePtr);
	fread(&ucharBad, sizeof(unsigned char), 1, filePtr);
	// Which type of image gets stored in imageTypeCode.
	fread(&imageTypeCode, sizeof(unsigned char), 1, filePtr);

	// For our purposes, the type code should be 2 (uncompressed RGB image)
	// or 3 (uncompressed black-and-white images).
	if (imageTypeCode != 2 && imageTypeCode != 3)
	{
		printf("this is a compressed tga\n");
		fclose(filePtr);
		return (NULL);
	}

	// Read 13 bytes of data we don't need.
	fread(&sintBad, sizeof(short int), 1, filePtr);
	fread(&sintBad, sizeof(short int), 1, filePtr);
	fread(&ucharBad, sizeof(unsigned char), 1, filePtr);
	fread(&sintBad, sizeof(short int), 1, filePtr);
	fread(&sintBad, sizeof(short int), 1, filePtr);

	// Read the image's width and height.
	fread(&tgaFile->width, sizeof(short int), 1, filePtr);
	fread(&tgaFile->height, sizeof(short int), 1, filePtr);
	printf("width = %d, height %d\n", tgaFile->width, tgaFile->height);
	// Read the bit depth.
	fread(&bitCount, sizeof(unsigned char), 1, filePtr);

	// Read one byte of data we don't need.
	fread(&ucharBad, sizeof(unsigned char), 1, filePtr);

	// Color mode -> 3 = BGR, 4 = BGRA.
	colorMode = bitCount / 8;
	imageSize = tgaFile->width * tgaFile->height * colorMode;
	printf("colorMode %d\n", colorMode);
	printf("imageSize %ld\n", imageSize);

	// Allocate memory for the image data.
	tgaFile->data = (unsigned char*)malloc(sizeof(unsigned char)*imageSize);

	// Read the image data.
	fread(tgaFile->data, sizeof(unsigned char), imageSize, filePtr);

	// Change from BGR to RGB so OpenGL can read the image data.
	for (int imageIdx = 0; imageIdx < imageSize; imageIdx += colorMode)
	{
		// printf("imageIdx %d\n", imageIdx);
		colorSwap = tgaFile->data[imageIdx];
		tgaFile->data[imageIdx] = tgaFile->data[imageIdx + 2];
		tgaFile->data[imageIdx + 2] = colorSwap;
	}

	fclose(filePtr);
	return (tgaFile);
}
