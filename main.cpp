#include "stdafx.h"
#include "SFLD.h"
#include "StateManager.h"
#include "BaseState.h"

int main(int argc, char* argv[])
{
	SFLD* sfld = new SFLD();
	sfld->start();
	delete sfld;
	return 0;
}