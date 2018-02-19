#include "Vue/VueCombat.h"
#include "Vue/MenuPrincipal.h"
#include "Vue/NouvellePartie.h"
#include "Vue/RejoindrePartie.h"
#include <thread>
#include <SFML/Network.hpp>
#include "Controleur/Navigation.h"

int main()
{

	Controleur::Fenetre fenetre;
	fenetre.run();

	sf::TcpSocket socket;
	sf::Socket::Status status = socket.connect("127.0.0.1", 53000);
	if (status != sf::Socket::Done)
	{
		// erreur...
	}


	char data[100] = "test";

	// socket TCP:
	if (socket.send(data, 100) != sf::Socket::Done)
	{
		// erreur...
	}

	
}