#pragma once

#include "../../lib/SFML-2.4.2/include/SFML/Network.hpp"
#include <iostream>

namespace Controleur
{
	class Reseaux
	{
	public:
		static void connecter()
		{
			
			sf::Socket::Status status = socket_.connect("127.0.0.1", 53000);
			if (status != sf::Socket::Done)
			{
				std::cout << "Impossible de se connecter au serveur" << std::endl;
			}


		}

	private:
		static sf::TcpSocket socket_;
	};


}
