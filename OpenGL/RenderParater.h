#pragma once
#include<iostream>
#include"../OpenGL/Mycamera.h"
#include <stb_image.h>


#include<queue>
#include<stack>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <learnopengl/shader_m.h>
//#include <learnopengl/model.h>
#include<learnopengl/filesystem.h>
#include <unordered_map>
#include<map>
#include<iostream>
#include<bitset>
#include<math.h>
#include<set>




using namespace std;
time_t BeginTime,CurrTime, EndTime, PauseTime,CuttedStartTime,CuttedEndTime,RenderBeginTime,RenderEndTime;

//uitest
static void glfw_error_callback(int error, const char* description)
{
	fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow* window);
unsigned int loadTexture(const char* path);
unsigned int loadCubemap(vector<std::string> faces);


unsigned int SCR_WIDTH = 1200;
unsigned int SCR_HEIGHT = 900;

// camera
//Mycamera camera = Mycamera(glm::vec3(30.0f, 30.0f, 80.0f));
//Mycamera camera = Mycamera(glm::vec3(0.0f, 0.0f, 3.0f));

//Mycamera camera = Mycamera(glm::vec3(70.0f, 50.0f, 100.0f));
Mycamera camera = Mycamera(glm::vec3(0.0f, 0.0f, 3.0f));


float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;

glm::vec3 lightPos = glm::vec3(12.0f, 10.0f, 20.0f);

void  processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.ProcessKeyboard(FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.ProcessKeyboard(LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.ProcessKeyboard(RIGHT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
		camera.ProcessKeyboard(UP, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
		camera.ProcessKeyboard(DOWN, deltaTime);

}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void  framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	//Êó±êÓÒ¼üµ÷ÕûÊÓ½Ç
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS) {

		if (firstMouse)
		{
			lastX = xpos;
			lastY = ypos;
			firstMouse = false;
		}

		float xoffset = xpos - lastX;
		float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

		lastX = xpos;
		lastY = ypos;

		camera.ProcessMouseMovement(xoffset, yoffset);
	}
	else {
		firstMouse = true;
	}
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(yoffset);
}

// utility function for loading a 2D texture from file
// ---------------------------------------------------
unsigned int loadTexture(char const* path)
{
    unsigned int textureID;
    glGenTextures(1, &textureID);

    int width, height, nrComponents;
    unsigned char* data = stbi_load(path, &width, &height, &nrComponents, 0);
    if (data)
    {
        GLenum format;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    }
    else
    {
        std::cout << "Texture failed to load at path: " << path << std::endl;
        stbi_image_free(data);
    }

    return textureID;
}

// loads a cubemap texture from 6 individual texture faces
// order:
// +X (right)
// -X (left)
// +Y (top)
// -Y (bottom)
// +Z (front) 
// -Z (back)
// -------------------------------------------------------
unsigned int loadCubemap(vector<std::string> faces)
{
    unsigned int textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

    int width, height, nrChannels;
    for (unsigned int i = 0; i < faces.size(); i++)
    {
        unsigned char* data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
        if (data)
        {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            stbi_image_free(data);
        }
        else
        {
            std::cout << "Cubemap texture failed to load at path: " << faces[i] << std::endl;
            stbi_image_free(data);
        }
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    return textureID;
}




GLint EdgeToBit[24]{
    2,6,//zÖá£¬6Î»ÓÒÒÆ
    1,0,//yÖá£¬0Î»ÓÒÒÆ
    2,0,//zÖá£¬0Î»ÓÒÒÆ
    1,6,//yÖá£¬6Î»ÓÒÒÆ
                  
    2,9,//zÖá£¬9Î»ÓÒÒÆ
    1,3,//yÖá£¬3Î»ÓÒÒÆ
    2,3,//zÖá£¬3Î»ÓÒÒÆ
    1,9,//yÖá£¬9Î»ÓÒÒÆ
                  
    0,9,//xÖá£¬9Î»ÓÒÒÆ
    0,3,//xÖá£¬3Î»ÓÒÒÆ
    0,0,//xÖá£¬0Î»ÓÒÒÆ
    0,6 //xÖá£¬6Î»ÓÒÒÆ

};

GLint EdgeVertex[24]{
    1,0,//0  0,1
    2,1,//1  1,2
    2,3,//2  2,3
    3,0,//3  3,0

    5,4,//4  4,5
    6,5,//5  5,6
    6,7,//6  6,7
    7,4,//7  7,4
    
    0,4,//8  0,4
    1,5,//9  1,5
    2,6,//10 2,6
    3,7 //11 3,7
    
};

float EdgeDirection[36] =
{
        1.0,  0.0, 0.0,
        0.0,  1.0, 0.0,
       -1.0,  0.0, 0.0,
        0.0, -1.0, 0.0,
        1.0,  0.0, 0.0,
        0.0,  1.0, 0.0,
       -1.0,  0.0, 0.0,
        0.0, -1.0, 0.0,
        0.0,  0.0, 1.0,
        0.0,  0.0, 1.0, 
        0.0,  0.0, 1.0,
        0.0,  0.0, 1.0
};




