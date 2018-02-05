#include "VueCombat.hpp"
#include "MenuPrincipal.cpp"
#include <thread>

int main()
	{
		std::thread vueCombat(vueCombatRun);
		std::thread menuPrincipal(MenuPrincipalRun);
		
		vueCombat.join();
		menuPrincipal.join();

	}
