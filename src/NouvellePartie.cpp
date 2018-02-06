#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <Windows.h>

inline int NouvellePartieRun() {

	int choix(0);
	sf::RenderWindow fenetre(sf::VideoMode(1000, 700), "Nouvelle partie");
	//fenetre.setVerticalSyncEnabled(true);
	fenetre.setFramerateLimit(12);
	sf::Sprite sprite;

	int frame(-1);

	sf::Texture titre;
	if (!titre.loadFromFile("ressources/sprite/titre.png"))
	{
		std::cout << "error img titre" << std::endl;
	}
	titre.setSmooth(false);

	sprite.setTexture(titre);

	sf::IntRect animation[11];
	animation[0] = sf::IntRect(0, 0, 256, 512);
	animation[1] = sf::IntRect(256, 0, 256, 512);
	animation[2] = sf::IntRect(512, 0, 256, 512);
	animation[3] = sf::IntRect(1024, 0, 256, 512);
	animation[4] = sf::IntRect(2048, 0, 256, 512);
	animation[5] = sf::IntRect(2048 * 2, 0, 256, 512);
	animation[6] = sf::IntRect(2048 * 4, 0, 256, 512);
	animation[7] = sf::IntRect(2048 * 8, 0, 256, 512);
	animation[8] = sf::IntRect(2048 * 16, 0, 256, 512);
	animation[9] = sf::IntRect(2048 * 32, 0, 256, 512);
	animation[10] = sf::IntRect(2048 * 64, 0, 256, 512);


	sf::Font font; // GESTION DE L'ECRITURE
	if (!font.loadFromFile("ressources/VCR_OSD_MONO_1.001.ttf"))
	{
		std::cout << "error font" << std::endl;
	}

	sf::Text TabMenu[2];
	TabMenu[0].setString("Creation de la partie");
	TabMenu[1].setString("Choix");

	for (int i = 0; i < 2; i++)
	{
		TabMenu[i].setFont(font);// choix de la police à utiliser
		TabMenu[i].setCharacterSize(24);// choix de la taille des caractères
		TabMenu[i].setFillColor(sf::Color::White);
		TabMenu[i].setPosition(450, i * 50 + 400);
	}

	boolean toucheLache(true);   //FIN GESTION DE L'ECRITURE

	while (fenetre.isOpen())
	{
		// on inspecte tous les évènements de la fenêtre qui ont été émis depuis la précédente itération
		sf::Event event;
		while (fenetre.pollEvent(event))
		{
			// évènement "fermeture demandée" : on ferme la fenêtre
			if (event.type == sf::Event::Closed)
				fenetre.close();
		}
		fenetre.clear(sf::Color::Black);

		frame = frame + 1;
		if (frame == 11)
		{
			frame = 0;
			std::cout << std::endl;
		}
		std::cout << frame;

		sprite.setTextureRect(sf::IntRect(0, 256 * frame, 512, 256));

		TabMenu[choix].setFillColor(sf::Color::White);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && toucheLache)
		{
			if (choix > 0)
			{
				choix -= 1;
			}
			toucheLache = false;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && toucheLache)
		{
			if (choix < 1)
			{
				choix += 1;
			}
			toucheLache = false;
		}

		if (event.type == sf::Event::KeyReleased)
		{
			toucheLache = true;
		}

		TabMenu[choix].setFillColor(sf::Color::Yellow);
		// c'est ici qu'on dessine tout
		// window.draw(...);
		for (int i(0); i<2; i++)
		{
			fenetre.draw(TabMenu[i]);
		}

		fenetre.draw(sprite);

		sprite.setTextureRect(animation[frame]);
		// fin de la frame courante, affichage de tout ce qu'on a dessiné
		fenetre.display();
	}
	return 0;
}