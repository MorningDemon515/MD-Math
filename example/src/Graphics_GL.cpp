#ifndef UNICODE
#define UNICODE
#endif 

#include "Main.h"
#include "../glad4.6/include/glad/glad.h"

#include "../../MD_Math.h"

extern HWND WindowHanled; 
HDC hDC; 
HGLRC hRC;

void Init_Shader_GL(const char* vertex, const char* fragment);
void Link_Shader_GL();
void Clean_Shader_GL();

extern unsigned int vertexShader;
extern unsigned int fragmentShader;
extern unsigned int shaderProgram;

float vertices[] = {
	-0.5f, -0.5f, 0.0f, 
	0.5f, 0.5f, 0.0f, 
	-0.5f,  0.5f, 0.0f,
	
	-0.5f,-0.5f,0.0f,
	0.5f,-0.5f,0.0f,
	0.5f,0.5f,0.0f,
	
	-0.5f, -0.5f, -0.5f, 
	0.5f, 0.5f, -0.5f, 
	-0.5f,  0.5f, -0.5f,
	
	-0.5f,-0.5f,-0.5f,
	0.5f,-0.5f,-0.5f,
	0.5f,0.5f,-0.5f,
	
	-0.5f,0.5f,0.0f,
	0.5f, 0.5f,-0.5f,
	-0.5f, 0.5f,-0.5f,
	
	0.5f, 0.5f, 0.0f,
	0.5f, 0.5f, -0.5f,
	-0.5f, 0.5f, 0.0f,
	
	-0.5f,-0.5f,0.0f,
	0.5f, -0.5f,-0.5f,
	-0.5f, -0.5f,-0.5f,
	
	0.5f, -0.5f, 0.0f,
	0.5f, -0.5f, -0.5f,
	-0.5f, -0.5f, 0.0f,
	
	-0.5f,-0.5f,0.0f,
	-0.5f,0.5f,0.0f,
	-0.5f, 0.5f, -0.5f,
	
	-0.5f,-0.5f,0.0f,
	-0.5f, 0.5f, -0.5f,
	-0.5,-0.5f,-0.5f,
	
	0.5f,-0.5f,0.0f,
	0.5f,0.5f,0.0f,
	0.5f, 0.5f, -0.5f,
	
	0.5f,-0.5f,0.0f,
	0.5f, 0.5f, -0.5f,
	0.5,-0.5f,-0.5f,

};

 unsigned int VBO, VAO;

void Init_OpenGL()
{
	// get the device context (DC)
	hDC = GetDC(WindowHanled);
	
	PIXELFORMATDESCRIPTOR pfd = {
		sizeof(PIXELFORMATDESCRIPTOR),    // size of this pfd  
		1,                                // version number  
		PFD_DRAW_TO_WINDOW |              // support window  
		PFD_SUPPORT_OPENGL |              // support OpenGL  
		PFD_DOUBLEBUFFER,                 // double buffered  
		PFD_TYPE_RGBA,                    // RGBA type  
		24,                               // 24-bit color depth  
		0, 0, 0, 0, 0, 0,                 // color bits ignored  
		0,                                // no alpha buffer  
		0,                                // shift bit ignored  
		0,                                // no accumulation buffer  
		0, 0, 0, 0,                       // accum bits ignored  
		32,                               // 32-bit z-buffer      
		0,                                // no stencil buffer  
		0,                                // no auxiliary buffer  
		PFD_MAIN_PLANE,                   // main layer  
		0,                                // reserved  
		0, 0, 0                           // layer masks ignored  
	};
	int iPixelFormat = ChoosePixelFormat(hDC, &pfd);
	SetPixelFormat(hDC, iPixelFormat, &pfd);
	hRC = wglCreateContext(hDC);
	wglMakeCurrent(hDC, hRC);
	
	gladLoadGL();
	
	SetWindowTextA(WindowHanled,"MathTest - OpenGL 4.6");
	
	Init_Shader_GL("glsl/vertex.txt","glsl/fragment.txt");
	
	Link_Shader_GL();
	
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
}

void Draw_OpenGL(){
		
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	
	MD_MATH_MATRIX model = MD_Math_IdentityMatrix;
	MD_MATH_MATRIX view = MD_Math_IdentityMatrix;
	MD_MATH_MATRIX projection = (MD_Math_PerspectiveMatrixRH(MD_Math_AngularToRadian(45.0f),
		(float)WINDOW_WIDTH / (float)WINDOW_HEIGHT,
		0.1f,
		100.0f));

	model = MD_Math_TranslationMatrix(0.0f,0.0f,-3.0f);
	
	MD_MATH_VECTOR3 eye = {0.0f,0.0f,3.0f};
	MD_MATH_VECTOR3 target = {0.0f,0.0f,0.0f};
    MD_MATH_VECTOR3 up = {0.0f,1.0f,0.0f};
	view = MD_Math_ViewMatrixRH(eye, target, up);
	
	unsigned int modelLoc = glGetUniformLocation(shaderProgram, "model");
	unsigned int viewLoc  = glGetUniformLocation(shaderProgram, "view");
	unsigned int projLoc =  glGetUniformLocation(shaderProgram, "projection");
    
	float model_ptr[16];
	MD_Math_MatrixToValue(model,model_ptr);
	
	float projection_ptr[16];
	MD_Math_MatrixToValue(projection,projection_ptr);
	
	float view_ptr[16];
	MD_Math_MatrixToValue(view,view_ptr);
	
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, model_ptr);
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, view_ptr);
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, projection_ptr);

	glUseProgram(shaderProgram);
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	
	SwapBuffers(hDC);
	Sleep(1);
}

void Clean_OpenGL()
{
	Clean_Shader_GL();
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	
	wglMakeCurrent(NULL, NULL);
	wglDeleteContext(hRC);
	ReleaseDC(WindowHanled, hDC);
}
