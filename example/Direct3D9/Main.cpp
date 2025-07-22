#include "Main.h"
#include "d3d9.h"
#include "../../MD_Math.h"
using namespace MD_Math;

bool run = true;
extern HWND WindowHanled;

IDirect3D9* d3d9;
IDirect3DDevice9* device;

IDirect3DVertexBuffer9* VB;
IDirect3DIndexBuffer9*  IB;

struct Vertex
{
	Vertex(){}
	Vertex(float x, float y, float z, D3DCOLOR color)
	{
		_x = x;  _y = y;  _z = z;
		_color = color;
	}
	float _x, _y, _z;
	D3DCOLOR _color;
	static const DWORD FVF;
};
const DWORD Vertex::FVF = D3DFVF_XYZ | D3DFVF_DIFFUSE;

void InitWindow(const char* title, HINSTANCE instanceHanled, int show);
float TimeDelta();

D3DMATRIX MD_MATH_MATRIXToD3DMATRIX(MATRIX m);

int WINAPI WinMain(HINSTANCE hInstance,
                    HINSTANCE hPrevInstance,
                    PSTR pCmdLine,
                    int nShowCmd)
{
    InitWindow("",hInstance,nShowCmd);

	d3d9 = Direct3DCreate9(D3D_SDK_VERSION);

	D3DPRESENT_PARAMETERS d3dpp;
	d3dpp.BackBufferWidth            = WINDOW_WIDTH;
	d3dpp.BackBufferHeight           = WINDOW_HEIGHT;
	d3dpp.BackBufferFormat           = D3DFMT_A8R8G8B8;
	d3dpp.BackBufferCount            = 1;
	d3dpp.MultiSampleType            = D3DMULTISAMPLE_NONE;
	d3dpp.MultiSampleQuality         = 0;
	d3dpp.SwapEffect                 = D3DSWAPEFFECT_DISCARD; 
	d3dpp.hDeviceWindow              = WindowHanled;
	d3dpp.Windowed                   = true;
	d3dpp.EnableAutoDepthStencil     = true; 
	d3dpp.AutoDepthStencilFormat     = D3DFMT_D24S8;
	d3dpp.Flags                      = 0;
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	d3dpp.PresentationInterval       = D3DPRESENT_INTERVAL_IMMEDIATE;

	d3d9->CreateDevice(
		D3DADAPTER_DEFAULT, 
		D3DDEVTYPE_HAL,       
		WindowHanled,               
		D3DCREATE_HARDWARE_VERTEXPROCESSING,                 
	    &d3dpp,             
	    &device);
	
	device->CreateVertexBuffer(
		8 * sizeof(Vertex), 
		D3DUSAGE_WRITEONLY,
		Vertex::FVF,
		D3DPOOL_MANAGED,
		&VB,
		0);

	device->CreateIndexBuffer(
		36 * sizeof(WORD),
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&IB,
		0);

	Vertex* vertices;
	VB->Lock(0, 0, (void**)&vertices, 0);

	vertices[0] = Vertex(-1.0f, -1.0f, -1.0f, D3DCOLOR_XRGB(0, 255, 0));
	vertices[1] = Vertex(-1.0f,  1.0f, -1.0f, D3DCOLOR_XRGB(0, 255, 0));
	vertices[2] = Vertex( 1.0f,  1.0f, -1.0f, D3DCOLOR_XRGB(0, 255, 0));
	vertices[3] = Vertex( 1.0f, -1.0f, -1.0f, D3DCOLOR_XRGB(0, 255, 0));
	vertices[4] = Vertex(-1.0f, -1.0f,  1.0f, D3DCOLOR_XRGB(0, 255, 0));
	vertices[5] = Vertex(-1.0f,  1.0f,  1.0f, D3DCOLOR_XRGB(0, 255, 0));
	vertices[6] = Vertex( 1.0f,  1.0f,  1.0f, D3DCOLOR_XRGB(0, 255, 0));
	vertices[7] = Vertex( 1.0f, -1.0f,  1.0f, D3DCOLOR_XRGB(0, 255, 0));

	VB->Unlock();

	WORD* indices = 0;
	IB->Lock(0, 0, (void**)&indices, 0);

	indices[0]  = 0; indices[1]  = 1; indices[2]  = 2;
	indices[3]  = 0; indices[4]  = 2; indices[5]  = 3;

	indices[6]  = 4; indices[7]  = 6; indices[8]  = 5;
	indices[9]  = 4; indices[10] = 7; indices[11] = 6;

	indices[12] = 4; indices[13] = 5; indices[14] = 1;
	indices[15] = 4; indices[16] = 1; indices[17] = 0;

	indices[18] = 3; indices[19] = 2; indices[20] = 6;
	indices[21] = 3; indices[22] = 6; indices[23] = 7;

	indices[24] = 1; indices[25] = 5; indices[26] = 6;
	indices[27] = 1; indices[28] = 6; indices[29] = 2;

	indices[30] = 4; indices[31] = 0; indices[32] = 3;
	indices[33] = 4; indices[34] = 3; indices[35] = 7;

	IB->Unlock();
    VECTOR3 position(0.0f, 0.0f, -5.0f);
	VECTOR3 target(0.0f, 0.0f, 0.0f);
	VECTOR3 up(0.0f, 1.0f, 0.0f);
	MATRIX V = ViewMatrixLH(position, target, up);

    D3DMATRIX View = MD_MATH_MATRIXToD3DMATRIX(V);
	device->SetTransform(D3DTS_VIEW, &View);

	MATRIX projection = PerspectiveMatrixLH(
		AngularToRadian(45.0f),
		(float) WINDOW_WIDTH / (float) WINDOW_HEIGHT,
		0.1f,
		100.0f
		);
	D3DMATRIX Proj = MD_MATH_MATRIXToD3DMATRIX(projection);
	device->SetTransform(D3DTS_PROJECTION,&Proj);

	device->SetRenderState(D3DRS_LIGHTING, false);

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
            MATRIX Rx, Ry;
			Rx = RotationMatrix(3.14f / 4.0f, 'X');

			static float y = 0.0f;
		    Ry = RotationMatrix(y, 'Y');
		    y += TimeDelta();

		    if( y >= 6.28f )
			    y = 0.0f;

			D3DMATRIX p = MD_MATH_MATRIXToD3DMATRIX(Rx * Ry);

		    device->SetTransform(D3DTS_WORLD, &p);

            device->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(255,0,0), 1.0f, 0);
			device->BeginScene();

		    device->SetStreamSource(0, VB, 0, sizeof(Vertex));
		    device->SetIndices(IB);
		    device->SetFVF(Vertex::FVF);

		    device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 8, 0, 12);
 
		    device->EndScene();
		    device->Present(0, 0, 0, 0);
        }

    }
    
    VB->Release();
	IB->Release();

	device->Release();
	d3d9->Release();
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

D3DMATRIX MD_MATH_MATRIXToD3DMATRIX(MATRIX m)
{
	D3DMATRIX temp;
    temp._11 = m._11;
	temp._21 = m._12;
	temp._31 = m._13;
	temp._41 = m._14;

	temp._12 = m._21;
	temp._22 = m._22;
	temp._32 = m._23;
	temp._42 = m._24;

	temp._13 = m._31;
	temp._23 = m._32;
	temp._33 = m._33;
	temp._43 = m._34;

	temp._14 = m._41;
	temp._24 = m._42;
	temp._34 = m._43;
	temp._44 = m._44;

	return temp;
}

float TimeDelta()
{
	static float lastTime = (float)timeGetTime(); 
	float currTime  = (float)timeGetTime();
	float timeDelta = (currTime - lastTime)*0.001f;
	lastTime = currTime;
	return timeDelta;
}
