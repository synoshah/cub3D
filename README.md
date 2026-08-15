*This project has been created as part of the 42 curriculum by fbaras, synoshah*

## Description

Start -> Working on the direction vectors / camera movement. I use functions COS(To how much of the horizontal axis we are keeping),
 and SIN(To see how much we are bleeding in the perpendicual axis, and where on the radious we will land vertically).
We feed these functions radians. let's say we want to shift our pov by 30 degrees, we will first convert the degree value into radians, 30 degrees is radians 0.5236~, cos(0.5236) = 0.866, sin(0.5236) = 0.5.

if our starting postion is let's say 3x, 4y. We will plop the old cordnites into our formula with the new value we just got.
 new_x = (3(old_x position * 0.866) - (4(old_y postion) * 0.5))
 for the first part we are saying take my original x and keep 86% of it. That gives us 2.5980. The original Y was 4. Since we are turning counter clockwise, the Y value is pushing the arrow further to the left (reducing X). This says, "Take 50% of my Y value and subtract it from X". 2.5980 - 2.0000 = 0.5980.
 The X value shrunk heavily from 3 down to 0.5980.

Cos measures how much of the original direction you keep along its own axis. At 30, you keep approx 86.6% of the length.

Sine measures how much "bleeds" or transfers over into the perpendicular axis. At 30, exactly 50% transfers over.



## Instructions

Run make to run the project.


## Resources

Learnt the concept of ray casting from lodev.org

Ray-Casting tutorial by permadi

3 Expert Tips for Using the Unit Circle by Hannah Muniz

Raycasting visualiser by "KernelOverseer"