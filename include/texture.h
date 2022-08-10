//
// Created by 玩奥i on 2022/8/9.
//

#ifndef OPENGL_TEST_TEXTURE_H
#define OPENGL_TEST_TEXTURE_H

#include <glad/glad.h>
#include <glm/vec3.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <string>
#include <memory>

#include <stb_image.h>

class Texture {
public:
    virtual ~Texture() = default;

    virtual void Bind() const = 0;
    virtual void Unbind() const = 0;

    virtual void Load(const std::string&) = 0;
};


class Texture2D : public Texture{
private:
    bool mipMap;
    GLint mipMapLevel;
    GLuint texture{};
    GLsizei width{}, height{};
    GLint nChannels{};
    glm::vec3 borderColor;
    unsigned char* data;
public:
    /**
     * @brief Create a 2d texture object
     *
     * @param width the width of texture
     * @param height the height of texture
     *
     */
    Texture2D(GLint wrap_s = GL_MIRRORED_REPEAT, GLint  wrap_t = GL_MIRRORED_REPEAT, GLint  minFilter = GL_LINEAR_MIPMAP_NEAREST, GLint  magFilter = GL_LINEAR, bool enableMipmap = true, GLint mipMapLevel = 4, glm::vec3 borderColor = glm::vec3(0.0f, 0.0f, 0.0f));

    ~Texture2D();

    void Load(const std::string& fname) override;

    void Bind() const override;

    void Unbind() const override;
};


#endif //OPENGL_TEST_TEXTURE_H
