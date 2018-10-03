// 
// Created by Balajanovski on 29/09/2018.
//

#include "Application.h"

#include "Util/Filesystem.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "TeapotMaterials.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

Application::Application()
        : GlfwHandle(3, 3) {

    window.reset(glfwCreateWindow(WINDOW_WIDTH,
                                  WINDOW_HEIGHT, "Teapot Demo", nullptr, nullptr));
    if (!window) {
        throwRuntimeError("Failed to create GLFW window");
    }
    glfwMakeContextCurrent(window.get());
    glfwSetFramebufferSizeCallback(window.get(), framebuffer_size_callback);
    // Use user pointer to allow for callback to access class members
    glfwSetWindowUserPointer(window.get(), this);
    glfwSetScrollCallback(window.get(), Application::scroll_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        throwRuntimeError("Failed to initialize GLAD");
    }

    glEnable(GL_DEPTH_TEST);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);

    glEnable(GL_MULTISAMPLE);

    shader = Shader(FileSystem::getPath("Shaders/vertex.vert").c_str(),
                    FileSystem::getPath("Shaders/fragment.frag").c_str());


    utah_teapot_model = std::make_shared<Model>(FileSystem::getPath("Resources/Models/utah-teapot.obj"), scene);
    table_model = std::make_shared<Model>(FileSystem::getPath("Resources/Models/table.3DS"), scene);
    stanford_dragon_model = std::make_shared<Model>(FileSystem::getPath("Resources/Models/dragon.obj"), scene);

    glm::mat4 model;
    model = glm::mat4(1.0);
    model = glm::scale(model, glm::vec3(0.2, 0.2, 0.2));
    model = glm::translate(model, glm::vec3(-4.2, -1, 0));
    teapot_object = scene.AddObject(utah_teapot_model, model, materials_list.find("emerald")->second);

    model = glm::mat4(1.0);
    model = glm::scale(model, glm::vec3(0.05, 0.05, 0.05));
    model = glm::translate(model, glm::vec3(0, -56, 0));
    table_object = scene.AddObject(table_model, model, materials_list.find("green plastic")->second);

    model = glm::mat4(1.0);
    model = glm::scale(model, glm::vec3(0.1, 0.1, 0.1));
    model = glm::translate(model, glm::vec3(4.2, -2, 0));
    model = glm::rotate(model, 0.0f, glm::vec3(0, 1, 0));
    dragon_object = scene.AddObject(stanford_dragon_model, model, materials_list.find("jade")->second);
}

void Application::render() {
    while (!glfwWindowShouldClose(window.get())) {
        glClearColor(0.0, 0.0, 0.0, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader.use();

        // projection transformation
        glm::mat4 projection = glm::perspective(glm::radians(fov),
                                                (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT, 0.1f, 100.0f);
        int projection_loc = glGetUniformLocation(static_cast<GLuint>(shader.ID()), "projection");
        glUniformMatrix4fv(projection_loc, 1, GL_FALSE, glm::value_ptr(projection));
        // view transformation
        glm::mat4 view = glm::lookAt(glm::vec3(0, 0.5, -4), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
        int view_loc = glGetUniformLocation(static_cast<GLuint>(shader.ID()), "view");
        glUniformMatrix4fv(view_loc, 1, GL_FALSE, glm::value_ptr(view));

        glm::mat4 model = glm::mat4(1.0);
        model = glm::scale(model, glm::vec3(0.1, 0.1, 0.1));
        model = glm::translate(model, glm::vec3(4.2 * cos(glfwGetTime()), -2, 4.2 * sin(glfwGetTime())));
        model = glm::rotate(model, -static_cast<float>(glfwGetTime()), glm::vec3(0, 1, 0));
        dragon_object->ChangeModelMatrix(model);

        model = glm::mat4(1.0);
        model = glm::scale(model, glm::vec3(0.2, 0.2, 0.2));
        model = glm::translate(model, glm::vec3(-4.2 * cos(glfwGetTime()), -1, -4.2 * sin(glfwGetTime())));
        model = glm::rotate(model, -static_cast<float>(glfwGetTime()), glm::vec3(0, 1, 0));
        teapot_object->ChangeModelMatrix(model);

        model = glm::mat4(1.0);
        model = glm::scale(model, glm::vec3(0.05, 0.05, 0.05));
        model = glm::translate(model, glm::vec3(0, -56, 0));
        model = glm::rotate(model, -static_cast<float>(glfwGetTime()), glm::vec3(0, 1, 0));
        table_object->ChangeModelMatrix(model);

        scene.Draw(shader);

        glfwSwapBuffers(window.get());
        glfwPollEvents();
    }
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void Application::scroll_callback(GLFWwindow *window, double x_offset, double y_offset) {
    auto application = static_cast<Application*>(glfwGetWindowUserPointer(window));

    if (application->fov >= 1.0f && application->fov <= 45.0f)
        application->fov -= y_offset;
    if (application->fov <= 1.0f)
        application->fov = 1.0f;
    if (application->fov >= 45.0f)
        application->fov = 45.0f;
}