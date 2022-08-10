//
// Created by 玩奥i on 2022/8/9.
//

#include "texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

Texture2D::Texture2D(GLint wrap_s, GLint wrap_t, GLint minFilter, GLint magFilter, bool enableMipmap, GLint mipMapLevel,
                     glm::vec3 borderColor): mipMap(enableMipmap), mipMapLevel(mipMapLevel), borderColor(borderColor), data(nullptr){
    glGenTextures(1, &this->texture);

    glBindTexture(GL_TEXTURE_2D, this->texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap_s);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap_t);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilter);
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, glm::value_ptr(this->borderColor));

    glBindTexture(GL_TEXTURE_2D, 0);
}

Texture2D::~Texture2D() {
    if(data != nullptr) stbi_image_free(this->data);
}

void Texture2D::Bind() const {
    glBindTexture(GL_TEXTURE_2D, this->texture);
}

void Texture2D::Unbind() const {
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture2D::Load(const std::string &fname) {
    this->data = stbi_load(fname.c_str(), &this->width, &this->height, &this->nChannels, 0);
    if(data == nullptr) {
        throw std::runtime_error("Failed to load image file.");
    }
    this->Bind();
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, this->width, this->height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    if(this->mipMap) glGenerateMipmap(GL_TEXTURE_2D);
    this->Unbind();
}