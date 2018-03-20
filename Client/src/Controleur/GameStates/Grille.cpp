#include "Grille.h"
#include "../../Modele/Case.h"
#include "../Navigation.h"
#include "MenuCombat/MenuAction.h"
#include "MenuCombat/MenuPlacement.h"

namespace Controleur
{
	Grille::Grille(Modele::Vecteur2<int> dimension) : 
		modele_(new Modele::Grille(dimension)), vue_(new Vue::Grille(modele_, this)), etatCombat_(EtatCombat::Placement),
		actionFaite_(false), deplacementFait_(false)
	{
		nbUniteAPlacerBleue = 5;
		nbUniteAPlacerRouge = 5;
		id = 1;
		equipeCourante = Modele::Equipe::Rouge;
	}

	Grille::Grille(Modele::Grille* modele) :modele_(modele), vue_(new Vue::Grille(modele_, this)), etatCombat_(EtatCombat::Selection),
		actionFaite_(false), deplacementFait_(false)
	{
		modele_->relancerOrdreDeJeu();
		setPositionCurseurUniteActuel();
	}

	Grille::~Grille()
	{
		delete modele_;
		delete vue_;
	}

	void Grille::handleEvent()
	{
		vue_->handleEvent();
	}

	void Grille::update()
	{
		vue_->update();
	}

	void Grille::afficher()
	{
		vue_->afficher();
	}

	void Grille::enclencherActionDeplacement(const ActionDeplacement& action)
	{
		switch(action)
		{
		case ActionDeplacement::Haut:
			try { deplacerCurseur(Modele::Vecteur2<int>::NORD); } catch(...){}
			break;
		case ActionDeplacement::Droite:
			try { deplacerCurseur(Modele::Vecteur2<int>::EST); } catch (...) {}
			break;
		case ActionDeplacement::Bas:
			try { deplacerCurseur(Modele::Vecteur2<int>::SUD); } catch (...) {}
			break;
		case ActionDeplacement::Gauche:
			try { deplacerCurseur(Modele::Vecteur2<int>::OUEST);} catch (...) {}
			break;
		}
	}

	void Grille::enclencherActionValidation()
	{
		
		switch(etatCombat_)
		{
		case EtatCombat::Navigation:
			naviguer();
			break;
		case EtatCombat::Selection:
			selectionerUnite();
			break;
		case EtatCombat::Deplacement:
			deplacerUnite();
			break;
		case EtatCombat::Attaque:
			attaquerUnite();
			break;
		case EtatCombat::Placement:
			placerUnite();
			break;
		}
	}

	void Grille::enclancherActionRetour()
	{
	}

	void Grille::enclancherActionMenu()
	{
	}

	void Grille::enclancherActionSpecial()
	{
	}

	void Grille::naviguer()
	{

	}

	void Grille::selectionerUnite()
	{
		Modele::Unite* unite = modele_->getCase(positionCurseur_)->getUnite();
		if (unite != nullptr)
		{
			Modele::Unite* uniteActuel = modele_->getUniteActuel();
			if (uniteActuel == nullptr)
			{
				modele_->relancerOrdreDeJeu();
				setPositionCurseurUniteActuel();
			}
			else if (unite == uniteActuel)
			{
				MenuAction* menuAction = new Controleur::MenuAction;
				if (deplacementFait_)menuAction->desactiverChoix(0);
				if (actionFaite_)menuAction->desactiverChoix(1);
				Controleur::Fenetre::empilerGameState(menuAction);
			}
		}
	}

	void Grille::deplacerUnite()
	{
		etatCombat_ = EtatCombat::Selection;
		std::list<Modele::Vecteur2<int>> derniereRecherche = modele_->getDerniereRechercheDeplacement();
		if (std::find(derniereRecherche.begin(), derniereRecherche.end(), positionCurseur_) == derniereRecherche.end())
		{
			modele_->nettoyerDerniereRechercheDeplacement();
			vue_->supprimerFiltreSurCases();
			selectionerUnite();
		}
		else
		{
			Modele::Unite* unite = modele_->getProprietaireDerniereRechercheDeplacement();
			Modele::Vecteur2<int> anciennePosition = unite->getPosition();
			Modele::Vecteur2<int> deplacement = positionCurseur_ - anciennePosition;

			modele_->deplacerUnite(unite, deplacement);
			
			vue_->supprimerFiltreSurCases();
			vue_->deplacerUnite(unite, deplacement);	

			modele_->nettoyerDerniereRechercheDeplacement();

			vue_->genererInformationPersonnage(unite);
			deplacementFait_ = true;
		}
	}

	void Grille::attaquerUnite()
	{
		etatCombat_ = EtatCombat::Selection;
		std::list<Modele::Vecteur2<int>> derniereRechercheAttaque = modele_->getDerniereRechercheAttaque();
		if (std::find(derniereRechercheAttaque.begin(), derniereRechercheAttaque.end(), positionCurseur_) == derniereRechercheAttaque.end())
		{
			modele_->nettoyerDerniereRechercheAttaque();
			vue_->supprimerFiltreSurCases();
			selectionerUnite();
		}
		else
		{
			Modele::Unite* unite = modele_->getCase(positionCurseur_)->getUnite();
			if (unite != nullptr && unite != modele_->getProprietaireDerniereRechercheAttaque())
			{
				vue_->attaquerUnite(modele_->getProprietaireDerniereRechercheAttaque(), unite);
				modele_->getProprietaireDerniereRechercheAttaque()->attaquer(unite);
				if (unite->getVieCourante() <= 0)
				{
					vue_->supprimerUnite(unite);
					modele_->supprimerUnite(unite);
					vue_->detruireInfomationPersonnage();
				}
				else
				{
					vue_->detruireInfomationPersonnage();
					vue_->genererInformationPersonnage(unite);
				}
				modele_->nettoyerDerniereRechercheAttaque();
				vue_->supprimerFiltreSurCases();
				actionFaite_ = true;
			}
			else
			{
				etatCombat_ = EtatCombat::Attaque;
			}
		}
	}

	void Grille::placerUnite()
	{
		Modele::Case* caseCourante = modele_->getCase(positionCurseur_);
		if (caseCourante->getTerrain() != Modele::Terrain::aquatique && caseCourante->getObstacle() == Modele::Obstacle::aucun && caseCourante->getUnite() == nullptr)
		{
			std::cout << id << std::endl;
			uniteCourante_->setPosition(positionCurseur_);
			std::cout << positionCurseur_.x << " / " << positionCurseur_.y << std::endl;
			modele_->ajouterUnite(uniteCourante_);
			vue_->ajouterUnite(uniteCourante_, Vue::Unite::cheminTextureUnite.at(uniteCourante_->getClasse()));
			std::cout <<" : "<< caseCourante->getUnite()->getPosition().x << " / " << caseCourante->getUnite()->getPosition().y << std::endl;

			if (equipeCourante == Modele::Equipe::Rouge)
			{
				nbUniteAPlacerRouge = nbUniteAPlacerRouge - 1;
				Controleur::Fenetre::empilerGameState(new MenuPlacement(Modele::Equipe::Bleu));
				equipeCourante = Modele::Equipe::Bleu;
			}
			else
			{
				nbUniteAPlacerBleue = nbUniteAPlacerBleue - 1;
				Controleur::Fenetre::empilerGameState(new MenuPlacement(Modele::Equipe::Rouge));
				equipeCourante = Modele::Equipe::Rouge;
			}
			if (nbUniteAPlacerRouge == 0 && nbUniteAPlacerBleue == 0)
			{
				Controleur::Fenetre::depilerGameState();
				etatCombat_ = EtatCombat::Selection;
				return;
			}
		}
		return;

	}
	void Grille::setUniteAPlacer(Modele::Unite* unite)
	{
		uniteCourante_ = unite;
	}

	void Grille::deplacerCurseur(Modele::Vecteur2<int> deplacement)
	{
		vue_->detruireInfomationPersonnage();
		modele_->getCase(positionCurseur_+deplacement);
		positionCurseur_ += deplacement;
		vue_->deplacerCurseur(deplacement);
		Modele::Unite* uniteCurseur = modele_->getCase(positionCurseur_)->getUnite();
		if (uniteCurseur != nullptr)
			vue_->genererInformationPersonnage(uniteCurseur);
	}

	void Grille::setPositionCurseur(Modele::Vecteur2<int> position)
	{
		vue_->detruireInfomationPersonnage();
		modele_->getCase(position);
		positionCurseur_ = position;
		vue_->setPositionCurseur(position);
		Modele::Unite* uniteCurseur = modele_->getCase(positionCurseur_)->getUnite();
		if (uniteCurseur != nullptr)
			vue_->genererInformationPersonnage(uniteCurseur);
	}

	void Grille::genererCasesAccessiblesDeplacement()
	{
		std::list<Modele::Vecteur2<int>> casesAccessibles(modele_->chercherCasesAccessiblesDeplacement(positionCurseur_, modele_->getCase(positionCurseur_)->getUnite()->getPorteeDeplacement()));
		vue_->genererFiltreSurCases(casesAccessibles);
	}
	void Grille::genererCasesAccessiblesAttaque()
	{
		std::list<Modele::Vecteur2<int>> casesAccessibles(modele_->chercherCasesAccessiblesAttaque(positionCurseur_, modele_->getCase(positionCurseur_)->getUnite()->getPorteeAttaque()));
		vue_->genererFiltreSurCases(casesAccessibles);
	}

	void Grille::setPositionCurseurUniteActuel()
	{
		Modele::Unite* uniteActuel = modele_->getUniteActuel();
		positionCurseur_ = uniteActuel->getPosition();
		vue_->setPositionCurseur(uniteActuel->getPosition());
		vue_->detruireInfomationPersonnage();
		vue_->genererInformationPersonnage(uniteActuel);
	}

	void Grille::finirTourUniteActuel()
	{
		modele_->finDeTour();
		Modele::Unite* uniteActuel = modele_->getUniteActuel();
		if (uniteActuel == nullptr)
		{
			modele_->relancerOrdreDeJeu();
		}
		setPositionCurseurUniteActuel();
		actionFaite_ = false;
		deplacementFait_ = false;
	}
	Modele::Grille* Grille::getGrilleModele() {
		return modele_;
	}

	void Grille::deplacerUniteDepuisReseaux(std::string nom, Modele::Vecteur2<int> deplacement)
	{
		Modele::Unite* uniteADeplacer = nullptr;
		for(Modele::Unite* unite : modele_->getUnites())
		{
			if(unite->getNom() == nom)
			{
				uniteADeplacer = unite;
				break;
			}
		}

		modele_->deplacerUnite(uniteADeplacer, deplacement);

		vue_->deplacerUnite(uniteADeplacer, deplacement);
	}

	void Grille::attaquerUniteDepuisReseaux(std::string source, std::string cible)
	{
		Modele::Unite* uniteSource = nullptr;
		for (Modele::Unite* unite : modele_->getUnites())
		{
			if (unite->getNom() == source)
			{
				uniteSource = unite;
				break;
			}
		}

		Modele::Unite* uniteCible = nullptr;
		for (Modele::Unite* unite : modele_->getUnites())
		{
			if (unite->getNom() == cible)
			{
				uniteCible = unite;
				break;
			}
		}

		vue_->attaquerUnite(uniteSource, uniteCible);
		uniteSource->attaquer(uniteCible);
	}
}
