#pragma once
#include <vector>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

namespace Vue
{
	struct Choix
	{
		bool actif;
		sf::Text texte;
	};

	class MenuChoix
	{
	public:

		MenuChoix(std::vector<std::string> textes, sf::Font police, int tailletexte, sf::Vector2i position = sf::Vector2i(0, 0));

	private:
		
		//Gestion de la boite
		sf::RectangleShape boite_;
		sf::Vector2i position_;
		
		//Gestion des textes
		sf::Font police_;
		int tailletexte_;
		std::vector<Choix> textes_;

		//Gestion des couleurs
		sf::Color couleurSelection_ = sf::Color::Yellow;
		sf::Color couleurInactif_ = sf::Color(100, 100, 100);
		sf::Color couleurActif_ = sf::Color::White;
	};
}
