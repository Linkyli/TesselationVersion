#version 440 core

layout (location = 0) out vec3 PrePosition;//要输出到颜色纹理的坐标

in vec2 TexCoords;

uniform sampler2D DepthTexture;

void main()
{   
    PrePosition.rgb = texture(DepthTexture,TexCoords).rgb;// vec3(1.0,1.0,1.0);//

}

