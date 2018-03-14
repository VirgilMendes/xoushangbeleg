#include "Vue/GameStates/Grille.h"
#include "Vue/GameStates/NouvellePartie.h"
#include "Vue/GameStates/RejoindrePartie.h"
#include <thread>
#include <SFML/Network.hpp>
#include "Controleur/Navigation.h"

int main()
{
	//int client;
	//std::cin >> client; std::cout << std::endl;

	std::string testXml = "<paquet><initialisation><carte><nom/></carte><unites><unite><nomUnite>Archer1555< / nomUnite><classe>Archer< / classe><equipe>Bleu< / equipe><position><x>50< / x><x>60< / x>< / position>< / unite><unite><nomUnite>Soldat76< / nomUnite><classe>Soldat< / classe><equipe>Bleu< / equipe><position><x>8< / x><x>7< / x>< / position>< / unite><unite><nomUnite>Tank166< / nomUnite><classe>Tank< / classe><equipe>Rouge< / equipe><position><x>10< / x><x>12< / x>< / position>< / unite>< / unites></initialisation>< / paquet>";
	Controleur::Fenetre::decodeXml(testXml);

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
			std::cout << "Impossible d'envoyer les donnees" << std::endl;
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
			std::cout << "impossible de recevoir des donnees du premier client" << std::endl;
		}
		std::cout << recus << " octes recu depuis client 1 : " << deplacement << std::endl;

		fenetre.decodeXml(deplacement);*/
	/*}*/
	
}
