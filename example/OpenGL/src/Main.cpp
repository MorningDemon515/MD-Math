#ifndef UNICODE
#define UNICODE
#endif 

#include "Main.h"

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#include <time.h>

bool run = true;
extern HWND WindowHanled;

const char* ReadFile(const char* wfile);

void InitWindow(const char* title, HINSTANCE instanceHanled, int show);

void Init_OpenGL();
void Draw_OpenGL();
void Clean_OpenGL();

//void Init_D3D9();
//void Draw_D3D9();
//void Clean_D3D9();

int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	PSTR pCmdLine,
	int nShowCmd)
{
	InitWindow("MathTest",hInstance,nShowCmd);
	
	Init_OpenGL();

	MSG msg;
	
	while(run)
	{
		if(PeekMessage(&msg,0,0,0,PM_REMOVE))
		{
			if(msg.message == WM_QUIT)
				run = false;
			
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			
			Draw_OpenGL();

		}
		
	}
	
	Clean_OpenGL();
	return msg.wParam;
}

void ErrorMessage_1(const char* message)
{
	MessageBoxA(NULL,message,"Engine Error!",MB_OK);
}

void ErrorMessage_2(HWND hwnd,const char* message)
{
	MessageBoxA(hwnd,message,"Engine Error!",MB_OK);
}

const char* ReadFile(const char* wfile)
{
	FILE *fp = NULL;
	static char buff[255];
	fp = fopen(wfile, "r");
	
	fgets(buff, 255, (FILE*)fp);
	return buff;
	fclose(fp);
}

float TimeDelta()
{
	static float lastTime = (float)timeGetTime(); 
	float currTime  = (float)timeGetTime();
	float timeDelta = (currTime - lastTime)*0.001f;
	lastTime = currTime;
	return timeDelta;
}
