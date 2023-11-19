#include <iostream>
#include "../include/ShaderProgram.h"

namespace Renderer {
    Renderer::ShaderProgram::ShaderProgram(const std::string &vertex_shader, const std::string &fragment_shader) {

        GLuint vertexShaderId;

        if(!CreateShader(vertex_shader, GL_VERTEX_SHADER, vertexShaderId)){
            std::cout << "ERROR::VERTEX SHADER: compile time error" << std::endl;
            return;
        }

        GLuint fragmentShaderId;

        if(!CreateShader(fragment_shader, GL_FRAGMENT_SHADER, fragmentShaderId)){
            std::cout << "ERROR::FRAGMENT_ SHADER: compile time error" << std::endl;
            glDeleteShader(vertexShaderId);
            return;
        }

        id = glCreateProgram();

        glAttachShader(id, vertexShaderId);
        glAttachShader(id, fragmentShaderId);

        glLinkProgram(id);

        GLint success;

        glGetProgramiv(id, GL_LINK_STATUS, &success);

        if (!success){
            GLchar infoLog[1024];
            glGetShaderInfoLog(id, sizeof(infoLog), nullptr, infoLog);

            std::cout << "ERROR::SHADER: Link time error:\n" << infoLog << std::endl;
        }
        else{
            isCompiled = true;
        }

        glDeleteShader(vertexShaderId);
        glDeleteShader(fragmentShaderId);
    }

    Renderer::ShaderProgram::~ShaderProgram() {
        glDeleteProgram(id);
    }

    void Renderer::ShaderProgram::Use() const {
        glUseProgram(id);
    }

    bool ShaderProgram::CreateShader(const std::string& source, const GLenum shaderType, GLuint &shaderId) {
        shaderId = glCreateShader(shaderType);
        const char* sourceCode = source.c_str();
        glShaderSource(shaderId, 1, &sourceCode, nullptr);
        glCompileShader(shaderId);
        GLint success;
        glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success);

        if (!success){
            GLchar infoLog[1024];
            glGetShaderInfoLog(shaderId, sizeof(infoLog), nullptr, infoLog);

            std::cout << "ERROR::SHADER: compile time error:\n" << infoLog << std::endl;

            return false;
        }

        return true;
    }

    ShaderProgram& ShaderProgram::operator=(ShaderProgram &&shaderProgram) noexcept {
        glDeleteProgram(id);
        id = shaderProgram.id;
        isCompiled = shaderProgram.isCompiled;
        shaderProgram.id = 0;
        shaderProgram.isCompiled = false;

        return *this;
    }

    ShaderProgram::ShaderProgram(ShaderProgram &&shaderProgram) noexcept {

        id = shaderProgram.id;
        isCompiled = shaderProgram.isCompiled;
        shaderProgram.id = 0;
        shaderProgram.isCompiled = false;
    }
}


