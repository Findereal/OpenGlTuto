//
// Created by armand on 29/06/2021.
//

#ifndef OPENGLTUTO_EBO_H
#define OPENGLTUTO_EBO_H

#include <glad/glad.h>

class EBO {
public:
    GLuint id;
    EBO(GLuint* indices, GLsizeiptr size);

    void Bind();
    void Unbind();
    void Delete();

};


#endif //OPENGLTUTO_EBO_H
