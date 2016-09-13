#ifndef __MDIRECT__
#define __MDIRECT__

#include "stdafx.h"

class MI3d9 : public IDirect3D9
{
private:
	IDirect3D9* original;
public:

	friend class ProxyManager;

	MI3d9(IDirect3D9* orig);
	~MI3d9();
	void setOriginal(IDirect3D9* orig);


	/*** IUnknown methods ***/
	HRESULT __stdcall QueryInterface(THIS_ REFIID riid, void** ppvObj);
	ULONG __stdcall AddRef(THIS);
	ULONG __stdcall Release(THIS);

	/*** IDirect3D9 methods ***/
	HRESULT __stdcall RegisterSoftwareDevice(THIS_ void* pInitializeFunction);
	UINT __stdcall GetAdapterCount(THIS);
	HRESULT __stdcall GetAdapterIdentifier(THIS_ UINT Adapter, DWORD Flags, D3DADAPTER_IDENTIFIER9* pIdentifier);
	UINT __stdcall GetAdapterModeCount(THIS_ UINT Adapter, D3DFORMAT Format);
	HRESULT __stdcall EnumAdapterModes(THIS_ UINT Adapter, D3DFORMAT Format, UINT Mode, D3DDISPLAYMODE* pMode);
	HRESULT __stdcall GetAdapterDisplayMode(THIS_ UINT Adapter, D3DDISPLAYMODE* pMode);
	HRESULT __stdcall CheckDeviceType(THIS_ UINT Adapter, D3DDEVTYPE DevType, D3DFORMAT AdapterFormat, D3DFORMAT BackBufferFormat, BOOL bWindowed);
	HRESULT __stdcall CheckDeviceFormat(THIS_ UINT Adapter, D3DDEVTYPE DeviceType, D3DFORMAT AdapterFormat, DWORD Usage, D3DRESOURCETYPE RType, D3DFORMAT CheckFormat);
	HRESULT __stdcall CheckDeviceMultiSampleType(THIS_ UINT Adapter, D3DDEVTYPE DeviceType, D3DFORMAT SurfaceFormat, BOOL Windowed, D3DMULTISAMPLE_TYPE MultiSampleType, DWORD* pQualityLevels);
	HRESULT __stdcall CheckDepthStencilMatch(THIS_ UINT Adapter, D3DDEVTYPE DeviceType, D3DFORMAT AdapterFormat, D3DFORMAT RenderTargetFormat, D3DFORMAT DepthStencilFormat);
	HRESULT __stdcall CheckDeviceFormatConversion(THIS_ UINT Adapter, D3DDEVTYPE DeviceType, D3DFORMAT SourceFormat, D3DFORMAT TargetFormat);
	HRESULT __stdcall GetDeviceCaps(THIS_ UINT Adapter, D3DDEVTYPE DeviceType, D3DCAPS9* pCaps);
	HMONITOR __stdcall GetAdapterMonitor(THIS_ UINT Adapter);
	HRESULT __stdcall CreateDevice(THIS_ UINT Adapter, D3DDEVTYPE DeviceType, HWND hFocusWindow, DWORD BehaviorFlags, D3DPRESENT_PARAMETERS* pPresentationParameters, IDirect3DDevice9** ppReturnedDeviceInterface);
};


#endif;