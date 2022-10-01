#pragma once
#include"../OpenGL/RenderParater.h"
#include"../ReadPathFile/ReadPath.h"
#include"../glAPI/LoadShaders.h"
//来自Iteration10

#define BUFFER_OFFSET(a) ((void*)(a))


ReadPath CutterFilePath;

glm::vec3 GetFileCutterPosOfPlane(int& Index) {

	if (Index >= CutterFilePath.CutterPath.size()) {
		Index = CutterFilePath.CutterPath.size() - 1;
	}
	glm::vec3 CutterPlanePos = glm::vec3(CutterFilePath.CutterPath[Index].x / (5.0f),
		CutterFilePath.CutterPath[Index].y / (5.0f),
		CutterFilePath.CutterPath[Index].z / (5.0f) - 8.0f);

	return  CutterPlanePos;
}
//刀具测试轨迹,输入平面的宽度与长度，以及刀具需要的的深度
glm::vec3* CutterPath(int width, int length, int depth, int PathPrecision = 100) {
	float MinDistance = (1.0f / int(PathPrecision));

	glm::vec3* PathPos = (glm::vec3*)malloc(PathPrecision * sizeof(glm::vec3));

	for (int i = 0; i < PathPrecision; i++) {
		PathPos[i] = glm::vec3(float(width) * MinDistance * i, float(length) * MinDistance * i, depth);
	}

	return PathPos;;
}

//设置帧缓冲，添加颜色缓冲附件与深度缓冲附件，暂未添加模板缓冲，未使用渲染缓冲对象附件（只写）
unsigned int SetFramBuffer(unsigned int SCR_WIDTH, unsigned int SCR_HEIGHT, unsigned int& textureColorbuffer) //,unsigned int& textureDepthbuffer,unsigned int& textureStencilbuffer
{
	// framebuffer configuration
	// -------------------------
	unsigned int framebuffer;
	//glGenFramebuffers(1, &framebuffer);
	//glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
	//
	//// create a color attachment texture,创建一个纹理附件作为颜色缓冲
	//glGenTextures(1, &textureColorbuffer);
	//glBindTexture(GL_TEXTURE_2D, textureColorbuffer);
	//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, SCR_WIDTH, SCR_HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//// 将它附加到当前绑定的帧缓冲对象
	//glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureColorbuffer, 0);

	////创建一个纹理附件作为深度缓冲
	//glGenTextures(1, &textureDepthbuffer);
	//glBindTexture(GL_TEXTURE_2D, textureDepthbuffer);
	//glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, SCR_WIDTH, SCR_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, NULL);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, textureDepthbuffer, 0);

	// 创建一个纹理附件作为深度缓冲
	//glGenTextures(1, &textureDepthbuffer);
	//glBindTexture(GL_TEXTURE_2D, textureDepthbuffer);
	//glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, SCR_WIDTH, SCR_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, textureDepthbuffer, 0);

	////创建一个纹理附件作为模板缓冲
	//glGenTextures(1, &textureStencilbuffer);
	//glBindTexture(GL_TEXTURE_2D, textureStencilbuffer);
	//glTexImage2D(GL_TEXTURE_2D, 0, GL_STENCIL_INDEX, SCR_WIDTH, SCR_HEIGHT, 0, GL_STENCIL_INDEX, GL_UNSIGNED_BYTE, NULL);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//glFramebufferTexture2D(GL_FRAMEBUFFER, GL_STENCIL_ATTACHMENT, GL_TEXTURE_2D, textureStencilbuffer, 0);

	//渲染缓冲对象存储的是OpenGL原生的渲染格式，渲染缓冲对象通常都是只写的，所以不能读取它们,深度值可以通过gl_FragCoord.z获取
	// create a renderbuffer object for depth and stencil attachment (we won't be sampling these)
	//unsigned int rbo;
	//glGenRenderbuffers(1, &rbo);
	//glBindRenderbuffer(GL_RENDERBUFFER, rbo);
	//glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, SCR_WIDTH, SCR_HEIGHT); // use a single renderbuffer object for both a depth AND stencil buffer.
	//glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo); // now actually attach it
	// now that we actually created the framebuffer and added all attachments we want to check if it is actually complete now

	//添加渲染缓冲对象(Render Buffer Object)为深度缓冲(Depth Buffer)，
	//GLuint rboDepth;
	//glGenRenderbuffers(1, &rboDepth);
	//glBindRenderbuffer(GL_RENDERBUFFER, rboDepth);
	//glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, SCR_WIDTH, SCR_HEIGHT);
	//glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, rboDepth);

	//添加渲染缓冲对象(Render Buffer Object)为模板缓冲(Depth Buffer)，并检查完整性
	//GLuint rboStencil;
	//glGenRenderbuffers(1, &rboStencil);
	//glBindRenderbuffer(GL_RENDERBUFFER, rboStencil);
	//glRenderbufferStorage(GL_RENDERBUFFER,GL_STENCIL_INDEX, SCR_WIDTH, SCR_HEIGHT);
	//glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rboDepth);


	glGenFramebuffers(1, &framebuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
	cout << "framebufferID: " << textureColorbuffer << endl;
	glGenTextures(1, &textureColorbuffer);
	glBindTexture(GL_TEXTURE_2D, textureColorbuffer);

	cout << "textureColorbufferID: " << textureColorbuffer << endl;
	cout << endl;
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, SCR_WIDTH, SCR_HEIGHT, 0, GL_RGB, GL_FLOAT, NULL);//SCR_WIDTH,SCR_HEIGHT
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	// 将它附加到当前绑定的帧缓冲对象
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureColorbuffer, 0);

	unsigned int rbo;
	glGenRenderbuffers(1, &rbo);
	glBindRenderbuffer(GL_RENDERBUFFER, rbo);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, SCR_WIDTH, SCR_HEIGHT); // use a single renderbuffer object for both a depth AND stencil buffer.
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo); // now actually attach it

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << endl;
	glBindFramebuffer(GL_FRAMEBUFFER, 0);


	return framebuffer;

}

//返回所获平面的指针,OldVer边长为2，大小为4 *  4  * 3  * sizeof(float)
GLfloat* SetMorePlane(GLfloat* NewVer, GLfloat* OldVer, int Width, int Length) {

	NewVer = (GLfloat*)malloc(4 * 4 * 3 * sizeof(float) * Width * Length);

	float X, Y, Z;

	for (int i = 0; i < Width; i++) {//边长
		for (int j = 0; j < Length; j++) {


			for (int PatchNum = 0; PatchNum < 4; PatchNum++) {//4个平面
				for (int PatchSize = 0; PatchSize < 4; PatchSize++) {//每个平面4个顶点

					//每个顶点三个分量确定位置,改动X分量


					X = OldVer[PatchNum * 4 * 3 + PatchSize * 3] + 2.0f * i;

					Y = OldVer[PatchNum * 4 * 3 + PatchSize * 3 + 1] + 2.0f * j;

					Z = OldVer[PatchNum * 4 * 3 + PatchSize * 3 + 2];

					NewVer[i * Length * 4 * 4 * 3 + j * 4 * 4 * 3 + PatchNum * 4 * 3 + PatchSize * 3] = X;

					NewVer[i * Length * 4 * 4 * 3 + j * 4 * 4 * 3 + PatchNum * 4 * 3 + PatchSize * 3 + 1] = Y;

					NewVer[i * Length * 4 * 4 * 3 + j * 4 * 4 * 3 + PatchNum * 4 * 3 + PatchSize * 3 + 2] = Z;
				}
			}
		}

	}


	return NewVer;
}

void Tesselation() {

	 const char* PathFilename = "D:\\Octree_res\\path\\temp.path";
	CutterFilePath.ReadPathfile(PathFilename);

	//140，90，40 除以10？
	int Width = 14;
	int Length = 9;

	float CutterR = 0.6;
	int PathPrecision = 2000;
	glm::vec3 CutterPos = glm::vec3(5.0, 5.0, -6.50f);
	glm::vec2 CubeTopAndBottom = glm::vec2(0.0f, -4.0f * 2.0f);



	//glfwSetErrorCallback(glfw_error_callback);//uitest
	if (!glfwInit())
		return;

	// Decide GL+GLSL versions
#if defined(IMGUI_IMPL_OPENGL_ES2)
	// GL ES 2.0 + GLSL 100
	const char* glsl_version = "#version 100";
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
#elif defined(__APPLE__)
	// GL 3.2 + GLSL 150
	const char* glsl_version = "#version 150";
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // Required on Mac
#else
	// GL 3.0 + GLSL 130
	const char* glsl_version = "#version 440";
	/*
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	*/
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // 3.0+ only
#endif


	GLFWwindow* window;
	/*
	//Octreecut.Visualizer(Octreecut.C, i,Octreecut.GetCutterBoundBox(Octreecut.C));
	// glfw: initialize and configure
// ------------------------------
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	*/

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	// glfw window creation
	// --------------------
	window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "TesselationSimple", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);


	// glad: load all OpenGL function pointers
// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return;
	}

	// configure global opengl state
	// -----------------------------
	glEnable(GL_DEPTH_TEST);

	//camera.Right += 100;//调整主相机视角

	const GLubyte* OpenGLVersion = glGetString(GL_VERSION); //返回当前OpenGL实现的版本号
	cout << "OpenGLVersion: " << OpenGLVersion << endl;



	GLuint VBO[5], VAO[5], EBO[5];
	glGenVertexArrays(5, VAO);
	glGenBuffers(5, VBO);
	glGenBuffers(5, EBO);


	//编译并附加shader程序到program上
	Shader TesselationShader(
		"./res/Tesselation/Shader/simpletess/simple.vert",
		"./res/Tesselation/Shader/simpletess/simple.frag",
		"./res/Tesselation/Shader/simpletess/simple.cont",
		"./res/Tesselation/Shader/simpletess/simple.eval",
		"./res/Tesselation/Shader/simpletess/simple.geom"
	);

	Shader CutterShader(
		"./res/Tesselation/Shader/simpletess/simple.vert",
		"./res/Tesselation/Shader/cutter/sphere.frag",
		"./res/Tesselation/Shader/simpletess/simple.cont",
		"./res/Tesselation/Shader/cutter/sphere.eval",
		"./res/Tesselation/Shader/cutter/sphere.geom"
	);

	//编译并附加shader程序到program上，渲染平面的深度到纹理上
	Shader RenderDepthShader(
		"./res/Tesselation/Shader/simpletess/simple.vert",
		"./res/Tesselation/Shader/RenderDepthTexture/RenderDepthTexture.frag",
		"./res/Tesselation/Shader/simpletess/simple.cont",
		"./res/Tesselation/Shader/RenderDepthTexture/RenderDepthTexture.eval",
		"./res/Tesselation/Shader/RenderDepthTexture/RenderDepthTexture.geom"
	);

	//编译并附加shader程序到program上，渲染刀具的深度到纹理上
	Shader RenderCutterDepthShader(
		"./res/Tesselation/Shader/simpletess/simple.vert",
		"./res/Tesselation/Shader/RenderDepthTexture/RenderDepthTexture.frag",
		"./res/Tesselation/Shader/simpletess/simple.cont",
		"./res/Tesselation/Shader/RenderDepthTexture/RenderDepthTextureforCutter.eval",
		"./res/Tesselation/Shader/RenderDepthTexture/RenderDepthTexture.geom"
	);
	//编译并附加shader程序到program上,使用深度纹理
	Shader PlaneUseDepthShader(
		"./res/Tesselation/Shader/simpletess/simple.vert",
		"./res/Tesselation/Shader/simpletess/simple.frag",
		"./res/Tesselation/Shader/simpletess/simple.cont",
		"./res/Tesselation/Shader/PlaneUseDepth/PlaneUseDepth.eval",
		"./res/Tesselation/Shader/simpletess/simple.geom"
	);

	Shader StoragePreDepthShader(
		"./res/Tesselation/Shader/StoragePreDepth/StoragePreDepth.vert",
		"./res/Tesselation/Shader/StoragePreDepth/StoragePreDepth.frag"
	);

	Shader InitPreDepthShader(
		"./res/Tesselation/Shader/StoragePreDepth/StoragePreDepth.vert",
		"./res/Tesselation/Shader/StoragePreDepth/InitPreDepthTexture.frag"
	);

	Shader RenderLastTextureShader(
		"./res/Tesselation/Shader/RenderLastTexture/RenderLastTexture.vert",
		"./res/Tesselation/Shader/RenderLastTexture/RenderLastTexture.frag"
	);

	Shader RenderBottomSurfaceShader(
		"./res/Tesselation/Shader/BottomSurface/BottomSurface.vert",
		"./res/Tesselation/Shader/BottomSurface/BottomSurface.frag",
		"./res/Tesselation/Shader/BottomSurface/BottomSurface.cont",
		"./res/Tesselation/Shader/BottomSurface/BottomSurface.eval",
		"./res/Tesselation/Shader/BottomSurface/BottomSurface.geom"
	);
	cout<<"Shader Over" << endl;
	const int  NumVertices = 4;  // vertices in our patch
	float MeshWidth = 1.0f;
	float MeshHeigth = 1.0f;
	glm::vec2 MinXY = glm::vec2(-0.5f, -0.5f);
	glm::vec3 PlaneNormal = glm::vec3(0.0f, 0.0f, 1.0f);


	//GLfloat vertices[NumVertices *  6] = {
	//         -0.5, -0.5 ,0.0f, 0.0f, 0.0f, 0.0f,
	//          0.5, -0.5 ,0.0f, 0.0f, 0.0f, 0.0f,
	//          0.5,  0.5 ,0.0f, 0.0f, 0.0f, 0.0f,
	//         -0.5,  0.5 ,0.0f, 0.0f, 0.0f, 0.0f
	//};

	//两个三角面片构成四边形
	float quadVertices[] = { // vertex attributes for a quad that fills the entire screen in Normalized Device Coordinates.
		// positions   // texCoords
		-1.0f,  1.0f,  0.0f, 1.0f,
		-1.0f, -1.0f,  0.0f, 0.0f,
		 1.0f, -1.0f,  1.0f, 0.0f,

		-1.0f,  1.0f,  0.0f, 1.0f,
		 1.0f, -1.0f,  1.0f, 0.0f,
		 1.0f,  1.0f,  1.0f, 1.0f
	};

	GLfloat TessVer[NumVertices * 4 * 3] = {
	 0.0, 0.0, 0.0  ,
	 1.0, 0.0, 0.0  ,
	 1.0, 1.0, 0.0  ,
	 0.0, 1.0, 0.0  ,


	 1.0, 0.0, 0.0  ,
	 1.0, 1.0, 0.0  ,
	 2.0, 1.0, 0.0  ,
	 2.0, 0.0, 0.0  ,

	 1.0, 1.0, 0.0  ,
	 1.0, 2.0, 0.0  ,
	 2.0, 2.0, 0.0  ,
	 2.0, 1.0, 0.0  ,

	 0.0,  1.0, 0.0  ,
	 1.0,  1.0, 0.0  ,
	 1.0,  2.0, 0.0  ,
	 0.0,  2.0, 0.0
	};
	GLfloat TV[9][3] = {
	  {-1.0, -1.0, 0.0 } ,
	  { 1.0, -1.0, 0.0 } ,
	  { 1.0,  1.0, 0.0 } ,
	  {-1.0,  1.0, 0.0 } ,

	  { 0.0, -1.0, 0.0 } ,
	  { 1.0,  0.0, 0.0 } ,
	  { 0.0,  1.0, 0.0 } ,
	  {-1.0,  0.0, 0.0 } ,

	  { 0.0,  0.0, 0.0 } ,
	};
	GLint TE[4][4] = {
		{0,4,8,7},
		{4,1,5,8},
		{8,5,2,6},
		{7,8,6,3}
	};


	GLfloat* BigPlane = nullptr;

	BigPlane = SetMorePlane(BigPlane, TessVer, Width, Length);
	glm::vec3* CuuterPathArray = CutterPath(Width * 2, Length * 2, CutterPos.z, PathPrecision);//使用的单元正方形面片边长为2，因此乘以2
	CutterPos = CuuterPathArray[0];
	GLuint program = TesselationShader.ID;
	GLuint CutterProgram = CutterShader.ID;

	//创建帧缓冲，使用渲染对象附件，创建的纹理大小也为视口大小
	unsigned int gPosition, PrePosition, LastPosition;
	unsigned int PlaneFrameBuffer, StoragePreDepthFrameBuffer, LastDpethFrameBuffer;

	PlaneFrameBuffer = SetFramBuffer(SCR_WIDTH, SCR_HEIGHT, gPosition);//渲染指定对象得到当前深度值
	StoragePreDepthFrameBuffer = SetFramBuffer(SCR_WIDTH, SCR_HEIGHT, PrePosition);//存储
	LastDpethFrameBuffer = SetFramBuffer(SCR_WIDTH, SCR_HEIGHT, LastPosition);//存储

	//GLfloat vertices[4] = {};
	//设置正交相机的位置


	//设置patch的Buffer和顶点对象以及顶点设置。
	glBindVertexArray(VAO[3]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[3]);
	glBufferData(GL_ARRAY_BUFFER, Width * Length * sizeof(TessVer), BigPlane, GL_STATIC_DRAW);//设置buffer
	//glUseProgram(program);
	//GLuint vPosition = glGetAttribLocation(program, "vPosition");//获取vPosition的位置
	//GLuint vNormal = glGetAttribLocation(program, "vNormal");//获取vNormal的位置
	//设置patch的顶点属性
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), BUFFER_OFFSET(0));//设置顶点属性
	//glEnableVertexAttribArray(vNormal);
	//glVertexAttribPointer(vNormal, 3, GL_FLOAT, GL_FALSE,  6 * sizeof(float), BUFFER_OFFSET(3 * sizeof(float)));
	glPatchParameteri(GL_PATCH_VERTICES, 4);//疑惑：是在每次调用glDrawArrays(GL_PATCHES,0,8)前都需要设置一次，还是说只需要设置一次	
	glBindBuffer(GL_ARRAY_BUFFER, 0);//解绑先
	glBindVertexArray(0);

	glBindVertexArray(VAO[2]);
	// 2. 把我们的顶点数组复制到一个顶点缓冲中，供OpenGL使用
	glBindBuffer(GL_ARRAY_BUFFER, VBO[2]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(TV), TV, GL_STATIC_DRAW);
	// 3. 复制我们的索引数组到一个索引缓冲中，供OpenGL使用
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[2]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(TE), TE, GL_STATIC_DRAW);
	// 4. 设定顶点属性指针
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));//设置顶点属性
	glPatchParameteri(GL_PATCH_VERTICES, 4);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);


	//半球渲染，半球顶点属性设置
	glBindVertexArray(VAO[1]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(TessVer), TessVer, GL_STATIC_DRAW);//设置buffer
	//设置patch的顶点属性
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), BUFFER_OFFSET(0));//设置顶点属性
	glPatchParameteri(GL_PATCH_VERTICES, 4);//只需要设置一次	
	glBindBuffer(GL_ARRAY_BUFFER, 0);//解绑先
	glBindVertexArray(0);

	//存储上次深度值渲染所需要的顶点对象// screen quad VAO
	unsigned int quadVAO, quadVBO;
	glGenVertexArrays(1, &quadVAO);
	glGenBuffers(1, &quadVBO);
	glBindVertexArray(quadVAO);
	glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);


	unsigned int NoiseMap = loadTexture("./res/Tesselation/Shader/snow/Noise.png");
	cout << "NoiseMapID:" << NoiseMap << endl;


	//glGetUniformLocation(program, "Noise");
	//glUniform1i(glGetUniformLocation(program, "Noise"),1,GL_FALSE,0);

	//设置主相机的位置,
	camera.Position = glm::vec3(Width, Length, (Width + Length) * 1.2);
	//camera.Front.z *= -1.0f;

	//设置正交相机的位置，乘以-1是为了将相机放在当前平面下方，
	//要注意正交相机的位置要在当前平面的对面平面的下方,不然刀具会与相机碰撞
	//同时要注意由于6个面的位置不同，因此放置相机的位置也要重新考虑；
	Mycamera PlaneCamera = Mycamera(glm::vec3(Width, Length, -1.0 * (Width + Length) * 2));
	PlaneCamera.Front.z *= -1.0f;//将相机从指向Z轴方向转变为指向Z轴正方向，这样就可以从平面底部看到平面；


	//初始化存储过往深度值的纹理
	glBindFramebuffer(GL_FRAMEBUFFER, StoragePreDepthFrameBuffer);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	InitPreDepthShader.use();
	glBindVertexArray(quadVAO);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, NoiseMap);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);//绑定回默认的帧缓冲


	int PathIndex = 0;
	while (!glfwWindowShouldClose(window)) {

		//if (PathPrecision > 0) {
		//	PathPrecision = PathPrecision - 1;
		//    CutterPos = CuuterPathArray[PathPrecision];
		//
		//}
		CutterPos = GetFileCutterPosOfPlane(PathIndex);
		PathIndex++;

		//四行代码搭配使用处理输入
		float currentFrame = static_cast<float>(glfwGetTime());
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		processInput(window);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
		glm::mat4 view = camera.GetViewMatrix();
		glm::mat4 model = glm::mat4(1.0f);



		//构建平面使用的正交相机，视口比例为4 ：3，因此使用的正交矩阵的比例也应该为4 ：3	1.6与1.2最好
		//补充使用视口的比例主要是为了在视口中显示时不会变形，想要将平面所在区域完全覆盖还是要使用和平面等比例的长宽的正交矩阵
		//glm::mat4 Orth0projection = glm::ortho(-1.6f * Width, 1.6f * Width, -1.2f * Length, 1.2f * Length, 0.1f, 100.0f);
		glm::mat4 OrthoView = PlaneCamera.GetViewMatrix();
		glm::mat4 Orthoprojection = glm::ortho(-1.0f * Width, 1.0f * Width, -1.0f * Length, 1.0f * Length, 0.1f, 100.0f);
		//projection = Orth0projection;
		glm::mat4 MainOrthoprojection = glm::ortho(-1.6f * Width, 1.6f * Width, -1.2f * Length, 1.2f * Length, 0.1f, 100.0f);
		glBindFramebuffer(GL_FRAMEBUFFER, PlaneFrameBuffer);
		// make sure we clear the framebuffer's content
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//绘制平面并将坐标写入颜色缓冲纹理附件
		RenderDepthShader.use();
		RenderDepthShader.setVec2("PlaneSize", glm::vec2(Width, Length));
		RenderDepthShader.setVec2("MinXY", MinXY);
		RenderDepthShader.setVec3("PlaneNormal", PlaneNormal);
		RenderDepthShader.setVec2("CubeTopAndBottom", CubeTopAndBottom);

		//TesselationShader.setInt("Noise", 0);
		glUniformMatrix4fv(glGetUniformLocation(RenderDepthShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(glGetUniformLocation(RenderDepthShader.ID, "view"), 1, GL_FALSE, glm::value_ptr(OrthoView));
		glUniformMatrix4fv(glGetUniformLocation(RenderDepthShader.ID, "projection"), 1, GL_FALSE, glm::value_ptr(Orthoprojection));
		glBindVertexArray(VAO[3]);
		//激活纹理并绑定，可以不使用用uniform
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, NoiseMap);
		//glActiveTexture(GL_TEXTURE1);
		//glBindTexture(GL_TEXTURE_2D, PrePosition);//PrePosition
		glDrawArrays(GL_PATCHES, 0, NumVertices * 4 * Width * Length);
		glBindVertexArray(0);


		//在帧缓冲中绘制刀具并将坐标写入颜色缓冲附件
		RenderCutterDepthShader.use();
		glUniformMatrix4fv(glGetUniformLocation(RenderCutterDepthShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(glGetUniformLocation(RenderCutterDepthShader.ID, "view"), 1, GL_FALSE, glm::value_ptr(OrthoView));
		glUniformMatrix4fv(glGetUniformLocation(RenderCutterDepthShader.ID, "projection"), 1, GL_FALSE, glm::value_ptr(Orthoprojection));
		RenderCutterDepthShader.setVec3("CutterPos", CutterPos);
		RenderCutterDepthShader.setFloat("R", CutterR);
		glBindVertexArray(VAO[1]);
		//glActiveTexture(GL_TEXTURE0);
		//glBindTexture(GL_TEXTURE_2D, PrePosition);
		glDrawArrays(GL_PATCHES, 0, NumVertices * 4);
		glBindVertexArray(0);



		//融合当前深度与上一次渲染得到的深度
		glBindFramebuffer(GL_FRAMEBUFFER, LastDpethFrameBuffer);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		RenderLastTextureShader.use();
		PlaneNormal = glm::vec3(0.0f, 0.0f, 1.0f);
		RenderLastTextureShader.setVec3("PlaneNormal", PlaneNormal);
		glBindVertexArray(quadVAO);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, gPosition);
		RenderLastTextureShader.setInt("CurrDepthTexture", 0);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, PrePosition);
		RenderLastTextureShader.setInt("PreDepthTexture", 1);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		glBindVertexArray(0);

		//存储当前深度值作为下次渲染的基础
		glBindFramebuffer(GL_FRAMEBUFFER, StoragePreDepthFrameBuffer);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		StoragePreDepthShader.use();
		glBindVertexArray(quadVAO);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, LastPosition);
		StoragePreDepthShader.setInt("DepthTexture", 0);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		glBindVertexArray(0);


		glm::vec3 LigthPos = glm::vec3(Width, Length, 4.0f);

		glBindFramebuffer(GL_FRAMEBUFFER, 0);//绑定回默认的帧缓冲
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		PlaneUseDepthShader.use();
		PlaneNormal = glm::vec3(0.0, 0.0, -1.0f);
		PlaneUseDepthShader.setVec2("PlaneSize", glm::vec2(Width, Length));
		PlaneUseDepthShader.setVec2("MinXY", MinXY);
		PlaneUseDepthShader.setVec3("PlaneNormal", PlaneNormal);
		PlaneUseDepthShader.setVec2("CubeTopAndBottom", CubeTopAndBottom);


		//根据最终深度纹理渲染平面
		//TesselationShader.setInt("Noise", 0);
		glUniformMatrix4fv(glGetUniformLocation(PlaneUseDepthShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(glGetUniformLocation(PlaneUseDepthShader.ID, "view"), 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(glGetUniformLocation(PlaneUseDepthShader.ID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
		glUniform3fv(glGetUniformLocation(PlaneUseDepthShader.ID, "lightPos"), 1, glm::value_ptr(LigthPos));
		glUniform3fv(glGetUniformLocation(PlaneUseDepthShader.ID, "lightColor"), 1, glm::value_ptr(glm::vec3(1.0f, 1.0f, 1.0f)));
		glUniform3fv(glGetUniformLocation(PlaneUseDepthShader.ID, "viewPos"), 1, glm::value_ptr(camera.Position));
		glUniform3fv(glGetUniformLocation(PlaneUseDepthShader.ID, "objectColor"), 1, glm::value_ptr(glm::vec3(0.5f, 0.737f, 0.813f)));
		glBindVertexArray(VAO[3]);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, LastPosition);//PrePosition,gPostion,LastPosition	
		glDrawArrays(GL_PATCHES, 0, NumVertices * 4 * Width * Length);
		glBindVertexArray(0);

		//渲染刀具
		glUseProgram(CutterProgram);
		glUniformMatrix4fv(glGetUniformLocation(CutterProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(glGetUniformLocation(CutterProgram, "view"), 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(glGetUniformLocation(CutterProgram, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
		glUniform3fv(glGetUniformLocation(CutterProgram, "lightPos"), 1, glm::value_ptr(LigthPos));
		glUniform3fv(glGetUniformLocation(CutterProgram, "lightColor"), 1, glm::value_ptr(glm::vec3(1.0f, 1.0f, 1.0f)));
		glUniform3fv(glGetUniformLocation(CutterProgram, "viewPos"), 1, glm::value_ptr(camera.Position));
		glUniform3fv(glGetUniformLocation(CutterProgram, "objectColor"), 1, glm::value_ptr(glm::vec3(0.5f, 0.737f, 0.813f)));
		CutterShader.setVec3("CutterPos", CutterPos);
		CutterShader.setFloat("R", CutterR);

		glBindVertexArray(VAO[1]);
		glDrawArrays(GL_PATCHES, 0, NumVertices * 4);
		glBindVertexArray(0);


		//渲染底部平面
		RenderBottomSurfaceShader.use();

		RenderBottomSurfaceShader.setVec2("PlaneSize", glm::vec2(Width, Length));
		RenderBottomSurfaceShader.setVec2("MinXY", MinXY);
		RenderBottomSurfaceShader.setVec3("PlaneNormal", PlaneNormal);
		RenderBottomSurfaceShader.setVec2("CubeTopAndBottom", CubeTopAndBottom);

		//TesselationShader.setInt("Noise", 0);
		glUniformMatrix4fv(glGetUniformLocation(RenderBottomSurfaceShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(glGetUniformLocation(RenderBottomSurfaceShader.ID, "view"), 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(glGetUniformLocation(RenderBottomSurfaceShader.ID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
		glUniform3fv(glGetUniformLocation(RenderBottomSurfaceShader.ID, "lightPos"), 1, glm::value_ptr(LigthPos));
		glUniform3fv(glGetUniformLocation(RenderBottomSurfaceShader.ID, "lightColor"), 1, glm::value_ptr(glm::vec3(1.0f, 1.0f, 1.0f)));
		glUniform3fv(glGetUniformLocation(RenderBottomSurfaceShader.ID, "viewPos"), 1, glm::value_ptr(camera.Position));
		glUniform3fv(glGetUniformLocation(RenderBottomSurfaceShader.ID, "objectColor"), 1, glm::value_ptr(glm::vec3(0.5f, 0.737f, 0.813f)));
		glBindVertexArray(VAO[3]);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, LastPosition);//PrePosition,gPostion,LastPosition	
		glDrawArrays(GL_PATCHES, 0, NumVertices * 4 * Width * Length);
		glBindVertexArray(0);



		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	///////////////////

	glfwTerminate();
}
//glBindVertexArray(VAO[2]);
//glActiveTexture(GL_TEXTURE0);
//glBindTexture(GL_TEXTURE_2D, NoiseMap);
//glDrawElements(GL_PATCHES, NumVertices * 4, GL_UNSIGNED_INT, 0);
//glBindVertexArray(0);
