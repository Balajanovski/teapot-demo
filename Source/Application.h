// 
// Created by Balajanovski on 29/09/2018.
//

#ifndef TEAPOT_DEMO_APPLICATION_H
#define TEAPOT_DEMO_APPLICATION_H

#include "Util/Cleanup.h"

#include "Util/Shader.h"
#include "Util/Model.h"

#include "Scene.h"

class Application : private GlfwHandle {
public:
    // Set scroll callback as friend
    friend void scroll_callback(GLFWwindow* window, double x_offset, double y_offset);

    Application();
    void render();
private:
    glfwWinPtr window;

    Shader shader;
    Scene scene;

    std::shared_ptr<Model> utah_teapot_model;
    std::shared_ptr<Model> table_model;
    std::shared_ptr<Model> stanford_dragon_model;

    std::shared_ptr<Object> dragon_object;
    std::shared_ptr<Object> teapot_object;
    std::shared_ptr<Object> table_object;

    float fov = 45.0f;
    static void scroll_callback(GLFWwindow* window, double x_offset, double y_offset);

    static constexpr unsigned int WINDOW_WIDTH = 680;
    static constexpr unsigned int WINDOW_HEIGHT = 680;
};


#endif //TEAPOT_DEMO_APPLICATION_H
