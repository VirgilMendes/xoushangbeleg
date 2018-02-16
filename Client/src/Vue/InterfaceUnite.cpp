#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <Windows.h>
#include "InterfaceUnite.h"
#include "Jauge.h"


namespace Vue 
{
	InterfaceUnite::InterfaceUnite(Modele::Unite *unite) : sf::Drawable() , unite(unite), vie(sf::Vector2f(270.0f,550.0f), unite->getVieMax(), unite->getVieCourante(), sf::Vector2f(30.0f,100.0f))
	{
		if (!ressource.loadFromFile("ressources/sprite/menu+figures.png"))
		{
			std::cout << "erreur chargement Texture menu+figures.png" << std::endl;
		}
		tete.setTexture(ressource);
		tete.scale(0.5f,0.5f);
		tete.setPosition(42,25+522);
		avatarUnite[ClasseEquipe(Modele::Classe::Tank, Modele::Equipe::Rouge)] = sf::IntRect(0,0,256,256);
		avatarUnite[ClasseEquipe(Modele::Classe::Tank, Modele::Equipe::Bleu)] = sf::IntRect(256, 0, 256, 256);
		avatarUnite[ClasseEquipe(Modele::Classe::Soldat, Modele::Equipe::Rouge)] = sf::IntRect(0, 256, 256, 256);
		avatarUnite[ClasseEquipe(Modele::Classe::Soldat, Modele::Equipe::Bleu)] = sf::IntRect(256, 256, 256, 256);
		avatarUnite[ClasseEquipe(Modele::Classe::Archer, Modele::Equipe::Rouge)] = sf::IntRect(0, 512, 256, 256);
		avatarUnite[ClasseEquipe(Modele::Classe::Archer, Modele::Equipe::Bleu)] = sf::IntRect(256, 512, 256, 256);

		this->setUnite(this->unite);

		if (!font.loadFromFile("../../ressources/VCR_OSD_MONO_1.001.ttf"))
		{
			std::cout << "error font" << std::endl;
		}

		TabStat[0].setString("Classe");
		TabStat[1].setString("Vie");
		TabStat[2].setString("Attaque");
		TabStat[3].setString("Defense");

		for (int i = 0; i < 4; i++)
		{
			TabStat[i].setFont(font);// choix de la police à utiliser
			TabStat[i].setCharacterSize(12);// choix de la taille des caractères
			TabStat[i].setFillColor(sf::Color::White);
			TabStat[i].setPosition(450, i * 50 + 400);
		}
		fond.setTexture(ressource);
		fond.setTextureRect(sf::IntRect(0,256+512,256,256));
		fond.scale(3.0f, 0.7f);
		fond.setPosition(0, 522);
	}

	Modele::Unite* InterfaceUnite::getUnite()
	{
		return unite;
	}

	void InterfaceUnite::setUnite(Modele::Unite *unite)
	{
		this->unite = unite;
		tete.setTextureRect(avatarUnite[ClasseEquipe(unite->getClasse(), unite->getEquipe())]);
	}

	void InterfaceUnite::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(fond, states);
		target.draw(tete, states);
	}

}