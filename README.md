*This project has been created as part of the 42 curriculum by fbaras, synoshah*

## Description

## Direction Vectors & Camera Movement

To handle camera rotation, we need to calculate how our direction vectors shift when the player turns. We achieve this using a 2D rotation matrix, which relies on the trigonometric functions Sine and Cosine.

Because these functions expect radians rather than degrees, any degree value must first be converted. For example, $30^\circ$ is approximately $0.5236$ radians.

### The Core Concepts
*   **Cosine ($\cos$)**: Measures how much of the original direction you keep along its own axis. For a $30^\circ$ turn, you retain approximately $86.6\%$ of the length ($\cos(0.5236) \approx 0.866$).
*   **Sine ($\sin$)**: Measures how much the vector "bleeds" or transfers over into the perpendicular axis. For a $30^\circ$ turn, exactly $50\%$ transfers over ($\sin(0.5236) = 0.5$).

### The Rotation Formula
To find our new direction vector, we pass our old coordinates into the standard 2D rotation formulas:

$$x' = x \cos(\theta) - y \sin(\theta)$$
$$y' = x \sin(\theta) + y \cos(\theta)$$

### Step-by-Step Example
Let's assume our starting position is $(x: 3, y: 4)$ and we want to shift our POV by $30^\circ$ counter-clockwise. Let's calculate our new $x$ position ($x'$):

1. **Calculate the X retention:** Take the original $x$ and keep $86.6\%$ of it. 
   $3 \times 0.866 = 2.598$
2. **Calculate the Y transfer:** Since we are turning counter-clockwise, the $y$ value pushes the vector further to the left, which reduces our total $x$. We take $50\%$ of our $y$ value to subtract from $x$.
   $4 \times 0.5 = 2.0$
3. **Calculate the final X:** 
   $2.598 - 2.0 = 0.598$

Through this rotation, the $x$ value shrinks heavily from $3$ down to $0.598$ because the $30^\circ$ turn redirected a large portion of the vector's magnitude into the $y$-axis.

## Instructions

Run make to run the project.


## Resources

Learnt the concept of ray casting from lodev.org

Ray-Casting tutorial by permadi

3 Expert Tips for Using the Unit Circle by Hannah Muniz

Raycasting visualiser by "KernelOverseer"
