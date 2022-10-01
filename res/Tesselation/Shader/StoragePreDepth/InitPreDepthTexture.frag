#version 440 core

layout (location = 0) out vec3 PrePosition;//要输出到颜色纹理的坐标

in vec2 TexCoords;

uniform sampler2D DepthTexture;

void main()
{
    
    PrePosition.xyz =  texture(DepthTexture,TexCoords).rgb;

}

