#include <gfx/texture.hpp>
#include <glad/glad.h>
#include <stb/images.h>
#include <iostream>

Texture::Texture(const char *path) {
    glGenTextures(1, &texture);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);

    set_texture_params();
    stbi_set_flip_vertically_on_load(true);
    load_texture(stbi_load(path, &width, &height, &nr_channels, 0));
}

Texture::Texture(const char *path, const u32 texture_unit) {
    glGenTextures(1, &texture);
    glActiveTexture(GL_TEXTURE0 + texture_unit);
    glBindTexture(GL_TEXTURE_2D, texture);

    set_texture_params();
    load_texture(stbi_load(path, &width, &height, &nr_channels, 0));
}

const u32 Texture::get_texture() {
    return texture;
}

void Texture::load_texture(byte *image) {
    if (image) {
        u32 format = (nr_channels == 4) ? GL_RGBA : GL_RGB;
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, format, GL_UNSIGNED_BYTE, image);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        std::cout << "Failed to load texture" << "\n"; 
    }

    stbi_image_free(image);
}

void Texture::set_texture_params() {
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

