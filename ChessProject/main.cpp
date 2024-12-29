#include "Chess.h"
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
int main() {
	{
		Chess chess;
		chess.play();
	}
	std::cout << _CrtDumpMemoryLeaks();
	return 0;
}