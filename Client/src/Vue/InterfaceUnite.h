#pragma once

#include "SFML/Graphics.hpp"
#pragma once

#include <string>
#include "../Modele/Unite.h"
#include "../Modele/Archer.h"
#include "../Modele/Soldat.h"
#include "../Modele/Tank.h"

#include "Jauge.h"

typedef std::pair<Modele::Classe, Modele::Equipe> ClasseEquipe;

namespace Vue
{

	class InterfaceUnite : public sf::Drawable
	{
	public:
		InterfaceUnite::InterfaceUnite(Modele::Unite* unite);

		Modele::Unite* getUnite();
		void setUnite(Modele::Unite *unite);

	private:
		Modele::Unite *unite;

		//Jauge barrevie;
		sf::Texture ressource;
		sf::Sprite fond;
		sf::Sprite tete;
		std::map<ClasseEquipe, sf::IntRect> avatarUnite;

		Jauge vie;

		sf::Font font;
		sf::Text TabStat[4];

		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	};


}