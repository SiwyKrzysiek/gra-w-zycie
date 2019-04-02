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

void saveHistoryAsGif(Board** boards, int numberOfBoards, char* outputFile, int delay)
{
    if (numberOfBoards < 1)
        return;

    int width;
    int heigth;
    getUpscaledImageSize(boards[0]->sizeX, boards[0]->sizeY, &width, &heigth);

    //Create gif
    ge_GIF* gif = ge_new_gif(
        outputFile,     //File name
        width, heigth,  //Gif size
        (uint8_t []) {  //Color pallet
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
        Pixel normalImage[currentBoard->sizeX * currentBoard->sizeY];

        //Set pixels of normal image
        for (int i = 0; i < currentBoard->sizeY; i++)
        {
            for (int j = 0; j < currentBoard->sizeX; j++)
            {
                int index = i * currentBoard->sizeX + j;
                CellState state = currentBoard->cells[index];
                normalImage[index] = (state == DEAD) ? 0 : 1;
            }
        }

        int x, y;
        Pixel* scaledImage = upscaleImage(normalImage, currentBoard->sizeX, currentBoard->sizeY, &x, &y);

        // Set frame pixels
        for (int i = 0; i < y; i++)
        {
            for (int j = 0; j < x; j++)
            {
                int index = i * width + j;
                gif->frame[index] = scaledImage[index];
            }
        }

        free(scaledImage);

        //Save frame
        ge_add_frame(gif, delay);
    }

    ge_close_gif(gif); //Free memory
}

void getUpscaledImageSize(int orginalX, int orginalY, int* newX, int* newY)
{
    int max = (orginalX > orginalY) ? orginalX : orginalY;

    int multiplier = ceil((double) MIN_IMAGE_SIZE / (double) max);
    if (max >= MIN_IMAGE_SIZE)
        multiplier = 1;

    *newX = orginalX*multiplier;
    *newY = orginalY*multiplier;
}

Pixel* upscaleImage(const Pixel* original, int imageX, int imageY, int* newX, int* newY)
{
    int max = (imageX > imageY) ? imageX : imageY;

    int multiplier = ceil((double) MIN_IMAGE_SIZE / (double) max);
    if (max >= MIN_IMAGE_SIZE)
        multiplier = 1;

    int newXdim = imageX*multiplier;
    int newYdim = imageY*multiplier;

    Pixel* resizedImage = malloc(newXdim * newYdim * sizeof(*resizedImage));
    for(int i = 0; i < newYdim; i++)
    {
        for(int j = 0; j < newXdim; j++)
        {
            int xIndex = j*imageX/newXdim;
            int yIndex = i*imageY/newYdim;

            resizedImage[i*newXdim + j] = original[yIndex*imageX + xIndex];
        }
    }

    *newX = newXdim;
    *newY = newYdim;

    return resizedImage;
}