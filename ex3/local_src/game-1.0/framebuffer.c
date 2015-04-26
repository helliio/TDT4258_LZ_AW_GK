#include "game.h"

int fbfd;
pixel_t (* fb)[screen_height][screen_width];

void setup_framebuffer(void)
{
    // mmap on non-regular files needs rw
    fbfd = open(fbdev, O_RDWR);
    {
        if(fbfd == -1)
        {
            perror("Could not open framebuffer '" fbdev "'");
            exit(EXIT_FAILURE);
        }
    }

    fb = mmap(NULL, fb_size, PROT_WRITE, MAP_SHARED, fbfd, 0);
    {
        if(fb == (void *) -1)
        {
            perror("Could not mmap framebuffer");
            exit(EXIT_FAILURE);
        }
    }

    memset(fb, black, fb_size);
    update_screen(0, 0, screen_width, screen_height);
}

void update_screen(int x, int y, int w, int h)
{
    struct fb_copyarea rect
        = { .dx = x
          , .dy = y
          , .width = w
          , .height = h
          };

    {
        // driver-specific ioctl to update screen
        int status = ioctl(fbfd, 0x4680, &rect);

        if(status == -1)
        {
            perror("Could not update framebuffer");
            exit(EXIT_FAILURE);
        }
    }
}
