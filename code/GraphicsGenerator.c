#include "GraphicsGenerator.h"

void savePng(Board *board, char *outputFile)
{
    //Set up setting
    png_byte color_type = PNG_COLOR_TYPE_GRAY;
    png_byte bit_depth = 8;
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
    {
        printf("[write_png_file] File %s could not be opened for writing", outputFile);
        exit(EXIT_FAILURE);
    }

    png_structp png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

    if (!png_ptr)
    {
        printf("[write_png_file] png_create_write_struct failed");
        fclose(fp);
        exit(EXIT_FAILURE);
    }

    png_infop info_ptr = png_create_info_struct(png_ptr);
    if (!info_ptr)
    {
        printf("[write_png_file] png_create_info_struct failed");
        png_destroy_write_struct(&png_ptr, (png_infopp)NULL);
        fclose(fp);
        exit(EXIT_FAILURE);
    }

    if (setjmp(png_jmpbuf(png_ptr)))
    {
        printf("[write_png_file] Error during init_io");        
        fclose(fp);
        png_destroy_write_struct(&png_ptr, &info_ptr);
        exit(EXIT_FAILURE);
    }

    png_init_io(png_ptr, fp);

    if (setjmp(png_jmpbuf(png_ptr)))
    {
        printf("[write_png_file] Error during writing header");
        fclose(fp);
        png_destroy_write_struct(&png_ptr, &info_ptr);
        exit(EXIT_FAILURE);
    }

    png_set_IHDR(png_ptr, info_ptr, width, height,
                 bit_depth, color_type, PNG_INTERLACE_NONE,
                 PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);

    png_write_info(png_ptr, info_ptr);

    if (setjmp(png_jmpbuf(png_ptr)))
    {
        printf("[write_png_file] Error during writing bytes");
        fclose(fp);
        png_destroy_write_struct(&png_ptr, &info_ptr);
        exit(EXIT_FAILURE);
    }

    png_write_image(png_ptr, row_pointers);

    if (setjmp(png_jmpbuf(png_ptr)))
    {
        printf("[write_png_file] Error during end of write");
        fclose(fp);
        png_destroy_write_struct(&png_ptr, &info_ptr);
        exit(EXIT_FAILURE);
    }

    png_write_end(png_ptr, NULL);

    for (int y = 0; y < height; y++)
        free(row_pointers[y]);
    free(row_pointers);

    png_destroy_write_struct(&png_ptr, &info_ptr);

    fclose(fp);
}

void saveHistoryAsGif(Board** boards, int numberOfBoards, char* outputFile)
{
    if (numberOfBoards < 1)
        return;

    int width = boards[0]->sizeX;
    int heigth = boards[0]->sizeY;

    //Create gif
    ge_GIF* gif = ge_new_gif(
        outputFile,     //File name
        width, heigth,  //Gif size
        (uint8_t []) {  //Color palet
            0x00, 0x00, 0x00, // 0 -> black
            0xFF, 0xFF, 0xFF, // 1 -> white
        },
        1,      //Palette depth = Log2(colors)
        1       //How many times to loop. 0 = infinite
    );
    
    //Save each board
    for (int n = 0; n < numberOfBoards; n++)
    {
        Board* currentBoard = boards[n];

        //Set pixels of next frame
        for (int i = 0; i < heigth; i++)
        {
            for (int j = 0; j < width; j++)
            {
                int index = i * width + j;
                CellState state = currentBoard->cells[index];
                gif->frame[index] = (state == DEAD) ? 0 : 1;
            }
        }
        //Save frame
        ge_add_frame(gif, DELAY_IN_MS_BETWEEN_GIF_FRAMES);
    }

    ge_close_gif(gif); //Free memory
}