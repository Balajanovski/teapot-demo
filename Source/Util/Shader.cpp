#include "Shader.h"

#include <fstream>
#include <sstream>
#include <iostream>
#include <cassert>

Shader::Shader(Shader&& other) : m_ID(other.m_ID) {
    // Increase the references counter
    (*m_references) += 1;
    other.m_references = m_references;
}

Shader& Shader::operator=(Shader&& rhs) {
    m_ID = rhs.m_ID;

    // Increase the references counter
    (*m_references) += 1;
    rhs.m_references = m_references;

    return *this;
}

Shader::~Shader() {
    // If there are no other references, delete the shader
    if (*m_references == 0) {
        glDeleteProgram(m_ID);
        return;
    }

    // Otherwise do nothing and just decrease the ref counter
    (*m_references) -= 1;
}

Shader::Shader(const char *vertex_path, const char *fragment_path) : m_references(std::make_shared<unsigned int>(0)) {

    // 1. retrieve the vertex/fragment source code from filePath
    std::string vertex_code;
    std::string fragment_code;
    std::ifstream vertex_shader_file;
    std::ifstream fragment_shader_file;

    // ensure ifstream objects can throw exceptions:
    vertex_shader_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fragment_shader_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try {
        // open files
        vertex_shader_file.open(vertex_path);
        fragment_shader_file.open(fragment_path);
        std::stringstream vShaderStream, fShaderStream;
        // read file's buffer contents into streams
        vShaderStream << vertex_shader_file.rdbuf();
        fShaderStream << fragment_shader_file.rdbuf();
        // close file handlers
        vertex_shader_file.close();
        fragment_shader_file.close();
        // convert stream into string
        vertex_code = vShaderStream.str();
        fragment_code = fShaderStream.str();
    }

    catch (std::ifstream::failure e) {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
    }

    const char *vertex_shader_code = vertex_code.c_str();
    const char *fragment_shader_code = fragment_code.c_str();

// 2. compile shaders
    GLuint vertex, fragment;
    int success;
    char info_log[512];

// vertex Shader
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vertex_shader_code, NULL);
    glCompileShader(vertex);
// print compile errors if any
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertex, 512, NULL, info_log);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << info_log << std::endl;
    };

// fragment Shader
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fragment_shader_code, NULL);
    glCompileShader(fragment);
// print compile errors if any
    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragment, 512, NULL, info_log);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << info_log << std::endl;
    };

// shader Program
    m_ID = glCreateProgram();
    glAttachShader(m_ID, vertex);
    glAttachShader(m_ID, fragment);
    glBindFragDataLocation(m_ID, 0, "out_color");
    glLinkProgram(m_ID);
// print linking errors if any
    glGetProgramiv(m_ID, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(m_ID, 512, NULL, info_log);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << info_log << std::endl;
    }

// delete the shaders as they're linked into our program now and no longer necessery
    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

void Shader::use() {
    glUseProgram(m_ID);
    assert(glGetError() == GL_NO_ERROR);
}

void Shader::set_bool(const std::string &name, bool value) const {
    glUniform1i(glGetUniformLocation(m_ID, name.c_str()), static_cast<int>(value));
    assert(glGetError() == GL_NO_ERROR);
}

void Shader::set_int(const std::string &name, int value) const {
    glUniform1i(glGetUniformLocation(m_ID, name.c_str()), value);
    assert(glGetError() == GL_NO_ERROR);
}

void Shader::set_unsigned_int(const std::string &name, unsigned int value) const {
    glUniform1ui(glGetUniformLocation(m_ID, name.c_str()), value);
    assert(glGetError() == GL_NO_ERROR);
}

void Shader::set_float(const std::string &name, float value) const {
    glUniform1f(glGetUniformLocation(m_ID, name.c_str()), value);
    assert(glGetError() == GL_NO_ERROR);
}
