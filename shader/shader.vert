#version 400

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 texCoords;

uniform mat4 projection;
uniform mat4 view;

out vec4 fPosition;
out vec4 fLightPosition;
out vec3 fNormal;
out vec2 fTexCoords;

void main(void)
{
    fPosition = view * vec4(position,1.0);
    fLightPosition = view * vec4(0.0,5.0,1.0,1.0);

    fNormal = vec3(view * vec4(normal,0.0));
    fTexCoords = texCoords;

    gl_Position = projection * fPosition;
}