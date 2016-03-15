#include "tga_loader.h"
//
// GLuint    loadTGA(const char* filename)
// {
// 	std::fstream filestr;
// 	struct tga_header   tgaheader;
// 	char * imageData;
//   	filestr.open (filename, std::fstream::in | std::fstream::binary);								// Open file
//   	if (filestr.is_open())														// Do the following actions, if file is opened
//   	{
//   		// read TGA header
//   		filestr.read((char*) &tgaheader , sizeof(struct tga_header));			// Read tga header. For more information: see tga.h and link above
//   		// printf("image type: %i n", tgaheader.imageTypeCode);
//
//   		// read pixel data
//   		int imageSize = tgaheader.width * tgaheader.height * tgaheader.bpp;		// Calculate image size
//
//   		 imageData = (char*) malloc(imageSize);							// Reserve space in the memory to store our image data
//   		filestr.read((char*) imageData, imageSize);						// Read image data from file, into the reserved memory place
//
//
//   		/*
//   		 * TGA is stored in BGR (Blue-Green-Red) format,
//   		 * we need to convert this to Red-Green-Blue (RGB).
//   		 * The following section does BGR to RGB conversion
//   		 */
//       //
//   		// if (tgaheader.bpp == 24)
//   		// {
//   		// 	for (int i = 0; i < imageSize; i+=3)
//   		// 	{
//   		// 		char c = imageData[i];
//   		// 		imageData[i] = imageData[i+2];
//   		// 		imageData[i+2] = c;
//   		// 	}
//   		// }
//   		// else
//   		// if (tgaheader.bpp == 32)
//   		// {
//   		// 	for (int i = 0; i < imageSize; i+=4)
//   		// 	{
//   		// 		// 32 bits per pixel   =  4 byte per pixel
//   		// 		char c = imageData[i];
//   		// 		imageData[i] = imageData[i+2];
//   		// 		imageData[i+2] = c;
//   		// 	}
//   		// }
//
//   		filestr.close();
//   	}
//   	else
//   	{
//   		std::cout << "Error opening file" << std::endl;
//   		return -1;
//   	}
//   return (0);
// }

GLuint LoadTGAFile(const char *filename)
{
    TGAFILE tgaFile;
    FILE *filePtr;
    unsigned char ucharBad;
    short int sintBad;
    long imageSize;
    int colorMode;
    unsigned char colorSwap;

    // Open the TGA file.
    filePtr = fopen(filename, "rb");
    if (filePtr == NULL)
    {
        return false;
    }

    // Read the two first bytes we don't need.
    fread(&ucharBad, sizeof(unsigned char), 1, filePtr);
    fread(&ucharBad, sizeof(unsigned char), 1, filePtr);

    // Which type of image gets stored in imageTypeCode.
    fread(&tgaFile.imageTypeCode, sizeof(unsigned char), 1, filePtr);

    // For our purposes, the type code should be 2 (uncompressed RGB image)
    // or 3 (uncompressed black-and-white images).
    if (tgaFile.imageTypeCode != 2 && tgaFile.imageTypeCode != 3)
    {
        fclose(filePtr);
        return false;
    }

    // Read 13 bytes of data we don't need.
    fread(&sintBad, sizeof(short int), 1, filePtr);
    fread(&sintBad, sizeof(short int), 1, filePtr);
    fread(&ucharBad, sizeof(unsigned char), 1, filePtr);
    fread(&sintBad, sizeof(short int), 1, filePtr);
    fread(&sintBad, sizeof(short int), 1, filePtr);

    // Read the image's width and height.
    fread(&tgaFile.imageWidth, sizeof(short int), 1, filePtr);
    fread(&tgaFile.imageHeight, sizeof(short int), 1, filePtr);

    // Read the bit depth.
    fread(&tgaFile.bitCount, sizeof(unsigned char), 1, filePtr);

    // Read one byte of data we don't need.
    fread(&ucharBad, sizeof(unsigned char), 1, filePtr);

    // Color mode -> 3 = BGR, 4 = BGRA.
    colorMode = tgaFile.bitCount / 8;
    imageSize = tgaFile.imageWidth * tgaFile.imageHeight * colorMode;

    // Allocate memory for the image data.
    tgaFile.imageData = (unsigned char*)malloc(sizeof(unsigned char)*imageSize);

    // Read the image data.
    fread(tgaFile.imageData, sizeof(unsigned char), imageSize, filePtr);

    // Change from BGR to RGB so OpenGL can read the image data.
    for (int imageIdx = 0; imageIdx < imageSize; imageIdx += colorMode)
    {
        colorSwap = tgaFile.imageData[imageIdx];
        tgaFile.imageData[imageIdx] = tgaFile.imageData[imageIdx + 2];
        tgaFile.imageData[imageIdx + 2] = colorSwap;
    }
    fclose(filePtr);
    return textureID;
}
