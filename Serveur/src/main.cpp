#include "pugixml.hpp"
#include <iostream>
#include "SFML/Network.hpp"


static void envoyerDonneesBloquant(std::string donnees, sf::TcpSocket& socket)
{
	sf::Packet paquet;
	paquet << donnees;
	if (socket.send(paquet) != sf::Socket::Done)
	{
		std::cout << "Impossible d'envoyer les donnees" << std::endl;
	}
}

static  std::string recevoirDonneesBloquant(sf::TcpSocket& socket)
{
	sf::Packet paquet;

	if (socket.receive(paquet) != sf::Socket::Done)
	{
		std::cout << "Impossible de recevoir les donnees" << std::endl;
		return "";
	}
	std::string donnees;
	paquet >> donnees;
	return donnees;
}

int main()
	{

	std::cout << "Lancement du Serveur de Xoushangbeleg" << std::endl;

	sf::TcpListener listener;

	// lie l'écouteur à un port
	if (listener.listen(53000) != sf::Socket::Done)
	{
		std::cout << "impossible de se lier au port" << std::endl;
	}


	{
		sf::TcpSocket hote;
		if (listener.accept(hote) != sf::Socket::Done)
		{
		std::cout << "impossible d'obtenir l'hote" << std::endl;
		}
	
	
		std::cout << "Connection de l'hote" << std::endl;
	
		std::string messageConnection(recevoirDonneesBloquant(hote));

		if (std::string(messageConnection) != "H")
		{
			std::cout << "Il n'y a pas d'hote à cette partie" << std::endl;
		}

		envoyerDonneesBloquant("H", hote);

	}

	{
		sf::TcpSocket invite;
		if (listener.accept(invite) != sf::Socket::Done)
		{
			std::cout << "impossible d'obtenir l'hote" << std::endl;
		}


		std::cout << "Connection de l'invite" << std::endl;

		std::string messageConnection(recevoirDonneesBloquant(invite));

		if (std::string(messageConnection) != "I")
		{
			std::cout << "Il y a déja un hote à cette partie" << std::endl;
		}

		envoyerDonneesBloquant("I", invite);

	}
	/*
	char deplacement[255];
	std::size_t recus;

	// socket TCP:
	if (client1.receive(deplacement, 255, recus) != sf::Socket::Done)
	{
		std::cout << "impossible de recevoir des données du premier client" << std::endl;
	}
	std::cout << recus << " octes reçu depuis client 1 : " << deplacement << std::endl;

	sf::TcpSocket client2;
	if (listener.accept(client2) != sf::Socket::Done)
	{
		std::cout << "impossible d'obtenir le second client" << std::endl;
	}

	// utilisez la socket "client" pour communiquer avec le client connecté,
	// et continuez à attendre de nouvelles connexions avec l'écouteur
	
	if (client2.send(deplacement, 255) != sf::Socket::Done)
	{
		std::cout << "impossible d'enviyer les données au second client" << std::endl;
	}
	*/
}
