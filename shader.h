#ifndef SHADER_H
#define SHADER_H
#include <qopenglfunctions_3_3_core.h>
#include <QWindow>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader : protected QOpenGLFunctions_3_3_Core {
public:
    Shader(std::string const& vertex_path, std::string const& fragment_path);
    void use();
    void load();
    unsigned int Id() const { return id_; };
    void setUniform(std::string const& name, bool value);
    void setUniform(std::string const& name, int value);
    void setUniform(std::string const& name, float value);
    void setUniform(std::string const& name, glm::mat4 const& vlaue);
    void setUniform(std::string const& name, glm::vec3 const& value);
protected:
private:
    unsigned int id_;
    std::string vertex_;
    std::string fragment_;
};


// inline implementations

inline void Shader::use()
{
    glUseProgram(id_);
}

inline void Shader::setUniform(std::string const& name, bool value)
{
    glUniform1i(glGetUniformLocation(id_, name.c_str()), value);
}

inline void Shader::setUniform(std::string const& name, int value)
{
    glUniform1i(glGetUniformLocation(id_, name.c_str()), value);
}

inline void Shader::setUniform(std::string const& name, float value)
{
    glUniform1f(glGetUniformLocation(id_, name.c_str()), value);
}

inline void Shader::setUniform(std::string const& name, glm::mat4 const& value)
{
    glUniformMatrix4fv(glGetUniformLocation(id_, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}

inline void Shader::setUniform(std::string const& name, glm::vec3 const& value)
{
    glUniform3fv(glGetUniformLocation(id_, name.c_str()), 1, glm::value_ptr(value));
}

#endif // SHADER_H
