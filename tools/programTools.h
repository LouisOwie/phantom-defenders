
#ifndef PHANTOM_DEFENDERS_PROGRAMTOOLS_H
#define PHANTOM_DEFENDERS_PROGRAMTOOLS_H
#include "../lib/GL/glew.h"
#include <string>

namespace Tools {
    GLuint linkProgram(GLuint vs, GLuint fs);
    GLuint createShader(GLenum shaderType, std::string shaderSource);
    bool checkError();
#define VERIFY(condition)  \
if (!(condition)) \
{ \
fprintf(stderr, "%s:%d: Verification '%s' failed.\n", \
__FILE__, __LINE__, #condition); \
exit(-1); \
}
}
#endif //PHANTOM_DEFENDERS_PROGRAMTOOLS_H