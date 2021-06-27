//
// Created by armand on 26/06/2021.
//

#include <iostream>
#include <math.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// defining shaders
const char *vertexShaderSource = "#version 330 core\n"
                                 "layout (location = 0) in vec3 aPos;\n"
                                 "void main()\n"
                                 "{\n"
                                 "    gl_Position=vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                                 "}\n\0";
const char *fragmentShaderSource = "#version 330 core\n"
                                   "out vec4 FragColor;\n"
                                   "void main()\n"
                                   "{\n"
                                   "    FragColor = vec4(0.8f, 0.3f, 0.02f, 1.0f);\n"
                                   "}\n\0";


int main() {
    // glfw needs to be initialized and terminated
    glfwInit();

    // declare version of OpenGL, here 3.3 (version A.B --> MAJOR = A, MINOR = B)
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // declare profile of OpenGL
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // creates array of vertices for triangle
    GLfloat vertices[] = {
            -0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,
            0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,
            0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f
    };

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

    // creates and setup shaders
    //  first create reference to the object shader,
    //  then take in the source code and compile it
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShader);  // does not throw errors if code is shit

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);    // same here

    //  then create the shader program:
    //  by assigning a reference to it and
    //  linking the two compiled shaders to it
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);

    // finally, wrap up the shader program and tidy up
    glLinkProgram(shaderProgram);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);


    // builds the triangle
    // vertex array object: where the data is used
    // vertex buffer object: where the data is stored
    GLuint VAO, VBO;
    // generate VAO before VBO !!!!
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1 /* only 1 3D object */, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0 /* position of vertex attribute */,
                          3 /* number of attributes per vertex */,
                          GL_FLOAT /* type of values */,
                          GL_FALSE /* matters only if values are int */,
                          3 * sizeof(float) /* amount of data in each vertex */,
                          (void *) nullptr /* offset of first vertex */);
    glEnableVertexAttribArray(0);

    // not mandatory, but better have it
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);


    // sets back buffer to navy blue
    glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // swaps front and back buffers to display blue
    glfwSwapBuffers(window);

    // window stays open until we close it
    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glfwSwapBuffers(window);

        // reacts to user inputs
        glfwPollEvents();
    }

    // free memory
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
