#version 330 core

layout(location = 0) in vec3 aPos;         // 3D position
layout(location = 1) in vec3 aNorm;         // Surface normal
layout(location = 2) in vec2 aTexCoord;       // Texture Coordinate

uniform mat4 vpU;
uniform mat4 modelU;
uniform mat4 normalU;

out vec3 FragPos;
out vec3 Normal;
out vec2 TexCoord;

void main()
{
        vec4 worldPos = modelU * vec4(aPos, 1.0);

        FragPos = vec3(worldPos);  // world-space position
        Normal = mat3(normalU) * aNorm;      // correct normal transformation
        TexCoord = aTexCoord;

        gl_Position = vpU * worldPos; // convert to 4D vec
}
