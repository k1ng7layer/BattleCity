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
        case 3:
            mode = GL_RGB;
        default: mode = GL_RGB;

    }

    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_2D, id);
    glTexImage2D(GL_TEXTURE_2D, 0, mode, m_width, m_height, 0, mode, GL_UNSIGNED_BYTE, data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapMode);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapMode);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filt);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filt);
}
