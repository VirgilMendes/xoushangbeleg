#include "Vue/GameStates/Combat.h"
#include "Vue/Combat/CarteGUI.h"
#include "Vue/GameStates/NouvellePartie.h"
#include "Vue/GameStates/RejoindrePartie.h"
#include <thread>
#include <SFML/Network.hpp>
#include "Controleur/Navigation.h"

int main()
{
	//int client;
	//std::cin >> client; std::cout << std::endl;

	Controleur::Fenetre::initialiser();
	Controleur::Fenetre::run();

	/*sf::TcpSocket socket;
	sf::Socket::Status status = socket.connect("127.0.0.1", 53000);
	if (status != sf::Socket::Done)
	{
		std::cout << "Impossible de se connecter au serveur" << std::endl;
	}
	
	if (client == 1)
	{
		std::cout << "Client 1" << std::endl;
		char deplacement[255];
		strcpy(deplacement, fenetre.deplacerUnite("Archer1", Modele::Vecteur2<int>(0, 0)).c_str());

		// socket TCP:
		if (socket.send(deplacement, 255) != sf::Socket::Done)
		{
			std::cout << "Impossible d'envoyer les données" << std::endl;
		}

		fenetre.run();
	}
	else
	{
		std::cout << "Client 2" << std::endl;
		char deplacement[255];
		std::size_t recus;

		if (socket.receive(deplacement, 255, recus) != sf::Socket::Done)
		{
			std::cout << "impossible de recevoir des données du premier client" << std::endl;
		}
		std::cout << recus << " octes reçu depuis client 1 : " << deplacement << std::endl;

		fenetre.decodeXml(deplacement);*/
	/*}*/
	
}
