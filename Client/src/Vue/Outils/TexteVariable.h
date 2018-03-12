#pragma once

#include "SFML/Graphics.hpp"
#include "../../Controleur/Navigation.h"

namespace Vue
{
	class TexteVariable : public sf::Text
	{
	public:
		TexteVariable() : Text("", Controleur::Fenetre::getPoliceParDefaut(), 15), positionValeurVariable_(0) {}
		TexteVariable(const std::string& texteConstant, const int positionValeurVariable = -1) : Text(texteConstant, Controleur::Fenetre::getPoliceParDefaut(), 15)
		{
			if (positionValeurVariable < 0)
				positionValeurVariable_ = texteConstant.size();
			else positionValeurVariable_ = positionValeurVariable;
		}

		void setValeurVariable(std::string valeur)
		{
			if (valeur == valeurVariable_)
				return;

			sf::String chaine = getString();
			chaine.erase(positionValeurVariable_, valeurVariable_.getSize());
			valeurVariable_ = valeur;
			chaine.insert(positionValeurVariable_, valeurVariable_);
			sf::Text::setString(chaine);
		}

		void setTexteConstant(std::string texte, int positionValeurVariable = -1)
		{
			if (positionValeurVariable < 0)
				positionValeurVariable_ = texte.size();
			else positionValeurVariable_ = positionValeurVariable;

			texte.insert(positionValeurVariable_, valeurVariable_);

			sf::Text::setString(texte);
		}
		
		void setString(const sf::String& string) = delete;

		private:

			int positionValeurVariable_;
			sf::String valeurVariable_;

	};
}