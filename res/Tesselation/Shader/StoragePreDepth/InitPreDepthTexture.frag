#version 440 core

layout (location = 0) out vec3 PrePosition;//Ҫ�������ɫ���������

in vec2 TexCoords;

uniform sampler2D DepthTexture;

void main()
{
    
    PrePosition.xyz =  texture(DepthTexture,TexCoords).rgb;

}

