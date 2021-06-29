//
// Created by armand on 29/06/2021.
//

#include "EBO.h"
#include <glad/glad.h>

EBO::EBO(GLuint* indices, GLsizeiptr size){
    glGenBuffers(1 /* only 1 3D object */, &id);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);  // says VBO will hold vertices data
}

void EBO::Bind() {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
}

void EBO::Unbind() {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void EBO::Delete() {
    glDeleteBuffers(1, &id);
}