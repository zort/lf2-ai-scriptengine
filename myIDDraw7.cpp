#include "StdAfx.h"
#include <varargs.h>

myIDDraw7::myIDDraw7(LPDIRECTDRAW7 pOriginal)
{
	m_pIDDraw = pOriginal;
}


myIDDraw7::~myIDDraw7(void)
{
}


HRESULT __stdcall myIDDraw7::QueryInterface (REFIID a, LPVOID FAR * b)
{
	
	char *iid = "?";
	if (a == IID_IDirectDraw) iid = "IID_IDirectDraw";
	if (a == IID_IDirectDraw2) iid = "IID_IDirectDraw2";
	if (a == IID_IDirectDraw4) iid = "IID_IDirectDraw4";
	if (a == IID_IDirectDraw7) iid = "IID_IDirectDraw7";


	*b = NULL;

	// call this to increase AddRef at original object
	// and to check if such an interface is there

	HRESULT hRes = m_pIDDraw->QueryInterface(a, b); 

	if (hRes == NOERROR) // if OK, send our "fake" address
	{
		if (a == IID_IDirectDraw7)
			*b = this;
	}
	
	return hRes;
}


ULONG   __stdcall myIDDraw7::AddRef(void)
{
	return(m_pIDDraw->AddRef());
}


ULONG   __stdcall myIDDraw7::Release(void)
{
	
	// call original routine
	ULONG count = m_pIDDraw->Release();
	


    // in case no further Ref is there, the Original Object has deleted itself
	// so do we here
	if (count == 0) 
	{
		m_pIDDraw = NULL;		
		delete(this); 
	}

	return(count);
}


HRESULT  __stdcall myIDDraw7::Compact(void)
{

	return(m_pIDDraw->Compact());
}


HRESULT  __stdcall myIDDraw7::CreateClipper(DWORD a, LPDIRECTDRAWCLIPPER FAR* b, IUnknown FAR* c)
{

	return(m_pIDDraw->CreateClipper(a, b, c));
}


HRESULT  __stdcall myIDDraw7::CreatePalette(DWORD a, LPPALETTEENTRY b, LPDIRECTDRAWPALETTE FAR* c, IUnknown FAR* d)
{
	HRESULT r = m_pIDDraw->CreatePalette(a, b, c, d);
	*c = new myIDDrawPalette(*c);
	return r;
}


HRESULT  __stdcall myIDDraw7::CreateSurface(LPDDSURFACEDESC2 a, LPDIRECTDRAWSURFACE7 FAR* b, IUnknown FAR* c)
{
	HRESULT r = m_pIDDraw->CreateSurface(a, b, c);

	return r;
}


HRESULT  __stdcall myIDDraw7::DuplicateSurface(LPDIRECTDRAWSURFACE7 a, LPDIRECTDRAWSURFACE7 FAR* b)
{
	
	return(m_pIDDraw->DuplicateSurface(a, b));
}


HRESULT  __stdcall myIDDraw7::EnumDisplayModes(DWORD a, LPDDSURFACEDESC2 b, LPVOID c, LPDDENUMMODESCALLBACK2 d)
{
	
	return(m_pIDDraw->EnumDisplayModes(a, b, c, d));
}


HRESULT  __stdcall myIDDraw7::EnumSurfaces(DWORD a, LPDDSURFACEDESC2 b, LPVOID c, LPDDENUMSURFACESCALLBACK7 d)
{
	
	return(m_pIDDraw->EnumSurfaces(a, b, c, d));
}


HRESULT  __stdcall myIDDraw7::FlipToGDISurface(void)
{
	
	return(m_pIDDraw->FlipToGDISurface());
}


HRESULT  __stdcall myIDDraw7::GetCaps(LPDDCAPS a, LPDDCAPS b)
{
	
	return(m_pIDDraw->GetCaps(a, b));
}


HRESULT  __stdcall myIDDraw7::GetDisplayMode(LPDDSURFACEDESC2 a)
{
	
	return(m_pIDDraw->GetDisplayMode(a));
}


HRESULT  __stdcall myIDDraw7::GetFourCCCodes(LPDWORD a, LPDWORD b)
{
	
	return(m_pIDDraw->GetFourCCCodes(a, b));
}


HRESULT  __stdcall myIDDraw7::GetGDISurface(LPDIRECTDRAWSURFACE7 FAR * a)
{
	
	return(m_pIDDraw->GetGDISurface(a));
}


HRESULT  __stdcall myIDDraw7::GetMonitorFrequency(LPDWORD a)
{

	return(m_pIDDraw->GetMonitorFrequency(a));
}


HRESULT  __stdcall myIDDraw7::GetScanLine(LPDWORD a)
{
	
	return(m_pIDDraw->GetScanLine(a));
}


HRESULT  __stdcall myIDDraw7::GetVerticalBlankStatus(LPBOOL a)
{
	
	return(m_pIDDraw->GetVerticalBlankStatus(a));
}


HRESULT  __stdcall myIDDraw7::Initialize(GUID FAR* a)
{
	
	return(m_pIDDraw->Initialize(a));
}


HRESULT  __stdcall myIDDraw7::RestoreDisplayMode(void)
{
	
	return(m_pIDDraw->RestoreDisplayMode());
}


HRESULT  __stdcall myIDDraw7::SetCooperativeLevel(HWND a, DWORD b)
{

	HRESULT h = m_pIDDraw->SetCooperativeLevel(a, b); 

	
	
	return(h);
}


HRESULT  __stdcall myIDDraw7::SetDisplayMode(DWORD a, DWORD b, DWORD c, DWORD d, DWORD e)
{
	HRESULT h = m_pIDDraw->SetDisplayMode(a, b, c, d, e);


	
	return(h); 
}


HRESULT  __stdcall myIDDraw7::WaitForVerticalBlank(DWORD a, HANDLE b)
{

	return(m_pIDDraw->WaitForVerticalBlank(a, b));
}


HRESULT  __stdcall myIDDraw7::GetAvailableVidMem(LPDDSCAPS2 a, LPDWORD b, LPDWORD c)
{

	return(m_pIDDraw->GetAvailableVidMem(a, b, c));
}


HRESULT  __stdcall myIDDraw7::GetSurfaceFromDC(HDC a, LPDIRECTDRAWSURFACE7 * b)
{
	
	return(m_pIDDraw->GetSurfaceFromDC(a, b));
}


HRESULT  __stdcall myIDDraw7::RestoreAllSurfaces(void)
{
	
	return(m_pIDDraw->RestoreAllSurfaces());
}


HRESULT  __stdcall myIDDraw7::TestCooperativeLevel(void)
{

	return(m_pIDDraw->TestCooperativeLevel());
}


HRESULT  __stdcall myIDDraw7::GetDeviceIdentifier(LPDDDEVICEIDENTIFIER2 a, DWORD b)
{
	
	return(m_pIDDraw->GetDeviceIdentifier(a, b));
}


HRESULT  __stdcall myIDDraw7::StartModeTest(LPSIZE a, DWORD b, DWORD c)
{
	
	return(m_pIDDraw->StartModeTest(a, b, c));
}


HRESULT  __stdcall myIDDraw7::EvaluateMode(DWORD a, DWORD * b)
{
	
	return(m_pIDDraw->EvaluateMode(a, b));
}
