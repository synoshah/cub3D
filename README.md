*This project has been created as part of the 42 curriculum by synoshah, fbaras*

## Description

We have built a custom raycasting engine written in C that uses miniLibX to project simple 2D grids into a 3D first-person perspective.

![alt text](<Screenshot from 2026-09-04 15-53-18.png>)
![alt text](<Screenshot from 2026-09-04 15-53-45.png>)
![alt text](<Screenshot from 2026-09-04 15-54-01.png>)
![alt text](<Screenshot from 2026-09-04 15-54-17.png>)

## Instructions

**Compile and run the Mandatory and Bonus**

- make
- ./cub3D maps/map.cub

- make bonus
- ./cub3D_bonus maps/map1.cub

- To check the codebase against the norminette while excluding the external minilibx library, run this at the root:

norminette $(find . -name "*.c" -o -name "*.h" | grep -v minilibx)

## Resources

- Learnt the concept of ray casting from lodev.org

- Ray-Casting tutorial by permadi

- 3 Expert Tips for Using the Unit Circle by Hannah Muniz

- Raycasting visualiser by "KernelOverseer"

**AI Usage:**

- AI was mainly used for finding faults in the code and giving suggestions when it came to trimming down functions to 25 lines.