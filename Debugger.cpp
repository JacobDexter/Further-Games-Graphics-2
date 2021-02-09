#include "Debugger.h"

void Debugger::FrameCounter() noexcept
{
	static int x = 0;
	char sz[1024] = { 0 };
	sprintf_s(sz, "The frame number is %d \n", x);
	OutputDebugStringA(sz);
	x++;
}
