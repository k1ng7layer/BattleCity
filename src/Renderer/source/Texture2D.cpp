#include "../Include/Texture2D.h"

#include <glad/glad.h>
#include <string>


Renderer::Texture2D::Texture2D(const GLuint width,
                               const GLuint height,
                               const unsigned char *data,
                               const unsigned int channels,
                               const GLenum filt,
                               GLenum wrapMode)
                               : m_width(width), m_height(height)
{

    switch (channels)
    {
        case 4:
            mode = GL_RGBA;
            break;
        case 3:
            mode = GL_RGB;
            break;
        default: mode = GL_RGB;
            break;

    }

    glGenTextures(1, &id);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, id);
    glTexImage2D(GL_TEXTURE_2D, 0, mode, m_width, m_height, 0, mode, GL_UNSIGNED_BYTE, data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapMode);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapMode);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filt);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filt);
    glGenerateMipmap(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);
}

Renderer::Texture2D &Renderer::Texture2D::operator=(Renderer::Texture2D &&texture2d){
    glDeleteTextures(1, &id);
    id = texture2d.id;
    texture2d.id = 0;
    mode = texture2d.mode;
    m_width = texture2d.m_width;
    m_height = texture2d.m_height;

    return *this;
}

Renderer::Texture2D::Texture2D(Texture2D&& texture2d)
{
    id = texture2d.id;
    texture2d.id = 0;
    mode = texture2d.mode;
    m_width = texture2d.m_width;
    m_height = texture2d.m_height;
}

void Renderer::Texture2D::Bind() const
{
    glBindTexture(GL_TEXTURE_2D, id);
}

Renderer::Texture2D::~Texture2D()
{
    glDeleteTextures(1, &id);
}


