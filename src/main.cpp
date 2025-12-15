#include <cmath>
#include <gfx/shader.hpp>
#include "SDL3/SDL_stdinc.h"
#include "SDL3/SDL_time.h"
#include "gfx/texture.hpp"
#include "object.hpp"
#include "window.hpp"
#include <types.hpp>
#include <glad/glad.h>
#include <stb/images.h>

bool poll_event(SDL_Event &event, Window &window);

f32 vertices[] = {
    // positions          // colors           // texture coords
     0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
     0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
    -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
    -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left 
};

u32 indices[] = {  
    0, 1, 3, // first triangle
    1, 2, 3  // second triangle
};
 
u32 VBO, VAO, EBO;
Texture *tex = nullptr;
Texture *tex2 = nullptr;
Shader *shad = nullptr;

void update() {
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, tex->get_texture());
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, tex2->get_texture());
    
    shad->use();
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

int main() {
    Window window {800, 600};
    window.create();

    Texture texture {"assets/container.jpg"};
    tex = &texture;

    Texture texture2 {"assets/awesomeface.png", GLTexUnit::GL1};
    tex2 = &texture2;

    Shader shader {"glsl/vertex.glsl", "glsl/fragment.glsl"};
    shad = &shader;

    Object obj {vertices, indices};

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, (obj.vertices.size() * sizeof(f32)), obj.vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, (obj.indices.size() * sizeof(u32)), obj.indices.data(), GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // texture coord attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    shad->use();
    shad->set_i32("tex1", 0);
    shad->set_i32("tex2", 1);

    SDL_Event event;
    while (poll_event(event, window)) {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        update();

        SDL_GL_SwapWindow(window.get_window());
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    window.destroy();

    return 0;
}

bool poll_event(SDL_Event &event, Window &window) {
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_EVENT_QUIT) {
            return false;
        } else if (event.type == SDL_EVENT_WINDOW_RESIZED) {
            window.update_size(event);
        } else if (event.type == SDL_EVENT_KEY_DOWN) {
            switch (event.key.key) {
                case SDLK_ESCAPE:
                    return false;
                case SDLK_L:
                    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                    break;
                case SDLK_F:
                    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                    break;
            }
        }
    }
    return true;
}
