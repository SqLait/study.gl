#include <gfx/shader.hpp>
#include "gfx/multitexture.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/ext/vector_float3.hpp"
#include "object.hpp"
#include "window.hpp"
#include <types.hpp>
#include <glad/glad.h>
#include <stb/images.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

bool poll_event(SDL_Event &event, Window &window);

f32 vertices2[] = {
    // positions          // colors           // texture coords
     0.2f,  0.2f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
     0.2f, -0.2f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
    -0.2f, -0.2f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
    -0.2f,  0.2f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left
};

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
 
Shader *shad = nullptr;
MultiTexture *mult = nullptr;
Object *ob = nullptr;

void update() {
    shad->use();
    mult->draw();

    glBindVertexArray(ob->vao);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
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

    glm::mat4 trans = glm::mat4(1.0f);
    trans = glm::translate(trans, glm::vec3(0.5f, 0.0f, 0.0f));
    trans = glm::rotate(trans, (float)SDL_GetTicks(), glm::vec3(0.0f, 0.0f, 1.0f));

    unsigned int transformLoc = glGetUniformLocation(shader.get_id(), "transform");
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));

    SDL_Event event;
    while (poll_event(event, window)) {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        update();

        glm::mat4 trans = glm::mat4(1.0f);
        trans = glm::translate(trans, glm::vec3(0.0f, 0.0f, 0.0f));
        trans = glm::rotate(trans, (float)SDL_GetTicks() / 1000, glm::vec3(0.0f, 0.0f, 1.0f));

        unsigned int transformLoc = glGetUniformLocation(shader.get_id(), "transform");
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));
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
