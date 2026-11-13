#version 330 core

in vec3 Normal;
in vec3 FragPos;

uniform vec3 u_Color;
uniform vec3 u_LightPos;

out vec4 FragColor;

const vec3 lightColor = vec3(1.0f, 1.0f, 1.0f);
const vec3 ambientColor = vec3(0.8f, 0.8f, 0.8f) * 0.6f;

void main()
{
    vec3 normals = normalize(Normal);
    vec3 lightDir = normalize(u_LightPos - FragPos);

    float diffuse = max(dot(normals, lightDir), 0.0f);
    vec3 diff = diffuse * lightColor;

    FragColor = vec4((ambientColor + diffuse) * u_Color, 1.0);
}