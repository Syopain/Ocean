#include "shader.h"
#include <fstream>
#include <sstream>
#include <iostream>

Shader::Shader(std::string const& vertex_path, std::string const& fragment_path) :
    vertex_(vertex_path),
    fragment_(fragment_path)
{
}

void Shader::load()
{
    initializeOpenGLFunctions();

    std::string vertex_code;
    std::string fragment_code;
    std::ifstream v_shader_file;
    std::ifstream f_shader_file;

    v_shader_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    f_shader_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try {
        v_shader_file.open(vertex_);
        f_shader_file.open(fragment_);
        std::stringstream v_shader_stream, f_shader_stream;
        v_shader_stream << v_shader_file.rdbuf();
        f_shader_stream << f_shader_file.rdbuf();
        v_shader_file.close();
        f_shader_file.close();
        vertex_code = v_shader_stream.str();
        fragment_code = f_shader_stream.str();
    }
    catch (std::ifstream::failure& e) {
        std::cout << "Error::Shader::FILE_NOT_SUCCESFULLY_READ";
    }

    char const* c_vertex_code = vertex_code.c_str();
    char const* c_fragment_code = fragment_code.c_str();


    // complie shader
    int success;
    char info_log[512];

    // vertex shader
    unsigned int vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &c_vertex_code, nullptr);
    glCompileShader(vertex);
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertex, 512, nullptr, info_log);
        std::cout << "Error::Shader::VERTEX::COMPLILATION_FAILED" << std::endl;
        std::cout << info_log << std::endl;
    }
    // fragment shader
    unsigned int fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &c_fragment_code, nullptr);
    glCompileShader(fragment);
    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragment, 512, nullptr, info_log);
        std::cout << "Error::Shader::FRAGMENT::COMPLILATION_FAILED" << std::endl;
        std::cout << info_log << std::endl;
    }

    id_ = glCreateProgram();
    glAttachShader(id_, vertex);
    glAttachShader(id_, fragment);
    glLinkProgram(id_);
    glGetProgramiv(id_, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(id_, 512, nullptr, info_log);
        std::cout << "Error::Shader::PROGRAM::LINKING_FAILED";
        std::cout << info_log;
    }

    glDeleteShader(vertex);
    glDeleteShader(fragment);
}
