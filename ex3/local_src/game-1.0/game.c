#include "game.h"

struct rect
{
    int x, y, w, h;
    int old_x, old_y;
};

struct rect pad_l =
{
    .x = 10,
    .y = (240-50)/2,
    .w = 10,
    .h = 50,
};

struct rect pad_r =
{
    .x = 320-10-10,
    .y = (240-50)/2,
    .w = 10,
    .h = 50,
};

struct rect ball =
{
    .x = 30,
    .y = (240-10)/2,
    .w = 10,
    .h = 10,
};

void really_draw_rect(pixel_t color, int x, int y, int w, int h)
{
    for(int yp = y; yp < (y+h); yp++)
        for(int xp = x; xp < (x+w); xp++)
            (*fb)[yp][xp] = color;
}

void draw_rect(struct rect * r)
{
    // TODO: Framebuffers often have a fill rect function.
    // Use that instead.

    {
        int x = r->old_x;
        int y = r->old_y;
        int w = r->w;
        int h = r->h;

        really_draw_rect(black, x,y,w,h);
    }


    {
        int x = r->x;
        int y = r->y;
        int w = r->w;
        int h = r->h;

        really_draw_rect(white, x,y,w,h);
    }

    update_screen( min(r->x, r->old_x), min(r->y, r->old_y)
                 ,(max(r->x, r->old_x) + r->w) - min(r->x, r->old_x)
                 ,(max(r->y, r->old_y) + r->h) - min(r->y, r->old_y) + 1);

    r->old_x = r->x;
    r->old_y = r->y;
}

#define left (-1)
#define right (1)

void update_ball(void)
{
    static int ball_dir = right;
    static int ball_vvel = 0;
    static int vvel_track = 0;

    if(
            (ball_dir == left
             && ball.x <= (pad_l.x + pad_l.w)
             && (ball.y + ball.h) > pad_l.y
             && ball.y < (pad_l.y + pad_l.h)
             )
            ||
            (
             ball_dir == right
             && (ball.x + ball.w) > pad_r.x
             && (ball.y + ball.h) > pad_r.y
             && ball.y < (pad_r.y + pad_r.h)
            )
      )
    {
        ball_dir *= -1;
        ball_vvel = ((pad_l.y + pad_l.h/2) - (ball.y + ball.h/2)) * 100 / pad_l.h;
    }

    if(
            (ball_vvel < 0 && ball.y == 0)
            ||
            (ball_vvel > 0 && ball.y+ball.h == screen_height - 1)
      )
    {
        ball_vvel *= -1;
        vvel_track *= -1;
    }

    if((ball_dir == left && ball.x > 0) || (ball_dir == right && ball.x + ball.w < screen_width))
        ball.x += ball_dir;
    else
    {
        ball_vvel = 0;
        vvel_track = 0;
    }

    vvel_track += ball_vvel;

    if(vvel_track >= 100)
    {
        ball.y += 1;
        vvel_track = 0;
    }
    if(vvel_track <= -100)
    {
        ball.y -= 1;
        vvel_track = 0;
    }
}

int gpfd;

void update_paddle(void)
{
    uint32_t din;
    read(gpfd, &din, 1);

    if(din & 1<<1)
        pad_l.y++;

    if(din & 1<<3)
        pad_l.y--;

    // R folows ball
    pad_r.y = ball.y - pad_r.h/2 + ball.h/2;
}

void update_game(void)
{
    draw_rect(&pad_l);
    draw_rect(&pad_r);
    draw_rect(&ball);

    update_ball();
    update_paddle();

 //   usleep(300e3);
}

int main(int argc, char *argv[])
{
	printf("Hello, this is Game!\n");

    gpfd = open("/dev/pad", O_RDONLY);
    {
        if(gpfd == -1)
        {
            perror("Could not open gamepad dev");
            exit(EXIT_FAILURE);
        }
    }

    setup_framebuffer();

    for(;;) update_game();
}
