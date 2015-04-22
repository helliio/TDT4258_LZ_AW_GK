#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#define FBDEV "/dev/fb0"
#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240

/** Compose colors of a 5-5-6 bit rgb pixel.
 */
uint16_t to_pixel(uint8_t red, uint8_t green, uint8_t blue)
{
    return red << (5+6) | green << 6 | blue;
}

void draw_something(FILE * fb)
{
    for(int y = 0; y < SCREEN_HEIGHT - 100; y++)
    {
        for(int x = 0; x < SCREEN_WIDTH - 100; x++)
        {
            //if( x < 50 || (50 + 31) < x
            // || y < 50 || (50 + 63) < y )
            //{
            //    //(*buf)[y][x] = to_pixel(0,0,0);
            //}
            //else
            //{
                uint16_t pixel = to_pixel((x-50), (y-50), (31 - (x-50)));
                fwrite(&pixel, sizeof(uint16_t), 1, fb);
            //}
        }
    }
}

int main(int argc, char *argv[])
{
	printf("Hello World, I'm fbtest-fileop!\n");

	FILE * fb = fopen(FBDEV, "w");
    {
        if(fb == NULL)
        {
            perror("Could not open framebuffer '" FBDEV "'");
            exit(EXIT_FAILURE);
        }
    }

    draw_something(fb);

    fclose(fb);

	exit(EXIT_SUCCESS);
}
