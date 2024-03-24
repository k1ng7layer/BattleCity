#include "../include/ResourceManager.h"
#include <sstream>
#include <fstream>
#include <iostream>
#define STB_IMAGE_IMPLEMENTATION
#define STBI_ONLY_PNG
#include "../include/stb_image.h"

ResourceManager::ResourceManager(const std::string &executablePath) {
    size_t found = executablePath.find_last_of("/\\");
    path = executablePath.substr(0, found);
}

std::string ResourceManager::GetFileString(const std::string &relativePath) const {
    std::ifstream f;
    f.open(path + "/" + relativePath, std::ios::in | std::ios::binary);

    if (!f.is_open()){
        std::cerr << "Failed to open file: " << relativePath << std::endl;

        return "";
    }

    std::stringstream buffer;
    buffer << f.rdbuf();

    return buffer.str();
}

std::shared_ptr<Renderer::ShaderProgram> ResourceManager::LoadShaderProgram(const std::string& shaderName, const std::string& vertexPath, const std::string& fragmentPath){

    std::string vertexString = GetFileString(vertexPath);

    if (vertexString.empty()){
        std::cerr << "No vertex shader found!" << std::endl;
        return nullptr;
    }

    std::string fragmentString = GetFileString(fragmentPath);

    if (fragmentString.empty()){
        std::cerr << "No fragment shader found!" << std::endl;
        return nullptr;
    }

    std::shared_ptr<Renderer::ShaderProgram>& newShader = shaderProgramsMap.emplace(shaderName, std::make_shared<Renderer::ShaderProgram>(vertexString, fragmentString)).first->second;

    if (newShader->IsCompiled()){
        return newShader;
    }

    std::cerr << "Can't load shader program:\n"
    << "Vertex: " << vertexPath << "\n"
    << "Fragment: " << fragmentPath << std::endl;

    return nullptr;
}

std::shared_ptr<Renderer::ShaderProgram> ResourceManager::GetShader(const std::string &shaderName) {
     ShaderProgramsMap::const_iterator it = shaderProgramsMap.find(shaderName);

     if (it != shaderProgramsMap.end()){
         return it->second;
     }

     std::cerr << "Can't find shader: " << shaderName << std::endl;
}

std::shared_ptr<Renderer::Texture2D> ResourceManager::LoadTexture(const std::string &textureName, const std::string &texturePath)
{
    int channels = 0;
    int width = 0;
    int height = 0;
    std::string textureFullPath = path + "/" + texturePath;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* pixels = stbi_load(textureFullPath.c_str(), &width, &height, &channels, 0);

    if (!pixels){
        std::cerr << "Cant load image" << texturePath << std::endl;

        return nullptr;
    }

    std::shared_ptr<Renderer::Texture2D> newTexture = m_textures.emplace(textureName, std::make_shared<Renderer::Texture2D>(width, height, pixels, channels, GL_NEAREST, GL_CLAMP_TO_EDGE)).first->second;

    stbi_image_free(pixels);

    return newTexture;
}

std::shared_ptr<Renderer::Texture2D> ResourceManager::GetTexture(const std::string &textureName)
{
    TexturesMap ::const_iterator it = m_textures.find(textureName);

    if (it != m_textures.end()){
        return it->second;
    }

    std::cerr << "Can't find texture: " << textureName << std::endl;
}
