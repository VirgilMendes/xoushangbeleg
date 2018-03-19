#pragma once

#include <SFML/Graphics.hpp>
#include "../../Outils/Animation.h"
#include <map>
#include "../../../Modele/Unite/Unite.h"

namespace Vue
{
	class Unite
	{
	public:
		Unite(Modele::Unite* unite, sf::Texture* texture);
		~Unite();

		void initAnimation();

		Modele::Unite* getModele() { return modele_; }
		
		bool deplacerUniteVers(Modele::Vecteur2<int> cible);
		void setPosition(Modele::Vecteur2<int> position);
		Modele::Vecteur2<int> getPosition();

		void mourrir();

		void update();
		void dessiner(sf::RenderTarget* cible, sf::RenderStates etat = sf::Transform());

		static const std::map<const Modele::Classe, const std::string> cheminTextureUnite;

		Animation* getAnimationDeplacementFace() { return &deplacementFace_; }
		Animation* getAnimationDeplacementDos() { return &deplacementDos_; }

	private:

		Animation idle_; 
		Animation deplacementFace_;
		Animation deplacementDos_;
		Animation attaque_;
		Modele::Unite* modele_;
		sf::Sprite* sprite_;
		sf::Image image_;
		sf::Texture* texture_;

		bool mort;

		Animation* animationDeplacementCourante_;
	};
}
