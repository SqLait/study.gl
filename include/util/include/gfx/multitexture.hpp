#pragma once

#include "gfx/shader.hpp"
#include <gfx/texture.hpp>
#include <types.hpp>
#include <span>
#include <vector>
#include <gfx/textureunit.hpp>

class MultiTexture {
    std::vector<Texture> textures;
public:
    MultiTexture(std::span<const char *> paths);
    void draw();
    void set_sampler(Shader &shader);
private:
    void load_texture(byte *image, usize index);
};
