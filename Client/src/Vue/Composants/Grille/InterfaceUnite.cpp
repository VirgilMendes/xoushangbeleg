#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <Windows.h>
#include "InterfaceUnite.h"
#include "../../Outils/Jauge.h"
#include "../../../Controleur/Navigation.h"
#include "../../Outils/TexteVariable.h"


namespace Vue 
{
	InterfaceUnite::InterfaceUnite(Modele::Unite *unite) : unite_(nullptr), 
		barreVie_(sf::Vector2f(200+60,550+20+5), unite->getVieMax(), unite->getVieCourante(), sf::Vector2f(300,10))
	{
		if (!textureAvatar_.loadFromFile("ressources/sprite/menu+figures.png"))
		{
			std::cout << "erreur chargement Texture menu+figures.png" << std::endl;
		}
		avatar_.setTexture(textureAvatar_);
		avatar_.scale(0.5f,0.5f);
		avatar_.setPosition(42,25+522);

		fond_.setTexture(textureAvatar_);
		fond_.setTextureRect(sf::IntRect(0, 3*256, 256, 256));
		fond_.scale(2.55f, 0.7f);
		fond_.setPosition(10, 525);
		
		nom_.setTexteConstant("NOM : ");
		nom_.setFillColor(sf::Color::White);
		nom_.setPosition(200, 550);

		classe_.setTexteConstant("CLASSE : ");
		classe_.setFillColor(sf::Color::White);
		classe_.setPosition(200+200, 550);

		vie_.setTexteConstant("PV  :									");
		vie_.setFillColor(sf::Color::White);
		vie_.setPosition(200, 550 + 20);

		attaque_.setTexteConstant("ATT : ");
		attaque_.setFillColor(sf::Color::White);
		attaque_.setPosition(200, 550+3*20);

		defense_.setTexteConstant("DEF : ");
		defense_.setFillColor(sf::Color::White);
		defense_.setPosition(200, 550+4*20);

		porteeDeplacement_.setTexteConstant("POD : ");
		porteeDeplacement_.setFillColor(sf::Color::White);
		porteeDeplacement_.setPosition(200+200, 550 + 3 * 20);

		porteeAttaque_.setTexteConstant("POA : ");
		porteeAttaque_.setFillColor(sf::Color::White);
		porteeAttaque_.setPosition(200+200, 550 + 4 * 20);

		equipe_.setTexteConstant("EQUIPE : ");
		equipe_.setFillColor(sf::Color::White);
		equipe_.setPosition(200 + 200, 550 + 6 * 20);

		setUnite(unite);
	}

	Modele::Unite* InterfaceUnite::getUnite()
	{
		return unite_;
	}

	void InterfaceUnite::setUnite(Modele::Unite *unite)
	{
		unite_ = unite;
		avatar_.setTextureRect(InterfaceUnite::avatarsUnite.at(ClasseEquipe(unite->getClasse(), unite->getEquipe())));

		nom_.setValeurVariable(unite_->getNom());
		classe_.setValeurVariable(unite_->getClasse()._to_string());
		vie_.setValeurVariable(std::to_string(unite_->getVieCourante()) + "/" + std::to_string(unite_->getVieMax()));
		attaque_.setValeurVariable(std::to_string(unite_->getAttaque()));
		defense_.setValeurVariable(std::to_string(unite_->getDefense()));
		porteeAttaque_.setValeurVariable(std::to_string(unite_->getPorteeAttaque()));
		porteeDeplacement_.setValeurVariable(std::to_string(unite_->getPorteeDeplacement()));
		equipe_.setValeurVariable(unite_->getEquipe()._to_string());

		barreVie_.setValeurMax(this->unite_->getVieMax());
		barreVie_.setValeurCourante(this->unite_->getVieCourante());
	}

	void InterfaceUnite::dessiner(sf::RenderTarget* target, sf::RenderStates& states)
	{
		target->draw(fond_, states);
		target->draw(avatar_, states);

		target->draw(nom_, states);
		target->draw(classe_, states);
		target->draw(barreVie_, states);
		target->draw(vie_, states);
		target->draw(attaque_, states);
		target->draw(defense_, states);
		target->draw(porteeDeplacement_, states);
		target->draw(porteeAttaque_, states);
		target->draw(equipe_, states);

	}

	const std::map<ClasseEquipe, sf::IntRect> InterfaceUnite::avatarsUnite = std::map<ClasseEquipe, sf::IntRect>
	{
		{ { Modele::Classe::Tank, Modele::Equipe::Rouge }, sf::IntRect(0, 0, 256, 256) },
		{ { Modele::Classe::Tank, Modele::Equipe::Bleu }, sf::IntRect(256, 0, 256, 256) },
		{ { Modele::Classe::Soldat, Modele::Equipe::Rouge }, sf::IntRect(0, 256, 256, 256) },
		{ { Modele::Classe::Soldat, Modele::Equipe::Bleu }, sf::IntRect(256, 256, 256, 256) },
		{ { Modele::Classe::Archer, Modele::Equipe::Rouge }, sf::IntRect(0, 512, 256, 256) },
		{ { Modele::Classe::Archer, Modele::Equipe::Bleu }, sf::IntRect(256, 512, 256, 256) }
	};
}
