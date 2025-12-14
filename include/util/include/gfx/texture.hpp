#pragma once
#include <optional>
#include <types.hpp>

enum class GLTexUnit : byte;

class Texture {
    u32 texture;
    i32 width;
    i32 height;
    i32 nr_channels;
    GLTexUnit tex_unit;

public:
    Texture(const char *path);
    Texture(const char *path, const GLTexUnit texture_unit);
    const u32 get_texture();

private:
    void set_texture_params();
    void load_texture(byte *image);
};

enum class GLTexUnit : byte {
    GL1 = 1,
    GL2 = 2,
    GL3 = 3,
    GL4 = 4,
    GL5 = 5,
    GL6 = 6,
    GL7 = 7,
    GL8 = 8,
    GL9 = 9,
    GL10 = 10,
    GL11 = 11,
    GL12 = 12,
    GL13 = 13,
    GL14 = 14,
    GL15 = 15,
};
