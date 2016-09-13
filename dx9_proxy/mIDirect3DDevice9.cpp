#include "stdafx.h"

using namespace std;

fstatistic_t MI3dDevice::stat{0,0,0,0,0,0,0};

MI3dDevice::MI3dDevice(IDirect3DDevice9* orig, MI3d9* creator)
{
	this->original = orig;
	this->creator = creator;
	this->tex_nr = 0;
	this->ref = 0;
	memset(&stat, 0, sizeof(fstatistic_t));
	textures.clear();
}

MI3dDevice::~MI3dDevice()
{
	this->original = NULL;
	this->creator = NULL;	
	


	list<texture_entry_t>::iterator it;
	it = textures.begin();
	while (it != textures.end())
	{
		if (it->treplaced != NULL)
		{
			it->treplaced->Release();
			it->treplaced = NULL;
			it = textures.erase(it);
		}
		else
			++it;
	}
	
	textures.clear();
}

/*** IUnknown methods ***/
HRESULT __stdcall MI3dDevice::QueryInterface(THIS_ REFIID riid, void** ppvObj)
{
	HRESULT result;

	result = original->QueryInterface(riid, ppvObj);
	
	if (result == S_OK)
	{
		*ppvObj = this;
	}
	
	return result;
}

ULONG __stdcall MI3dDevice::AddRef(THIS)
{
	ULONG result;

	this->ref = result = original->AddRef();

	return result;
}

ULONG __stdcall MI3dDevice::Release(THIS)
{
	ULONG result;
	//MessageBoxA(NULL, "MI3dDevice::Release>Enter Release MI3dDevice", "Release MI3dDevice", MB_OK);

	this->ref = result = original->Release();

	extern ProxyManager manager;
	if (result == 0)
	{
		this->creator = NULL;
		manager.setDevice(NULL);
		//MessageBoxA(NULL, "MI3dDevice::Release> Delete MI3dDevice", "Release MI3dDevice", MB_OK);
		delete(this);
	}	

	return result;
}


/*** IDirect3DDevice9 methods ***/
HRESULT __stdcall MI3dDevice::TestCooperativeLevel(THIS)
{
	HRESULT result;

	result = original->TestCooperativeLevel();

	return result;
}

UINT __stdcall MI3dDevice::GetAvailableTextureMem(THIS)
{
	UINT result;

	result = original->GetAvailableTextureMem();

	return result;
}

HRESULT __stdcall MI3dDevice::EvictManagedResources(THIS)
{
	HRESULT result;

	result = original->EvictManagedResources();

	return result;
}

HRESULT __stdcall MI3dDevice::GetDirect3D(THIS_ IDirect3D9** ppD3D9)
{
	HRESULT result;

	//MessageBoxA(NULL, "GetDirect3D", "Info", MB_OK);
	result = original->GetDirect3D(ppD3D9);
	*ppD3D9 = this->creator;

	return result;
}

HRESULT __stdcall MI3dDevice::GetDeviceCaps(THIS_ D3DCAPS9* pCaps)
{
	HRESULT result;

	result = original->GetDeviceCaps(pCaps);

	return result;
}

HRESULT __stdcall MI3dDevice::GetDisplayMode(THIS_ UINT iSwapChain, D3DDISPLAYMODE* pMode)
{
	HRESULT result;

	result = original->GetDisplayMode(iSwapChain, pMode);

	return result;
}

HRESULT __stdcall MI3dDevice::GetCreationParameters(THIS_ D3DDEVICE_CREATION_PARAMETERS *pParameters)
{
	HRESULT result;

	result = original->GetCreationParameters(pParameters);

	return result;
}

HRESULT __stdcall MI3dDevice::SetCursorProperties(THIS_ UINT XHotSpot, UINT YHotSpot, IDirect3DSurface9* pCursorBitmap)
{
	HRESULT result;

	result = original->SetCursorProperties(XHotSpot, YHotSpot, pCursorBitmap);

	return result;
}

void __stdcall MI3dDevice::SetCursorPosition(THIS_ int X, int Y, DWORD Flags)
{
	original->SetCursorPosition(X, Y, Flags);
}

BOOL __stdcall MI3dDevice::ShowCursor(THIS_ BOOL bShow)
{
	BOOL result;

	result = original->ShowCursor(bShow);

	return result;
}

HRESULT __stdcall MI3dDevice::CreateAdditionalSwapChain(THIS_ D3DPRESENT_PARAMETERS* pPresentationParameters, IDirect3DSwapChain9** pSwapChain)
{
	HRESULT result;

	result = original->CreateAdditionalSwapChain(pPresentationParameters, pSwapChain);

	return result;
}

//TODO
HRESULT __stdcall MI3dDevice::GetSwapChain(THIS_ UINT iSwapChain, IDirect3DSwapChain9** pSwapChain)
{
	HRESULT result;

	result = original->GetSwapChain(iSwapChain, pSwapChain);

	return result;
}

UINT __stdcall MI3dDevice::GetNumberOfSwapChains(THIS)
{
	UINT result;

	result = original->GetNumberOfSwapChains();

	return result;
}

HRESULT __stdcall MI3dDevice::Reset(THIS_ D3DPRESENT_PARAMETERS* pPresentationParameters)
{
	HRESULT result;

	result = original->Reset(pPresentationParameters);

	return result;
}

HRESULT __stdcall MI3dDevice::Present(THIS_ CONST RECT* pSourceRect, CONST RECT* pDestRect, HWND hDestWindowOverride, CONST RGNDATA* pDirtyRegion)
{
	HRESULT result;
	//MessageBoxA(NULL, "Creating new Device!", "Success", MB_OK);
	//D3DRECT rec = { 1, 1, 50, 50 };
	//this->original->Clear(1, &rec, D3DCLEAR_TARGET, D3DCOLOR_ARGB(255, 255, 255, 0), 0, 0);

	//this->original->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	//this->original->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	/*
	this->original->SetRenderState(D3DRS_CLIPPING, FALSE);
	this->original->SetRenderState(D3DRS_LIGHTING, FALSE);
	this->original->SetRenderState(D3DRS_AMBIENT, WHITE);
	this->original->SetRenderState(D3DRS_TEXTUREFACTOR, GREEN);
	this->original->SetRenderState(D3DRS_RANGEFOGENABLE, FALSE);
	this->original->SetRenderState(D3DRS_FOGENABLE, FALSE);
	this->original->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
	this->original->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_FLAT);
	*/
	//resetTextureStageState(-1);
	result = original->Present(pSourceRect, pDestRect, hDestWindowOverride, pDirtyRegion);


	return result;
}

//TODO
HRESULT __stdcall MI3dDevice::GetBackBuffer(THIS_ UINT iSwapChain, UINT iBackBuffer, D3DBACKBUFFER_TYPE Type, IDirect3DSurface9** ppBackBuffer)
{
	HRESULT result;

	result = original->GetBackBuffer(iSwapChain, iBackBuffer, Type, ppBackBuffer);

	return result;
}

HRESULT __stdcall MI3dDevice::GetRasterStatus(THIS_ UINT iSwapChain, D3DRASTER_STATUS* pRasterStatus)
{
	HRESULT result;

	result = original->GetRasterStatus(iSwapChain, pRasterStatus);

	return result;
}

HRESULT __stdcall MI3dDevice::SetDialogBoxMode(THIS_ BOOL bEnableDialogs)
{
	HRESULT result;

	result = original->SetDialogBoxMode(bEnableDialogs);

	return result;
}

void __stdcall MI3dDevice::SetGammaRamp(THIS_ UINT iSwapChain, DWORD Flags, CONST D3DGAMMARAMP* pRamp)
{
	original->SetGammaRamp(iSwapChain, Flags, pRamp);
}

void __stdcall MI3dDevice::GetGammaRamp(THIS_ UINT iSwapChain, D3DGAMMARAMP* pRamp)
{
	original->GetGammaRamp(iSwapChain, pRamp);
}

//TODO
HRESULT __stdcall MI3dDevice::CreateTexture(THIS_ UINT Width, UINT Height, UINT Levels, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool, IDirect3DTexture9** ppTexture, HANDLE* pSharedHandle)
{
	HRESULT result;
	list<texture_entry_t>::iterator it;
	bool new_texture = true;


	result = original->CreateTexture(Width, Height, Levels, Usage, Format, Pool, ppTexture, pSharedHandle);

	texture_entry_t entry = { Width, Height, Levels, Usage, Format, Pool, *ppTexture, pSharedHandle, NULL, L"", false, false, false, false};
	
	
	it = textures.begin();
	while (it != textures.end())
	{
		if ((entry.ppTexture == it->ppTexture)/* && (it->treplaced != NULL)*/)
		{
			new_texture = false;
			if (it->treplaced != NULL)
			{
				it->treplaced->Release();
				it->treplaced = NULL;
				//MessageBoxA(NULL, "Custom Texture released!", "MI3dDevice::CreateTexture", MB_OK);
			}
			it = textures.erase(it);
		}
		else
		{
			++it;
		}
	}
	textures.push_back(entry);
	return result;
}

//TODO
HRESULT __stdcall MI3dDevice::CreateVolumeTexture(THIS_ UINT Width, UINT Height, UINT Depth, UINT Levels, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool, IDirect3DVolumeTexture9** ppVolumeTexture, HANDLE* pSharedHandle)
{
	HRESULT result;

	result = original->CreateVolumeTexture(Width, Height, Depth, Levels, Usage, Format, Pool, ppVolumeTexture, pSharedHandle);

	return result;
}

//TODO
HRESULT __stdcall MI3dDevice::CreateCubeTexture(THIS_ UINT EdgeLength, UINT Levels, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool, IDirect3DCubeTexture9** ppCubeTexture, HANDLE* pSharedHandle)
{
	HRESULT result;

	result = original->CreateCubeTexture(EdgeLength, Levels, Usage, Format, Pool, ppCubeTexture, pSharedHandle);

	return result;
}

//TODO
HRESULT __stdcall MI3dDevice::CreateVertexBuffer(THIS_ UINT Length, DWORD Usage, DWORD FVF, D3DPOOL Pool, IDirect3DVertexBuffer9** ppVertexBuffer, HANDLE* pSharedHandle)
{
	HRESULT result;

	result = original->CreateVertexBuffer(Length, Usage, FVF, Pool, ppVertexBuffer, pSharedHandle);

	return result;
}

//TODO
HRESULT __stdcall MI3dDevice::CreateIndexBuffer(THIS_ UINT Length, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool, IDirect3DIndexBuffer9** ppIndexBuffer, HANDLE* pSharedHandle)
{
	HRESULT result;

	result = original->CreateIndexBuffer(Length, Usage, Format, Pool, ppIndexBuffer, pSharedHandle);

	return result;
}

HRESULT __stdcall MI3dDevice::CreateRenderTarget(THIS_ UINT Width, UINT Height, D3DFORMAT Format, D3DMULTISAMPLE_TYPE MultiSample, DWORD MultisampleQuality, BOOL Lockable, IDirect3DSurface9** ppSurface, HANDLE* pSharedHandle)
{
	HRESULT result;

	result = original->CreateRenderTarget(Width, Height, Format, MultiSample, MultisampleQuality, Lockable, ppSurface, pSharedHandle);

	return result;
}

HRESULT __stdcall MI3dDevice::CreateDepthStencilSurface(THIS_ UINT Width, UINT Height, D3DFORMAT Format, D3DMULTISAMPLE_TYPE MultiSample, DWORD MultisampleQuality, BOOL Discard, IDirect3DSurface9** ppSurface, HANDLE* pSharedHandle)
{
	HRESULT result;

	result = original->CreateDepthStencilSurface(Width, Height, Format, MultiSample, MultisampleQuality, Discard, ppSurface, pSharedHandle);

	return result;
}

HRESULT __stdcall MI3dDevice::UpdateSurface(THIS_ IDirect3DSurface9* pSourceSurface, CONST RECT* pSourceRect, IDirect3DSurface9* pDestinationSurface, CONST POINT* pDestPoint)
{
	HRESULT result;

	result = original->UpdateSurface(pSourceSurface, pSourceRect, pDestinationSurface, pDestPoint);

	return result;
}

HRESULT __stdcall MI3dDevice::UpdateTexture(THIS_ IDirect3DBaseTexture9* pSourceTexture, IDirect3DBaseTexture9* pDestinationTexture)
{
	HRESULT result;

	result = original->UpdateTexture(pSourceTexture, pDestinationTexture);

	return result;
}

HRESULT __stdcall MI3dDevice::GetRenderTargetData(THIS_ IDirect3DSurface9* pRenderTarget, IDirect3DSurface9* pDestSurface)
{
	HRESULT result;

	result = original->GetRenderTargetData(pRenderTarget, pDestSurface);

	return result;
}

HRESULT __stdcall MI3dDevice::GetFrontBufferData(THIS_ UINT iSwapChain, IDirect3DSurface9* pDestSurface)
{
	HRESULT result;

	result = original->GetFrontBufferData(iSwapChain, pDestSurface);

	return result;
}

HRESULT __stdcall MI3dDevice::StretchRect(THIS_ IDirect3DSurface9* pSourceSurface, CONST RECT* pSourceRect, IDirect3DSurface9* pDestSurface, CONST RECT* pDestRect, D3DTEXTUREFILTERTYPE Filter)
{
	HRESULT result;

	result = original->StretchRect(pSourceSurface, pSourceRect, pDestSurface, pDestRect, Filter);

	return result;
}

HRESULT __stdcall MI3dDevice::ColorFill(THIS_ IDirect3DSurface9* pSurface, CONST RECT* pRect, D3DCOLOR color)
{
	HRESULT result;

	result = original->ColorFill(pSurface, pRect, color);

	return result;
}

HRESULT __stdcall MI3dDevice::CreateOffscreenPlainSurface(THIS_ UINT Width, UINT Height, D3DFORMAT Format, D3DPOOL Pool, IDirect3DSurface9** ppSurface, HANDLE* pSharedHandle)
{
	HRESULT result;

	result = original->CreateOffscreenPlainSurface(Width, Height, Format, Pool, ppSurface, pSharedHandle);

	return result;
}

HRESULT __stdcall MI3dDevice::SetRenderTarget(THIS_ DWORD RenderTargetIndex, IDirect3DSurface9* pRenderTarget)
{
	HRESULT result;

	result = original->SetRenderTarget(RenderTargetIndex, pRenderTarget);

	return result;
}

HRESULT __stdcall MI3dDevice::GetRenderTarget(THIS_ DWORD RenderTargetIndex, IDirect3DSurface9** ppRenderTarget)
{
	HRESULT result;

	result = original->GetRenderTarget(RenderTargetIndex, ppRenderTarget);

	return result;
}

HRESULT __stdcall MI3dDevice::SetDepthStencilSurface(THIS_ IDirect3DSurface9* pNewZStencil)
{
	HRESULT result;

	result = original->SetDepthStencilSurface(pNewZStencil);

	return result;
}

HRESULT __stdcall MI3dDevice::GetDepthStencilSurface(THIS_ IDirect3DSurface9** ppZStencilSurface)
{
	HRESULT result;

	result = original->GetDepthStencilSurface(ppZStencilSurface);

	return result;
}

HRESULT __stdcall MI3dDevice::BeginScene(THIS)
{
	HRESULT result;

	result = original->BeginScene();

	return result;
}

HRESULT __stdcall MI3dDevice::EndScene(THIS)
{
	HRESULT result;

	result = original->EndScene();

	return result;
}

HRESULT __stdcall MI3dDevice::Clear(THIS_ DWORD Count, CONST D3DRECT* pRects, DWORD Flags, D3DCOLOR Color, float Z, DWORD Stencil)
{
	HRESULT result;

	result = original->Clear(Count, pRects, Flags, Color, Z, Stencil);

	return result;
}

HRESULT __stdcall MI3dDevice::SetTransform(THIS_ D3DTRANSFORMSTATETYPE State, CONST D3DMATRIX* pMatrix)
{
	HRESULT result;

	result = original->SetTransform(State, pMatrix);

	return result;
}

HRESULT __stdcall MI3dDevice::GetTransform(THIS_ D3DTRANSFORMSTATETYPE State, D3DMATRIX* pMatrix)
{
	HRESULT result;

	result = original->GetTransform(State, pMatrix);

	return result;
}

HRESULT __stdcall MI3dDevice::MultiplyTransform(THIS_ D3DTRANSFORMSTATETYPE type, CONST D3DMATRIX* matrix)
{
	HRESULT result;

	result = original->MultiplyTransform(type, matrix);

	return result;
}

HRESULT __stdcall MI3dDevice::SetViewport(THIS_ CONST D3DVIEWPORT9* pViewport)
{
	HRESULT result;

	result = original->SetViewport(pViewport);

	return result;
}

HRESULT __stdcall MI3dDevice::GetViewport(THIS_ D3DVIEWPORT9* pViewport)
{
	HRESULT result;

	result = original->GetViewport(pViewport);

	return result;
}

HRESULT __stdcall MI3dDevice::SetMaterial(THIS_ CONST D3DMATERIAL9* pMaterial)
{
	HRESULT result;

	result = original->SetMaterial(pMaterial);

	return result;
}

HRESULT __stdcall MI3dDevice::GetMaterial(THIS_ D3DMATERIAL9* pMaterial)
{
	HRESULT result;

	result = original->GetMaterial(pMaterial);

	return result;
}

HRESULT __stdcall MI3dDevice::SetLight(THIS_ DWORD Index, CONST D3DLIGHT9* light)
{
	HRESULT result;

	result = original->SetLight(Index, light);

	return result;
}

HRESULT __stdcall MI3dDevice::GetLight(THIS_ DWORD Index, D3DLIGHT9* light)
{
	HRESULT result;

	result = original->GetLight(Index, light);

	return result;
}

HRESULT __stdcall MI3dDevice::LightEnable(THIS_ DWORD Index, BOOL Enable)
{
	HRESULT result;

	//result = original->LightEnable(Index, FALSE);
	result = original->LightEnable(Index, Enable);

	return result;
}

HRESULT __stdcall MI3dDevice::GetLightEnable(THIS_ DWORD Index, BOOL* pEnable)
{
	HRESULT result;

	result = original->GetLightEnable(Index, pEnable);

	return result;
}

HRESULT __stdcall MI3dDevice::SetClipPlane(THIS_ DWORD Index, CONST float* pPlane)
{
	HRESULT result;

	result = original->SetClipPlane(Index, pPlane);

	return result;
}

HRESULT __stdcall MI3dDevice::GetClipPlane(THIS_ DWORD Index, float* pPlane)
{
	HRESULT result;

	result = original->GetClipPlane(Index, pPlane);

	return result;
}

HRESULT __stdcall MI3dDevice::SetRenderState(THIS_ D3DRENDERSTATETYPE State, DWORD Value)
{
	HRESULT result;

	result = original->SetRenderState(State, Value);

	return result;
}

HRESULT __stdcall MI3dDevice::GetRenderState(THIS_ D3DRENDERSTATETYPE State, DWORD* pValue)
{
	HRESULT result;

	result = original->GetRenderState(State, pValue);

	return result;
}

HRESULT __stdcall MI3dDevice::CreateStateBlock(THIS_ D3DSTATEBLOCKTYPE Type, IDirect3DStateBlock9** ppSB)
{
	HRESULT result;

	result = original->CreateStateBlock(Type, ppSB);

	return result;
}

HRESULT __stdcall MI3dDevice::BeginStateBlock(THIS)
{
	HRESULT result;

	result = original->BeginStateBlock();

	return result;
}

HRESULT __stdcall MI3dDevice::EndStateBlock(THIS_ IDirect3DStateBlock9** ppSB)
{
	HRESULT result;

	result = original->EndStateBlock(ppSB);

	return result;
}

HRESULT __stdcall MI3dDevice::SetClipStatus(THIS_ CONST D3DCLIPSTATUS9* pClipStatus)
{
	HRESULT result;

	result = original->SetClipStatus(pClipStatus);

	return result;
}

HRESULT __stdcall MI3dDevice::GetClipStatus(THIS_ D3DCLIPSTATUS9* pClipStatus)
{
	HRESULT result;

	result = original->GetClipStatus(pClipStatus);

	return result;
}

HRESULT __stdcall MI3dDevice::GetTexture(THIS_ DWORD Stage, IDirect3DBaseTexture9** ppTexture)
{
	HRESULT result;

	result = original->GetTexture(Stage, ppTexture);

	return result;
}


void MI3dDevice::convGUID(GUID guid, char sguid[37])
{
	sprintf(sguid, "%X-%X-%X-%X-%X%X",
		guid.Data1, guid.Data2, guid.Data3,
		*((uint16_t*)&guid.Data4[0]), ((uint16_t*)&guid.Data4[2]), *((uint32_t*)&guid.Data4[4]));

}


void MI3dDevice::saveTexture(wstring filename, void* data, const texture_entry_t& desc)
{
	BITMAPFILEHEADER   bmfHeader;
	BITMAPINFOHEADER   bi;

	bi.biSize = sizeof(BITMAPINFOHEADER);
	bi.biWidth = desc.Width;
	bi.biHeight = desc.Height;
	bi.biPlanes = 1;
	bi.biBitCount = 32;
	bi.biCompression = BI_RGB;
	bi.biSizeImage = 0;
	bi.biXPelsPerMeter = 0;
	bi.biYPelsPerMeter = 0;
	bi.biClrUsed = 0;
	bi.biClrImportant = 0;
	DWORD dwBmpSize = ((desc.Width * bi.biBitCount + 31) / 32) * 4 * desc.Height;


	// A file is created, this is where we will save the screen capture.
	HANDLE hFile = CreateFile(filename.c_str(),
		GENERIC_WRITE,
		0,
		NULL,
		CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL, NULL);

	// Add the size of the headers to the size of the bitmap to get the total file size
	DWORD dwSizeofDIB = dwBmpSize + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

	//Offset to where the actual bitmap bits start.
	bmfHeader.bfOffBits = (DWORD)sizeof(BITMAPFILEHEADER) + (DWORD)sizeof(BITMAPINFOHEADER);

	//Size of the file
	bmfHeader.bfSize = dwSizeofDIB;

	//bfType must always be BM for Bitmaps
	bmfHeader.bfType = 0x4D42; //BM   

	DWORD dwBytesWritten = 0;
	WriteFile(hFile, (LPSTR)&bmfHeader, sizeof(BITMAPFILEHEADER), &dwBytesWritten, NULL);
	WriteFile(hFile, (LPSTR)&bi, sizeof(BITMAPINFOHEADER), &dwBytesWritten, NULL);
	WriteFile(hFile, (LPSTR)data, dwBmpSize, &dwBytesWritten, NULL);


	//Close the handle for the file that was created
	CloseHandle(hFile);
}

void MI3dDevice::saveTexture(wstring filename, void* data, UINT width, UINT height)
{
	BITMAPFILEHEADER   bmfHeader;
	BITMAPINFOHEADER   bi;

	bi.biSize = sizeof(BITMAPINFOHEADER);
	bi.biWidth = width;
	bi.biHeight = height;
	bi.biPlanes = 1;
	bi.biBitCount = 32;
	bi.biCompression = BI_RGB;
	bi.biSizeImage = 0;
	bi.biXPelsPerMeter = 0;
	bi.biYPelsPerMeter = 0;
	bi.biClrUsed = 0;
	bi.biClrImportant = 0;
	DWORD dwBmpSize = ((width * bi.biBitCount + 31) / 32) * 4 * height;


	// A file is created, this is where we will save the screen capture.
	HANDLE hFile = CreateFile(filename.c_str(),
		GENERIC_WRITE,
		0,
		NULL,
		CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL, NULL);

	// Add the size of the headers to the size of the bitmap to get the total file size
	DWORD dwSizeofDIB = dwBmpSize + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

	//Offset to where the actual bitmap bits start.
	bmfHeader.bfOffBits = (DWORD)sizeof(BITMAPFILEHEADER) + (DWORD)sizeof(BITMAPINFOHEADER);

	//Size of the file
	bmfHeader.bfSize = dwSizeofDIB;

	//bfType must always be BM for Bitmaps
	bmfHeader.bfType = 0x4D42; //BM   

	DWORD dwBytesWritten = 0;
	WriteFile(hFile, (LPSTR)&bmfHeader, sizeof(BITMAPFILEHEADER), &dwBytesWritten, NULL);
	WriteFile(hFile, (LPSTR)&bi, sizeof(BITMAPINFOHEADER), &dwBytesWritten, NULL);
	WriteFile(hFile, (LPSTR)data, dwBmpSize, &dwBytesWritten, NULL);


	//Close the handle for the file that was created
	CloseHandle(hFile);
}

void MI3dDevice::hashTexture(wstring& texhash, const void *data, long size)
{

	HCRYPTPROV hCryptProv;
	HCRYPTHASH hHash;

	byte* hash;
	unsigned long hash_len;
	unsigned long tmp = sizeof(unsigned long);

	// Get a handle to a cryptography provider context.
	CryptAcquireContext(&hCryptProv, NULL, NULL, PROV_RSA_FULL, CRYPT_VERIFYCONTEXT);

	// Acquire a hash object handle.
	CryptCreateHash(hCryptProv, CALG_MD5, 0, 0, &hHash);

	//Add data to be hashed
	CryptHashData(hHash, (const byte*)data, size, CRYPT_USERDATA);

	
	//compute hash
	CryptGetHashParam(hHash, HP_HASHSIZE, (byte*)&hash_len, &tmp, 0);
	hash = new byte[hash_len];
	CryptGetHashParam(hHash, HP_HASHVAL, hash, &hash_len, 0);

	wstringstream hash_str;
	hash_str.str(L"");
	for (int b = 0; b < hash_len; ++b)
	{
		hash_str.fill(L'0');
		hash_str.width(2);
		hash_str << hex << hash[b];
	}
	texhash = hash_str.str();

	// After processing, hCryptProv and hHash must be released.
	if (hash)
		delete[] hash;
	if (hHash)
		CryptDestroyHash(hHash);
	if (hCryptProv)
		CryptReleaseContext(hCryptProv, 0);
}

bool __stdcall MI3dDevice::isEqualWstring(const wstring& str1, const wstring& str2)
{
	if (str1.length() != str2.length())
		return false;

	if (str1.compare(str2) == 0)
		return true;

	return false;
}

bool MI3dDevice::textureExist(wstring log, wstring texhash, unsigned long* pos)
{
	FILE* flog = NULL;
	unsigned long size = 0;
	unsigned long len = 0;
	unsigned long bytes_read = 0;
	unsigned long bytes = 0;
	unsigned long p = 0;
	unsigned long found_pos = 0;
	bool error = false;
	bool found = false;
	wstringstream curr_hash;

	wchar_t* content = NULL;


	flog = _wfopen(log.c_str(), L"rb");

	if (flog)
	{
		fseek(flog, 0, SEEK_END);
		size = ftell(flog);
		rewind(flog);

		len = ((size + sizeof(wchar_t)-1) / sizeof(wchar_t));
		content = new wchar_t[len];
		if (content == NULL)
		{
			MessageBoxW(NULL, L"Alloc failure", L"textureExist", MB_OK);
			fclose(flog);
		}
		else
		{
			fread(content, size, 1, flog);
			if (ferror(flog) ||feof(flog))
				error = true;

			fclose(flog);

			if (!error)
			{
				p = 0;
				while ((p < len) && !found)
				{
					if ((content[p] == L'\r') || (content[p] == L'\n') || (content[p] == L' ') || (content[p] == L'\t'))
						++p;
					else
					{
						found_pos = p;
						curr_hash.clear();
						curr_hash.str(L"");
						while ((p < len) && (content[p] != L'\r') && (content[p] != L'\n'))
						{
							curr_hash << content[p];
							++p;
						}

						found = this->isEqualWstring(texhash, curr_hash.str());						
					}
				}
			}
			else
				MessageBoxW(NULL, L"File Read failure", L"textureExist", MB_OK);
			delete[] content;

		}
	}

	if (found && (pos != NULL))
		*pos = found_pos;

	return found;
}


void MI3dDevice::addNewTextureHash(wstring log, wstring texhash)
{
	FILE* flog;
	wstringstream append;
	wchar_t* content = NULL;
	unsigned long size = 0;


	flog = _wfopen(log.c_str(), L"ab");
	fseek(flog, 0, SEEK_END);
	size = ftell(flog);
	

	if (flog)
	{
		append.str(L"");
		if (size != 0)
			append << L"\r\n" << texhash;
		else
			append << texhash;
		
		fwrite(append.str().c_str(), sizeof(wchar_t), append.str().length(), flog);

		fclose(flog);
	}
}



HRESULT __stdcall MI3dDevice::SetTexture(THIS_ DWORD Stage, IDirect3DBaseTexture9* pTexture)
{
	HRESULT result = D3D_OK;
	DWORD tsize = 0;
	unsigned char* data = NULL;
	char sguid[37] = { 0, };
	char str[1024*128] = { 0, };
	char ttypes[1024 * 128] = { 0, };
	char ttype[1024 * 128] = { 0, };
	GUID guid = { 0 };
	HRESULT presult = D3D_OK;
	HRESULT hres = -1;
	bool digimon = false;
	bool modTexture = true;
	int modLevel = 1;
	int saveLevel = 3;
	list<texture_entry_t>::iterator it = textures.begin();
	//getsize for buffer



	if (pTexture)
	{
		int i = 0;
		while ((it != textures.end()) && (it->ppTexture != pTexture))
		{
			//sprintf(ttype, "[%x] ", (int)it->Format);
			//strcat(ttypes, ttype);
			++i;
			++it;
		}


		if (it == textures.end())
		{
			guid = __uuidof(pTexture);
			convGUID(guid, sguid);
			sprintf(str, "Texture known: %d\r\nAll Types==============\r\n%s", it != textures.end(), ttypes);
			MessageBoxA(NULL, str, "sguid", MB_OK);
		}
		else
		{
			if (it->Levels < saveLevel)
				saveLevel = it->Levels;
			if (((it->Format == D3DFMT_A8R8G8B8) || (it->Format == D3DFMT_X8R8G8B8)) && (it->treplaced == NULL) &&
				(it->Levels > modLevel))
			{


				uint8_t* data = NULL;
				uint8_t* conv = NULL;
				uint8_t* curr = NULL;
				D3DLOCKED_RECT d3dlr;
				D3DSURFACE_DESC sdesc;

				if ((it->ppTexture->GetLevelDesc(saveLevel - 1, &sdesc) == D3D_OK) &&
					(it->ppTexture->LockRect(saveLevel - 1, &d3dlr, 0, 0) == D3D_OK))
				{
					if (curr = conv = new uint8_t[sdesc.Width * abs((long long)sdesc.Height) * sizeof(uint8_t) * 4])
					{
						data = (uint8_t*)(d3dlr.pBits);
						curr = conv;


						LONG lTexturePitch = d3dlr.Pitch;
						uint8_t* line_ref = data;

						/*
						wstringstream str;
						str.str(L"");
						str << L"Level = " << saveLevel - 1 << L"\r\nResolution:" << sdesc.Width << L"x" << sdesc.Height
							<< L"\r\ndata:" << hex << data << L", line_size = " << dec << lTexturePitch << L"Bytes";
						//MessageBoxW(NULL, str.str().c_str(), L"Error", MB_OK);
						*/


						for (long y = 0; y < abs((long long)sdesc.Height); ++y)
						{
							for (long x = 0; x < sdesc.Width; ++x)
							{
								curr[y * (sdesc.Width * sizeof(uint8_t) * 4) + 4 * x] = data[0]; //b
								curr[y * (sdesc.Width * sizeof(uint8_t) * 4) + 4 * x + 1] = data[1]; //g
								curr[y * (sdesc.Width * sizeof(uint8_t) * 4) + 4 * x + 2] = data[2]; //r
								curr[y * (sdesc.Width * sizeof(uint8_t) * 4) + 4 * x + 3] = data[3]; //a

								data += 4 * sizeof(uint8_t);
							}
							line_ref += lTexturePitch;
							data = line_ref;

						}

						it->ppTexture->UnlockRect(0);

						wstring hash = L"";
						wstringstream fstream;
						hashTexture(hash, conv, sdesc.Width * sdesc.Height * 4 * sizeof(uint8_t));
						it->hash = hash;
						fstream.str(L"");
						fstream << L"C:\\dmo\\Textures\\" << hash << L".bmp";
						//MessageBoxW(NULL, fstream.str().c_str(), L"Textur", MB_OK);
						if (textureExist(L"C:\\dmo\\digimon.txt", it->hash, NULL))
							it->digimon = true;
						if (textureExist(L"C:\\dmo\\effects.txt", it->hash, NULL))
							it->effect = true;
						if (textureExist(L"C:\\dmo\\partners.txt", it->hash, NULL))
							it->partner = true;
						if (textureExist(L"C:\\dmo\\enemies.txt", it->hash, NULL))
							it->enemy = true;

						if ((it->treplaced == NULL) && !textureExist(L"C:\\dmo\\textures.txt", hash, NULL))
						{
							//MessageBoxW(NULL, fstream.str().c_str(), L"Neue Textur", MB_OK);
							addNewTextureHash(L"C:\\dmo\\textures.txt", hash);
							saveTexture(fstream.str(), conv, sdesc.Width, sdesc.Height);
						}


						if (conv)
							delete[] conv;
						conv = curr = NULL;


						++this->tex_nr;
					}

				}
			}


			if (modTexture)
			{
				digimon = it->digimon;
				uint8_t r, g, b, a;
				if (it->digimon)
				{
					if (it->partner)
					{
						r = 255; g = 0; b = 0; a = 255;
					}
					else if (it->enemy)
					{
						r = 0; g = 255; b = 0; a = 255;
					}
					else
					{
						r = 0; g = 0; b = 255; a = 255;
					}
				}
				else if (it->effect)
				{
					r = 255; g = 255; b = 255; a = 0;
				}
				else
				{
					r = 255; g = 0; b = 0; a = 255;
				}
				if (it->Format == D3DFMT_A8R8G8B8)
				{

					if (it->Levels > modLevel) 
					{
						if (it->treplaced == NULL)
							hres = original->CreateTexture(it->Width, it->Height, it->Levels, 0, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, &it->treplaced, NULL);
						if (hres == D3D_OK)
						{
							for (int l = 0; l < it->Levels; ++l)
							{
								D3DSURFACE_DESC sdesc;
								D3DLOCKED_RECT d3dlr;
								D3DLOCKED_RECT od3dlr;

								it->ppTexture->GetLevelDesc(l, &sdesc);
								it->treplaced->LockRect(l, &d3dlr, 0, 0);
								it->ppTexture->LockRect(l, &od3dlr, 0, 0);

								LONG lTexturePitch = d3dlr.Pitch;
								LONG olTexturePitch = od3dlr.Pitch;
								LONG lSamplePitch = 4 * it->Width;
								uint8_t* data = (uint8_t*)(d3dlr.pBits);//+lSamplePitch + it->Height;
								uint8_t* odata = (uint8_t*)(od3dlr.pBits);
								uint8_t* line_ref = data;
								uint8_t* oline_ref = odata;

								
								for (long y = 0; y < sdesc.Height; ++y)
								{
									for (long x = 0; x < sdesc.Width; ++x)
									{
										//data[0] = odata[0];
										//data[1] = odata[1];
										//data[2] = odata[2];
										//data[3] = odata[3];
										data[0] = b; //b
										data[1] = g; //g
										data[2] = r; //r
										data[3] = a; //a

										data += 4 * sizeof(uint8_t);
										odata += 4 * sizeof(uint8_t);
									}
									line_ref += lTexturePitch;
									oline_ref += olTexturePitch;
									data = line_ref;
									odata = oline_ref;
								}

								it->ppTexture->UnlockRect(0);
								it->treplaced->UnlockRect(0);
							}
						}
						if (digimon || it->effect)
							pTexture = it->treplaced;
					}


				}
				else if (it->Format == D3DFMT_X8R8G8B8)
				{
					if (it->Levels > modLevel)
					{
						if (it->treplaced == NULL)
							hres = original->CreateTexture(it->Width, it->Height, it->Levels, 0, D3DFMT_X8R8G8B8, D3DPOOL_MANAGED, &it->treplaced, NULL);
						if (hres == D3D_OK)
						{
							for (int l = 0; l < it->Levels; ++l)
							{
								D3DSURFACE_DESC sdesc;
								D3DLOCKED_RECT d3dlr;
								D3DLOCKED_RECT od3dlr;

								it->ppTexture->GetLevelDesc(l, &sdesc);
								it->treplaced->LockRect(l, &d3dlr, 0, 0);
								it->ppTexture->LockRect(l, &od3dlr, 0, 0);

								LONG lTexturePitch = d3dlr.Pitch;
								LONG olTexturePitch = od3dlr.Pitch;
								LONG lSamplePitch = 4 * it->Width;
								uint8_t* data = (uint8_t*)(d3dlr.pBits);//+lSamplePitch + it->Height;
								uint8_t* odata = (uint8_t*)(od3dlr.pBits);
								uint8_t* line_ref = data;
								uint8_t* oline_ref = odata;

								for (long y = 0; y < sdesc.Height; ++y)
								{
									for (long x = 0; x < sdesc.Width; ++x)
									{
										//data[0] = odata[0];
										//data[1] = odata[1];
										//data[2] = odata[2];
										//data[3] = odata[3];
										data[0] = b; //b
										data[1] = g; //g
										data[2] = r; //r
										data[3] = a; //a

										data += 4 * sizeof(uint8_t);
										odata += 4 * sizeof(uint8_t);
									}
									line_ref += lTexturePitch;
									oline_ref += olTexturePitch;
									data = line_ref;
									odata = oline_ref;
								}

								it->ppTexture->UnlockRect(0);
								it->treplaced->UnlockRect(0);
							}
						}
						if (digimon || it->effect)
							pTexture = it->treplaced;
					}

				}
				else if (it->Format == D3DFMT_R5G6B5)
				{
					if (it->treplaced == NULL)
						hres = original->CreateTexture(it->Width, it->Height, it->Levels, 0, D3DFMT_R5G6B5, D3DPOOL_MANAGED, &it->treplaced, NULL);
					/*
					if (hres == D3D_OK)
					{

					D3DLOCKED_RECT d3dlr;
					it->treplaced->LockRect(0, &d3dlr, 0, 0);
					LONG lTexturePitch = d3dlr.Pitch;
					LONG lSamplePitch = 4 * it->Width;
					uint16_t* data = (uint16_t*)(d3dlr.pBits);// +lSamplePitch + it->Height;
					uint16_t* line_ref = data;

					for (long y = 0; y < it->Height; ++y)
					{
					for (long x = 0; x < it->Width; ++x)
					{

					*data = 0;
					*data = 0xF800;
					data += sizeof(uint16_t);
					}
					line_ref += lTexturePitch;
					data = line_ref;
					}

					it->treplaced->UnlockRect(0);

					//result = original->SetTexture(Stage, NULL);

					}
					*/
					//pTexture = it->treplaced;

					//result = original->SetTexture(Stage, pTexture);
					//result = original->SetTexture(Stage, NULL);

				}
				else if (it->Format == D3DFMT_DXT5)
				{
					if (it->treplaced == NULL)
						hres = original->CreateTexture(it->Width, it->Height, it->Levels, 0, D3DFMT_DXT5, D3DPOOL_MANAGED, &it->treplaced, NULL);
					if (hres == D3D_OK)
					{
						/*
						D3DLOCKED_RECT d3dlr;
						it->treplaced->LockRect(0, &d3dlr, 0, 0);
						LONG lTexturePitch = d3dlr.Pitch/4;
						LONG lSamplePitch = it->Width/4;
						uint64_t* data = (uint64_t*)(d3dlr.pBits);// +lSamplePitch + it->Height;
						uint64_t* line_ref = data;

						for (long y = 0; y < it->Height; ++y)
						{
						for (long x = 0; x < it->Width; ++x)
						{

						*data = ULONG_MAX;
						data += sizeof(uint64_t);
						}
						line_ref += lTexturePitch;
						data = line_ref;
						}

						it->treplaced->UnlockRect(0);
						*/
						//result = original->SetTexture(Stage, NULL);

					}
					//pTexture = it->treplaced;
					//pTexture = NULL;
					//result = original->SetTexture(Stage, NULL);
					//result = original->SetTexture(Stage, pTexture);
				}
			}


			result = original->SetTexture(Stage, pTexture);
		}
	}

	return result;
	//return D3D_OK;
}

HRESULT __stdcall MI3dDevice::GetTextureStageState(THIS_ DWORD Stage, D3DTEXTURESTAGESTATETYPE Type, DWORD* pValue)
{
	HRESULT result;

	result = original->GetTextureStageState(Stage, Type, pValue);

	return result;
}

/*
D3DTSS_COLOROP                = 1,
D3DTSS_COLORARG1              = 2,
D3DTSS_COLORARG2              = 3,
D3DTSS_ALPHAOP                = 4,
D3DTSS_ALPHAARG1              = 5,
D3DTSS_ALPHAARG2              = 6,
D3DTSS_BUMPENVMAT00           = 7,
D3DTSS_BUMPENVMAT01           = 8,
D3DTSS_BUMPENVMAT10           = 9,
D3DTSS_BUMPENVMAT11           = 10,
D3DTSS_TEXCOORDINDEX          = 11,
D3DTSS_BUMPENVLSCALE          = 22,
D3DTSS_BUMPENVLOFFSET         = 23,
D3DTSS_TEXTURETRANSFORMFLAGS  = 24,
D3DTSS_COLORARG0              = 26,
D3DTSS_ALPHAARG0              = 27,
D3DTSS_RESULTARG              = 28,
D3DTSS_CONSTANT               = 32,
D3DTSS_FORCE_DWORD            = 0x7fffffff
*/

//https://msdn.microsoft.com/en-us/library/windows/desktop/bb174462%28v=vs.85%29.aspx
void MI3dDevice::resetTextureStageState(int stage)
{
	int s = 0;

	for (s = 0; s < 8; ++s)
	{
		original->SetTextureStageState(s, D3DTSS_COLOROP, D3DTOP_MODULATE);
		//original->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_DISABLE);
		original->SetTextureStageState(s, D3DTSS_COLORARG1, D3DTA_TEXTURE);
		original->SetTextureStageState(s, D3DTSS_COLORARG2, D3DTA_CURRENT);
		original->SetTextureStageState(s, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);
		original->SetTextureStageState(s, D3DTSS_ALPHAARG1, D3DTA_CONSTANT);
		original->SetTextureStageState(s, D3DTSS_ALPHAARG2, D3DTA_CONSTANT);
		original->SetTextureStageState(s, D3DTSS_CONSTANT, D3DTA_CONSTANT);
	}


		

}

HRESULT __stdcall MI3dDevice::SetTextureStageState(THIS_ DWORD Stage, D3DTEXTURESTAGESTATETYPE Type, DWORD Value)
{
	HRESULT result;

	result = original->SetTextureStageState(Stage, Type, Value);
	//result = original->SetTextureStageState(Stage, D3DTSS_COLORARG2, D3DTA_DIFFUSE);
	//result = original->SetTextureStageState(Stage, D3DTSS_COLOROP, D3DTOP_DISABLE);

	return result;
}

HRESULT __stdcall MI3dDevice::GetSamplerState(THIS_ DWORD Sampler, D3DSAMPLERSTATETYPE Type, DWORD* pValue)
{
	HRESULT result;

	result = original->GetSamplerState(Sampler, Type, pValue);

	return result;
}

HRESULT __stdcall MI3dDevice::SetSamplerState(THIS_ DWORD Sampler, D3DSAMPLERSTATETYPE Type, DWORD Value)
{
	HRESULT result;

	result = original->SetSamplerState(Sampler, Type, Value);

	return result;
}

HRESULT __stdcall MI3dDevice::ValidateDevice(THIS_ DWORD* pNumPasses)
{
	HRESULT result;

	result = original->ValidateDevice(pNumPasses);

	return result;
}

HRESULT __stdcall MI3dDevice::SetPaletteEntries(THIS_ UINT PaletteNumber, CONST PALETTEENTRY* pEntries)
{
	HRESULT result;

	result = original->SetPaletteEntries(PaletteNumber, pEntries);

	return result;
}

HRESULT __stdcall MI3dDevice::GetPaletteEntries(THIS_ UINT PaletteNumber, PALETTEENTRY* pEntries)
{
	HRESULT result;

	result = original->GetPaletteEntries(PaletteNumber, pEntries);

	return result;
}

HRESULT __stdcall MI3dDevice::SetCurrentTexturePalette(THIS_ UINT PaletteNumber)
{
	HRESULT result;

	result = original->SetCurrentTexturePalette(PaletteNumber);

	return result;
}

HRESULT __stdcall MI3dDevice::GetCurrentTexturePalette(THIS_ UINT *PaletteNumber)
{
	HRESULT result;

	result = original->GetCurrentTexturePalette(PaletteNumber);

	return result;
}

HRESULT __stdcall MI3dDevice::SetScissorRect(THIS_ CONST RECT* pRect)
{
	HRESULT result;

	result = original->SetScissorRect(pRect);

	return result;
}

HRESULT __stdcall MI3dDevice::GetScissorRect(THIS_ RECT* pRect)
{
	HRESULT result;

	result = original->GetScissorRect(pRect);

	return result;
}

HRESULT __stdcall MI3dDevice::SetSoftwareVertexProcessing(THIS_ BOOL bSoftware)
{
	HRESULT result;

	result = original->SetSoftwareVertexProcessing(bSoftware);

	return result;
}

BOOL __stdcall MI3dDevice::GetSoftwareVertexProcessing(THIS)
{
	BOOL result;

	result = original->GetSoftwareVertexProcessing();

	return result;
}

HRESULT __stdcall MI3dDevice::SetNPatchMode(THIS_ float nSegments)
{
	HRESULT result;

	result = original->SetNPatchMode(nSegments);

	return result;
}

float __stdcall MI3dDevice::GetNPatchMode(THIS)
{
	float result;

	result = original->GetNPatchMode();

	return result;
}

HRESULT __stdcall MI3dDevice::DrawPrimitive(THIS_ D3DPRIMITIVETYPE PrimitiveType, UINT StartVertex, UINT PrimitiveCount)
{
	HRESULT result;

	stat.DrawPrimitive++;
	result = original->DrawPrimitive(PrimitiveType, StartVertex, PrimitiveCount);

	return result;
}

//TODO This is the drawing function used by DMO, use GetStreamSource to get the vertex buffer
//TODO Alternatively intercept SetStreamSource
HRESULT __stdcall MI3dDevice::DrawIndexedPrimitive(THIS_ D3DPRIMITIVETYPE type, INT BaseVertexIndex, UINT MinVertexIndex, UINT NumVertices, UINT startIndex, UINT primCount)
{
	HRESULT result;

	stat.DrawIndexedPrimitive++;

	result = original->DrawIndexedPrimitive(type, BaseVertexIndex, MinVertexIndex, NumVertices, startIndex, primCount);

	return result;
}

HRESULT __stdcall MI3dDevice::DrawPrimitiveUP(THIS_ D3DPRIMITIVETYPE PrimitiveType, UINT PrimitiveCount, CONST void* pVertexStreamZeroData, UINT VertexStreamZeroStride)
{
	HRESULT result;

	stat.DrawPrimitiveUP++;
	result = original->DrawPrimitiveUP(PrimitiveType, PrimitiveCount, pVertexStreamZeroData, VertexStreamZeroStride);

	return result;
}

HRESULT __stdcall MI3dDevice::DrawIndexedPrimitiveUP(THIS_ D3DPRIMITIVETYPE PrimitiveType, UINT MinVertexIndex, UINT NumVertices, UINT PrimitiveCount, CONST void* pIndexData, D3DFORMAT IndexDataFormat, CONST void* pVertexStreamZeroData, UINT VertexStreamZeroStride)
{
	HRESULT result;

	stat.DrawIndexedPrimitiveUP++;
	result = original->DrawIndexedPrimitiveUP(PrimitiveType, MinVertexIndex, NumVertices, PrimitiveCount, pIndexData, IndexDataFormat, pVertexStreamZeroData, VertexStreamZeroStride);

	return result;
}

HRESULT __stdcall MI3dDevice::ProcessVertices(THIS_ UINT SrcStartIndex, UINT DestIndex, UINT VertexCount, IDirect3DVertexBuffer9* pDestBuffer, IDirect3DVertexDeclaration9* pVertexDecl, DWORD Flags)
{
	HRESULT result;

	result = original->ProcessVertices(SrcStartIndex, DestIndex, VertexCount, pDestBuffer, pVertexDecl, Flags);

	return result;
}

//TODO
HRESULT __stdcall MI3dDevice::CreateVertexDeclaration(THIS_ CONST D3DVERTEXELEMENT9* pVertexElements, IDirect3DVertexDeclaration9** ppDecl)
{
	HRESULT result;

	result = original->CreateVertexDeclaration(pVertexElements, ppDecl);

	return result;
}

HRESULT __stdcall MI3dDevice::SetVertexDeclaration(THIS_ IDirect3DVertexDeclaration9* pDecl)
{
	HRESULT result;

	result = original->SetVertexDeclaration(pDecl);

	return result;
}

HRESULT __stdcall MI3dDevice::GetVertexDeclaration(THIS_ IDirect3DVertexDeclaration9** ppDecl)
{
	HRESULT result;

	result = original->GetVertexDeclaration(ppDecl);

	return result;
}

HRESULT __stdcall MI3dDevice::SetFVF(THIS_ DWORD FVF)
{
	HRESULT result;

	result = original->SetFVF(FVF);

	return result;
}

HRESULT __stdcall MI3dDevice::GetFVF(THIS_ DWORD* pFVF)
{
	HRESULT result;

	result = original->GetFVF(pFVF);

	return result;
}

HRESULT __stdcall MI3dDevice::CreateVertexShader(THIS_ CONST DWORD* pFunction, IDirect3DVertexShader9** ppShader)
{
	HRESULT result;

	result = original->CreateVertexShader(pFunction, ppShader);

	return result;
}

HRESULT __stdcall MI3dDevice::SetVertexShader(THIS_ IDirect3DVertexShader9* pShader)
{
	HRESULT result;

	result = original->SetVertexShader(pShader);

	return result;
}

HRESULT __stdcall MI3dDevice::GetVertexShader(THIS_ IDirect3DVertexShader9** ppShader)
{
	HRESULT result;

	result = original->GetVertexShader(ppShader);

	return result;
}

HRESULT __stdcall MI3dDevice::SetVertexShaderConstantF(THIS_ UINT StartRegister, CONST float* pConstantData, UINT Vector4fCount)
{
	HRESULT result;

	result = original->SetVertexShaderConstantF(StartRegister, pConstantData, Vector4fCount);

	return result;
}

HRESULT __stdcall MI3dDevice::GetVertexShaderConstantF(THIS_ UINT StartRegister, float* pConstantData, UINT Vector4fCount)
{
	HRESULT result;

	result = original->GetVertexShaderConstantF(StartRegister, pConstantData, Vector4fCount);

	return result;
}

HRESULT __stdcall MI3dDevice::SetVertexShaderConstantI(THIS_ UINT StartRegister, CONST int* pConstantData, UINT Vector4iCount)
{
	HRESULT result;

	result = original->SetVertexShaderConstantI(StartRegister, pConstantData, Vector4iCount);

	return result;
}

HRESULT __stdcall MI3dDevice::GetVertexShaderConstantI(THIS_ UINT StartRegister, int* pConstantData, UINT Vector4iCount)
{
	HRESULT result;

	result = original->GetVertexShaderConstantI(StartRegister, pConstantData, Vector4iCount);

	return result;
}

HRESULT __stdcall MI3dDevice::SetVertexShaderConstantB(THIS_ UINT StartRegister, CONST BOOL* pConstantData, UINT  BoolCount)
{
	HRESULT result;

	result = original->SetVertexShaderConstantB(StartRegister, pConstantData, BoolCount);

	return result;
}

HRESULT __stdcall MI3dDevice::GetVertexShaderConstantB(THIS_ UINT StartRegister, BOOL* pConstantData, UINT BoolCount)
{
	HRESULT result;

	result = original->GetVertexShaderConstantB(StartRegister, pConstantData, BoolCount);

	return result;
}

HRESULT __stdcall MI3dDevice::SetStreamSource(THIS_ UINT StreamNumber, IDirect3DVertexBuffer9* pStreamData, UINT OffsetInBytes, UINT Stride)
{
	HRESULT result;

	stat.SetStreamSource++;
	result = original->SetStreamSource(StreamNumber, pStreamData, OffsetInBytes, Stride);

	return result;
}

HRESULT __stdcall MI3dDevice::GetStreamSource(THIS_ UINT StreamNumber, IDirect3DVertexBuffer9** ppStreamData, UINT* pOffsetInBytes, UINT* pStride)
{
	HRESULT result;

	result = original->GetStreamSource(StreamNumber, ppStreamData, pOffsetInBytes, pStride);

	return result;
}

HRESULT __stdcall MI3dDevice::SetStreamSourceFreq(THIS_ UINT StreamNumber, UINT Setting)
{
	HRESULT result;

	result = original->SetStreamSourceFreq(StreamNumber, Setting);

	return result;
}

HRESULT __stdcall MI3dDevice::GetStreamSourceFreq(THIS_ UINT StreamNumber, UINT* pSetting)
{
	HRESULT result;

	result = original->GetStreamSourceFreq(StreamNumber, pSetting);

	return result;
}

HRESULT __stdcall MI3dDevice::SetIndices(THIS_ IDirect3DIndexBuffer9* pIndexData)
{
	HRESULT result;

	result = original->SetIndices(pIndexData);

	return result;
}

HRESULT __stdcall MI3dDevice::GetIndices(THIS_ IDirect3DIndexBuffer9** ppIndexData)
{
	HRESULT result;

	result = original->GetIndices(ppIndexData);

	return result;
}

HRESULT __stdcall MI3dDevice::CreatePixelShader(THIS_ CONST DWORD* pFunction, IDirect3DPixelShader9** ppShader)
{
	HRESULT result;

	result = original->CreatePixelShader(pFunction, ppShader);

	return result;
}

HRESULT __stdcall MI3dDevice::SetPixelShader(THIS_ IDirect3DPixelShader9* pShader)
{
	HRESULT result;

	result = original->SetPixelShader(pShader);

	return result;
}

HRESULT __stdcall MI3dDevice::GetPixelShader(THIS_ IDirect3DPixelShader9** ppShader)
{
	HRESULT result;

	result = original->GetPixelShader(ppShader);

	return result;
}

HRESULT __stdcall MI3dDevice::SetPixelShaderConstantF(THIS_ UINT StartRegister, CONST float* pConstantData, UINT Vector4fCount)
{
	HRESULT result;

	result = original->SetPixelShaderConstantF(StartRegister, pConstantData, Vector4fCount);

	return result;
}

HRESULT __stdcall MI3dDevice::GetPixelShaderConstantF(THIS_ UINT StartRegister, float* pConstantData, UINT Vector4fCount)
{
	HRESULT result;

	result = original->GetPixelShaderConstantF(StartRegister, pConstantData, Vector4fCount);

	return result;
}

HRESULT __stdcall MI3dDevice::SetPixelShaderConstantI(THIS_ UINT StartRegister, CONST int* pConstantData, UINT Vector4iCount)
{
	HRESULT result;

	result = original->SetPixelShaderConstantI(StartRegister, pConstantData, Vector4iCount);

	return result;
}

HRESULT __stdcall MI3dDevice::GetPixelShaderConstantI(THIS_ UINT StartRegister, int* pConstantData, UINT Vector4iCount)
{
	HRESULT result;

	result = original->GetPixelShaderConstantI(StartRegister, pConstantData, Vector4iCount);

	return result;
}

HRESULT __stdcall MI3dDevice::SetPixelShaderConstantB(THIS_ UINT StartRegister, CONST BOOL* pConstantData, UINT  BoolCount)
{
	HRESULT result;

	result = original->SetPixelShaderConstantB(StartRegister, pConstantData, BoolCount);

	return result;
}

HRESULT __stdcall MI3dDevice::GetPixelShaderConstantB(THIS_ UINT StartRegister, BOOL* pConstantData, UINT BoolCount)
{
	HRESULT result;

	result = original->GetPixelShaderConstantB(StartRegister, pConstantData, BoolCount);

	return result;
}

HRESULT __stdcall MI3dDevice::DrawRectPatch(THIS_ UINT Handle, CONST float* pNumSegs, CONST D3DRECTPATCH_INFO* pRectPatchInfo)
{
	HRESULT result;

	stat.DrawRectPatch++;
	result = original->DrawRectPatch(Handle, pNumSegs, pRectPatchInfo);

	return result;
}

HRESULT __stdcall MI3dDevice::DrawTriPatch(THIS_ UINT Handle, CONST float* pNumSegs, CONST D3DTRIPATCH_INFO* pTriPatchInfo)
{
	HRESULT result;

	stat.DrawTriPatch++;
	result = original->DrawTriPatch(Handle, pNumSegs, pTriPatchInfo);

	return result;
}

HRESULT __stdcall MI3dDevice::DeletePatch(THIS_ UINT Handle)
{
	HRESULT result;

	result = original->DeletePatch(Handle);

	return result;
}

HRESULT __stdcall MI3dDevice::CreateQuery(THIS_ D3DQUERYTYPE Type, IDirect3DQuery9** ppQuery)
{
	HRESULT result;

	result = original->CreateQuery(Type, ppQuery);

	return result;
}
