
#include <glad/glad.h>
#include <string>
namespace Renderer {
    class Texture2D
    {
    public:
        Texture2D(const GLuint width,
                  const GLuint height,
                  const unsigned char *data,
                  const unsigned int channels = 4,
                  const GLenum filt = GL_LINEAR,
                  GLenum wrapMode = GL_CLAMP_TO_EDGE);

        Texture2D() = delete;
        Texture2D(const Texture2D&) = delete;
        Texture2D& operator = (const Texture2D&) = delete;
        Texture2D& operator = (Texture2D&& texture2d);
        Texture2D(Texture2D&& texture2d);

        void Bind() const;

        ~Texture2D();

    private:
        GLuint id;
        GLenum mode;
        unsigned int m_width;
        unsigned int m_height;
    };
}