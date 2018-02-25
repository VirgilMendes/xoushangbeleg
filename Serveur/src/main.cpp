#include "pugixml.hpp"
#include <iostream>
#include "SFML/Network.hpp"

int main()
	{

	std::cout << "Serveur" << std::endl;

	sf::TcpListener listener;

	// lie l'écouteur à un port
	if (listener.listen(53000) != sf::Socket::Done)
	{
		std::cout << "impossible de se lier au port" << std::endl;
	}

	// accepte une nouvelle connexion
	sf::TcpSocket client1;
	if (listener.accept(client1) != sf::Socket::Done)
	{
		std::cout << "impossible d'obtenir le premier client" << std::endl;
	}

	char parametre[100];
	std::size_t received;

	// socket TCP:
	if (client1.receive(parametre, 100, received) != sf::Socket::Done)
	{
		std::cout << "impossible de recevoir des données du premier client" << std::endl;
	}
	std::cout << "Received from 1 " << received << " " << parametre << " bytes" << std::endl;

	sf::TcpSocket client2;
	if (listener.accept(client2) != sf::Socket::Done)
	{
		std::cout << "impossible d'obtenir le second client" << std::endl;
	}

	// utilisez la socket "client" pour communiquer avec le client connecté,
	// et continuez à attendre de nouvelles connexions avec l'écouteur
	
	if (client2.send(parametre, 100) != sf::Socket::Done)
	{
		std::cout << "impossible d'enviyer les données au second client" << std::endl;
	}
}
