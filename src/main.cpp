#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

#include "Render/VertexBuffer.h"
#include "Render/IndexBuffer.h"
#include "Render/VertexArrayObject.h"
#include "OS/WindowProcessing.h"
#include "Render/ShaderProgram.h"
#include "Render/Texture2D.h"
#include "Render/Camera/CameraController.h"
#include "Render/Objects/Primitives.h"

engine::CameraController camController;
float deltaTime = 0.0f, lastFrame = 0.0f;

int main()
{
    camController = engine::CameraController();
    auto cam1 = camController.CreateCamera( {2.5f, 0.0f, 0.5f}, 0.0f, -155.0f, 45.0f);
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

    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", nullptr, nullptr);
    if(window == nullptr)
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
    if(!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    engine::VertexBuffer vb(engine::primitives::cubeVertices, sizeof(engine::primitives::cubeVertices), GL_STATIC_DRAW);
    engine::IndexBuffer ib(engine::primitives::cubeIndices, sizeof(engine::primitives::cubeIndices), GL_STATIC_DRAW);

    engine::VertexArrayObject vao;
    vao.AddIndexBuffer(ib);
    vao.SetVertexAttribPointer(vb, 0, 3, GL_FLOAT, false, 8 * sizeof(float), nullptr);
    vao.SetVertexAttribPointer(vb, 1, 3, GL_FLOAT, false, 8 * sizeof(float), (void*) (3 * sizeof(float)));
    vao.SetVertexAttribPointer(vb, 2, 2, GL_FLOAT, false, 8 * sizeof(float), (void*) (6 * sizeof(float)));
    vao.EnableVertexAttribPointer(0);
    vao.EnableVertexAttribPointer(1);
    vao.EnableVertexAttribPointer(2);


    engine::ShaderProgram basicShader("res/shader/basic.vert", "res/shader/basic.frag");
    engine::ShaderProgram lightSourceShader("res/shader/basic.vert", "res/shader/lightSource.frag");

    engine::Texture2D diffuseMap("res/textures/box2.png", GL_RGBA, GL_RGB, GL_REPEAT, GL_REPEAT, GL_LINEAR, GL_LINEAR, true);
    engine::Texture2D specularMap("res/textures/box2_spec.png", GL_RGBA, GL_RGB, GL_REPEAT, GL_REPEAT, GL_LINEAR, GL_LINEAR, true);
    diffuseMap.SetTextureSlot(0);
    specularMap.SetTextureSlot(1);
    basicShader.LinkTextureSlotToUniform("material.diffuse", 0 );
    basicShader.LinkTextureSlotToUniform("material.specular", 1 );

    glEnable(GL_DEPTH_TEST);

    while(!glfwWindowShouldClose(window))
    {
        float currentFrame = (float)glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;


        engine::processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        vao.Bind();

        glm::mat4 projection;
        projection = glm::perspective(glm::radians(camController.GetActiveCameraPointer()->GetFov()), 800.0f / 600.0f, 0.1f, 100.0f);
        basicShader.SetUniformMatrix4fv("projection", 1, false, glm::value_ptr(projection));
        lightSourceShader.SetUniformMatrix4fv("projection", 1, false, glm::value_ptr(projection));

        glm::mat4 view;
        view = glm::lookAt(camController.GetActiveCameraPointer()->GetPositionVector(), camController.GetActiveCameraPointer()->GetPositionVector() + camController.GetActiveCameraPointer()->GetDirectionVector(), glm::vec3(0.0f, 1.0f, 0.0f));
        basicShader.SetUniformMatrix4fv("view", 1, false, glm::value_ptr(view));
        lightSourceShader.SetUniformMatrix4fv("view", 1, false, glm::value_ptr(view));


        basicShader.Bind();
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0, 0, -1));
        basicShader.SetUniformMatrix4fv("model", 1, false, glm::value_ptr(model));

        basicShader.SetUniform1f("material.shininess", 32.0f);

        basicShader.SetUniform3f("light.position", {2.0f, 0.0f, 1.0f});
        basicShader.SetUniform3f("light.ambient", {0.2f, 0.2f, 0.2f});
        basicShader.SetUniform3f("light.diffuse", {0.5f, 0.5f, 0.5f});
        basicShader.SetUniform3f("light.specular", {1.0f, 1.0f, 1.0f});

        basicShader.SetUniform3f("viewPos", {camController.GetActiveCameraPointer()->GetPositionVector().x,camController.GetActiveCameraPointer()->GetPositionVector().y,camController.GetActiveCameraPointer()->GetPositionVector().z});
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, nullptr);
        basicShader.Unbind();

        lightSourceShader.Bind();
        model = glm::mat4(1.0f);
        model = glm::scale(model, glm::vec3(0.3, 0.3, 0.3));
        model = glm::translate(model, glm::vec3(2, 0, 1));
        lightSourceShader.SetUniformMatrix4fv("model", 1, false, glm::value_ptr(model));
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, nullptr);
        lightSourceShader.Unbind();


        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}
