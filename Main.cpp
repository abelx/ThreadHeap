#include "CTheadHeap.h"
#include "CMemoryPool.h"
#include <Windows.h>
#include "TEST.h"

int main()
{
		//TEST_HEAP();
	//TEST_HEAPWITHDEPOSITOR();
	TEST_THREAD_DEPOSITHEAP();
	//TEST_THREAD_MESSAGEHEAP();
	return 0;
}
