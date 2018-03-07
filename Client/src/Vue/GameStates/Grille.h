#pragma once 
#include "SFML/Graphics.hpp"
#include "../../Modele/Grille.h"
#include "../Outils/Node.h"
#include "../Combat/Curseur.h"
#include "../Combat/Unite.h"
#include "../Combat/InterFaceUnite.h"
#include "../../Controleur/GameStates/GameState.h"
#include "GameState.h"
#include "../Combat/FiltreCase.h"

namespace Controleur
{
	class Grille;
}

namespace Vue
{
	typedef std::pair<Modele::Terrain, int > ParametreSol;
	typedef std::tuple<Modele::Terrain, Modele::Obstacle, int > ParametreElement;

	class Grille : public sf::View, Node, GameState
	{
	public :
		Grille(Modele::Grille* modele, Controleur::Grille* controleur);
		virtual ~Grille();

		void miseAJourAnimation();

		void setPositionCurseur(Modele::Vecteur2<int> position);
		void deplacerCurseur(Modele::Vecteur2<int> deplacement);

		void ajouterUnite(Modele::Unite* unite, std::string cheminTexture);
		void deplacerUnite(Modele::Unite* unite, Modele::Vecteur2<int> deplacement);

		void genererInformationPersonnage(Modele::Unite* unite);
		void detruireInfomationPersonnage();

		void genererFiltreSurCases(std::list<Modele::Vecteur2<int>> cases);
		void supprimerFiltreSurCases();

		void handleEvent() override;
		void update() override;
		void dessiner() override;

	protected:
		void dessinerNode(sf::RenderTarget* target, const sf::Transform& transform) override{}
		void setPositionElements(sf::Vector2i position) override {}
		void setTailleElements(sf::Vector2i taille) override {}
		void setRotationElements(int rotation) override {}

		private :

			std::map<std::string, sf::Texture*> textures_;

			Curseur curseur_;

			InterfaceUnite* interfaceUnite_;

			Modele::Grille* modele_;
			Controleur::Grille* controleur_;

			std::list<Unite> unites_;

			sf::Texture textureGrille_;
			sf::Texture textureObstacle_;

			sf::VertexArray sommets_;

			FiltreCase* filtreCase_;

			sf::Clock* horloge_;
			int frame_;
	};
}
