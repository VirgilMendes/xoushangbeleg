#include "Vue/GameStates/VueCombat.h"
#include "Vue/GameStates/MenuPrincipal.h"
#include "Vue/GameStates/NouvellePartie.h"
#include "Vue/GameStates/RejoindrePartie.h"
#include <thread>
#include <SFML/Network.hpp>
#include "Controleur/Navigation.h"

int main()
{
	int client;
	std::cin >> client; std::cout << std::endl;

	//Controleur::Fenetre fenetre;
	//fenetre.run();

	sf::TcpSocket socket;
	sf::Socket::Status status = socket.connect("127.0.0.1", 53000);
	if (status != sf::Socket::Done)
	{
		std::cout << "Impossible de se connecter au serveur" << std::endl;
	}
	if (client == 1)
	{
		std::cout << "Client 1" << std::endl;
		char parametre[100] = "Chunchunmaru !!!";

		// socket TCP:
		if (socket.send(parametre, 100) != sf::Socket::Done)
		{
			std::cout << "Impossible d'envoyer les données" << std::endl;
		}
	}
	else
	{
		std::cout << "Client 2" << std::endl;
		char parametre[100];
		std::size_t received;

		if (socket.receive(parametre, 100, received) != sf::Socket::Done)
		{
			std::cout << "impossible de recevoir des données du premier client" << std::endl;
		}
		std::cout << "Received from 1 " << received << " " << parametre << " bytes" << std::endl;
	}
}
