#pragma once
#include <optional>
#include <types.hpp>
#include <gfx/textureunit.hpp>

class Texture {
    u32 texture;
    i32 width;
    i32 height;
    i32 nr_channels;

public:
    Texture(const char *path);
    Texture(const char *path, const u32 texture_unit);
    const u32 get_texture();

private:
    void set_texture_params();
    void load_texture(byte *image);
};
