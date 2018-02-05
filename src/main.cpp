#include "VueCombat.hpp"
#include "MenuPrincipal.cpp"
#include <thread>

int main()
	{
		std::thread vueCombat(vueCombatRun);
		std::thread MenuPrincipal(MenuPrincipalRun);
		
		vueCombat.join();
	}
