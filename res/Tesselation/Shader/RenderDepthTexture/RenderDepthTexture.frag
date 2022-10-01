#version 440 core

layout (location = 0) out vec3 gPosition;

//uniform sampler2D Noise;
//uniform sampler2D PrePosition;

in GS_OUT {
     vec3 ViewPos;
     vec2 PosTexCoord;
} gs_out;



void main()
{
    //VerPos = vec4(vec3(gl_FragCoord.z), 1.0);
   
    //ÆÁÄ»×ø±êÎª-1µ½1
    vec2 PrePosTexCoord;
    PrePosTexCoord.x = (gl_FragCoord.x + 1.0f)/(2.0f);
    PrePosTexCoord.y = (gl_FragCoord.y + 1.0f)/(2.0f);

    PrePosTexCoord = gs_out.PosTexCoord;
   
    gPosition  = gs_out.ViewPos;   

    //gPosition.z = min(gs_out.ViewPos.z, texture(PrePosition,PrePosTexCoord).b);
    
    //if(gs_out.ViewPos.z < texture(PrePosition,PrePosTexCoord).b){
    //     gPosition  = gs_out.ViewPos;      
    //}
    //else{
    //    gPosition  = texture(PrePosition,PrePosTexCoord).rgb;   
    //};
    
    //gPosition  = texture(PrePosition,PrePosTexCoord).rgb;   
    //gPosition  = texture(Noise,PrePosTexCoord).rgb;   
    //gPosition  = gs_out.ViewPos;
    //gPosition = texture(PrePosition,PrePosTexCoord).rgb;
    //gPosition = gs_out.ViewPos;
    //gPosition.z = tempPos.z;

    //gPosition = vec3(0.0,0.0,gl_FragCoord.z);


}