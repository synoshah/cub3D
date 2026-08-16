*This project has been created as part of the 42 curriculum by fbaras, synoshah*

## Description

### Camera Movement & Direction Vectors

To handle the camera movement and shifting direction vectors, I'm using two main functions: 
*   **COS**: Determines how much of the original horizontal axis we are keeping.
*   **SIN**: Determines how much we are "bleeding" into the perpendicular axis, and where on the radius we will land vertically.

In short: **Cos** measures how much of the original direction you keep along its own axis, while **Sine** measures how much transfers over into the perpendicular axis. 

Because we feed these functions radians instead of degrees, we have to convert them first. Let's say we want to shift our POV by 30 degrees. 30 degrees is roughly 0.5236 radians:
*   `cos(0.5236) = 0.866` (At 30 degrees, you keep approx 86.6% of the length)
*   `sin(0.5236) = 0.5` (At 30 degrees, exactly 50% transfers over)

#### The Math
If our starting position is `x = 3`, `y = 4`, we just plop the old coordinates into our formula with the new values we got. 

To find our new X:
`new_x = (old_x * 0.866) - (old_y * 0.5)`
`new_x = (3 * 0.866) - (4 * 0.5)`

**Breaking it down:**
For the first part, we are basically saying "take my original X and keep 86% of it." That gives us `2.5980`. 

The original Y was 4. Since we are turning counter-clockwise, the Y value is pushing the arrow further to the left, which reduces X. This says, "Take 50% of my Y value and subtract it from X." 
`2.5980 - 2.0000 = 0.5980`

Through this turn, the X value shrunk heavily from 3 down to 0.5980.

## Instructions

Run make to run the project.


## Resources

Learnt the concept of ray casting from lodev.org

Ray-Casting tutorial by permadi

3 Expert Tips for Using the Unit Circle by Hannah Muniz

Raycasting visualiser by "KernelOverseer"
