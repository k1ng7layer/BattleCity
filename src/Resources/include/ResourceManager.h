#pragma once
#include <string>
#include <memory>
#include <map>
#include "../../Renderer/Include/ShaderProgram.h"

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

private:
    std::string GetFileString(const std::string& relativePath) const;
    typedef  std::map<const std::string, std::shared_ptr<Renderer::ShaderProgram>> ShaderProgramsMap;
    ShaderProgramsMap shaderProgramsMap;

    std::string path;
};

