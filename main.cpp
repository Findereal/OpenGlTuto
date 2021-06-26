//
// Created by armand on 26/06/2021.
//

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

int main() {
    // glfw needs to be initialized and terminated
    glfwInit();

    // declare version of OpenGL, here 3.3 (version A.B --> MAJOR = A, MINOR = B)
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // declare profile of OpenGL
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // creates window object with error detection.
    // a window has to be deleted after use
    GLFWwindow *window = glfwCreateWindow(600, 600, "title", nullptr, nullptr);
    if (window == nullptr) {
        std::cout << "Failed to create window" << std::endl;
        glfwTerminate();
        return -1;
    }

    // use the window
    glfwMakeContextCurrent(window);

    // load openGL config into glad
    gladLoadGL();

    // declare window area to render
    glViewport(0, 0, 600, 600);

    // sets back buffer to navy blue
    glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // swaps front and back buffers to display blue
    glfwSwapBuffers(window);

    // window stays open until we close it
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
    }
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
