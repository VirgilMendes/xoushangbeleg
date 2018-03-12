#pragma once

#include "SFML/Graphics.hpp"
#pragma once

#include <string>
#include "../../../Modele/Unite/Unite.h"
#include "../../../Modele/Unite/Archer.h"
#include "../../../Modele/Unite/Soldat.h"
#include "../../../Modele/Unite/Tank.h"
#include "../../Constante.h"

#include "../../Outils/Jauge.h"
#include "../../Outils/TexteVariable.h"

typedef std::pair<Modele::Classe, Modele::Equipe> ClasseEquipe;

namespace Vue
{

	class InterfaceUnite
	{
	public:
		InterfaceUnite::InterfaceUnite(Modele::Unite* unite);

		Modele::Unite* getUnite();
		void setUnite(Modele::Unite *unite);

		static const std::map<ClasseEquipe, sf::IntRect> avatarsUnite;

		void dessiner(sf::RenderTarget* target, sf::RenderStates& states);

	private:
		
		Modele::Unite* unite_;

		sf::Texture textureAvatar_;
		sf::Sprite fond_;
		sf::Sprite avatar_;

		Jauge barreVie_;

		TexteVariable TabStat[4];

		TexteVariable nom_;
		TexteVariable classe_;
		TexteVariable vie_;
		TexteVariable attaque_;
		TexteVariable defense_;
		TexteVariable porteeDeplacement_;
		TexteVariable porteeAttaque_;
	};

}