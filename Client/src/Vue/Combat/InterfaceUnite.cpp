#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <Windows.h>
#include "InterfaceUnite.h"
#include "Jauge.h"


namespace Vue 
{
	InterfaceUnite::InterfaceUnite(Modele::Unite *unite) : sf::Drawable() , unite(unite), vie(sf::Vector2f(300.0f,584.0f), unite->getVieMax(), unite->getVieCourante(), sf::Vector2f(200.0f,15.0f))
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

		if (!font.loadFromFile("ressources/VCR_OSD_MONO_1.001.ttf"))
		{
			std::cout << "error font" << std::endl;
		}

		TabStat[0].setString("Classe : ");
		TabStat[1].setString("Vie : ");
		TabStat[2].setString("Attaque : ");
		TabStat[3].setString("Defense : ");

		for (int i = 0; i < 4; i++)
		{
			TabStat[i].setFont(font);// choix de la police à utiliser
			TabStat[i].setCharacterSize(15);// choix de la taille des caractères
			TabStat[i].setFillColor(sf::Color::White);
			TabStat[i].setPosition(200, i * 32 + 550);
		}
		fond.setTexture(ressource);
		fond.setTextureRect(sf::IntRect(0,256+512,256,256));
		fond.scale(2.55f, 0.7f);
		fond.setPosition(0, 522);

		classeText.setFont(font);// choix de la police à utiliser
		classeText.setCharacterSize(15);// choix de la taille des caractères
		classeText.setFillColor(sf::Color::White);
		classeText.setPosition(300, 550);

		vieText.setPosition(530, 582);
		vieText.setFont(font);// choix de la police à utiliser
		vieText.setCharacterSize(15);// choix de la taille des caractères
		vieText.setFillColor(sf::Color::White);

		statTextAtt.setPosition(300, 614);
		statTextAtt.setFont(font);// choix de la police à utiliser
		statTextAtt.setCharacterSize(15);// choix de la taille des caractères
		statTextAtt.setFillColor(sf::Color::White);

		statTextDef.setPosition(300, 646);
		statTextDef.setFont(font);// choix de la police à utiliser
		statTextDef.setCharacterSize(15);// choix de la taille des caractères
		statTextDef.setFillColor(sf::Color::White);
	}

	Modele::Unite* InterfaceUnite::getUnite()
	{
		return unite;
	}

	void InterfaceUnite::setUnite(Modele::Unite *unite)
	{
		this->unite = unite;
		tete.setTextureRect(avatarUnite[ClasseEquipe(unite->getClasse(), unite->getEquipe())]);

		switch (this->unite->getClasse())
		{
		case Modele::Classe::Tank:
			classeText.setString("Tank");
			break;
		case Modele::Classe::Soldat:
			classeText.setString("Soldat");
			break;
		case Modele::Classe::Archer:
			classeText.setString("Archer");
			break;
		}
		
		vie.setValeurMax(this->unite->getVieMax());
		vie.setValeurCourante(this->unite->getVieCourante());
		vieText.setString(std::to_string(this->unite->getVieCourante()) + "/"+ std::to_string(this->unite->getVieMax()));
		statTextAtt.setString(std::to_string(this->unite->getStatAtt()));
		statTextDef.setString(std::to_string(this->unite->getStatDef()));
	}

	void InterfaceUnite::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		
		target.draw(fond, states);
		target.draw(tete, states);

		for (int i = 0; i < 4; i++)
		{
			target.draw(TabStat[i]);
		}

		target.draw(classeText, states);
		target.draw(vie, states);
		target.draw(vieText, states);
		target.draw(statTextAtt, states);
		target.draw(statTextDef, states);
	}

}