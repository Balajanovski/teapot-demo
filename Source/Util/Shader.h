#ifndef OPENGL_BOILERPLATE_SHADER_H
#define OPENGL_BOILERPLATE_SHADER_H

#include "NoCopy.h"

#include <glad/glad.h>
#include <memory>
#include <string>

class Shader : public NoCopy {
private:
    GLuint m_ID; // The program ID
public:
    GLuint ID() { return m_ID; }

    // References counter
    std::shared_ptr<unsigned int> m_references;

    // R-value constructor
    Shader(Shader&&);

    // Destructor
    ~Shader();

    // Copy operator
    Shader& operator= (Shader&& rhs);

    // constructor reads and builds the shader
    Shader(const char* vertex_path, const char* fragment_path);

    Shader() : m_references(std::make_shared<unsigned int>(0)) { }

    // use/activate the shader
    void use();

    // utility uniform functions
    void set_bool(const std::string &name, bool value) const;
    void set_int(const std::string &name, int value) const;
    void set_unsigned_int(const std::string &name, unsigned int value) const;
    void set_float(const std::string &name, float value) const;

};




#endif //OPENGL_BOILERPLATE_SHADER_H
