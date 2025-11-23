
#include "programTools.h"
namespace Tools {
    GLuint linkProgram(const GLuint vs, const GLuint fs) {
        const GLuint program = glCreateProgram();
        glAttachShader(program, vs);
        glAttachShader(program, fs);
        glLinkProgram(program);

        return program;
    }

    GLuint createShader(const GLenum shaderType, const std::string shaderSource) {
        const GLuint shader = glCreateShader(shaderType);
        const char* sourceCStr = shaderSource.c_str();
        glShaderSource(shader, 1, &sourceCStr, nullptr);
        glCompileShader(shader);
        return shader;
    }

    bool checkError() {
        if (const GLenum err = glGetError(); err != GL_NO_ERROR) {
            std::fprintf(stderr, "OpenGL error 0x%04X\n occurred", err);
            return false;
        }
        return true;
    }
}