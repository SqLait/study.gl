#include <gfx/shader.hpp>
#include "window.hpp"
#include <types.hpp>
#include <glad/glad.h>

bool poll_event(SDL_Event &event, Window &window);

float vertices[] = {
    0.5f, -0.5f, 0.0f,  // bottom right
    -0.5f, -0.5f, 0.0f,  // bottom left
    0.0f,  0.5f, 0.0f   // top 
};

u32 VBO, VAO;
u32 fragmentShader;
u32 vertexShader;
Shader *shad = nullptr;

void update() {
    shad->use();
    glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

int main() {
    Window window {800, 600};
    window.create();

    Shader shader {"glsl/vertex.glsl", "glsl/fragment.glsl"};
    shad = &shader;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0); 

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0); 

    SDL_Event event;
    while (poll_event(event, window)) {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        update();

        SDL_GL_SwapWindow(window.get_window());
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
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
