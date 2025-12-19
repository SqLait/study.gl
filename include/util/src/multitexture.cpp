#include "gfx/textureunit.hpp"
#include <gfx/multitexture.hpp>
#include <glad/glad.h>
#include <stb/images.h>
#include <string>

MultiTexture::MultiTexture(std::span<const char *> paths) {
    for (usize i = 0; i < paths.size() && i < 16; i++) {
        textures.push_back(Texture(paths[i], i));
    }
    textures.shrink_to_fit();
}

void MultiTexture::set_sampler(Shader &shader) {
    shader.use();
    for (usize i = 0; i < textures.size(); i++) {
        std::string sampler_name = "tex" + std::to_string(i + 1);
        shader.set_i32(sampler_name.c_str(), i);
    }
}

void MultiTexture::draw() {
    for (usize i = 0; i < textures.size(); i++) {
        glActiveTexture(GL_TEXTURE0 + i);
        glBindTexture(GL_TEXTURE_2D, textures[i].get_texture());
    }
}
