#include "gfx/debug.hpp"
#include <gfx/shader.hpp>
#include <glad/glad.h>
#include <iostream>
#include <types.hpp>
#include <fstream>
#include <sstream>

static std::string get_glsl_shader(const char *path);
static void shader_compile_status(u32 shader);

Shader::Shader(const char *vertex_path, const char *fragment_path) {
    auto vtx = get_glsl_shader(vertex_path);
    auto frag = get_glsl_shader(fragment_path);

    const char *vtx_code = vtx.c_str(); 
    const char *frag_code = frag.c_str();

    u32 vertex = glCreateShader(GL_VERTEX_SHADER);
    u32 fragment = glCreateShader(GL_FRAGMENT_SHADER);

    compile_shader(vertex, vtx_code);
    compile_shader(fragment, frag_code);

    id = glCreateProgram();
    glAttachShader(id, vertex);
    glAttachShader(id, fragment);
    glLinkProgram(id);

    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

Shader::~Shader() {
    glDeleteProgram(id);
}

void Shader::use() {
    glUseProgram(id);
}

void Shader::set_bool(const char *name, bool value) {
    glUniform1i(glGetUniformLocation(id, name), (i32)value);
}

void Shader::set_i32(const char *name, i32 value) {
    glUniform1i(glGetUniformLocation(id, name), value);
}

void Shader::set_f32(const char *name, f32 value) {
    glUniform1f(glGetUniformLocation(id, name), value);
}

const u32 Shader::get_id() {
    return id;
}

void Shader::compile_shader(u32 shader, const char *glsl) {
    glShaderSource(shader, 1, &glsl, NULL);
    glCompileShader(shader);
    shader_compile_status(shader);
}

static std::string get_glsl_shader(const char *path) {
    std::ifstream shader;
    std::stringstream shader_stream;

    shader.open(path);
    shader_stream << shader.rdbuf();		
    shader.close();

    return shader_stream.str();
}

static void shader_compile_status(u32 shader) {
    i32 success;
    char infoLog[512];

    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

    if(!success) {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
}
