#include "Grille.h"
#include "../../Modele/Case.h"

namespace Controleur
{
	Grille::Grille(Modele::Vecteur2<int> dimension) : modele_(new Modele::Grille(dimension)), vue_(new Vue::Grille(modele_, this))
	{
		Modele::Unite* unite = new Modele::Archer(Modele::Equipe::Bleu, "Archer", 3,4);
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
		std::list<Modele::Vecteur2<int>> casesAccessibles(modele_->chercherCasesAccessibles(positionCurseur_, 2));
		for (auto caseAccessible : casesAccessibles)
			std::cout << std::to_string(caseAccessible) << std::endl;
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
		modele_->getCase(positionCurseur_+deplacement);
		positionCurseur_ += deplacement;
		vue_->deplacerCurseur(deplacement);
	}

	void Grille::setPositionCurseur(Modele::Vecteur2<int> position)
	{
		modele_->getCase(position);
		positionCurseur_ = position;
		vue_->setPositionCurseur(position);
	}
}
