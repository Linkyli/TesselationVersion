#version 440 core

layout (location = 0) in  vec3  vPosition;
//in  vec3  vNormal;
//out vec3  VertNormal;
void
main()
{
    gl_Position = vec4(vPosition,1.0);
    //VertNormal = vNormal;
}
