//
// Created by armand on 26/06/2021.
//

#include <iostream>
#include <cmath>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "shadersClass.h"
#include "VBO.h"
#include "VAO.h"
#include "EBO.h"
//#include "stb_image.h"


// creates array of vertices for square
GLfloat vertices[] = {
        //   COORDINATES     /     COLORS      //
        -.5f, -.5f, .0f, 1.f, 0.f, 0.f,  // lower left
        .5f, -.5f, .0f, 0.f, 1.f, 0.f,  // lower right
        -.5f, .5f, .0f, 0.f, 0.f, 1.f,  // upper left
        .5f, .5f, .0f, 1.f, 1.f, 1.f   // upper right
};

// declares order of vertices to visit
GLuint indices[] = {0, 3, 2,
                    0, 1, 3};

// scale should never be 0
GLfloat scaleFactor = .1f;


int main() {
    // glfw needs to be initialized and terminated
    glfwInit();

    // declare version of OpenGL, here 3.3 (version A.B --> MAJOR = A, MINOR = B)
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // declare profile of OpenGL
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    // temporary fix
    // TODO : have the coordinates follow the size of the window when it's resized

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

    // instantiate shaders
    Shader shaderProgram("default.vert", "default.frag");

    // Creates reference points for data
    // vertex array object: where the data is used
    // vertex buffer object: where the data is stored
    // generate VAO before VBO !!!!
    VAO VAO1;
    VAO1.Bind();

    VBO VBO1(vertices, sizeof(vertices));
    EBO EBO1(indices, sizeof(indices));

    VAO1.linkAttrib(VBO1, 0, 3, GL_FLOAT, 6 * sizeof(float), (void *) 0);
    VAO1.linkAttrib(VBO1, 1, 3, GL_FLOAT, 6 * sizeof(float), (void *) (3 * sizeof(float)));

    VAO1.Unbind();
    VBO1.Unbind();
    EBO1.Unbind();

    // reference the "uniform" variable
    GLuint uniID = glGetUniformLocation(shaderProgram.id, "scale");

    // not mandatory, but better have it
    // sets back buffer to navy blue
    glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // swaps front and back buffers to display blue
    glfwSwapBuffers(window);

    // window stays open until we close it
    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        shaderProgram.Activate();
        // initialize the "uniform" variable /!\ ONLY AFTER activating shader program
        glUniform1f((GLint) uniID, scaleFactor);
        VAO1.Bind();
        glDrawElements(GL_TRIANGLES /* primitive to use */,
                       6 /* number of indices to draw */,
                       GL_UNSIGNED_INT /* type of data for indices */,
                       nullptr /* first index of indices to draw */);
        glfwSwapBuffers(window);

        // reacts to user inputs
        glfwPollEvents();
    }

    // free memory
    VAO1.Delete();
    VBO1.Delete();
    EBO1.Delete();
    shaderProgram.Delete();

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
