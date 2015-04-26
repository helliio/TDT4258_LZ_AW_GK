// We want access to nonstandard stuff
#define _BSD_SOURCE

#include <stdlib.h>    // NULL, EXIT_FAILURE
#include <stdint.h>    // uint16_t
#include <stdio.h>     // printf, perror
#include <fcntl.h>     // open
#include <sys/mman.h>  // mmap
#include <linux/fb.h>  // fb_copyarea
#include <sys/ioctl.h> // ioctl
#include <unistd.h>    // usleep
#include <string.h>    // memset


#define fbdev "/dev/fb0"
#define screen_width (320)
#define screen_height (240)
#define fb_size (sizeof(pixel_t)*screen_width*screen_height)
#define white (0xffff)
#define black (0x0000)

#define max(a,b) (((a) > (b)) ? (a) : (b))
#define min(a,b) (((a) < (b)) ? (a) : (b))

typedef uint16_t pixel_t;

void setup_framebuffer(void);
void update_screen(int x, int y, int w, int h);

extern int fbfd;
extern pixel_t (* fb)[screen_height][screen_width];
