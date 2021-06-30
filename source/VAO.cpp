//
// Created by armand on 29/06/2021.
//

#include "VAO.h"

VAO::VAO() {
    glGenVertexArrays(1, &id);
}

void VAO::linkAttrib(VBO &VBO, GLuint layout, GLuint numComp, GLenum type, GLsizeiptr stride, void *offset) {
    VBO.Bind();
    glVertexAttribPointer(layout /* position of vertex attribute */,
                          numComp /* number of attributes per vertex */,
                          type /* type of values */,
                          GL_FALSE /* matters only if values are int */,
                          stride /* amount of data in each vertex */,
                          offset /* offset of first vertex */);
    glEnableVertexAttribArray(layout);
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