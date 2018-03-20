#pragma once

#include "../../lib/SFML-2.4.2/include/SFML/Network.hpp"
#include <iostream>

namespace Controleur
{
	class Reseaux
	{
	public:
		static void connecterHote()
		{
			connecter();
			envoyerDonneesBloquant("H");
			if(recevoirDonneesBloquant()!="H")
				std::cout << "erreur connection" << std::endl;
		}

		static void connecterInvitee()
		{
			connecter();
			envoyerDonneesBloquant("I");
			if (recevoirDonneesBloquant() != "I")
				std::cout << "erreur connection" << std::endl;
		}

		static void envoyerDonneesBloquant(std::string donnees)
		{
			sf::Packet paquet;
			paquet << donnees;
			if (socket_.send(paquet) != sf::Socket::Done)
			{
				std::cout << "Impossible d'envoyer les donnees" << std::endl;
			}
		}

		static  std::string recevoirDonneesBloquant()
		{
			sf::Packet paquet;
			
			if (socket_.receive(paquet) != sf::Socket::Done)
			{
				std::cout << "Impossible de recevoir les donnees" << std::endl;
			}
			std::string donnees;      
			paquet >> donnees;
			return donnees;
		}

	private:

		static void connecter()
		{
			sf::Socket::Status status = socket_.connect("127.0.0.1", 53000);
			if (status != sf::Socket::Done)
			{
				std::cout << "Impossible de se connecter au serveur" << std::endl;
			}
		}

		static sf::TcpSocket socket_;
	};


}
