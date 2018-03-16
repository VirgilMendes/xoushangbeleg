#include <string>
#include "../../Outils/Animation.h"
#include "../MenuChoix.h"

namespace Controleur {
	class RejoindrePartie;
}

namespace Vue
{

	class RejoindrePartie : public MenuChoix
	{
	public:

		RejoindrePartie(std::vector<Controleur::Choix> choix, Controleur::RejoindrePartie* controleur);

		void afficher() override;

		void setIP();
		void setIP(std::string std);
		std::string getIP();

	private:

		sf::Texture textureLogo_;
		sf::Sprite logo_;

		Animation animationLogo_;

		sf::Text titreMenu_;

		sf::Text ip_;
	};

}
