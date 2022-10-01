#version 440 core


in  vec3 EvalNormal;

out vec4 FragColor;

in GS_OUT {
    vec3 FragPos;
    vec3 Normal;

} gs_out;

uniform sampler2D DepthTexture;
//uniform sampler2D Noise;

uniform vec3 lightPos; 
uniform vec3 lightColor;
uniform vec3 objectColor;
uniform vec3 viewPos; 


void main()
{
    //objectColor = vec3(0.192,0.192,0.192);
    

    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;

    vec3 norm = normalize(gs_out.Normal);
    vec3 lightDir = normalize(lightPos - gs_out.FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;
            

    // specular
    float specularStrength = 0.3;
    vec3 viewDir = normalize(viewPos - gs_out.FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * lightColor; 

    vec3 result = (ambient + diffuse + specular) * objectColor;

    //result = (ambient + diffuse + specular) * texture(DepthTexture, vec2(gs_out.TexCoord)).rgb;

    //vec4 VerPos = vec4(gl_FragCoord);
    FragColor = vec4(result, 1.0);


}