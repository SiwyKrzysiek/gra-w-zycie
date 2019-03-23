#include "GraphicsGenerator.h"

void savePng(Board *board, char *outputFile)
{
    //Set up setting
    png_byte color_type = PNG_COLOR_TYPE_GRAY;
    png_byte bit_depth = 8;
    int number_of_passes = 7;
    int width = board->sizeX;
    int height = board->sizeY;

    png_bytep* row_pointers = (png_bytep *)malloc(sizeof(png_bytep) * height);
    for (int y = 0; y < height; y++)
        row_pointers[y] = (png_byte *)malloc(sizeof(png_byte) * width);

    for (int y = 0; y < height; y++)
    {
        png_byte *row = row_pointers[y];
        for (int x = 0; x < width; x++)
        {
            CellState cell = board->cells[y * board->sizeX + x];
            row[x] = (cell == ALIVE) ? 255 : 0;
        }
    }

    //Writing to file
    FILE *fp = fopen(outputFile, "wb");
    if (!fp)
        printf("[write_png_file] File %s could not be opened for writing", outputFile);

    png_structp png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

    if (!png_ptr)
        printf("[write_png_file] png_create_write_struct failed");

    png_infop info_ptr = png_create_info_struct(png_ptr);
    if (!info_ptr)
        printf("[write_png_file] png_create_info_struct failed");

    if (setjmp(png_jmpbuf(png_ptr)))
        printf("[write_png_file] Error during init_io");

    png_init_io(png_ptr, fp);

    if (setjmp(png_jmpbuf(png_ptr)))
        printf("[write_png_file] Error during writing header");

    png_set_IHDR(png_ptr, info_ptr, width, height,
                 bit_depth, color_type, PNG_INTERLACE_NONE,
                 PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);

    png_write_info(png_ptr, info_ptr);

    if (setjmp(png_jmpbuf(png_ptr)))
        printf("[write_png_file] Error during writing bytes");

    png_write_image(png_ptr, row_pointers);

    if (setjmp(png_jmpbuf(png_ptr)))
        printf("[write_png_file] Error during end of write");

    png_write_end(png_ptr, NULL);

    for (int y = 0; y < height; y++)
        free(row_pointers[y]);
    free(row_pointers);

    fclose(fp);
}