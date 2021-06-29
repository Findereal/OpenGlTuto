//
// Created by armand on 29/06/2021.
//

#include "VBO.h"

VBO::VBO(GLfloat* vertices, GLsizeiptr size){
    glGenBuffers(1 /* only 1 3D object */, &id);
    glBindBuffer(GL_ARRAY_BUFFER, id);
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);  // says VBO will hold vertices data
}

void VBO::Bind() {
    glBindBuffer(GL_ARRAY_BUFFER, id);
}

void VBO::Unbind() {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VBO::Delete() {
    glDeleteBuffers(1, &id);
}