#pragma once
#include <string>
#include "glad/glad.h"

namespace Renderer{
    class ShaderProgram {
    public:
            ShaderProgram(const std::string& vertex_shader, const std::string& fragment_shader);
            ~ShaderProgram();
            bool IsCompiled() const {return isCompiled;}
            void Use() const;
            void SetInt(const std::string& name, const GLint value);
            ShaderProgram() = delete;
            ShaderProgram(ShaderProgram&) = delete;
            ShaderProgram& operator = (const ShaderProgram&) = delete;
            ShaderProgram& operator = (ShaderProgram&& shaderProgram) noexcept;
            ShaderProgram(ShaderProgram&& shaderProgram) noexcept;
    private:
        bool CreateShader(const std::string& source, const GLenum shaderType, GLuint& shaderId);
        bool isCompiled {false};
        GLuint id {0};
    };
}



