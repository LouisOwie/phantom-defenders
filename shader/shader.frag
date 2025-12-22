#version 400

in vec4 fPosition;
in vec4 fLightPosition;
in vec3 fNormal;
in vec2 fTexCoords;

// texture sampler
uniform sampler2D texture_diffuse;
uniform sampler2D texture_specular;
uniform bool hasTexture;
uniform bool hasSpecularTexture;
uniform vec3 kd_color;

// output
out vec4 color;

void main(void)
{
    vec3 o =-normalize(fPosition.xyz);
    vec3 n = normalize(fNormal);
    vec3 r = reflect(o,n);
    vec3 l = normalize(fLightPosition.xyz-fPosition.xyz);

    float ambient = 0.1;
    float diffuse = 0.7*max(0.0,dot(n,l));
    float specular = 0.6*pow(max(0.0,-dot(r,l)),4.0);

    vec4 baseColor = vec4(1.0, 1.0, 1.0, 1.0);
    if (hasTexture) {
        baseColor = texture(texture_diffuse, fTexCoords);
    }
    else {
        baseColor = vec4(kd_color, 1.0);
    }

    vec4 specularMap = vec4(0.5, 0.5, 0.5, 1.0);
    if (hasSpecularTexture) {
        specularMap = texture(texture_specular, fTexCoords);
    }

    color = baseColor * ( ambient + diffuse ) + specularMap * specular;
}