#include "GraphicsGenerator.h"

static double myCeil(double number)
{
    double increased = number + 0.5;

    int a = (int)number;
    int b = (int)increased;

    if (b - a == 0) //Number should be rounded down
        return number;
    else
        return increased;
}

void savePng(Board *board, char *outputFile)
{
    //Set up setting
    png_byte color_type = PNG_COLOR_TYPE_GRAY;
    png_byte bit_depth = 8;

    int width;
    int height;
    getUpscaledImageSize(board->sizeX, board->sizeY, &width, &height);

    Pixel *orginalImage = translateBoardToPixels(board, 255, 0);
    Pixel *scaledImage = upscaleImage(orginalImage, board->sizeX, board->sizeY);
    free(orginalImage);

    png_bytep *row_pointers = (png_bytep *)malloc(sizeof(png_bytep) * height);
    for (int y = 0; y < height; y++)
        row_pointers[y] = (png_byte *)malloc(sizeof(png_byte) * width);

    for (int y = 0; y < height; y++)
    {
        png_byte *row = row_pointers[y];
        for (int x = 0; x < width; x++)
        {
            row[x] = scaledImage[y * width + x];
        }
    }
    free(scaledImage);

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

void saveHistoryAsGif(Board **boards, int numberOfBoards, char *outputFile, int delay)
{
    if (numberOfBoards < 1)
        return;

    int gifWidth;
    int gifHeigth;
    getUpscaledImageSize(boards[0]->sizeX, boards[0]->sizeY, &gifWidth, &gifHeigth);

    //Create gif
    ge_GIF *gif = ge_new_gif(
        outputFile,          //File name
        gifWidth, gifHeigth, //Gif size
        (uint8_t[]){
            //Color pallet
            0x00, 0x00, 0x00, // 0 -> black
            0xFF, 0xFF, 0xFF, // 1 -> white
        },
        1, //Palette depth = Log2(colors)
        1  //How many times to loop. 0 = infinite
    );

    //Save each board
    for (int n = 0; n < numberOfBoards; n++)
    {
        Board *currentBoard = boards[n];

        Pixel *normalImage = translateBoardToPixels(currentBoard, 1, 0);
        Pixel *scaledImage = upscaleImage(normalImage, currentBoard->sizeX, currentBoard->sizeY);
        free(normalImage);

        // Set frame pixels
        for (int i = 0; i < gifHeigth; i++)
        {
            for (int j = 0; j < gifWidth; j++)
            {
                int index = i * gifWidth + j;
                gif->frame[index] = scaledImage[index];
            }
        }
        free(scaledImage);

        //Save frame
        ge_add_frame(gif, delay);
    }

    ge_close_gif(gif); //Free memory
}

Pixel *translateBoardToPixels(Board *board, Pixel valueOfAlive, Pixel valueOfDead)
{
    Pixel *image = malloc(board->sizeY * board->sizeX * sizeof(*image));

    for (int i = 0; i < board->sizeY; i++)
    {
        for (int j = 0; j < board->sizeX; j++)
        {
            int index = i * board->sizeX + j;
            CellState state = board->cells[index];
            image[index] = (state == ALIVE) ? valueOfAlive : valueOfDead;
        }
    }

    return image;
}

void getUpscaledImageSize(int orginalX, int orginalY, int *newX, int *newY)
{
    int max = (orginalX > orginalY) ? orginalX : orginalY;

    int multiplier = myCeil((double)MIN_IMAGE_SIZE / (double)max);
    if (max >= MIN_IMAGE_SIZE)
        multiplier = 1;

    *newX = orginalX * multiplier;
    *newY = orginalY * multiplier;
}

Pixel *upscaleImage(const Pixel *original, int imageX, int imageY)
{
    int newX;
    int newY;
    getUpscaledImageSize(imageX, imageY, &newX, &newY);

    Pixel *resizedImage = malloc(newX * newY * sizeof(*resizedImage));
    for (int i = 0; i < newY; i++)
    {
        for (int j = 0; j < newX; j++)
        {
            int xIndex = j * imageX / newX;
            int yIndex = i * imageY / newY;

            resizedImage[i * newX + j] = original[yIndex * imageX + xIndex];
        }
    }

    return resizedImage;
}