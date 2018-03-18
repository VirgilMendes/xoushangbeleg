#include "PlacementUnite.h"
#include <iostream>
#include "../../Modele/Unite/Unite.h"
#include "../../Controleur/Navigation.h"
#include "../../Controleur/GameStates/PlacementUnite.h"

namespace Vue {

	PlacementUnite::PlacementUnite(Controleur::PlacementUnite* controleur, Modele::Equipe equipe, int nbUniteRestantes): 
		controleur_(controleur), nbUniteRestantes(nbUniteRestantes), choix(1)
	{
		if (!ressource.loadFromFile("ressources/sprite/menu+figures.png"))
		{
			//std::cout << "erreur chargement menu+figures.png dans placement" << std::endl;
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


		teteTank.setTextureRect(sf::IntRect(equipe._to_integral()*256, 0, 256, 256));
		teteSoldat.setTextureRect(sf::IntRect(equipe._to_integral()*256, 256, 256, 256));
		teteArcher.setTextureRect(sf::IntRect(equipe._to_integral()*256, 512, 256, 256));
			
		
		fond.setTexture(ressource);
		fond.setTextureRect(sf::IntRect(0, 3*256, 256, 256));
		fond.scale(2.55f, 0.7f);
		fond.setPosition(0, 522);

		fondUnitesRestantes.setTexture(ressource);
		fondUnitesRestantes.setTextureRect(sf::IntRect(0, 3 * 256, 256, 256));
		fondUnitesRestantes.scale(0.5f, 0.5f);
		fondUnitesRestantes.setPosition(630, 550);

		this->setNbUniteRestantes(nbUniteRestantes);
		textUnitesRestantes.setFont(Controleur::Fenetre::getPoliceParDefaut());
		textUnitesRestantes.setCharacterSize(60);
		textUnitesRestantes.setFillColor(sf::Color::White);
		textUnitesRestantes.setPosition(660,580);

		classeText[0].setString("Tank");
		classeText[1].setString("Soldat");
		classeText[2].setString("Archer");

		for (int i = 0; i < 3; i++)
		{
			classeText[i].setPosition((i+1)*100+i*88, 668);
			classeText[i].setFont(Controleur::Fenetre::getPoliceParDefaut());
			classeText[i].setCharacterSize(20);
			classeText[i].setFillColor(sf::Color::White);
			if (i == choix)
			{
				classeText[i].setFillColor(sf::Color::Yellow);
			}
		}

		curseur.setPosition(sf::Vector2i((choix+1)*30+choix*160,505));
	}

	void PlacementUnite::afficher()
	{
		sf::RenderStates states;

		sf::RenderWindow* target = Controleur::Fenetre::fenetre;
		
		target->draw(fond, states);
		target->draw(fondUnitesRestantes, states);
		target->draw(textUnitesRestantes, states);
		target->draw(teteTank, states);
		target->draw(teteArcher, states);
		target->draw(teteSoldat, states);

		for (int i = 0; i < 3; i++)
		{
			target->draw(classeText[i], states);
		}
		
		curseur.dessiner(*target, states);
	}

	int PlacementUnite::getChoix()
	{
		return choix;
	}

	void PlacementUnite::setChoix(int choix)
	{
		this->choix = choix;
		curseur.setPosition(sf::Vector2i((choix + 1) * 30 + choix * 160, 505));
		for (int i = 0; i < 3; i++)
		{
			classeText[i].setFillColor(sf::Color::White);
			if (i == choix)
			{
				classeText[i].setFillColor(sf::Color::Yellow);
			}
		}
	}

	int PlacementUnite::getNbUniteRestantes()
	{
		return nbUniteRestantes;
	}
	void PlacementUnite::setNbUniteRestantes(int nbUniteRestantes)
	{
		this->nbUniteRestantes = nbUniteRestantes;
		textUnitesRestantes.setString("x"+ std::to_string(nbUniteRestantes));
	}

	void PlacementUnite::handleEvent() 
	{
		sf::Event event;
		while (Controleur::Fenetre::fenetre->pollEvent(event))
		{
			switch (event.type)
			{

			case sf::Event::Closed:
				Controleur::Fenetre::fenetre->close();
			case sf::Event::KeyPressed:
				switch (event.key.code)
				{
				case sf::Keyboard::Z: case sf::Keyboard::Up:
					controleur_->enclencherActionDeplacement(Controleur::ActionDeplacement::Bas);
					break;
				case sf::Keyboard::D: case sf::Keyboard::Right:
					controleur_->enclencherActionDeplacement(Controleur::ActionDeplacement::Droite);
					break;
				case sf::Keyboard::S: case sf::Keyboard::Down:
					controleur_->enclencherActionDeplacement(Controleur::ActionDeplacement::Haut);
					break;
				case sf::Keyboard::Q: case sf::Keyboard::Left:
					controleur_->enclencherActionDeplacement(Controleur::ActionDeplacement::Gauche);
					break;
				case sf::Keyboard::K: case sf::Keyboard::Return:
					controleur_->enclencherActionValidation();
					break;
				case sf::Keyboard::Escape:
					Controleur::Fenetre::fenetre->close();
					break;
				default: break;
				}
			}
		}
	}

	void PlacementUnite::update()
	{
	}
}