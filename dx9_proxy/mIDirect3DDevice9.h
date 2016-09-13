#ifndef __MDEVICE__
#define __MDEVICE__

#include "stdafx.h"

using namespace std; 

typedef struct fstatistic{

	unsigned long DrawPrimitive;
	unsigned long DrawIndexedPrimitive;
	unsigned long DrawPrimitiveUP;
	unsigned long DrawIndexedPrimitiveUP;
	unsigned long DrawRectPatch;
	unsigned long DrawTriPatch;
	unsigned long SetStreamSource;
} fstatistic_t;

typedef struct texture_entry
{
	UINT Width;
	UINT Height;
	UINT Levels;
	DWORD Usage;
	D3DFORMAT Format;
	D3DPOOL Pool;
	IDirect3DTexture9* ppTexture;
	HANDLE* pSharedHandle;
	IDirect3DTexture9* treplaced;
	wstring hash;
	bool digimon;
	bool effect;
	bool partner;
	bool enemy;
} texture_entry_t;

class MI3dDevice : public IDirect3DDevice9
{
public:
	friend class ProxyManager;

	int ref;
	IDirect3DDevice9* original;
	MI3d9* creator;
	std::list<texture_entry_t> textures;
	uint64_t tex_nr;
	static fstatistic_t stat;
	
	void convGUID(GUID guid, char sguid[37]);
	void resetTextureStageState(int stage);
	void saveTexture(wstring filename, void* data, const texture_entry_t& desc);
	void saveTexture(wstring filename, void* data, UINT width, UINT height);
	void hashTexture(wstring& texhash, const void *data, long size);
	bool textureExist(wstring log, wstring texhash, unsigned long* pos);
	void addNewTextureHash(wstring log, wstring texhash);
	bool __stdcall isEqualWstring(const wstring& str1, const wstring& str2);


	MI3dDevice(IDirect3DDevice9* orig, MI3d9* creator);
	~MI3dDevice();

	/*** IUnknown methods ***/
	HRESULT __stdcall QueryInterface(THIS_ REFIID riid, void** ppvObj);
	ULONG __stdcall AddRef(THIS);
	ULONG __stdcall Release(THIS);

	/*** IDirect3DDevice9 methods ***/
	HRESULT __stdcall TestCooperativeLevel(THIS);
	UINT __stdcall GetAvailableTextureMem(THIS);
	HRESULT __stdcall EvictManagedResources(THIS);
	HRESULT __stdcall GetDirect3D(THIS_ IDirect3D9** ppD3D9);
	HRESULT __stdcall GetDeviceCaps(THIS_ D3DCAPS9* pCaps);
	HRESULT __stdcall GetDisplayMode(THIS_ UINT iSwapChain, D3DDISPLAYMODE* pMode);
	HRESULT __stdcall GetCreationParameters(THIS_ D3DDEVICE_CREATION_PARAMETERS *pParameters);
	HRESULT __stdcall SetCursorProperties(THIS_ UINT XHotSpot, UINT YHotSpot, IDirect3DSurface9* pCursorBitmap);
	void __stdcall SetCursorPosition(THIS_ int X, int Y, DWORD Flags);
	BOOL __stdcall ShowCursor(THIS_ BOOL bShow);
	HRESULT __stdcall CreateAdditionalSwapChain(THIS_ D3DPRESENT_PARAMETERS* pPresentationParameters, IDirect3DSwapChain9** pSwapChain);
	HRESULT __stdcall GetSwapChain(THIS_ UINT iSwapChain, IDirect3DSwapChain9** pSwapChain);
	UINT __stdcall GetNumberOfSwapChains(THIS);
	HRESULT __stdcall Reset(THIS_ D3DPRESENT_PARAMETERS* pPresentationParameters);
	HRESULT __stdcall Present(THIS_ CONST RECT* pSourceRect, CONST RECT* pDestRect, HWND hDestWindowOverride, CONST RGNDATA* pDirtyRegion);
	HRESULT __stdcall GetBackBuffer(THIS_ UINT iSwapChain, UINT iBackBuffer, D3DBACKBUFFER_TYPE Type, IDirect3DSurface9** ppBackBuffer);
	HRESULT __stdcall GetRasterStatus(THIS_ UINT iSwapChain, D3DRASTER_STATUS* pRasterStatus);
	HRESULT __stdcall SetDialogBoxMode(THIS_ BOOL bEnableDialogs);
	void __stdcall SetGammaRamp(THIS_ UINT iSwapChain, DWORD Flags, CONST D3DGAMMARAMP* pRamp);
	void __stdcall GetGammaRamp(THIS_ UINT iSwapChain, D3DGAMMARAMP* pRamp);
	HRESULT __stdcall CreateTexture(THIS_ UINT Width, UINT Height, UINT Levels, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool, IDirect3DTexture9** ppTexture, HANDLE* pSharedHandle);
	HRESULT __stdcall CreateVolumeTexture(THIS_ UINT Width, UINT Height, UINT Depth, UINT Levels, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool, IDirect3DVolumeTexture9** ppVolumeTexture, HANDLE* pSharedHandle);
	HRESULT __stdcall CreateCubeTexture(THIS_ UINT EdgeLength, UINT Levels, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool, IDirect3DCubeTexture9** ppCubeTexture, HANDLE* pSharedHandle);
	HRESULT __stdcall CreateVertexBuffer(THIS_ UINT Length, DWORD Usage, DWORD FVF, D3DPOOL Pool, IDirect3DVertexBuffer9** ppVertexBuffer, HANDLE* pSharedHandle);
	HRESULT __stdcall CreateIndexBuffer(THIS_ UINT Length, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool, IDirect3DIndexBuffer9** ppIndexBuffer, HANDLE* pSharedHandle);
	HRESULT __stdcall CreateRenderTarget(THIS_ UINT Width, UINT Height, D3DFORMAT Format, D3DMULTISAMPLE_TYPE MultiSample, DWORD MultisampleQuality, BOOL Lockable, IDirect3DSurface9** ppSurface, HANDLE* pSharedHandle);
	HRESULT __stdcall CreateDepthStencilSurface(THIS_ UINT Width, UINT Height, D3DFORMAT Format, D3DMULTISAMPLE_TYPE MultiSample, DWORD MultisampleQuality, BOOL Discard, IDirect3DSurface9** ppSurface, HANDLE* pSharedHandle);
	HRESULT __stdcall UpdateSurface(THIS_ IDirect3DSurface9* pSourceSurface, CONST RECT* pSourceRect, IDirect3DSurface9* pDestinationSurface, CONST POINT* pDestPoint);
	HRESULT __stdcall UpdateTexture(THIS_ IDirect3DBaseTexture9* pSourceTexture, IDirect3DBaseTexture9* pDestinationTexture);
	HRESULT __stdcall GetRenderTargetData(THIS_ IDirect3DSurface9* pRenderTarget, IDirect3DSurface9* pDestSurface);
	HRESULT __stdcall GetFrontBufferData(THIS_ UINT iSwapChain, IDirect3DSurface9* pDestSurface);
	HRESULT __stdcall StretchRect(THIS_ IDirect3DSurface9* pSourceSurface, CONST RECT* pSourceRect, IDirect3DSurface9* pDestSurface, CONST RECT* pDestRect, D3DTEXTUREFILTERTYPE Filter);
	HRESULT __stdcall ColorFill(THIS_ IDirect3DSurface9* pSurface, CONST RECT* pRect, D3DCOLOR color);
	HRESULT __stdcall CreateOffscreenPlainSurface(THIS_ UINT Width, UINT Height, D3DFORMAT Format, D3DPOOL Pool, IDirect3DSurface9** ppSurface, HANDLE* pSharedHandle);
	HRESULT __stdcall SetRenderTarget(THIS_ DWORD RenderTargetIndex, IDirect3DSurface9* pRenderTarget);
	HRESULT __stdcall GetRenderTarget(THIS_ DWORD RenderTargetIndex, IDirect3DSurface9** ppRenderTarget);
	HRESULT __stdcall SetDepthStencilSurface(THIS_ IDirect3DSurface9* pNewZStencil);
	HRESULT __stdcall GetDepthStencilSurface(THIS_ IDirect3DSurface9** ppZStencilSurface);
	HRESULT __stdcall BeginScene(THIS);
	HRESULT __stdcall EndScene(THIS);
	HRESULT __stdcall Clear(THIS_ DWORD Count, CONST D3DRECT* pRects, DWORD Flags, D3DCOLOR Color, float Z, DWORD Stencil);
	HRESULT __stdcall SetTransform(THIS_ D3DTRANSFORMSTATETYPE State, CONST D3DMATRIX* pMatrix);
	HRESULT __stdcall GetTransform(THIS_ D3DTRANSFORMSTATETYPE State, D3DMATRIX* pMatrix);
	HRESULT __stdcall MultiplyTransform(THIS_ D3DTRANSFORMSTATETYPE type, CONST D3DMATRIX* matrix);
	HRESULT __stdcall SetViewport(THIS_ CONST D3DVIEWPORT9* pViewport);
	HRESULT __stdcall GetViewport(THIS_ D3DVIEWPORT9* pViewport);
	HRESULT __stdcall SetMaterial(THIS_ CONST D3DMATERIAL9* pMaterial);
	HRESULT __stdcall GetMaterial(THIS_ D3DMATERIAL9* pMaterial);
	HRESULT __stdcall SetLight(THIS_ DWORD Index, CONST D3DLIGHT9* light);
	HRESULT __stdcall GetLight(THIS_ DWORD Index, D3DLIGHT9* light);
	HRESULT __stdcall LightEnable(THIS_ DWORD Index, BOOL Enable);
	HRESULT __stdcall GetLightEnable(THIS_ DWORD Index, BOOL* pEnable);
	HRESULT __stdcall SetClipPlane(THIS_ DWORD Index, CONST float* pPlane);
	HRESULT __stdcall GetClipPlane(THIS_ DWORD Index, float* pPlane);
	HRESULT __stdcall SetRenderState(THIS_ D3DRENDERSTATETYPE State, DWORD Value);
	HRESULT __stdcall GetRenderState(THIS_ D3DRENDERSTATETYPE State, DWORD* pValue);
	HRESULT __stdcall CreateStateBlock(THIS_ D3DSTATEBLOCKTYPE Type, IDirect3DStateBlock9** ppSB);
	HRESULT __stdcall BeginStateBlock(THIS);
	HRESULT __stdcall EndStateBlock(THIS_ IDirect3DStateBlock9** ppSB);
	HRESULT __stdcall SetClipStatus(THIS_ CONST D3DCLIPSTATUS9* pClipStatus);
	HRESULT __stdcall GetClipStatus(THIS_ D3DCLIPSTATUS9* pClipStatus);
	HRESULT __stdcall GetTexture(THIS_ DWORD Stage, IDirect3DBaseTexture9** ppTexture);
	HRESULT __stdcall SetTexture(THIS_ DWORD Stage, IDirect3DBaseTexture9* pTexture);
	HRESULT __stdcall GetTextureStageState(THIS_ DWORD Stage, D3DTEXTURESTAGESTATETYPE Type, DWORD* pValue);
	HRESULT __stdcall SetTextureStageState(THIS_ DWORD Stage, D3DTEXTURESTAGESTATETYPE Type, DWORD Value);
	HRESULT __stdcall GetSamplerState(THIS_ DWORD Sampler, D3DSAMPLERSTATETYPE Type, DWORD* pValue);
	HRESULT __stdcall SetSamplerState(THIS_ DWORD Sampler, D3DSAMPLERSTATETYPE Type, DWORD Value);
	HRESULT __stdcall ValidateDevice(THIS_ DWORD* pNumPasses);
	HRESULT __stdcall SetPaletteEntries(THIS_ UINT PaletteNumber, CONST PALETTEENTRY* pEntries);
	HRESULT __stdcall GetPaletteEntries(THIS_ UINT PaletteNumber, PALETTEENTRY* pEntries);
	HRESULT __stdcall SetCurrentTexturePalette(THIS_ UINT PaletteNumber);
	HRESULT __stdcall GetCurrentTexturePalette(THIS_ UINT *PaletteNumber);
	HRESULT __stdcall SetScissorRect(THIS_ CONST RECT* pRect);
	HRESULT __stdcall GetScissorRect(THIS_ RECT* pRect);
	HRESULT __stdcall SetSoftwareVertexProcessing(THIS_ BOOL bSoftware);
	BOOL __stdcall GetSoftwareVertexProcessing(THIS);
	HRESULT __stdcall SetNPatchMode(THIS_ float nSegments);
	float __stdcall GetNPatchMode(THIS);
	HRESULT __stdcall DrawPrimitive(THIS_ D3DPRIMITIVETYPE PrimitiveType, UINT StartVertex, UINT PrimitiveCount);
	HRESULT __stdcall DrawIndexedPrimitive(THIS_ D3DPRIMITIVETYPE type, INT BaseVertexIndex, UINT MinVertexIndex, UINT NumVertices, UINT startIndex, UINT primCount);
	HRESULT __stdcall DrawPrimitiveUP(THIS_ D3DPRIMITIVETYPE PrimitiveType, UINT PrimitiveCount, CONST void* pVertexStreamZeroData, UINT VertexStreamZeroStride);
	HRESULT __stdcall DrawIndexedPrimitiveUP(THIS_ D3DPRIMITIVETYPE PrimitiveType, UINT MinVertexIndex, UINT NumVertices, UINT PrimitiveCount, CONST void* pIndexData, D3DFORMAT IndexDataFormat, CONST void* pVertexStreamZeroData, UINT VertexStreamZeroStride);
	HRESULT __stdcall ProcessVertices(THIS_ UINT SrcStartIndex, UINT DestIndex, UINT VertexCount, IDirect3DVertexBuffer9* pDestBuffer, IDirect3DVertexDeclaration9* pVertexDecl, DWORD Flags);
	HRESULT __stdcall CreateVertexDeclaration(THIS_ CONST D3DVERTEXELEMENT9* pVertexElements, IDirect3DVertexDeclaration9** ppDecl);
	HRESULT __stdcall SetVertexDeclaration(THIS_ IDirect3DVertexDeclaration9* pDecl);
	HRESULT __stdcall GetVertexDeclaration(THIS_ IDirect3DVertexDeclaration9** ppDecl);
	HRESULT __stdcall SetFVF(THIS_ DWORD FVF);
	HRESULT __stdcall GetFVF(THIS_ DWORD* pFVF);
	HRESULT __stdcall CreateVertexShader(THIS_ CONST DWORD* pFunction, IDirect3DVertexShader9** ppShader);
	HRESULT __stdcall SetVertexShader(THIS_ IDirect3DVertexShader9* pShader);
	HRESULT __stdcall GetVertexShader(THIS_ IDirect3DVertexShader9** ppShader);
	HRESULT __stdcall SetVertexShaderConstantF(THIS_ UINT StartRegister, CONST float* pConstantData, UINT Vector4fCount);
	HRESULT __stdcall GetVertexShaderConstantF(THIS_ UINT StartRegister, float* pConstantData, UINT Vector4fCount);
	HRESULT __stdcall SetVertexShaderConstantI(THIS_ UINT StartRegister, CONST int* pConstantData, UINT Vector4iCount);
	HRESULT __stdcall GetVertexShaderConstantI(THIS_ UINT StartRegister, int* pConstantData, UINT Vector4iCount);
	HRESULT __stdcall SetVertexShaderConstantB(THIS_ UINT StartRegister, CONST BOOL* pConstantData, UINT  BoolCount);
	HRESULT __stdcall GetVertexShaderConstantB(THIS_ UINT StartRegister, BOOL* pConstantData, UINT BoolCount);
	HRESULT __stdcall SetStreamSource(THIS_ UINT StreamNumber, IDirect3DVertexBuffer9* pStreamData, UINT OffsetInBytes, UINT Stride);
	HRESULT __stdcall GetStreamSource(THIS_ UINT StreamNumber, IDirect3DVertexBuffer9** ppStreamData, UINT* pOffsetInBytes, UINT* pStride);
	HRESULT __stdcall SetStreamSourceFreq(THIS_ UINT StreamNumber, UINT Setting);
	HRESULT __stdcall GetStreamSourceFreq(THIS_ UINT StreamNumber, UINT* pSetting);
	HRESULT __stdcall SetIndices(THIS_ IDirect3DIndexBuffer9* pIndexData);
	HRESULT __stdcall GetIndices(THIS_ IDirect3DIndexBuffer9** ppIndexData);
	HRESULT __stdcall CreatePixelShader(THIS_ CONST DWORD* pFunction, IDirect3DPixelShader9** ppShader);
	HRESULT __stdcall SetPixelShader(THIS_ IDirect3DPixelShader9* pShader);
	HRESULT __stdcall GetPixelShader(THIS_ IDirect3DPixelShader9** ppShader);
	HRESULT __stdcall SetPixelShaderConstantF(THIS_ UINT StartRegister, CONST float* pConstantData, UINT Vector4fCount);
	HRESULT __stdcall GetPixelShaderConstantF(THIS_ UINT StartRegister, float* pConstantData, UINT Vector4fCount);
	HRESULT __stdcall SetPixelShaderConstantI(THIS_ UINT StartRegister, CONST int* pConstantData, UINT Vector4iCount);
	HRESULT __stdcall GetPixelShaderConstantI(THIS_ UINT StartRegister, int* pConstantData, UINT Vector4iCount);
	HRESULT __stdcall SetPixelShaderConstantB(THIS_ UINT StartRegister, CONST BOOL* pConstantData, UINT  BoolCount);
	HRESULT __stdcall GetPixelShaderConstantB(THIS_ UINT StartRegister, BOOL* pConstantData, UINT BoolCount);
	HRESULT __stdcall DrawRectPatch(THIS_ UINT Handle, CONST float* pNumSegs, CONST D3DRECTPATCH_INFO* pRectPatchInfo);
	HRESULT __stdcall DrawTriPatch(THIS_ UINT Handle, CONST float* pNumSegs, CONST D3DTRIPATCH_INFO* pTriPatchInfo);
	HRESULT __stdcall DeletePatch(THIS_ UINT Handle);
	HRESULT __stdcall CreateQuery(THIS_ D3DQUERYTYPE Type, IDirect3DQuery9** ppQuery);
};


#endif;