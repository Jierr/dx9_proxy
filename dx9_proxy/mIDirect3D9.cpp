#include "stdafx.h"

/*** IUnknown methods ***/
/*
S&R
setup calls to original (MI3d9::([^\(]*)(\([^\)]*\))\r?\n{\r?\n[^\n]*) ->					$1\r\n\tresult = original->$2$3;
clean calls				(original->[^\( ;\n]*)\((([^ ,]*, )*)([^ ,]* \*?)?([^\)]*\)); ->	$1($2$5;
clean (THIS)			(original->[^\(]*)\(THIS\) ->										$1()
add return				^(([^ ;\(\){}\r\n]*) __stdcall[^\}]*)								$1\treturn result;\r\n
*/
HRESULT __stdcall MI3d9::QueryInterface(THIS_ REFIID riid, void** ppvObj)
{
	HRESULT result;


	result = original->QueryInterface(riid, ppvObj);
	
	extern ProxyManager manager;
	if (result == S_OK)
	{
		*ppvObj = this;
	}
	
	return result;
}

ULONG __stdcall MI3d9::AddRef(THIS)
{
	ULONG result;

	result = original->AddRef();

	return result;
}

ULONG __stdcall MI3d9::Release(THIS)
{
	ULONG result;

	result = original->Release();

	
	extern ProxyManager manager;
	if (result == 0)
	{
		manager.setManager(NULL);
		delete(this);
	}
	

	return result;
}


/*** IDirect3D9 methods ***/
HRESULT __stdcall MI3d9::RegisterSoftwareDevice(THIS_ void* pInitializeFunction)
{
	HRESULT result;

	result = original->RegisterSoftwareDevice(pInitializeFunction);

	return result;
}

UINT __stdcall MI3d9::GetAdapterCount(THIS)
{
	UINT result;

	result = original->GetAdapterCount();

	return result;
}

HRESULT __stdcall MI3d9::GetAdapterIdentifier(THIS_ UINT Adapter, DWORD Flags, D3DADAPTER_IDENTIFIER9* pIdentifier)
{
	HRESULT result;

	result = original->GetAdapterIdentifier(Adapter, Flags, pIdentifier);

	return result;
}

UINT __stdcall MI3d9::GetAdapterModeCount(THIS_ UINT Adapter, D3DFORMAT Format)
{
	UINT result;

	result = original->GetAdapterModeCount(Adapter, Format);

	return result;
}

HRESULT __stdcall MI3d9::EnumAdapterModes(THIS_ UINT Adapter, D3DFORMAT Format, UINT Mode, D3DDISPLAYMODE* pMode)
{
	HRESULT result;

	result = original->EnumAdapterModes(Adapter, Format, Mode, pMode);

	return result;
}

HRESULT __stdcall MI3d9::GetAdapterDisplayMode(THIS_ UINT Adapter, D3DDISPLAYMODE* pMode)
{
	HRESULT result;

	result = original->GetAdapterDisplayMode(Adapter, pMode);

	return result;
}

HRESULT __stdcall MI3d9::CheckDeviceType(THIS_ UINT Adapter, D3DDEVTYPE DevType, D3DFORMAT AdapterFormat, D3DFORMAT BackBufferFormat, BOOL bWindowed)
{
	HRESULT result;

	result = original->CheckDeviceType(Adapter, DevType, AdapterFormat, BackBufferFormat, bWindowed);

	return result;
}

HRESULT __stdcall MI3d9::CheckDeviceFormat(THIS_ UINT Adapter, D3DDEVTYPE DeviceType, D3DFORMAT AdapterFormat, DWORD Usage, D3DRESOURCETYPE RType, D3DFORMAT CheckFormat)
{
	HRESULT result;

	result = original->CheckDeviceFormat(Adapter, DeviceType, AdapterFormat, Usage, RType, CheckFormat);

	return result;
}

HRESULT __stdcall MI3d9::CheckDeviceMultiSampleType(THIS_ UINT Adapter, D3DDEVTYPE DeviceType, D3DFORMAT SurfaceFormat, BOOL Windowed, D3DMULTISAMPLE_TYPE MultiSampleType, DWORD* pQualityLevels)
{
	HRESULT result;

	result = original->CheckDeviceMultiSampleType(Adapter, DeviceType, SurfaceFormat, Windowed, MultiSampleType, pQualityLevels);

	return result;
}

HRESULT __stdcall MI3d9::CheckDepthStencilMatch(THIS_ UINT Adapter, D3DDEVTYPE DeviceType, D3DFORMAT AdapterFormat, D3DFORMAT RenderTargetFormat, D3DFORMAT DepthStencilFormat)
{
	HRESULT result;

	result = original->CheckDepthStencilMatch(Adapter, DeviceType, AdapterFormat, RenderTargetFormat, DepthStencilFormat);

	return result;
}

HRESULT __stdcall MI3d9::CheckDeviceFormatConversion(THIS_ UINT Adapter, D3DDEVTYPE DeviceType, D3DFORMAT SourceFormat, D3DFORMAT TargetFormat)
{
	HRESULT result;

	result = original->CheckDeviceFormatConversion(Adapter, DeviceType, SourceFormat, TargetFormat);

	return result;
}

HRESULT __stdcall MI3d9::GetDeviceCaps(THIS_ UINT Adapter, D3DDEVTYPE DeviceType, D3DCAPS9* pCaps)
{
	HRESULT result;

	result = original->GetDeviceCaps(Adapter, DeviceType, pCaps);

	return result;
}

HMONITOR __stdcall MI3d9::GetAdapterMonitor(THIS_ UINT Adapter)
{
	HMONITOR result;

	result = original->GetAdapterMonitor(Adapter);

	return result;
}

HRESULT __stdcall MI3d9::CreateDevice(THIS_ UINT Adapter, D3DDEVTYPE DeviceType, HWND hFocusWindow, DWORD BehaviorFlags, D3DPRESENT_PARAMETERS* pPresentationParameters, IDirect3DDevice9** ppReturnedDeviceInterface)
{
	HRESULT result;
	char str[1024] = { 0, };

	//MessageBoxA(NULL, "Creating new Device!", "Success", MB_OK);
	result = original->CreateDevice(Adapter, DeviceType, hFocusWindow, BehaviorFlags, pPresentationParameters, ppReturnedDeviceInterface);
	
	extern ProxyManager manager;

	manager.createDeviceFromOriginal((IDirect3DDevice9*)*ppReturnedDeviceInterface, this);

	sprintf(str, "MI3dDevice:%p\r\norig=(%p==%p)\r\ncreator=(%p==%p)",
		(void*)manager.getDevice(), 
		(void*)manager.getDevice()->original, (void*)*ppReturnedDeviceInterface, 
		(void*)manager.getDevice()->creator, (void*)this);
	*ppReturnedDeviceInterface = (IDirect3DDevice9*)manager.getDevice();
	//MessageBoxA(NULL, str, "Success", MB_OK);
	
	return result;
}


MI3d9::MI3d9(IDirect3D9* orig)
{
	original = orig;
}


void MI3d9::setOriginal(IDirect3D9* orig)
{
	original = orig;
}

MI3d9::~MI3d9()
{

}

