//
// Created by armand on 29/06/2021.
//

#include "VAO.h"

VAO::VAO() {
    glGenVertexArrays(1, &id);
}

void VAO::linkVBO(VBO &VBO, GLuint layout) {
    VBO.Bind();
    glVertexAttribPointer(layout /* position of vertex attribute */,
                          3 /* number of attributes per vertex */,
                          GL_FLOAT /* type of values */,
                          GL_FALSE /* matters only if values are int */,
                          3 * sizeof(float) /* amount of data in each vertex */,
                          (void *) nullptr /* offset of first vertex */);
    glEnableVertexAttribArray(0);
    VBO.Unbind();
}

void VAO::Bind() {
    glBindVertexArray(id);
}

void VAO::Unbind() {
    glBindVertexArray(0);
}

void VAO::Delete() {
    glDeleteVertexArrays(1, &id);
}