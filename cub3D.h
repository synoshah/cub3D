#ifndef CUB3D_H
#define CUB3D_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <mlx.h>
#include <math.h>

#include "include/image.h"
#include "include/shapes.h"

#define KEY_W 119
#define KEY_S 115
#define KEY_A 97
#define KEY_D 100
#define KEY_ESC 65307
#define KEY_LEFT 65361
#define KEY_RIGHT 65363

typedef struct s_player
{
    double pypos_x; // double because we need to implement small steps.
    double pypos_y;

    double dir_x; // the dda algorithm needs to know the exact center point 
    double dir_y; // of your vision to calculate where to cast the rays.

    double camera_x; // This determines your field of view.
    double camera_y; //  Without this plane, our engine can only shoot one laser straight ahead. The engine uses this line to spread the 800 rays across the screen.
    // It start from the extreme left axis_y(0) and goes till the extreme right axis_x(800).

    double move_speed; // what it says.

    double rotation_speed; // degrees to turn.

    void *player;
}   t_player;

#endif