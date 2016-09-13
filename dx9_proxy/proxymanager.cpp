#include "stdafx.h"



ProxyManager::ProxyManager()
{
	this->dxmanager = NULL;
	this->device = NULL;
}

ProxyManager::~ProxyManager()
{
	if (this->device)
	{
		//MessageBoxA(NULL, "~ProxyManage>Release Device", "Release MI3dDevice", MB_OK);
		//this->device->Release();
		this->device = NULL;
	}
	if (this->dxmanager)
	{
		//MessageBoxA(NULL, "~ProxyManage>Release Direct3D", "Release MI3d9", MB_OK);
		//this->dxmanager->Release();
		this->dxmanager = NULL;
	}
}

MI3dDevice* ProxyManager::createDeviceFromOriginal(IDirect3DDevice9* dev, MI3d9* d3d)
{
	this->device = new MI3dDevice(dev, d3d);
	return this->device;
}


MI3d9* ProxyManager::createManagerFromOriginal(IDirect3D9* man)
{
	this->dxmanager = new MI3d9(man);
	return this->dxmanager;
}

MI3dDevice* ProxyManager::getDevice()
{
	return this->device;
}

void ProxyManager::setDevice(MI3dDevice* dev)
{
	this->device = dev;
}

MI3d9* ProxyManager::getManager()
{
	return this->dxmanager;
}

void ProxyManager::setManager(MI3d9* manager)
{
	this->dxmanager = manager;
}
