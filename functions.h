#include <process.h>
#include <Windows.h>

int g_DivUp(int numa, int numb);
int g_Align(int a, int b);
#define MSG_MY_ALLOC WM_USER + 100
#define	MSG_MY_FREE WM_USER + 101

DWORD64 GetTimeTick();

int ComputeBit2Index(int flag);
bool SetBit(int *source, int pos);
int ClearBits(int source, int pos);