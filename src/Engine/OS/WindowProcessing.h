#ifndef BLOCKBUILDINGGAME_WINDOWPROCESSING_H
#define BLOCKBUILDINGGAME_WINDOWPROCESSING_H

#include <GLFW/glfw3.h>

namespace engine
{
    void framebuffer_size_callback(GLFWwindow* window, int width, int height);
    void processInput(GLFWwindow* window);
    void mouse_callback(GLFWwindow* window, double xPos, double yPos);
    void scroll_callback(GLFWwindow* window, double xOffset, double yOffset);
}

#endif //BLOCKBUILDINGGAME_WINDOWPROCESSING_H
