#pragma once
#include <string>
#include <memory>
#include <map>
#include "../../Renderer/Include/ShaderProgram.h"
#include "../../Renderer/Include/Texture2D.h"

class ResourceManager {
public:
    ResourceManager(const std::string& executablePath);
    ~ResourceManager() = default;
    ResourceManager(const ResourceManager&) = delete;
    ResourceManager& operator=(const ResourceManager&) = delete;
    ResourceManager& operator = (ResourceManager&&) = delete;
    ResourceManager(ResourceManager&&) = delete;

    std::shared_ptr<Renderer::ShaderProgram> LoadShaderProgram(const std::string& shaderName, const std::string& vertexPath, const std::string& fragmentPath);
    std::shared_ptr<Renderer::ShaderProgram> GetShader(const std::string& shaderName);
    std::shared_ptr<Renderer::Texture2D> LoadTexture(const std::string& textureName, const std::string& texturePath);
    std::shared_ptr<Renderer::Texture2D> GetTexture(const std::string& textureName);

private:
    std::string GetFileString(const std::string& relativePath) const;
    typedef std::map<const std::string, std::shared_ptr<Renderer::ShaderProgram>> ShaderProgramsMap;
    ShaderProgramsMap shaderProgramsMap;
    typedef std::map<const std::string, std::shared_ptr<Renderer::Texture2D>> TexturesMap;
    TexturesMap m_textures;
    std::string path;
};

