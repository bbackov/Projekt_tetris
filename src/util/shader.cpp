#include "shader.hpp"
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <iostream>

static std::string loadFile(const std::string& path) {
    std::ifstream f(path);
    if (!f.is_open()) {
        std::cerr << "Cannot open shader file: " << path << "\n";
        throw std::runtime_error("Cannot open shader file");
    }
    std::stringstream ss;
    ss << f.rdbuf();
    return ss.str();
}

static GLuint compileShader(GLenum type, const char* src) {
    GLuint id = glCreateShader(type);
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    GLint ok;
    glGetShaderiv(id, GL_COMPILE_STATUS, &ok);
    if (!ok) {
        char log[512];
        glGetShaderInfoLog(id, 512, nullptr, log);
        std::cerr << "Shader compile error:\n" << log << "\n";
        throw std::runtime_error("Shader compile error");
    }
    return id;
}

static GLuint linkProgram(GLuint vs, GLuint fs) {
    GLuint p = glCreateProgram();
    glAttachShader(p, vs);
    glAttachShader(p, fs);
    glLinkProgram(p);

    GLint ok;
    glGetProgramiv(p, GL_LINK_STATUS, &ok);
    if (!ok) {
        char log[512];
        glGetProgramInfoLog(p, 512, nullptr, log);
        std::cerr << "Program link error:\n" << log << "\n";
        throw std::runtime_error("Program link error");
    }
    return p;
}

Shader::Shader(const std::string& vertexPath, const std::string& fragmentPath) {
    std::string vsSource = loadFile(vertexPath);
    std::string fsSource = loadFile(fragmentPath);

    GLuint vs = compileShader(GL_VERTEX_SHADER, vsSource.c_str());
    GLuint fs = compileShader(GL_FRAGMENT_SHADER, fsSource.c_str());

    program = linkProgram(vs, fs);

    glDeleteShader(vs);
    glDeleteShader(fs);
}

void Shader::use() const {
    glUseProgram(program);
}