#version 440 core
layout (triangles) in;
layout (triangle_strip, max_vertices = 6) out;
//layout (line_strip, max_vertices = 6) out;



uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec3 lightPos; 
uniform float MeshHeigth;
uniform vec2 MinXY;


uniform vec2 CubeTopAndBottom;

out GS_OUT {
     vec3 FragPos;
     vec3 Normal;

} gs_out;//以结构体的形式输出到片元着色器

  vec4 P1;//1轴方向
  vec4 P2;//2轴方向
  vec4 P3;//12轴方向


vec3 GetNormal()
{  
    //vec3 a = vec3(P1) - vec3(P3);
    //vec3 b = vec3(P1) - vec3(P2);
    //return normalize(cross(a, b));
   vec3 a = vec3(gl_in[0].gl_Position) - vec3(gl_in[1].gl_Position);
   vec3 b = vec3(gl_in[2].gl_Position) - vec3(gl_in[1].gl_Position);
   return normalize(cross(a, b));
}


void EmitTri(){

     P1 = gl_in[0].gl_Position;
     P2 = gl_in[1].gl_Position;
     P3 = gl_in[2].gl_Position;

     vec3 FragPos1 = vec3(model * P1);
     vec3 FragPos2 = vec3(model * P2);
     vec3 FragPos3 = vec3(model * P3);


     P1 = projection * view * model * P1;
     P2 = projection * view * model * P2;
     P3 = projection * view * model * P3;

     vec3 normal = GetNormal();

     vec3 TriCenter;
     TriCenter.x = (gl_in[0].gl_Position.x + gl_in[1].gl_Position.x + gl_in[2].gl_Position.x)/(3.0f);
     TriCenter.y = (gl_in[0].gl_Position.y + gl_in[1].gl_Position.y + gl_in[2].gl_Position.y)/(3.0f);
     TriCenter.z = (gl_in[0].gl_Position.z + gl_in[1].gl_Position.z + gl_in[2].gl_Position.z)/(3.0f);
    
     vec3 CenterToTri = lightPos - TriCenter ;

     float negative = dot(CenterToTri,normal);

     if(negative < 0 ){
         normal = (-1.0f) * normal;
     }

     //normal = mat3(transpose(inverse(model))) * normal;
    
     gl_Position = P1;
     gs_out.FragPos = FragPos1;
     gs_out.Normal = normal;
     EmitVertex();                      
                                        
     gl_Position = P2 ;                  
     gs_out.FragPos = FragPos2;         
     gs_out.Normal = normal;                      
     EmitVertex();                       
                                         
     gl_Position = P3;                   
     gs_out.FragPos = FragPos3;          
     gs_out.Normal = normal;
     EmitVertex();

     EndPrimitive();
    
}

void EmitNewQuard(vec4 NP0, vec4 NP1,vec4 NP2,vec4 NP3){

     vec4 Q0,Q1,Q2,Q3;
     Q0 = NP0;
     Q1 = NP1;
     Q2 = NP2;
     Q3 = NP3;

     vec3 FragPos0 = vec3(model * Q0);
     vec3 FragPos1 = vec3(model * Q1);
     vec3 FragPos2 = vec3(model * Q2);
     vec3 FragPos3 = vec3(model * Q3);


     Q0 = projection * view * model * Q0;
     Q1 = projection * view * model * Q1;
     Q2 = projection * view * model * Q2;
     Q3 = projection * view * model * Q3;

     vec3 a = vec3(Q0) - vec3(Q1);
     vec3 b = vec3(Q2) - vec3(Q1);  
     vec3 normal = normalize(cross(a, b));


     vec3 QuardCenter;
     QuardCenter.x = (Q0.x + Q1.x + Q2.x + Q3.x)/(4.0f);
     QuardCenter.y = (Q0.y + Q1.y + Q2.y + Q3.y)/(4.0f);
     QuardCenter.z = (Q0.z + Q1.z + Q2.z + Q3.z)/(4.0f);
    

     vec3 CenterToTri = lightPos - QuardCenter ;

     float negative = dot(CenterToTri,normal);

     if(negative < 0 ){
         normal = (-1.0f) * normal;
     }


     gl_Position = Q0;
     gs_out.FragPos = FragPos1;
     gs_out.Normal = normal;
     EmitVertex();   
              
     gl_Position = Q1;
     gs_out.FragPos = FragPos1;
     gs_out.Normal = normal;    
     EmitVertex();                      
                                        
     gl_Position = Q2 ;                  
     gs_out.FragPos = FragPos2;         
     gs_out.Normal = normal;                                                   
     EmitVertex();                       
                                         
     gl_Position = Q3;                   
     gs_out.FragPos = FragPos3;          
     gs_out.Normal = normal;                                         
     EmitVertex();

     EndPrimitive();
    
}


void EmitNewTri(){


     vec3 FragPos1 = vec3(model * P1);
     vec3 FragPos2 = vec3(model * P2);
     vec3 FragPos3 = vec3(model * P3);

     vec3 a = vec3(P1) - vec3(P2);
     vec3 b = vec3(P3) - vec3(P2);  
     vec3 normal = normalize(cross(a, b));


     vec3 TriCenter;
     TriCenter.x = (P1.x + P2.x + P3.x)/(3.0f);
     TriCenter.y = (P1.y + P2.y + P3.y)/(3.0f);
     TriCenter.z = (P1.z + P2.z + P3.z)/(3.0f);
    
     vec3 CenterToTri = lightPos - TriCenter ;

     P1 = projection * view * model * P1;
     P2 = projection * view * model * P2;
     P3 = projection * view * model * P3;




     float negative = dot(CenterToTri,normal);

     if(negative < 0 ){
         normal = (-1.0f) * normal;
     }

     //normal = mat3(transpose(inverse(model))) * normal;
    
     gl_Position = P1;
     gs_out.FragPos = FragPos1;
     gs_out.Normal = normal;
     EmitVertex();                      
                                        
     gl_Position = P2 ;                  
     gs_out.FragPos = FragPos2;         
     gs_out.Normal = normal;                      
     EmitVertex();                       
                                         
     gl_Position = P3;                   
     gs_out.FragPos = FragPos3;          
     gs_out.Normal = normal;
     EmitVertex();

     EndPrimitive();
}

void TestTri(){
    vec4 oldPoint[3];
    
    int countPoint = 0;

    for(int i = 0;i< 3;i++){ 
        if(gl_in[i].gl_Position.z < CubeTopAndBottom.y){
          oldPoint[2 - countPoint] = gl_in[i].gl_Position;
          countPoint++;
        }else{
          oldPoint[i - countPoint]= gl_in[i].gl_Position;
        }
    
    }
    if(countPoint>0) return;
    if(countPoint == 3 ) return;
    
    
    if(countPoint == 0 ){
       EmitTri();
       return;
    }
    
    
    vec4 B1,B2;
    
   if(countPoint == 1){
      B1.x =( abs(oldPoint[0].z) * oldPoint[2].x + abs(oldPoint[2].z) * oldPoint[0].x )/(abs(oldPoint[0].z) + abs(oldPoint[2].z));
      B1.y =( abs(oldPoint[0].z) * oldPoint[2].y + abs(oldPoint[2].z) * oldPoint[0].y )/(abs(oldPoint[0].z) + abs(oldPoint[2].z));
      B1.z = CubeTopAndBottom.y;
   
      B2.x =( abs(oldPoint[1].z) * oldPoint[2].x + abs(oldPoint[2].z) * oldPoint[1].x )/(abs(oldPoint[1].z) + abs(oldPoint[2].z));
      B2.y =( abs(oldPoint[1].z) * oldPoint[2].y + abs(oldPoint[2].z) * oldPoint[1].y )/(abs(oldPoint[1].z) + abs(oldPoint[2].z));
      B2.z = CubeTopAndBottom.y;

      EmitNewQuard(B1,B2,oldPoint[1],oldPoint[0]);
      return;

    }else if(countPoint == 2){

      B1.x =( abs(oldPoint[0].z) * oldPoint[2].x + abs(oldPoint[2].z) * oldPoint[0].x )/(abs(oldPoint[0].z) + abs(oldPoint[2].z));
      B1.y =( abs(oldPoint[0].z) * oldPoint[2].y + abs(oldPoint[2].z) * oldPoint[0].y )/(abs(oldPoint[0].z) + abs(oldPoint[2].z));
      B1.z = CubeTopAndBottom.y;
   
      B2.x =( abs(oldPoint[0].z) * oldPoint[1].x + abs(oldPoint[1].z) * oldPoint[0].x )/(abs(oldPoint[0].z) + abs(oldPoint[1].z));                                                                                                                      
      B2.y =( abs(oldPoint[0].z) * oldPoint[1].y + abs(oldPoint[1].z) * oldPoint[0].y )/(abs(oldPoint[0].z) + abs(oldPoint[1].z));
      B2.z = CubeTopAndBottom.y;

      P1 = oldPoint[0];
      P2 = B1;
      P3 = B2;

      EmitNewTri();
      return;
    }
    
return;
   
      
   
}


void main() {  
    TestTri();
}



