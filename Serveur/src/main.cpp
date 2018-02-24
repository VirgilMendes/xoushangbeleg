#include "pugixml.hpp"
#include <iostream>
#include "SFML/Network.hpp"

int main()
	{

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
	sf::TcpSocket client2;
	if (listener.accept(client2) != sf::Socket::Done)
	{
		std::cout << "impossible d'obtenir le second client" << std::endl;
	}

	// utilisez la socket "client" pour communiquer avec le client connecté,
	// et continuez à attendre de nouvelles connexions avec l'écouteur
	
	char data[100];
	std::size_t received;

	// socket TCP:
	if (client1.receive(data, 100, received) != sf::Socket::Done)
	{
		std::cout << "impossible de recevoir des données du premier client" << std::endl;
	}
	std::cout << "Received from 1 " << received << " "<< data <<" bytes" << std::endl;

	if (client2.receive(data, 100, received) != sf::Socket::Done)
	{
		std::cout << "impossible de recevoir des données du second client" << std::endl;
	}
	std::cout << "Received from 2 " << received << " " << data << " bytes" << std::endl;


}
