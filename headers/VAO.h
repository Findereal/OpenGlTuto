//
// Created by armand on 29/06/2021.
//

#ifndef OPENGLTUTO_VAO_H
#define OPENGLTUTO_VAO_H

#include <glad/glad.h>
#include "VBO.h"


class VAO {
public:
    GLuint id;
    VAO();

    void linkAttrib(VBO &VBO, GLuint layout, GLuint numComp, GLenum type, GLsizeiptr stride, void *offset);

    void Bind();
    void Unbind();
    void Delete();
};


#endif //OPENGLTUTO_VAO_H
