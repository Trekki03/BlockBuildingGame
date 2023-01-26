#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <algorithm>
#include "OS/WindowProcessing.h"
#include "Render/ShaderProgram.h"
#include "Render/Texture2D.h"
#include "Render/Camera/CameraController.h"
#include "Game/World/Objects/BlockManager.h"
#include "Game/World/WorldGen/Chunk.h"

engine::CameraController camController;
float deltaTime = 0.0f, lastFrame = 0.0f;

int main()
{
    camController = engine::CameraController();
    auto cam1 = camController.CreateCamera({40.0f, 250.0f, 0.5f}, 0.0f, -155.0f, 45.0f);
    camController.SetActiveCamera(cam1);

    glfwInit();
    //Set OpenGL Context to Version 3.3 core
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);    //Needed by MacOS
#endif

    GLFWwindow *window = glfwCreateWindow(800, 600, "LearnOpenGL", nullptr, nullptr);
    if (window == nullptr)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwSetFramebufferSizeCallback(window, engine::framebuffer_size_callback);
    glfwMakeContextCurrent(window);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(window, engine::mouse_callback);
    glfwSetScrollCallback(window, engine::scroll_callback);
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    game::BlockManager manager;

    engine::ShaderProgram basicShader("res/shader/basic.vert", "res/shader/basic.frag");
    engine::ShaderProgram lightSourceShader("res/shader/basic.vert", "res/shader/lightSource.frag");

    engine::Texture2D diffuseMap("res/textures/TextureAtlas.jpg", GL_RGB, GL_RGB, GL_REPEAT, GL_REPEAT, GL_NEAREST,
                                 GL_NEAREST, false);
    engine::Texture2D specularMap("res/textures/TextureAtlas.jpg", GL_RGB, GL_RGB, GL_REPEAT, GL_REPEAT, GL_NEAREST,
                                  GL_NEAREST, false);
    diffuseMap.SetTextureSlot(0);
    specularMap.SetTextureSlot(1);
    basicShader.LinkTextureSlotToUniform("material.diffuse", 0);
    basicShader.LinkTextureSlotToUniform("material.specular", 1);

    glEnable(GL_DEPTH_TEST);


    game::Chunk *chunks[4][4];
    for (int x = 0; x < 4; x++)
    {
        for (int y = 0; y < 4; y++)
        {
            chunks[x][y] = new game::Chunk(&manager);
        }
    }

    while(!glfwWindowShouldClose(window))
    {
        float currentFrame = (float)glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        engine::processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glm::mat4 projection;
        projection = glm::perspective(glm::radians(camController.GetActiveCameraPointer()->GetFov()), 800.0f / 600.0f, 0.1f, 100.0f);
        basicShader.SetUniformMatrix4fv("projection", 1, false, glm::value_ptr(projection));
        lightSourceShader.SetUniformMatrix4fv("projection", 1, false, glm::value_ptr(projection));

        glm::mat4 view;
        view = glm::lookAt(camController.GetActiveCameraPointer()->GetPositionVector(), camController.GetActiveCameraPointer()->GetPositionVector() + camController.GetActiveCameraPointer()->GetDirectionVector(), glm::vec3(0.0f, 1.0f, 0.0f));
        basicShader.SetUniformMatrix4fv("view", 1, false, glm::value_ptr(view));
        lightSourceShader.SetUniformMatrix4fv("view", 1, false, glm::value_ptr(view));


        //Draw Cubes
        basicShader.Bind();
        basicShader.SetUniform1f("material.shininess", 32.0f);
        basicShader.SetUniform3f("light.position", {2.0f, 6.0f, 1.0f});
        basicShader.SetUniform3f("light.ambient", {0.4f, 0.4f, 0.4f});
        basicShader.SetUniform3f("light.diffuse", {0.5f, 0.5f, 0.5f});
        basicShader.SetUniform3f("light.specular", {1.0f, 1.0f, 1.0f});
        basicShader.SetUniform3f("viewPos", {camController.GetActiveCameraPointer()->GetPositionVector().x,camController.GetActiveCameraPointer()->GetPositionVector().y,camController.GetActiveCameraPointer()->GetPositionVector().z});

        glm::mat4 model;
        for(int cx = 0; cx < 4; cx++)
        {
            for(int cz = 0; cz < 4; cz++)
            {
                model = glm::mat4(1.0f);
                model = glm::translate(model, glm::vec3(cx*16, 0,cz*16));
                basicShader.SetUniformMatrix4fv("model", 1, false, glm::value_ptr(model));

                engine::VertexArrayObject* vao = chunks[cx][cz]->GetVao();
                if(vao == nullptr)
                { continue;}
                vao->Bind();

                glDrawElements(GL_TRIANGLES, vao->GetVertexCount(), GL_UNSIGNED_INT, nullptr);
                vao->Unbind();

            }
        }
        basicShader.Unbind();

        //Draw light source
        /*lightSourceShader.Bind();
        model = glm::mat4(1.0f);
        model = glm::scale(model, glm::vec3(0.3, 0.3, 0.3));
        model = glm::translate(model, glm::vec3(2, 6, 1));
        lightSourceShader.SetUniformMatrix4fv("model", 1, false, glm::value_ptr(model));
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, nullptr);
        lightSourceShader.Unbind();*/

        std::cout << 1/deltaTime << std::endl;

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();

    return 0;
}

