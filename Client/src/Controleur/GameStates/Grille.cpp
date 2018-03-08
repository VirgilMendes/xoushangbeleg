#include "Grille.h"
#include "../../Modele/Case.h"

namespace Controleur
{
	Grille::Grille(Modele::Vecteur2<int> dimension) : modele_(new Modele::Grille(dimension)), vue_(new Vue::Grille(modele_, this))
	{
		Modele::Unite* unite = new Modele::Tank("Billy", Modele::Equipe::Bleu, Modele::Vecteur2<int>(3,4));
		modele_->ajouterUnite(unite);
		vue_->ajouterUnite(unite, Vue::Unite::cheminTextureUnite.at(unite->getClasse()));
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

	void Grille::dessiner()
	{
		vue_->dessiner();
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
		
		std::list<Modele::Vecteur2<int>> derniereRecherche = modele_->getDerniereRecherche();
		if (std::find(derniereRecherche.begin(), derniereRecherche.end(), positionCurseur_) == derniereRecherche.end())
		{
			vue_->supprimerFiltreSurCases();
			Modele::Unite* unite = modele_->getCase(positionCurseur_)->getUnite();
			if (unite != nullptr)
			{
				std::list<Modele::Vecteur2<int>> casesAccessibles(modele_->chercherCasesAccessibles(positionCurseur_, unite->getPorteeDeplacement()));
				vue_->genererFiltreSurCases(casesAccessibles);
			}
		}
		else
		{
			Modele::Unite* unite = modele_->getProprietaireDerniereRecherche();
			Modele::Vecteur2<int> anciennePosition = unite->getPosition();
			Modele::Vecteur2<int> deplacement = positionCurseur_ - anciennePosition;

			modele_->deplacerUnite(unite, deplacement);
			modele_->nettoyerDerniereRecherche();
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
}
