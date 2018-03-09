#include "PlacementUnite.h"
#include <iostream>
#include "../../Modele/Unite/Unite.h"
#include "../../Controleur/Navigation.h"

namespace Vue {

	PlacementUnite::PlacementUnite(Modele::Equipe equipe, int nbUniteRestantes)
	{
		this->nbUniteRestantes = nbUniteRestantes;

		if (!ressource.loadFromFile("ressources/sprite/menu+figures.png"))
		{
			std::cout << "erreur chargement menu+figures.png dans placement" << std::endl;
		}
		teteTank.setTexture(ressource);
		teteTank.scale(0.5f, 0.5f);
		teteTank.setPosition(62, 15 + 522);

		teteSoldat.setTexture(ressource);
		teteSoldat.scale(0.5f, 0.5f);
		teteSoldat.setPosition(128+62*2, 15 + 522);

		teteArcher.setTexture(ressource);
		teteArcher.scale(0.5f, 0.5f);
		teteArcher.setPosition(128*2+62*3, 15 + 522);

		if (equipe == Modele::Equipe::Bleu)
		{

			teteTank.setTextureRect(sf::IntRect(256, 0, 256, 256));
			teteSoldat.setTextureRect(sf::IntRect(256, 256, 256, 256));
			teteArcher.setTextureRect(sf::IntRect(256, 512, 256, 256));
			
		}
		else
		{
			teteTank.setTextureRect(sf::IntRect(0, 0, 256, 256));
			teteSoldat.setTextureRect(sf::IntRect(0, 256, 256, 256));
			teteArcher.setTextureRect(sf::IntRect(0, 512, 256, 256));
		}
		fond.setTexture(ressource);
		fond.setTextureRect(sf::IntRect(0, 256 + 512, 256, 256));
		fond.scale(2.55f, 0.7f);
		fond.setPosition(0, 522);


		if (!font.loadFromFile("ressources/VCR_OSD_MONO_1.001.ttf"))
		{
			std::cout << "error font" << std::endl;
		}

		classeText[0].setString("Tank");
		classeText[1].setString("Soldat");
		classeText[2].setString("Archer");

		for (int i = 0; i < 3; i++)
		{
			classeText[i].setPosition((i+1)*75+i*128, 668);
			classeText[i].setFont(font);
			classeText[i].setCharacterSize(20);
			classeText[i].setFillColor(sf::Color::White);
		}
	}

	void PlacementUnite::afficher()
	{
		sf::RenderStates states;

		sf::RenderWindow* target = Controleur::Fenetre::fenetre;


		
		target->draw(fond, states);
		target->draw(teteTank, states);
		target->draw(teteArcher, states);
		target->draw(teteSoldat, states);

		for (int i = 0; i < 3; i++)
		{
			target->draw(classeText[i], states);
		}

	}

	int PlacementUnite::getChoix()
	{
		return choix;
	}

	void PlacementUnite::setChoix(int choix)
	{
		this->choix = choix;
	}

	int PlacementUnite::getNbUniteRestantes()
	{
		return nbUniteRestantes;
	}
	void PlacementUnite::setNbUniteRestantes(int nbUniteRestantes)
	{
		this->nbUniteRestantes = nbUniteRestantes;
	}

	void PlacementUnite::handleEvent() 
	{

	}

	void PlacementUnite::update()
	{

	}
}