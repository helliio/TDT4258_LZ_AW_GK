#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
//#include <string.h>

#include <stdio.h>
#include <fcntl.h>

#include <linux/fb.h>
#include <sys/mman.h>
#include <sys/ioctl.h>

#define FBDEV "/dev/fb0"
#define SCREEN_WIDTH (320)
#define SCREEN_HEIGHT (240)
#define SCREEN_SIZE (SCREEN_WIDTH*SCREEN_HEIGHT)

/** Compose colors of a 5-5-6 bit rgb pixel.
 */
uint16_t to_pixel(uint8_t red, uint8_t green, uint8_t blue)
{
    return red << (5+6) | green << 6 | blue;
}

void draw_something(uint16_t * fb)
{
    for(int y = 0; y < SCREEN_HEIGHT; y++)
    {
        for(int x = 0; x < SCREEN_WIDTH; x++)
        {
            uint16_t pixel = to_pixel((x-50), (y-50), (31 - (x-50)));
            *fb++ = pixel;
        }
    }
}

int main(int argc, char *argv[])
{
	printf("Hello World, I'm fbtest-fileop!\n");

    // mmap on non-regular files needs rw
	int fbfd = open(FBDEV, O_RDWR);
    {
        if(fbfd == -1)
        {
            perror("Could not open framebuffer '" FBDEV "'");
            exit(EXIT_FAILURE);
        }
    }

    uint16_t * fb = mmap(NULL, 2*SCREEN_SIZE, PROT_WRITE, MAP_SHARED, fbfd, 0);
    {
        if(fb == (void *) -1)
        {
            perror("Could not mmap framebuffer");
            exit(EXIT_FAILURE);
        }
    }

    draw_something(fb);

    struct fb_copyarea rect
        = { .dx = 0
          , .dy = 0
          , .width = SCREEN_WIDTH
          , .height = SCREEN_HEIGHT
          };

    // driver-specific ioctl to update screen
    ioctl(fbfd, 0x4680, &rect);

    munmap(fb, 2*SCREEN_SIZE);

    close(fbfd);

	exit(EXIT_SUCCESS);
}
