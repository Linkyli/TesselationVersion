#version 440 core
layout (triangles) in;
layout (triangle_strip, max_vertices = 6) out;
//layout (line_strip, max_vertices = 6) out;



uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform vec2 PlaneSize;
uniform float MeshHeigth;
uniform vec2 MinXY;

out GS_OUT {
     vec3 ViewPos;
     vec2 PosTexCoord;

} gs_out;//以结构体的形式输出到片元着色器

  vec4 P1;//1轴方向
  vec4 P2;//2轴方向
  vec4 P3;//12轴方向


vec3 GetNormal()
{  
    vec3 a = vec3(P1) - vec3(P3);
    vec3 b = vec3(P3) - vec3(P2);
    return normalize(cross(a, b));
}


void EmitQuard3(){

     P1 = gl_in[0].gl_Position;
     P2 = gl_in[1].gl_Position;
     P3 = gl_in[2].gl_Position;

     vec3 FragPos1 = vec3(model * P1);
     vec3 FragPos2 = vec3(model * P2);
     vec3 FragPos3 = vec3(model * P3);

     P1 = projection * view * model * P1;
     P2 = projection * view * model * P2;
     P3 = projection * view * model * P3;


     vec3 normal =  GetNormal();
     
    
     gl_Position = P1;
     gs_out.ViewPos.xyz = gl_in[0].gl_Position.xyz;     
     gs_out.PosTexCoord.x = (gl_in[0].gl_Position.x) /(2.0f * PlaneSize.x);
     gs_out.PosTexCoord.y = (gl_in[0].gl_Position.y) /(2.0f * PlaneSize.y);
     EmitVertex();                      
                                        
     gl_Position = P2 ;                  
     gs_out.ViewPos.xyz = gl_in[1].gl_Position.xyz;  
     gs_out.PosTexCoord.x = (gl_in[1].gl_Position.x) /(2.0f * PlaneSize.x);
     gs_out.PosTexCoord.y = (gl_in[1].gl_Position.y) /(2.0f * PlaneSize.y);
       
     EmitVertex();                       
                                         
     gl_Position = P3;                   
     gs_out.ViewPos.xyz = gl_in[2].gl_Position.xyz;
     gs_out.PosTexCoord.x = (gl_in[2].gl_Position.x) /(2.0f * PlaneSize.x);
     gs_out.PosTexCoord.y = (gl_in[2].gl_Position.y) /(2.0f * PlaneSize.y);
     EmitVertex();

     EndPrimitive();
    
}

void main() {  
   EmitQuard3();
   return;
}



