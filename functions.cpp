#include "functions.h"
#include "consts.h"
const int HEAP_MEMORY_UNIT = 8;

int g_DivUp(int numa, int numb)
{
	return (numa-1)/numb + 1;
}

int g_Align(int a, int b)
{
	return g_DivUp(a, b) * b;
}