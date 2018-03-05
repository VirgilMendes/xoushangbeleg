#pragma once
#include <SFML/Graphics.hpp>

namespace Vue
{
	class Node
	{
	public:
		virtual ~Node() = default;

		Node(){}
		
		//Fonction de transformation relative
		virtual void deplacerRelativement(sf::Vector2f deplacement) final
		{
			transformation_.translate(deplacement);
		}
		virtual void echelonnerRelativement(sf::Vector2f echelon) final
		{
			transformation_.scale(echelon);
		}
		virtual void pivoterRelativement(sf::Vector2f rotation) final
		{
			transformation_.translate(rotation);
		}

		//Fonction de transformation global
		virtual void setPosition(sf::Vector2i position) final
		{
			position_ = position;
			for (std::pair<std::string, Node*> enfant : enfants_)
			{
				enfant.second->setPosition(position);
			}
			setPositionElements(position);
		}
		virtual void setTaille(sf::Vector2i taille) final
		{
			taille_ = taille;
			for (std::pair<std::string, Node*> enfant : enfants_)
			{
				enfant.second->setPosition(taille);
			}
			setTailleElements(taille);
		}
		virtual void setRotation(int rotation) final
		{
			rotation_ = rotation;
			for (std::pair<std::string, Node*> enfant : enfants_)
			{
				enfant.second->setRotation(rotation);
			}
			setRotationElements(rotation);
		}

		//Fonction de gestion des enfants
		virtual void ajouterEnfant(std::string nom, Node* node) final
		{
			if (enfants_.count(nom))
				throw std::runtime_error("nom de Node existe déjà");
			enfants_[nom] = node;
		}

		virtual Node* getEnfant(std::string nom) final
		{
			return enfants_.at(nom);
		}

		virtual std::map<std::string,Node*> getEnfants(std::string nom) final
		{
			return enfants_;
		}

		virtual void retirerEnfant(std::string nom) final
		{
			enfants_.erase(enfants_.find(nom));
		}
		
		//Dessin
		virtual  void dessiner(sf::RenderTarget* cible, const sf::Transform& transformationParent) final
		{
			sf::Transform transformationFinale = transformationParent * transformation_;

			dessinerNode(cible, transformationFinale);
	
			for (std::pair<std::string, Node*> enfant : enfants_)
				enfant.second->dessiner(cible, transformationFinale);
		}

	protected:

		virtual void dessinerNode(sf::RenderTarget* target, const sf::Transform& transform) = 0;
		virtual void setPositionElements(sf::Vector2i position) = 0;
		virtual void setTailleElements(sf::Vector2i taille) = 0;
		virtual void setRotationElements(int rotation) = 0;

		sf::Vector2i position_;
		sf::Vector2i taille_;
		int rotation_;

		sf::Transform transformation_;
		std::map<std::string, Node*> enfants_;
	};
}
