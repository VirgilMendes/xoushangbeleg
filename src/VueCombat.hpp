#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

inline int vueCombatRun()
{
	// création de la fenêtre
	sf::RenderWindow window(sf::VideoMode(800, 600), "Xoushangbeleg : Vue Combat");
	window.setFramerateLimit(30);

	sf::Texture textureSol;
	textureSol.loadFromFile("ressources/sprite/ground_tiles.png");
	textureSol.setSmooth(true);
	
	sf::Sprite tile;
	tile.setTexture(textureSol);
	tile.setTextureRect(sf::IntRect(32, 64, 32, 32));
	tile.setPosition(0, 0);


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

		window.draw(tile);

		// fin de la frame courante, affichage de tout ce qu'on a dessiné
		window.display();
	}

	return 0;
}
