// 
// Created by Balajanovski on 29/09/2018.
//

#ifndef TEAPOT_DEMO_CLEANUP_H
#define TEAPOT_DEMO_CLEANUP_H

#include "NoCopy.h"

#include <cstdint>
#include <memory>
#include <sstream>
#include <iostream>

#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <glfw/glfw3.h>

[[noreturn]] inline void throwRuntimeError(const std::string &msg) {
    std::stringstream ss;
    ss << "error: " << msg;
    throw std::runtime_error(ss.str());
}

struct GlfwHandle : NoCopy {
    GlfwHandle(unsigned int major_version, unsigned int minor_version) {
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, major_version);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minor_version);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_SAMPLES, 4);

#ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    }

    ~GlfwHandle() { glfwTerminate(); }
};

template<typename... Args>
void cleanup(Args *... args){
    using ex = int[];
    (void)ex{(cleanup(args), 0)..., 0};
}
/*
 * These specializations serve to free the passed argument and also provide the
 * base cases for the recursive call above, eg. when args is only a single item
 * one of the specializations below will be called by
 * cleanup(std::forward<Args>(args)...), ending the recursion
 * We also make it safe to pass nullptrs to handle situations where we
 * don't want to bother finding out which values failed to load (and thus are null)
 * but rather just want to clean everything up and let cleanup sort it out
 */

inline void cleanup(GLFWwindow* win) {
    if (!win) {
        return;
    }
    glfwDestroyWindow(win);
}

struct Cleaner {
    template <class T>
    void operator() (T *p) const {
        cleanup(p);
    }
};

using glfwWinPtr = std::unique_ptr<GLFWwindow, Cleaner>;


#endif //TEAPOT_DEMO_CLEANUP_H
