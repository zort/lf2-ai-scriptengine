#include "StdAfx.h"
#include <varargs.h>

myIDDrawPalette::myIDDrawPalette(LPDIRECTDRAWPALETTE pOriginal)
{
	m_pIDDrawPalette = pOriginal;
}


myIDDrawPalette::~myIDDrawPalette(void)
{
}


HRESULT __stdcall myIDDrawPalette::QueryInterface (REFIID, LPVOID FAR * b)
{
	
	*b = NULL;

	return E_NOTIMPL;
}


ULONG   __stdcall myIDDrawPalette::AddRef(void)
{
	return(m_pIDDrawPalette->AddRef());
}


ULONG   __stdcall myIDDrawPalette::Release(void)
{

	
	// call original routine
	ULONG count = m_pIDDrawPalette->Release();
	

    // in case no further Ref is there, the Original Object has deleted itself
	// so do we here
	if (count == 0) 
	{
		m_pIDDrawPalette = NULL;		
		delete(this); 
	}

	return(count);
}



HRESULT  __stdcall myIDDrawPalette::GetCaps(LPDWORD a)
{
	return m_pIDDrawPalette->GetCaps(a);
}



HRESULT  __stdcall myIDDrawPalette::GetEntries(DWORD a,DWORD b,DWORD c,LPPALETTEENTRY d)
{
	return m_pIDDrawPalette->GetEntries(a,b,c,d);
}



HRESULT  __stdcall myIDDrawPalette::Initialize(LPDIRECTDRAW a, DWORD b, LPPALETTEENTRY c)
{
	return m_pIDDrawPalette->Initialize(((myIDDrawInterface*)a)->getAsDirectDraw(),b,c);
}



HRESULT  __stdcall myIDDrawPalette::SetEntries(DWORD a,DWORD b,DWORD c,LPPALETTEENTRY d)
{
	unsigned int i, j;
	char temp[128], temp2[32];
	j = 0;
	temp[0] = 0;
	for (i = b; i < c; i++)
	{
		sprintf(temp2,"%06X ", ((int*)d)[i-b]);
		strcat(temp, temp2);
		j++;
		if (j == 16)
		{
			temp[0] = 0;
			j = 0;
		}
	}
	return m_pIDDrawPalette->SetEntries(a,b,c,d);
}