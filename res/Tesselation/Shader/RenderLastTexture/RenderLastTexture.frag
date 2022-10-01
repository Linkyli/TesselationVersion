#version 440 core

layout (location = 0) out vec3 LastPosition;//要输出到颜色纹理的坐标

in vec2 TexCoords;
uniform vec3 PlaneNormal;
uniform sampler2D CurrDepthTexture;
uniform sampler2D PreDepthTexture;

float vec3dot(vec3 a,vec3 b){
    return (a.x * b.x + a.y * b.y + a.z * b.z);
}

void main()
{   
    vec3 CurrDepth= texture(CurrDepthTexture,TexCoords).rgb;
    vec3 PreDepth = texture(PreDepthTexture,TexCoords).rgb;
   
    LastPosition = PreDepth;
    //vec3 PN = vec3(0.0f,0.0f,0.0f);
    LastPosition.z = min(CurrDepth.z,PreDepth.z);
    //LastPosition.z = min(vec3dot(CurrDepth,PN),vec3dot(PreDepth,PN));
    //LastPosition.z = PreDepth.z -  (CurrDepth.z - PreDepth.z);
}

