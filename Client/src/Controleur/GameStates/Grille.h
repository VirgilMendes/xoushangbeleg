#pragma once 
#include "../../Modele/Grille.h"
#include "GameState.h"
#include "../../Vue/GameStates/Grille.h"


namespace Controleur
{

	BETTER_ENUM(EtatCombat, int,
		Placement,
		Navigation,
		Selection,
		Deplacement,
		Attaque
		)

	class Grille : public GameState
	{
	public:
		Grille(Modele::Vecteur2<int> dimensions_);
		Grille(Modele::Grille* modele);
		virtual ~Grille();

		void handleEvent() override;
		void update() override;
		void afficher() override;

		void enclencherActionDeplacement(const ActionDeplacement& action) override;
		void enclencherActionValidation() override;
		void enclancherActionRetour() override;
		void enclancherActionMenu() override;
		void enclancherActionSpecial() override;

		void naviguer();
		void selectionerUnite();
		void deplacerUnite();
		void attaquerUnite();
		void placerUnite();

		void setUniteAPlacer(Modele::Unite* unite);

		void deplacerCurseur(Modele::Vecteur2<int> deplacement);
		void setPositionCurseur(Modele::Vecteur2<int> position);

		void genererCasesAccessiblesDeplacement();
		void genererCasesAccessiblesAttaque();

		void setPositionCurseurUniteActuel();
		void finirTourUniteActuel();

		Modele::Grille* getGrilleModele();

		Modele::Unite* getUniteCourante() { return uniteCourante_; }
		EtatCombat getEtatCombat() { return etatCombat_; }
		int getNbUniteAPlacerRouge() { return nbUniteAPlacerRouge; }
		int getNbUniteAPlacerBleue() { return nbUniteAPlacerBleue; }
		void setEtatCombat(const EtatCombat& etatCombat) { etatCombat_ = etatCombat; }


		void deplacerUniteDepuisReseaux(std::string nom, Modele::Vecteur2<int> deplacement);
		void attaquerUniteDepuisReseaux(std::string source, std::string cible);
		void finirTourDepuisReseaux();
		void placerUniteDepuisReseaux(Modele::Classe classe, Modele::Vecteur2<int> position);

		int getId() { return id; }
		void incrementerId() { id = id + 1; }
		Modele::Equipe getEquipeCourante() { return equipeCourante_; }


	private:

		Modele::Grille* modele_;

		Modele::Unite* uniteCourante_;

		Modele::Vecteur2<int> positionCurseur_;

		EtatCombat etatCombat_;

		Vue::Grille* vue_;

		bool actionFaite_;
		bool deplacementFait_;

		Modele::Equipe equipeJoueur_;
		Modele::Equipe equipeCourante_;


		int nbUniteAPlacerRouge;
		int nbUniteAPlacerBleue;

		int id;
	};
}
