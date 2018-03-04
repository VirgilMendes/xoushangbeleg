#pragma once

#include "../../Controleur/Navigation.h"
#include "Combat.h"


namespace Vue
{
	Combat::Combat() : interfaceUnite(&Modele::Tank(Modele::Equipe::Rouge, std::string("Benoit"), 0, 0)),
	                   grille_(LONGUEUR_GRILLE, std::vector<sf::Sprite>(LARGEUR_GRILLE, sf::Sprite()))
	{
		textureSol_.loadFromFile("ressources/sprite/map.png");
		textureSol_.setSmooth(true);
		CarteGUI carte;

		ajouterUnite("Archer1", "ressources/sprite/Archer_sprite.png", sf::Vector2i(4, 3));

		for(int i(0); i < LONGUEUR_GRILLE; i++)
		{
			for(int j(0); j < LARGEUR_GRILLE; j++)
			{
				sf::Sprite* sprite = &grille_[i][j];
				sprite->setTexture(textureSol_);
				sprite->setTextureRect(sf::IntRect(0, 0, 64, 64));
				sprite->setPosition(i * 64, j * 64);
			}
		}

		sf::Font font;
		font.loadFromFile("ressources/VCR_OSD_MONO_1.001.ttf");
		menuAction_ = new MenuChoix(std::vector<std::string>{"test1", "test2", "test3"}, font, 20);
		menuAction_->setPosition(Modele::Vecteur2<int>(600, 0));
	}

	Combat::~Combat()
	{
		auto iterateur = textures_.begin();
		while(iterateur != textures_.end())
		{
			delete iterateur->second;
			++iterateur;
		}
		delete menuAction_;
	}

	void Combat::handleEvent(sf::Event event)
	{
		switch (event.type)
		{

		case sf::Event::KeyPressed:
			switch (event.key.code)
			{
			case sf::Keyboard::Z:
				curseur_.deplacerCurseur(sf::Vector2i(0, -1));
				menuAction_->deplacerAuChoixPrecedant();
				break;
			case sf::Keyboard::Q:
				curseur_.deplacerCurseur(sf::Vector2i(-1, 0));
				break;
			case sf::Keyboard::S:
				curseur_.deplacerCurseur(sf::Vector2i(0, 1));
				menuAction_->deplacerAuChoixSuivant();
				break;
			case sf::Keyboard::D:
				curseur_.deplacerCurseur(sf::Vector2i(1, 0));
				break;
			case sf::Keyboard::Up:
				menuAction_->deplacerAuChoixPrecedant();
				break;
			case sf::Keyboard::Down:
				menuAction_->deplacerAuChoixSuivant();
				break;
			default: break;
			}
		}
	}

	void Combat::update()
	{
		
	}

	void Combat::draw()
	{
		/*
		for (auto colone : grille_)
		{
		for (sf::Sprite sprite : colone)
		{
		fenetre->draw(sprite);
		}
		}*/

		Controleur::Fenetre::fenetre->draw(carte_);

		Controleur::Fenetre::fenetre->draw(curseur_);
		for (Unite unite : unites_)
			Controleur::Fenetre::fenetre->draw(unite);
		Controleur::Fenetre::fenetre->draw(interfaceUnite);

		menuAction_->dessiner(Controleur::Fenetre::fenetre, sf::Transform());
	}

	void Combat::ajouterUnite(std::string nom, std::string cheminTexture, Modele::Vecteur2<int> position)
	{
		sf::Texture* texture;
		if(textures_.find(cheminTexture) == textures_.end())
		{
			sf::Image image;
			image.loadFromFile(cheminTexture);
			image.createMaskFromColor(sf::Color::Transparent, 0);

			texture = new sf::Texture;
			texture->loadFromImage(image);
		}
		else
		{
			texture = textures_[cheminTexture];
		}

		unites_.push_back(Unite(nom, texture, position));
	}

	void Combat::deplacerUnite(std::string nom, Modele::Vecteur2<int> position)
	{
		Unite* unite = nullptr;

		auto iterateur = unites_.begin();
		while(iterateur != unites_.end())
		{
			if(iterateur->getNom() == nom)
			{
				unite = &*iterateur;
				break;
			}
			++iterateur;
		}
		if(iterateur == unites_.end()) return;
		unite->setPosition(position);
		Modele::Unite* test = new Modele::Archer(Modele::Equipe::Bleu, "Archer", 4, 3);
		test->setPosition(Modele::Vecteur2<int>(10, 3));
		delete test;
	}
}
