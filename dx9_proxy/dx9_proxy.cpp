
#include "stdafx.h"

static const char targetDll[] = "C:/Windows/System32/d3d9.dll";


ProxyManager manager;
HINSTANCE hLib = NULL;

typedef void (WINAPI *protoDirect3DShaderValidatorCreate9_t)(void);

typedef int(WINAPI *protoD3DPERF_BeginEvent_t)(D3DCOLOR, LPCWSTR);
typedef int(WINAPI *protoD3DPERF_EndEvent_t)(void);
typedef void(WINAPI *protoD3DPERF_SetMarker_t)(D3DCOLOR, LPCWSTR);
typedef void(WINAPI *protoD3DPERF_SetRegion_t)(D3DCOLOR, LPCWSTR);
typedef BOOL(WINAPI *protoD3DPERF_QueryRepeatFrame_t)(void);
typedef void(WINAPI *protoD3DPERF_SetOptions_t)(DWORD);
typedef DWORD(WINAPI *protoD3DPERF_GetStatus_t)(void);

typedef IDirect3D9* (WINAPI *protoDirect3DCreate9_t)(UINT);
typedef HRESULT (WINAPI *protoDirect3DCreate9Ex_t)(UINT, IDirect3D9Ex**);


protoDirect3DShaderValidatorCreate9_t pDirect3DShaderValidatorCreate9 = NULL;

protoD3DPERF_BeginEvent_t pD3DPERF_BeginEvent = NULL;
protoD3DPERF_EndEvent_t pD3DPERF_EndEvent = NULL;
protoD3DPERF_SetMarker_t pD3DPERF_SetMarker = NULL;
protoD3DPERF_SetRegion_t pD3DPERF_SetRegion = NULL;
protoD3DPERF_QueryRepeatFrame_t pD3DPERF_QueryRepeatFrame = NULL;
protoD3DPERF_SetOptions_t pD3DPERF_SetOptions = NULL;
protoD3DPERF_GetStatus_t pD3DPERF_GetStatus = NULL;

protoDirect3DCreate9_t ptDirect3DCreate9 = NULL;
protoDirect3DCreate9Ex_t ptDirect3DCreate9Ex = NULL;

void WINAPI Direct3DShaderValidatorCreate9(void);

int WINAPI D3DPERF_BeginEvent(D3DCOLOR col, LPCWSTR wszName);
int WINAPI D3DPERF_EndEvent(void);
void WINAPI D3DPERF_SetMarker(D3DCOLOR col, LPCWSTR wszName);
void WINAPI D3DPERF_SetRegion(D3DCOLOR col, LPCWSTR wszName);
BOOL WINAPI D3DPERF_QueryRepeatFrame(void);
void WINAPI D3DPERF_SetOptions(DWORD dwOptions);
DWORD WINAPI D3DPERF_GetStatus(void);

IDirect3D9* WINAPI Direct3DCreate9(UINT SDKVersion);
HRESULT WINAPI Direct3DCreate9Ex(UINT SDKVersion, IDirect3D9Ex** direct3Dex);

void WINAPI Direct3DShaderValidatorCreate9(void)
{
	if (hLib == NULL)
		hLib = LoadLibraryA(targetDll);
	if (hLib == NULL)
		return;
	pDirect3DShaderValidatorCreate9 = (protoDirect3DShaderValidatorCreate9_t)GetProcAddress(hLib, "Direct3DShaderValidatorCreate9");
	if (pDirect3DShaderValidatorCreate9 != NULL)
		pDirect3DShaderValidatorCreate9();
}


int WINAPI D3DPERF_BeginEvent(D3DCOLOR col, LPCWSTR wszName)
{
	if (hLib == NULL)
		hLib = LoadLibraryA(targetDll);
	if (hLib == NULL)
		return 0;
	pD3DPERF_BeginEvent = (protoD3DPERF_BeginEvent_t)GetProcAddress(hLib, "D3DPERF_BeginEvent");
	if (pD3DPERF_BeginEvent != NULL)
		return pD3DPERF_BeginEvent(col, wszName);
	return 0;
}

int WINAPI D3DPERF_EndEvent(void)
{
	if (hLib == NULL)
		hLib = LoadLibraryA(targetDll);
	if (hLib == NULL)
		return 0;
	pD3DPERF_EndEvent = (protoD3DPERF_EndEvent_t)GetProcAddress(hLib, "D3DPERF_EndEvent");
	if (pD3DPERF_EndEvent != NULL)
		return pD3DPERF_EndEvent();
	return 0;
}

void WINAPI D3DPERF_SetMarker(D3DCOLOR col, LPCWSTR wszName)
{
	if (hLib == NULL)
		hLib = LoadLibraryA(targetDll);
	if (hLib == NULL)
		return;
	pD3DPERF_SetMarker = (protoD3DPERF_SetMarker_t)GetProcAddress(hLib, "D3DPERF_SetMarker");
	if (pD3DPERF_SetMarker != NULL)
		pD3DPERF_SetMarker(col, wszName);
}

void WINAPI D3DPERF_SetRegion(D3DCOLOR col, LPCWSTR wszName)
{
	if (hLib == NULL)
		hLib = LoadLibraryA(targetDll);
	if (hLib == NULL)
		return;
	pD3DPERF_SetRegion = (protoD3DPERF_SetRegion_t)GetProcAddress(hLib, "D3DPERF_SetRegion");
	if (pD3DPERF_SetRegion != NULL)
		pD3DPERF_SetRegion(col, wszName);

}

BOOL WINAPI D3DPERF_QueryRepeatFrame(void)
{
	if (hLib == NULL)
		hLib = LoadLibraryA(targetDll);
	if (hLib == NULL)
		return false;
	pD3DPERF_QueryRepeatFrame = (protoD3DPERF_QueryRepeatFrame_t)GetProcAddress(hLib, "D3DPERF_QueryRepeatFrame");
	if (pD3DPERF_QueryRepeatFrame != NULL)
		return pD3DPERF_QueryRepeatFrame();
	return true;
}

void WINAPI D3DPERF_SetOptions(DWORD dwOptions)
{
	if (hLib == NULL)
		hLib = LoadLibraryA(targetDll);
	if (hLib == NULL)
		return;
	pD3DPERF_SetOptions = (protoD3DPERF_SetOptions_t)GetProcAddress(hLib, "D3DPERF_SetOptions");
	if (pD3DPERF_SetOptions != NULL)
		pD3DPERF_SetOptions(dwOptions);
}

DWORD WINAPI D3DPERF_GetStatus(void)
{
	if (hLib == NULL)
		hLib = LoadLibraryA(targetDll);
	if (hLib == NULL)
		return (DWORD)0;
	pD3DPERF_GetStatus = (protoD3DPERF_GetStatus_t)GetProcAddress(hLib, "D3DPERF_GetStatus");
	if (pD3DPERF_GetStatus != NULL)
		return pD3DPERF_GetStatus();
	return 0;
}


IDirect3D9* WINAPI Direct3DCreate9(UINT SDKVersion)
{
	IDirect3D9* result = NULL;
	MI3d9* mresult = NULL;
	if (hLib == NULL)
		hLib = LoadLibraryA(targetDll);
	if (hLib == NULL)
		return NULL;

	ptDirect3DCreate9 = (protoDirect3DCreate9_t)GetProcAddress(hLib, "Direct3DCreate9");

	if (ptDirect3DCreate9 != NULL)
	{
		result = ptDirect3DCreate9(SDKVersion);

		//MessageBoxA(NULL, "Succeded to call Direct3DCreate9", "Success", MB_OK);
		return result;
		manager.createManagerFromOriginal(result);
		//MessageBoxA(NULL, "Direct3DCreate9 called", "Success", MB_OK);

	}
	else
	{
		MessageBoxA(NULL, "failed to call Direct3DCreate9", "Fail", MB_OK);
	}

	return manager.getManager();
}


HRESULT WINAPI Direct3DCreate9Ex(UINT SDKVersion, IDirect3D9Ex** direct3Dex)
{
	if (hLib == NULL)
		hLib = LoadLibraryA(targetDll);
	if (hLib == NULL)
		return NULL;
	ptDirect3DCreate9Ex = (protoDirect3DCreate9Ex_t)GetProcAddress(hLib, "Direct3DCreate9Ex");
	if (ptDirect3DCreate9Ex != NULL)
		return ptDirect3DCreate9Ex(SDKVersion, direct3Dex);

	return 0;
}

