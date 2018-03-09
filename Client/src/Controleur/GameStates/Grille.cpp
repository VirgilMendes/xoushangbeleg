#include "Grille.h"
#include "../../Modele/Case.h"
#include "../Navigation.h"
#include "MenuCombat/MenuAction.h"

namespace Controleur
{
	Grille::Grille(Modele::Vecteur2<int> dimension) : modele_(new Modele::Grille(dimension)), vue_(new Vue::Grille(modele_, this))
	{
		Modele::Unite* billy = new Modele::Tank("Billy", Modele::Equipe::Bleu, Modele::Vecteur2<int>(3,4));
		modele_->ajouterUnite(billy);
		vue_->ajouterUnite(billy, Vue::Unite::cheminTextureUnite.at(billy->getClasse()));

		Modele::Unite* roger = new Modele::Archer("Roger", Modele::Equipe::Rouge, Modele::Vecteur2<int>(4, 4));
		modele_->ajouterUnite(roger);
		vue_->ajouterUnite(roger, Vue::Unite::cheminTextureUnite.at(roger->getClasse()));

		Modele::Unite* gerard = new Modele::Soldat("Gerard", Modele::Equipe::Bleu, Modele::Vecteur2<int>(4, 3));
		modele_->ajouterUnite(gerard);
		vue_->ajouterUnite(gerard, Vue::Unite::cheminTextureUnite.at(gerard->getClasse()));
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
		if(!modele_->getDerniereRechercheAttaque().empty())
		{
			std::list<Modele::Vecteur2<int>> derniereRechercheAttaque = modele_->getDerniereRechercheAttaque();
			if (std::find(derniereRechercheAttaque.begin(), derniereRechercheAttaque.end(), positionCurseur_) != derniereRechercheAttaque.end());
			{
				Modele::Unite* unite = modele_->getCase(positionCurseur_)->getUnite();
				if (unite != nullptr)
				{
					modele_->getProprietaireDerniereRechercheAttaque()->attaquer(unite);
					if(unite->getVieCourante() < 0)
					{
						vue_->supprimerUnite(unite);
						modele_->supprimerUnite(unite);
					}
					else
					{
						vue_->detruireInfomationPersonnage();
						vue_->genererInformationPersonnage(unite);
					}
				}	
			}
			modele_->nettoyerDerniereRechercheAttaque();
			vue_->supprimerFiltreSurCases();
			return;
		}
		std::list<Modele::Vecteur2<int>> derniereRecherche = modele_->getDerniereRechercheDeplacement();
		if (std::find(derniereRecherche.begin(), derniereRecherche.end(), positionCurseur_) == derniereRecherche.end())
		{
			modele_->nettoyerDerniereRechercheDeplacement();
			vue_->supprimerFiltreSurCases();
			Modele::Unite* unite = modele_->getCase(positionCurseur_)->getUnite();
			if (unite != nullptr)
			{
				Controleur::Fenetre::empilerGameState(new Controleur::MenuAction());
			}
		}
		else
		{
			Modele::Unite* unite = modele_->getProprietaireDerniereRechercheDeplacement();
			Modele::Vecteur2<int> anciennePosition = unite->getPosition();
			Modele::Vecteur2<int> deplacement = positionCurseur_ - anciennePosition;

			modele_->deplacerUnite(unite, deplacement);
			modele_->nettoyerDerniereRechercheDeplacement();
			vue_->deplacerUnite(unite, deplacement);
			vue_->supprimerFiltreSurCases();
			vue_->genererInformationPersonnage(unite);
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
}
