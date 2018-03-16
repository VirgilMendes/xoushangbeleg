#include "Grille.h"
#include "../../Modele/Case.h"
#include "../../Controleur/GameStates/GameState.h"
#include "../../Controleur/Navigation.h"
#include "../../Controleur/GameStates/Grille.h"
#include "../Composants/Grille/FiltreCase.h"

namespace Vue
{
	Grille::Grille(Modele::Grille* modele, Controleur::Grille* controleur) : sf::View(sf::Vector2f(0,0), sf::Vector2f(1280, 720)), modele_(modele), controleur_(controleur), interfaceUnite_(nullptr)
	{
		horloge_ = new sf::Clock;

		if (!textureGrille_.loadFromFile("ressources/sprite/map.png"))
		{
			std::cout << "erreur chargement Texture TextureGrille.png" << std::endl;
		}
		if (!textureObstacle_.loadFromFile("ressources/sprite/TextureObstacles.png"))
		{
			std::cout << "erreur chargement Texture TextureObstacle.png" << std::endl;
		}

		const int largeur(modele_->getDimension().x), hauteur(modele_->getDimension().y);

		// on redimensionne le tableau de vertex pour qu'il puisse contenir tout le niveau
		sommets_.setPrimitiveType(sf::Quads);
		sommets_.resize( largeur * hauteur * 4);

		// on remplit le tableau de vertex, avec un quad par tuile
		for (unsigned int i = 0; i < largeur; ++i)
			for (unsigned int j = 0; j < hauteur; ++j)
			{
				Modele::Case* caseGrille = modele_->getCase(Modele::Vecteur2<int>(i,j));

				// on recupere le code de tuile courant
				const int caseNombre(caseGrille->getTerrain()._to_integral() * 8 + caseGrille->getObstacle()._to_integral() * 2 + 1);

				// on recupere un pointeur vers le quad a definir dans le tableau de vertex
				sf::Vertex* quad = &sommets_[(i + j * largeur) * 4];

				// on definit ses quatre coins
				quad[0].position = sf::Vector2f(i * RES_TEXTURE_XSB, j * RES_TEXTURE_XSB);
				quad[1].position = sf::Vector2f((i + 1) * RES_TEXTURE_XSB, j * RES_TEXTURE_XSB);
				quad[2].position = sf::Vector2f((i + 1) * RES_TEXTURE_XSB, (j + 1) * RES_TEXTURE_XSB);
				quad[3].position = sf::Vector2f(i * RES_TEXTURE_XSB, (j + 1) * RES_TEXTURE_XSB);

				// on definit ses quatre coordonnees de texture
				quad[0].texCoords = sf::Vector2f(caseNombre * RES_TEXTURE_XSB, 0);
				quad[1].texCoords = sf::Vector2f((caseNombre + 1) * RES_TEXTURE_XSB, 0);
				quad[2].texCoords = sf::Vector2f((caseNombre + 1) * RES_TEXTURE_XSB, RES_TEXTURE_XSB);
				quad[3].texCoords = sf::Vector2f(caseNombre * RES_TEXTURE_XSB, RES_TEXTURE_XSB);
			}
		setCenter(0, 0);
	}

	Grille::~Grille()
	{
		auto iterateur = textures_.begin();
		while (iterateur != textures_.end())
		{
			delete iterateur->second;
			++iterateur;
		}
		if (interfaceUnite_ != nullptr)
			delete interfaceUnite_;
	}

	void Grille::miseAJourAnimation()
	{
		if (horloge_->getElapsedTime().asMilliseconds() >= 1000)
		{
			if (frame_ == 1)
			{
				frame_ = 0;
			}
			else
			{
				frame_ = 1;
			}
			horloge_->restart();
		}

		const int largeur(modele_->getDimension().x), hauteur(modele_->getDimension().y);

		for (int i = 0; i < largeur; i++)
		{
			for (int j = 0; j < hauteur; j++)
			{
				Modele::Case* caseGrille = modele_->getCase(Modele::Vecteur2<int>(i, j));
				sf::Vertex* quad = &sommets_[(i + j * largeur) * 4];
				const int caseNombre(caseGrille->getTerrain()._to_integral() * 8 + caseGrille->getObstacle()._to_integral() * 2 + 1);

				quad[0].texCoords = sf::Vector2f((caseNombre - 1 + frame_) * RES_TEXTURE_XSB, 0);
				quad[1].texCoords = sf::Vector2f((caseNombre + frame_) * RES_TEXTURE_XSB, 0);
				quad[2].texCoords = sf::Vector2f((caseNombre + frame_) * RES_TEXTURE_XSB, RES_TEXTURE_XSB);
				quad[3].texCoords = sf::Vector2f((caseNombre - 1 + frame_) * RES_TEXTURE_XSB, RES_TEXTURE_XSB);
			}
		}
	}

	void Grille::setPositionCurseur(Modele::Vecteur2<int> position)
	{
		curseur_.setPosition(position);
		setCenter(position.x*64, position.y*64);
	}

	void Grille::deplacerCurseur(Modele::Vecteur2<int> deplacement)
	{
		curseur_.deplacerCurseur(deplacement);	
		setCenter(getCenter()+sf::Vector2f(deplacement.x*64, deplacement.y*64));
	}

	void Grille::ajouterUnite(Modele::Unite* unite, std::string cheminTexture)
	{
		
		sf::Texture* texture;
		if (textures_.find(cheminTexture) == textures_.end())
		{
			sf::Image image;
			image.loadFromFile(cheminTexture);
			image.createMaskFromColor(sf::Color::Transparent, 0);

			texture = new sf::Texture;
			texture->loadFromImage(image);
		}
		else
		{
			texture = textures_[cheminTexture];
		}
		unites_.push_back(Unite(unite, texture));
	}

	void Grille::deplacerUnite(Modele::Unite* unite, Modele::Vecteur2<int> deplacement)
	{
		Vue::Unite* uniteVue = nullptr;
		for(auto iterateur(unites_.begin()); iterateur != unites_.end(); ++iterateur )
		{
			if (iterateur->getModele() == unite)
			{
				uniteVue = &(*iterateur);
				break;
			}
		}
		if(uniteVue == nullptr)
			return;

		std::stack<Modele::Vecteur2<int>> chemin = this->modele_->chercherChemin(uniteVue->getModele()->getPosition()+deplacement);
		int i = uniteVue->getPosition().x;
		int j = uniteVue->getPosition().y;
		std::cout << " debut : i = " << i << " / j = " << j << std::endl;
		while (!chemin.empty())
		{
			std::cout << "pile : x = " << chemin.top().x << " / y = " << chemin.top().y << std::endl;
			if (i != chemin.top().x*RES_TEXTURE_XSB)
			{
				if (i < chemin.top().x*RES_TEXTURE_XSB)
				{
					while (i < chemin.top().x*RES_TEXTURE_XSB)
					{
						i+=8;
						uniteVue->setPosition(Modele::Vecteur2<int>(i, j));
						this->afficher();
					}
				}
				else
				{
					while (i > chemin.top().x*RES_TEXTURE_XSB)
					{
						i -= 8;
						uniteVue->setPosition(Modele::Vecteur2<int>(i, j));
						this->afficher();
					}
				}
				std::cout << "sprite : x = " << uniteVue->getPosition().x << " / y = " << uniteVue->getPosition().y << std::endl;
			}
			else 
			{
				if (j < chemin.top().y*RES_TEXTURE_XSB)
				{
					while (j < chemin.top().y*RES_TEXTURE_XSB)
					{
						j+=8;
						uniteVue->setPosition(Modele::Vecteur2<int>(i, j));
						this->afficher();
					}
				}
				else
				{
					while (j > chemin.top().y*RES_TEXTURE_XSB)
					{
						j-=8;
						uniteVue->setPosition(Modele::Vecteur2<int>(i, j));
						this->afficher();
					}
				}
				std::cout << "sprite : x = " << uniteVue->getPosition().x << " / y = " << uniteVue->getPosition().y << std::endl;
			}
			std::cout << "i = " << i << " / j = " << j << std::endl;
			i = chemin.top().x*RES_TEXTURE_XSB;
			j = chemin.top().y*RES_TEXTURE_XSB;
			chemin.pop();
		}
	}

	void Grille::supprimerUnite(Modele::Unite* unite)
	{
		for (auto iterateur(unites_.begin()); iterateur != unites_.end(); ++iterateur)
		{
			if ((*iterateur).getModele() == unite)
			{
				iterateur->mourrir();;
				return;
			}
		}
	}

	void Grille::genererInformationPersonnage(Modele::Unite* unite)
	{
		interfaceUnite_ = new InterfaceUnite(unite);
	}

	void Grille::detruireInfomationPersonnage()
	{
		interfaceUnite_ = __nullptr;
	}

	void Grille::genererFiltreSurCases(std::list<Modele::Vecteur2<int>> cases)
	{
		filtreCase_ = new FiltreCase(cases);
	}

	void Grille::supprimerFiltreSurCases()
	{
		filtreCase_ = nullptr;
	}

	void Grille::handleEvent()
	{
		sf::Event event;
		while (Controleur::Fenetre::fenetre->pollEvent(event))
		{
			switch (event.type)
			{

			case sf::Event::Closed:
				Controleur::Fenetre::fenetre->close();
			case sf::Event::KeyPressed:
				switch (event.key.code)
				{
				case sf::Keyboard::Z: case sf::Keyboard::Up:
					controleur_->enclencherActionDeplacement(Controleur::ActionDeplacement::Bas);
					break;
				case sf::Keyboard::D: case sf::Keyboard::Right:
					controleur_->enclencherActionDeplacement(Controleur::ActionDeplacement::Droite);
					break;
				case sf::Keyboard::S: case sf::Keyboard::Down:
					controleur_->enclencherActionDeplacement(Controleur::ActionDeplacement::Haut);
					break;
				case sf::Keyboard::Q: case sf::Keyboard::Left:
					controleur_->enclencherActionDeplacement(Controleur::ActionDeplacement::Gauche);
					break;
				case sf::Keyboard::K: case sf::Keyboard::Return:
					controleur_->enclencherActionValidation();
					break;
				case sf::Keyboard::Escape:
					Controleur::Fenetre::fenetre->close();
					break;
				default: break;
				}
			}
		}
	}

	void Grille::update()
	{
	}

	void Grille::afficher()
	{
		sf::RenderWindow* fenetre = Controleur::Fenetre::fenetre;
		sf::RenderStates etat;

		miseAJourAnimation();

		fenetre->setView(*this);
		// on applique la texture du tileset du sol
		etat.texture = &textureGrille_;

		// et on dessine enfin le tableau de vertex du sol 
		fenetre->draw(sommets_, etat);

		fenetre->draw(curseur_, etat);

		for (Unite unite : unites_)
			unite.dessiner(fenetre, etat);

		if (filtreCase_ != nullptr)
			filtreCase_->dessiner(fenetre, etat);

		fenetre->setView(fenetre->getDefaultView());
		if (interfaceUnite_ != nullptr)
			interfaceUnite_->dessiner(fenetre, etat);

	}
}