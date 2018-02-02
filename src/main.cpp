#include "VueCombat.hpp"
#include <thread>

int main()
	{
		std::thread vueCombat(vueCombatRun);
		
		
		vueCombat.join();
	}
