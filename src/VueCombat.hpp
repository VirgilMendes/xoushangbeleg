#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

class Curseur : public sf::Drawable
{
public:
	Curseur() : position_(0, 0), forme_(sf::Vector2f(32,32))
	{
		image_.create(32, 32, sf::Color::Red);
		image_.createMaskFromColor(sf::Color::Red, 50);
		
		texture_.loadFromImage(image_);

		forme_.setPosition(position_.x*32, position_.y*32);
		forme_.setTexture(&texture_);
	}

	Curseur(sf::Vector2i position) : position_(position), forme_(sf::Vector2f(32, 32))
	{
		image_.create(32, 32, sf::Color::Red);
		image_.createMaskFromColor(sf::Color::Red, 50);

		texture_.loadFromImage(image_);

		forme_.setPosition(position_.x * 32, position_.y * 32);
		forme_.setTexture(&texture_);
	}

	void deplacementCurseur(sf::Vector2i position)
	{
		position_ = position;
		forme_.setPosition(position.x*32, position.y*32);
	}
	
	sf::Vector2i getPosition() { return position_; }


private:
	
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override
	{
		target.draw(forme_, states);
	}
	
	sf::Vector2i position_;
	sf::RectangleShape forme_;
	sf::Image image_;
	sf::Texture texture_;
};

inline int vueCombatRun()
{

	const int LONGUEUR_GRILLE = 10;
	const int LARGEUR_GRILLE = 10;

	// cr�ation de la fen�tre
	sf::RenderWindow window(sf::VideoMode(800, 600), "Xoushangbeleg : Vue Combat");
	window.setFramerateLimit(60);

	sf::Texture textureSol;
	textureSol.loadFromFile("ressources/sprite/ground_tiles.png");
	textureSol.setSmooth(true);
	
	std::vector<std::vector<sf::Sprite>> grille(LONGUEUR_GRILLE, std::vector<sf::Sprite>(LARGEUR_GRILLE, sf::Sprite()));
	for(int i(0); i < LONGUEUR_GRILLE; i++)
	{
		for(int j(0); j < LARGEUR_GRILLE; j++)
		{
			sf::Sprite* sprite = &grille[i][j];
			sprite->setTexture(textureSol);
			sprite->setTextureRect(sf::IntRect(32, 64, 32, 32));
			sprite->setPosition(i*32, j*32);
		}
	}

	Curseur curseur;

	// on fait tourner le programme tant que la fen�tre n'a pas �t� ferm�e
	while (window.isOpen())
	{
		// on traite tous les �v�nements de la fen�tre qui ont �t� g�n�r�s depuis la derni�re it�ration de la boucle
		sf::Event event;
		while (window.pollEvent(event))
		{
			// fermeture de la fen�tre lorsque l'utilisateur le souhaite
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;

			case sf::Event::KeyPressed:
				switch (event.key.code)
				{
				case sf::Keyboard::Z:
					curseur.deplacementCurseur(curseur.getPosition() + sf::Vector2i(0, -1));
					break;
				case sf::Keyboard::Q:
					curseur.deplacementCurseur(curseur.getPosition() + sf::Vector2i(-1, 0));
					break;
				case sf::Keyboard::S:
					curseur.deplacementCurseur(curseur.getPosition() + sf::Vector2i(0, 1));
					break;
				case sf::Keyboard::D:
					curseur.deplacementCurseur(curseur.getPosition() + sf::Vector2i(1, 0));
					break;
				default: break;


				}

			}
		}

		// effacement de la fen�tre en noir
		window.clear(sf::Color::Black);

		for (auto colone : grille)
		{
			for (sf::Sprite sprite : colone)
			{
				window.draw(sprite);
			}
		}

		window.draw(curseur);

		// fin de la frame courante, affichage de tout ce qu'on a dessin�
		window.display();
	}

	return 0;
}
