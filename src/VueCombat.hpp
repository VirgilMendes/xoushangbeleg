#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

inline int vueCombatRun()
{

	const int LONGUEUR_GRILLE = 10;
	const int LARGEUR_GRILLE = 10;

	// création de la fenêtre
	sf::RenderWindow window(sf::VideoMode(800, 600), "Xoushangbeleg : Vue Combat");
	window.setFramerateLimit(1);

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

	// on fait tourner le programme tant que la fenêtre n'a pas été fermée
	while (window.isOpen())
	{
		// on traite tous les évènements de la fenêtre qui ont été générés depuis la dernière itération de la boucle
		sf::Event event;
		while (window.pollEvent(event))
		{
			// fermeture de la fenêtre lorsque l'utilisateur le souhaite
			if (event.type == sf::Event::Closed)
				window.close();
		}

		// effacement de la fenêtre en noir
		window.clear(sf::Color::Black);

		for (auto colone : grille)
		{
			for (sf::Sprite sprite : colone)
			{
				window.draw(sprite);
			}
		}

		// fin de la frame courante, affichage de tout ce qu'on a dessiné
		window.display();
	}

	return 0;
}
