//
// Created by armand on 29/06/2021.
//

#ifndef OPENGLTUTO_SHADERSCLASS_H
#define OPENGLTUTO_SHADERSCLASS_H

#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cerrno>

std::string get_file_contents(const char* filename);

class Shader {
public:
    GLuint id;

    Shader(const char *vFile, const char *fFile);

    void Activate();

    void Delete();

private:
    void compileErrors(unsigned int shader, const char *type);
};

#endif //OPENGLTUTO_SHADERSCLASS_H
