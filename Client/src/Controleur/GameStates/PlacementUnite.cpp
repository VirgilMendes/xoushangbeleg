#include "PlacementUnite.h"
#include "../../Modele/Unite/Unite.h"

namespace Controleur {

	PlacementUnite::PlacementUnite()
	{

		vue_ = new Vue::PlacementUnite(this, Modele::Equipe::Bleu, 9);
		interfaceUtilisateur_ = true;
	}

	void PlacementUnite::handleEvent()
	{
		vue_->handleEvent();
	}

	void PlacementUnite::update()
	{
		vue_->update();
	}

	void PlacementUnite::afficher()
	{
		vue_->afficher();
	}
}