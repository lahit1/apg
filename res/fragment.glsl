#version 330 core


uniform vec3 materialAmbientC;
uniform vec3 materialDiffuseC;
uniform vec3 materialSpecularC;
uniform float materialShininess;

uniform sampler2D materialDiffuseT;
uniform sampler2D materialSpecularT;
uniform sampler2D materialNormalT;


uniform vec3 viewPos;      // Camera position

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoord;

out vec4 FragColor;      // Output color

void main()
{
        FragColor = texture(materialDiffuseT, TexCoord);
//      FragColor = vec4(TexCoord, 0.0, 1.0);
}
