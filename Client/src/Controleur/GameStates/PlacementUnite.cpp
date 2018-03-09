#include "PlacementUnite.h"
#include "../../Modele/Unite/Unite.h"

namespace Controleur {

	PlacementUnite::PlacementUnite()
	{

		vue_ = new Vue::PlacementUnite(Modele::Equipe::Bleu, 9);
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