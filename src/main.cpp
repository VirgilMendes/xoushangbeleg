#include "VueCombat.hpp"
#include "MenuPrincipal.cpp"
#include "NouvellePartie.cpp"
#include <thread>

int main()
	{
		std::thread vueCombat(vueCombatRun);
		std::thread menuPrincipal(MenuPrincipalRun);
		
		vueCombat.join();
		menuPrincipal.join();
		std::thread nouvellePartie(NouvellePartieRun);
		nouvellePartie.join();
	}
