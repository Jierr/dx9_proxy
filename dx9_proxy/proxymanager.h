#ifndef __PROXYMANAGER__
#define __PROXYMANAGER__

#include "stdafx.h"

using namespace std;

const D3DXCOLOR WHITE(D3DCOLOR_XRGB(255, 255, 255));
const D3DXCOLOR BLACK(D3DCOLOR_XRGB(0, 0, 0));
const D3DXCOLOR RED(D3DCOLOR_XRGB(255, 0, 0));
const D3DXCOLOR GREEN(D3DCOLOR_XRGB(0, 255, 0));
const D3DXCOLOR BLUE(D3DCOLOR_XRGB(0, 0, 255));
const D3DXCOLOR YELLOW(D3DCOLOR_XRGB(255, 255, 0));
const D3DXCOLOR CYAN(D3DCOLOR_XRGB(0, 255, 255));
const D3DXCOLOR MAGENTA(D3DCOLOR_XRGB(255, 0, 255));

typedef struct dxmanager{
	REFIID id;
	MI3d9* entry;
}dxmanager_t; 

typedef struct dxdevice{
	REFIID id;
	MI3dDevice entry;
}dxdevice_t;


typedef struct vertexXYZColor

{
	float x, y, z; // Position in 3d space
	D3DCOLOR  color;   // Color
	static const DWORD VertexFormat = D3DFVF_XYZ | D3DFVF_DIFFUSE;
	float u, v;    // Texture coordinates
} vertexXYZColor_t;

typedef struct vertexXYZColorTexture
{
	float x, y, z; // Position in 3d space
	D3DCOLOR  color;   // Color
	float u, v;    // Texture coordinates
	static const DWORD VertexFormat = D3DFVF_XYZ | D3DFVF_DIFFUSE;
} vertexXYZColorTexture_t;

typedef struct vertexXYZColour
{

	float x, y, z, rhw; // Position in 3d space
	D3DCOLOR  color;   // Color
} vertexXYZColour_t;

class ProxyManager{

public:
	MI3d9* dxmanager;
	MI3dDevice*  device;
	ProxyManager();
	~ProxyManager();


	MI3dDevice* createDeviceFromOriginal(IDirect3DDevice9* dev, MI3d9* d3d);
	MI3d9* createManagerFromOriginal(IDirect3D9* man);
	MI3dDevice* getDevice();
	void setDevice(MI3dDevice* dev);
	MI3d9* getManager();
	void setManager(MI3d9* manager);
};


#endif;