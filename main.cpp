#include <iostream>



#include "Game.h"

#define WIDTH 800
#define HEIGHT 600

void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

int main()
{
    Game game(WIDTH, HEIGHT);

    return 0;
}