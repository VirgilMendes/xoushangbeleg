#include "VueCombat.hpp"
#include "MenuPrincipal.cpp"
#include "NouvellePartie.cpp"
#include <thread>

int main()
	{
		std::thread vueCombat(vueCombatRun);
		std::thread menuPrincipal(MenuPrincipalRun);
		std::thread menuPrincipal(NouvellePartieRun);
		
		vueCombat.join();
		menuPrincipal.join();

	}
