#include "WindowProcessing.h"
#include <glm/glm.hpp>
#include "Render/Camera/CameraController.h"

bool wireMode = false;
bool lastKeyState_V = false;
bool firstMouse = true;

extern float deltaTime;
extern engine::CameraController camController;

namespace engine
{
    void framebuffer_size_callback(GLFWwindow* window, int width, int height)
    {
        glViewport(0, 0, width, height);
    }

    void processInput(GLFWwindow* window)
    {
        if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        {
            glfwSetWindowShouldClose(window, true);
        }

        if(glfwGetKey(window, GLFW_KEY_V) == GLFW_PRESS)
        {
            if(lastKeyState_V)
            {
                return;
            }

            lastKeyState_V = true;
            if (wireMode)
            {
                glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                wireMode = false;
            } else
            {
                glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                wireMode = true;
            }

        }
        else if( (glfwGetKey(window, GLFW_KEY_V) == GLFW_RELEASE) && lastKeyState_V)
        {
            lastKeyState_V = false;
        }

        const float cameraSpeed = 2.5f * deltaTime;

        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        {
            camController.GetActiveCameraPointer()->AddPositionVector(cameraSpeed * camController.GetActiveCameraPointer()->GetDirectionVector());
        }

        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        {
            camController.GetActiveCameraPointer()->AddPositionVector(-(cameraSpeed * camController.GetActiveCameraPointer()->GetDirectionVector()));
        }

        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        {
            camController.GetActiveCameraPointer()->AddPositionVector( - (glm::normalize(
                    glm::cross(camController.GetActiveCameraPointer()->GetDirectionVector(),glm::vec3(0.0f, 1.0f, 0.0f)))
                                                                          * cameraSpeed));
        }

        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        {
            camController.GetActiveCameraPointer()->AddPositionVector ( glm::normalize(
                    glm::cross(camController.GetActiveCameraPointer()->GetDirectionVector(), glm::vec3(0.0f, 1.0f, 0.0f)))
                                                                        * cameraSpeed);
        }
    }

    float lastX = 400, lastY = 300;
    void mouse_callback(GLFWwindow* window, double xPos, double yPos)
    {
        if(firstMouse)
        {
            lastX = xPos;
            lastY = yPos;
            firstMouse = !firstMouse;
        }

        float xOffset = xPos - lastX;
        float yOffset = lastY - yPos;
        lastX = xPos;
        lastY = yPos;

        const float sensitivity = 0.1f;
        xOffset *= sensitivity;
        yOffset *= sensitivity;

        camController.GetActiveCameraPointer()->AddYaw(xOffset);
        camController.GetActiveCameraPointer()->AddPitch(yOffset);

    }

    void scroll_callback(GLFWwindow* window, double xOffset, double yOffset)
    {
        camController.GetActiveCameraPointer()->AddFov((float)yOffset);
    }
}