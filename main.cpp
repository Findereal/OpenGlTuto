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
#include "stb_image.h"


// creates array of vertices for square
GLfloat vertices[] = {
        //   COORDINATES     /     COLORS      / TEXTURE COORDINATES //
        -.5f, -.5f, .0f, 1.f, 0.f, 0.f, .0f, .0f, // lower left
        .5f, -.5f, .0f, 0.f, 1.f, 0.f, 1.f, .0f,// lower right
        -.5f, .5f, .0f, 0.f, 0.f, 1.f, .0f, 1.f, // upper left
        .5f, .5f, .0f, 1.f, 1.f, 1.f, 1.f, 1.f// upper right
};

// declares order of vertices to visit
GLuint indices[] = {0, 3, 2,
                    0, 1, 3};

// scale should never be 0
GLfloat scaleFactor = 2.f;

std::string pathToTextures;


int main() {
    pathToTextures = "../resources/Textures/";
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

    VAO1.linkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void *) 0);
    VAO1.linkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void *) (3 * sizeof(float)));
    VAO1.linkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void *) (6 * sizeof(float)));

    VAO1.Unbind();
    VBO1.Unbind();
    EBO1.Unbind();

    // reference the "uniform" variable
    GLuint uniID = glGetUniformLocation(shaderProgram.id, "scale");

    // Texture variables
    // 1. import image
    const char *filePath = pathToTextures.append("test.png").c_str();
    int imgHei, imgWid, numColCh;
    stbi_set_flip_vertically_on_load(true); // stb reads images top left to bot right
    // and opengl reads image bot left to top right
    unsigned char *imgBytes = stbi_load(filePath, &imgWid, &imgHei, &numColCh, 0);
    // 2. GLreference the texture
    GLuint texture;
    glGenTextures(1, &texture);
    // 3. Activate the texture (put it in a slot) and load image
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);

    // 4. Input parameters for the texture
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    float flatColor[] = {1.f, 1.f, 1.f, 1.f};                                 // for clamp to border, has to give the
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR,
                     flatColor);    // border color in a float vector ==> gltexparamFV

    // 5. Link image to texture object
    glTexImage2D(GL_TEXTURE_2D /* texture type */,
                 0,
                 GL_RGBA /* color profile of texture */,
                 imgWid,
                 imgHei,
                 0,
                 GL_RGBA /* color profile of source image */,
                 GL_UNSIGNED_BYTE /* pixel data type */,
                 imgBytes /* source image */);
    glGenerateMipmap(GL_TEXTURE_2D);


    // 6. free memory
    stbi_image_free(imgBytes);
    glBindTexture(GL_TEXTURE_2D, 0);


    // not mandatory, but better have it
    // sets back buffer to navy blue
    glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // swaps front and back buffers to display blue
    glfwSwapBuffers(window);

    GLuint tex0uni = glGetUniformLocation(shaderProgram.id, "tex0");
    shaderProgram.Activate();
    glUniform1i(tex0uni, 0);


    // window stays open until we close it
    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        shaderProgram.Activate();
        // initialize the "uniform" variable /!\ ONLY AFTER activating shader program
        glUniform1f((GLint) uniID, scaleFactor);
        glBindTexture(GL_TEXTURE_2D, texture);
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
    glDeleteTextures(1, &texture);
    shaderProgram.Delete();

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
