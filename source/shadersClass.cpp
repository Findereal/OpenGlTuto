//
// Created by armand on 29/06/2021.
//

#include "shadersClass.h"

std::string get_file_contents(const char *filename) {
    printf("%s\n", filename);


    std::ifstream f(filename, std::ios::binary);
    if (f) {
        std::string str;

        f.seekg(0, std::ios::end);
        str.reserve(f.tellg());
        f.seekg(0, std::ios::beg);

        str.assign((std::istreambuf_iterator<char>(f)),
                   std::istreambuf_iterator<char>());
        return (str);
    } else {
        std::cout << "we have a problem here\n";
        return "1";
    }
}

Shader::Shader(const char *vFile, const char *fFile) {
    // get relative path of source files
    std::string path = "../resources/Shader/";
    std::string vPath = path;
    vPath.append(vFile);
    std::string fPath = path;
    fPath.append(fFile);

    // read source files
    std::string vCode = get_file_contents(vPath.c_str());
    std::string fCode = get_file_contents(fPath.c_str());

    const char *vSource = vCode.c_str();
    const char *fSource = fCode.c_str();

    // creates and setup shaders
    //  first create reference to the object shader,
    //  then take in the source code and compile it
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vSource, nullptr);
    glCompileShader(vertexShader);  // does not throw errors if code is shit
    compileErrors(vertexShader, "VERTEX");
    Z

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fSource, nullptr);
    glCompileShader(fragmentShader);    // same here
    compileErrors(fragmentShader, "FRAGMENT");

    //  then create the shader program:
    //  by assigning a reference to it and
    //  linking the two compiled shaders to it
    id = glCreateProgram();
    glAttachShader(id, vertexShader);
    glAttachShader(id, fragmentShader);

    // finally, wrap up the shader program and tidy up
    glLinkProgram(id);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void Shader::Activate() {
    glUseProgram(id);
}

void Shader::Delete() {
    glDeleteProgram(id);
}

void Shader::compileErrors(unsigned int shader, const char *type) {
    GLint hasComp;
    char infoLog[1024];
    if (type != "PROGRAM") {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &hasComp);
        if (hasComp == GL_FALSE) {
            glGetShaderInfoLog(shader, 1024, NULL, infoLog);
            std::cout << "Shader Compilation Error for " << type << "\n" << std::endl;
        }
    } else {
        glGetProgramiv(shader, GL_COMPILE_STATUS, &hasComp);
        if (hasComp == GL_FALSE) {
            glGetProgramInfoLog(shader, 1024, NULL, infoLog);
            std::cout << "Shader Linking Error for " << type << "\n" << std::endl;
        }
    }
}