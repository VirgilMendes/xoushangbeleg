#include "Grille.h"
#include "../../Modele/Case.h"

#define RESOLUTION 64

namespace Vue
{
	Grille::Grille(Modele::Grille* grille) : sf::View(sf::Vector2f(0,0), sf::Vector2f(1000, 700)), grille_(grille), interfaceUnite_(nullptr)
	{
		horloge_ = new sf::Clock;
		int frame = 0;

		if (!textureGrille_.loadFromFile("ressources/sprite/map.png"))
		{
			std::cout << "erreur chargement Texture TextureGrille.png" << std::endl;
		}
		if (!textureObstacle_.loadFromFile("ressources/sprite/TextureObstacles.png"))
		{
			std::cout << "erreur chargement Texture TextureObstacle.png" << std::endl;
		}

		const int largeur(grille_->getDimension().x), hauteur(grille_->getDimension().y);

		// on redimensionne le tableau de vertex pour qu'il puisse contenir tout le niveau
		sommets_.setPrimitiveType(sf::Quads);
		sommets_.resize( largeur * hauteur * 4);

		// on remplit le tableau de vertex, avec un quad par tuile
		for (unsigned int i = 0; i < largeur; ++i)
			for (unsigned int j = 0; j < hauteur; ++j)
			{
				Modele::Case* caseGrille = grille_->getCase(Modele::Vecteur2<int>(i,j));

				// on récupère le code de tuile courant
				const int caseNombre(caseGrille->getTerrain()._to_integral() * 8 + caseGrille->getObstacle()._to_integral() * 2 + 1);

				// on récupère un pointeur vers le quad à définir dans le tableau de vertex
				sf::Vertex* quad = &sommets_[(i + j * largeur) * 4];

				// on définit ses quatre coins
				quad[0].position = sf::Vector2f(i * RESOLUTION, j * RESOLUTION);
				quad[1].position = sf::Vector2f((i + 1) * RESOLUTION, j * RESOLUTION);
				quad[2].position = sf::Vector2f((i + 1) * RESOLUTION, (j + 1) * RESOLUTION);
				quad[3].position = sf::Vector2f(i * RESOLUTION, (j + 1) * RESOLUTION);

				// on définit ses quatre coordonnées de texture
				quad[0].texCoords = sf::Vector2f(caseNombre * RESOLUTION, 0);
				quad[1].texCoords = sf::Vector2f((caseNombre + 1) * RESOLUTION, 0);
				quad[2].texCoords = sf::Vector2f((caseNombre + 1) * RESOLUTION, RESOLUTION);
				quad[3].texCoords = sf::Vector2f(caseNombre * RESOLUTION, RESOLUTION);
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

		delete grille_; 
	}

	void Grille::miseAJourAnimation()
	{
		if (horloge_->getElapsedTime().asMilliseconds() >= 1000)
		{
			if (frame == 1)
			{
				frame = 0;
			}
			else
			{
				frame = 1;
			}
			horloge_->restart();
		}
		
		const int largeur(grille_->getDimension().x), hauteur(grille_->getDimension().y);

		for (int i = 0; i < largeur; i++)
		{
			for (int j = 0; j < hauteur; j++)
			{
				Modele::Case* caseGrille = grille_->getCase(Modele::Vecteur2<int>(i, j));
				sf::Vertex* quad = &sommets_[(i + j * largeur) * 4];
				const int caseNombre(caseGrille->getTerrain()._to_integral() * 8 + caseGrille->getObstacle()._to_integral() * 2 + 1);

				// on définit ses quatre coordonnées de texture
				quad[0].texCoords = sf::Vector2f((caseNombre - 1 + frame) * RESOLUTION, 0);
				quad[1].texCoords = sf::Vector2f((caseNombre + frame) * RESOLUTION, 0);
				quad[2].texCoords = sf::Vector2f((caseNombre + frame) * RESOLUTION, RESOLUTION);
				quad[3].texCoords = sf::Vector2f((caseNombre - 1 + frame) * RESOLUTION, RESOLUTION);
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
		if (interfaceUnite_ != nullptr)
		{
			delete interfaceUnite_;
			interfaceUnite_ = nullptr;
		}
		curseur_.deplacerCurseur(deplacement);
		if (grille_->getCase(curseur_.getPosition())->getUnite() != nullptr)
			interfaceUnite_ = new InterfaceUnite(grille_->getCase(curseur_.getPosition())->getUnite());
		
		setCenter(getCenter()+sf::Vector2f(deplacement.x*64, deplacement.y*64));
	}

	void Grille::ajouterUnite(std::string nom, std::string cheminTexture, Modele::Vecteur2<int> position)
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
		Modele::Unite* unite = new Modele::Archer(Modele::Equipe::Bleu, nom, position.x, position.y);
		grille_->ajouterUnite(unite);
		unites_.push_back(Unite(nom, texture, position));
	}



	void Grille::deplacerUnite(std::string nom, Modele::Vecteur2<int> position)
	{
		for(auto iterateur(unites_.begin()); iterateur != unites_.end(); ++iterateur )
		{
			if (iterateur->getNom() == nom)
			{
				iterateur->setPosition(position);
				grille_->deplacerUnite(nom, position);
				return;
			}
		}
	}

	void Grille::afficherCaseAccessible()
	{
		std::list<Modele::Vecteur2<int>> coordonneeCasesAccessibles = grille_->chercherCasesAccessibles(curseur_.getPosition(), 3);
		for(auto coordonneeCase : coordonneeCasesAccessibles)
			std::cout <<  std::to_string(coordonneeCase) << std::endl;
	}

	void Grille::dessiner(sf::RenderTarget& target, sf::RenderStates states)
	{
		Grille::miseAJourAnimation();

		target.setView(*this);
		// on applique la texture du tileset du sol
		states.texture = &textureGrille_;

		// et on dessine enfin le tableau de vertex du sol 
		target.draw(sommets_, states);

		target.draw(curseur_);

		for (Unite unite : unites_)
			target.draw(unite);

		target.setView(target.getDefaultView());
		if (interfaceUnite_ != nullptr)
			target.draw(*interfaceUnite_);
	}
}