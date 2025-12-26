#include <gfx/shader.hpp>
#include "SDL3/SDL_keycode.h"
#include "data/vertex.hpp"
#include "gfx/multitexture.hpp"
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/vector_float3.hpp"
#include "glm/trigonometric.hpp"
#include "object.hpp"
#include "time/time.hpp"
#include "transform.hpp"
#include "window.hpp"
#include <types.hpp>
#include <glad/glad.h>
#include <stb/images.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

bool poll_event(SDL_Event &event, Window &window);

Vertices vertices({
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
    0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
    0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
    0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

    0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
    0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
    0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
});

glm::vec3 cubePositions[] = {
    glm::vec3( 2.0f,  5.0f, -15.0f), 
    glm::vec3(-1.5f, -2.2f, -2.5f),  
    glm::vec3(-3.8f, -2.0f, -12.3f),  
    glm::vec3( 2.4f, -0.4f, -3.5f),  
    glm::vec3(-1.7f,  3.0f, -7.5f),  
    glm::vec3( 1.3f, -2.0f, -2.5f),  
    glm::vec3( 1.5f,  2.0f, -2.5f), 
    glm::vec3( 1.5f,  0.2f, -1.5f), 
    glm::vec3(-1.3f,  1.0f, -1.5f)  
};

u32 indices[] = {  
    0, 1, 3, // first triangle
    1, 2, 3  // second triangle
};
Shader *shad = nullptr;
MultiTexture *mult = nullptr;
Object *ob = nullptr;

void update() {
    shad->use();
    mult->draw();

    glBindVertexArray(ob->vao);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    for(usize i = 0; i < 9; i++) {
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, cubePositions[i]);
        float angle = 20.0f * i; 
        model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
        shad->set_mat4("model", model);

        glDrawArrays(GL_TRIANGLES, 0, 36);
    }
}

int main() {
    Window window(800, 600);
    window.create();

    const char *paths[] = {"assets/container.jpg", "assets/awesomeface.png", "assets/brick.png"};
    MultiTexture multi(paths);
    mult = &multi;

    Shader shader("glsl/vertex.glsl", "glsl/fragment.glsl");
    shad = &shader;

    Object obj(vertices, indices);
    ob = &obj;

    multi.set_sampler(shader);

    SDL_Event event;

    glEnable(GL_DEPTH_TEST);
    while (poll_event(event, window)) {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glm::mat4 model = glm::mat4(1.0f);
        glm::mat4 view = glm::mat4(1.0f);
        glm::mat4 projection = glm::mat4(1.0f);

        model = glm::rotate(model, ((float)SDL_GetTicks() / 1000) * glm::radians(50.0f), glm::vec3(0.0f, 0.5f, 1.0f));
        view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
        projection = glm::perspective(
            glm::radians(45.0f),
            (f32)window.get_width() / (f32)window.get_height(), 0.1f, 100.0f);

        u32 modelLoc = shader.get_uniform_location("model");
        u32 viewLoc = shader.get_uniform_location("view");
        u32 projLoc = shader.get_uniform_location("projection");

        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
        update();

        SDL_GL_SwapWindow(window.get_window());
    }

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
