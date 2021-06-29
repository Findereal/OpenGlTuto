//
// Created by armand on 29/06/2021.
//

#ifndef OPENGLTUTO_VBO_H
#define OPENGLTUTO_VBO_H

#include <glad/glad.h>

class VBO {
public:
    GLuint id;
    VBO(GLfloat* vertices, GLsizeiptr size);

    void Bind();
    void Unbind();
    void Delete();

};


#endif //OPENGLTUTO_VBO_H
