#pragma once
#include <string>
#include <glad/glad.h>



class Shader {
public:
    GLuint program;

    Shader(const std::string& vertexPath, const std::string& fragmentPath);
    void use() const;
};