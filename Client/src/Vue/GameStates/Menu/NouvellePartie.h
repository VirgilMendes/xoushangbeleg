#include <string>
#include "../../Outils/Animation.h"
#include "../MenuChoix.h"

namespace Controleur {
	class NouvellePartie;
}

namespace Vue
{

	class NouvellePartie : public MenuChoix
	{
	public:

		NouvellePartie(std::vector<Controleur::Choix> choix, Controleur::NouvellePartie* controleur);

		void afficher() override;

		void NouvellePartie::setIP();
		void NouvellePartie::setIP(std::string std);
		std::string NouvellePartie::getIP();

	private:

		sf::Texture textureLogo_;
		sf::Sprite logo_;

		Animation animationLogo_;

		sf::Text titreMenu_;

		sf::Text ip_;
	};

}
