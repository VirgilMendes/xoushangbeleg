#include "Vue/GameStates/VueCombat.h"
#include "Vue/GameStates/MenuPrincipal.h"
#include "Vue/GameStates/NouvellePartie.h"
#include "Vue/GameStates/RejoindrePartie.h"
#include <thread>
#include <SFML/Network.hpp>
#include "Controleur/Navigation.h"

int main()
{

	//Controleur::Fenetre fenetre;
	//fenetre.run();

	sf::TcpSocket socket;
	sf::Socket::Status status = socket.connect("127.0.0.1", 53000);
	if (status != sf::Socket::Done)
	{
		std::cout << "Impossible de se connecter au serveur" << std::endl;
	}


	char data[100] = "test";

	// socket TCP:
	if (socket.send(data, 100) != sf::Socket::Done)
	{
		std::cout << "Impossible d'envoyer les données" << std::endl;
	}
}
