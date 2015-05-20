#include "functions.h"


int g_DivUp(int numa, int numb)
{
	return (numa-1)/numb + 1;
}

int g_Align(int a, int b)
{
	return g_DivUp(a, b) * b;
}

DWORD64 GetTimeTick()
{
	DWORD64 tmp = 0;
	__asm
	{
		RDTSC
		mov dword ptr tmp, eax
		mov dword ptr tmp[4], edx 
	}
	return tmp;
}

int ComputeBit2Index(int flag)
{
	int ret;
	__asm 
	{
		mov eax, flag 
		bsf ebx, eax
		mov ret, ebx
	}
	return ret;
}

bool SetBit(int *source, int pos)
{
	if(pos<0 || pos>31)
		return false;
	
	*source = (*source) | (1<<pos);
	return true;
}

int ClearBits(int source, int pos)
{
	if(pos <= 0)
		return source;
	if(pos > 31)
		return 0;

	return (-1 << pos) & source;
}