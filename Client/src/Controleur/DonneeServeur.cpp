#pragma once

#include "DonneeServeur.h"

namespace Controleur {

	void DonneeServeur::decoderXml(std::string chaineXMl) {
		pugi::xml_document document;
		document.load_string(chaineXMl.c_str());
		pugi::xml_node action = document.child("paquet").first_child(); 
		std::string nomAction = std::string(action.name());
		
		if (nomAction == "finDeTour")
		{
			executerFinDeTourDepuisXML(action);
		}
		else if (nomAction == "deplacement")
		{
			std::cout << "test" << std::endl;
			executerDeplacementUniteDepuisXML(action);
		}
		else if (nomAction == "attaque")
		{
			executerAttaqueUniteDepuisXML(action);
		}
		else
		{
			return;
		}


	}

	std::string DonneeServeur::genererDeplacementUniteVersXML(std::string nom, Modele::Vecteur2<int> deplacement)
	{
		pugi::xml_document document;
		pugi::xml_node nodeAction = document.append_child("paquet").append_child("deplacement");
		pugi::xml_node nodeUnite = nodeAction.append_child("unite");
		nodeUnite.append_attribute("nom").set_value(nom.c_str());
		pugi::xml_node nodeDeplacement = nodeAction.append_child("deplacement");
		nodeDeplacement.append_attribute("x").set_value(deplacement.x);
		nodeDeplacement.append_attribute("y").set_value(deplacement.y);

		std::stringstream flux;
		document.print(flux);
		return flux.str();
	}

	void DonneeServeur::executerDeplacementUniteDepuisXML(pugi::xml_node action) 
	{
		
		std::string nom = action.child("unite").attribute("nom").as_string();

		pugi::xml_node nodeDeplacement = action.child("deplacement");
		Modele::Vecteur2<int> deplacement(nodeDeplacement.attribute("x").as_int(), nodeDeplacement.attribute("y").as_int());

		Grille* grille = Controleur::Fenetre::getProchaineGrille();
		std::cout << nom << " " << std::to_string(deplacement) << std::endl;
		grille->deplacerUniteDepuisReseaux(nom, deplacement);
	}

	std::string DonneeServeur::genererAttaqueUniteVersXML(std::string source, std::string cible)
	{
		pugi::xml_document document;
		pugi::xml_node nodeAction = document.append_child("paquet").append_child("attaque");
		pugi::xml_node nodeSource = nodeAction.append_child("source");
		nodeSource.append_attribute("nom").set_value(source.c_str());
		pugi::xml_node nodeCible = nodeAction.append_child("cible");
		nodeCible.append_attribute("nom").set_value(cible.c_str());

		std::stringstream flux;
		document.print(flux);
		return flux.str();
	}

	void DonneeServeur::executerAttaqueUniteDepuisXML(pugi::xml_node action)
	{
		std::string source = action.child("source").attribute("nom").as_string();
		std::string cible = action.child("cible").attribute("nom").as_string();

		Grille* grille = Controleur::Fenetre::getProchaineGrille();
		grille->attaquerUniteDepuisReseaux(source, cible);
	}

	std::string DonneeServeur::genererFinDeTourVersXML()
	{
		pugi::xml_document document;
		pugi::xml_node nodeAction = document.append_child("paquet").append_child("finDeTour");

		std::stringstream flux;
		document.print(flux);
		return flux.str();
	}

	void DonneeServeur::executerFinDeTourDepuisXML(pugi::xml_node action)
	{
		Grille* grille = Controleur::Fenetre::getProchaineGrille();
		std::cout << "loli" << std::endl;
		grille->finirTourDepuisReseaux();
	}

	std::string DonneeServeur::genererGrilleVersChaineXML(Modele::Grille* grille)
	{
		pugi::xml_document document;
		pugi::xml_node nodeRacine = document.append_child("paquet").append_child("initialisation");
		pugi::xml_node nodeGrille = nodeRacine.append_child("grille");

		Modele::Vecteur2<int> dimension = grille->getDimension();
		pugi::xml_node nodeDimension = nodeGrille.append_child("dimension");
		nodeDimension.append_attribute("x").set_value(dimension.x);
		nodeDimension.append_attribute("y").set_value(dimension.y);

		for (std::vector<Modele::Case*> ligne : grille->getCases())
		{
			for (Modele::Case* caseModele : ligne)
			{
				pugi::xml_node nodeCase = nodeGrille.append_child("case");

				Modele::Vecteur2<int> position = caseModele->getPosition();
				pugi::xml_node nodePosition = nodeCase.append_child("position");
				nodePosition.append_attribute("x").set_value(position.x);
				nodePosition.append_attribute("y").set_value(position.y);
				nodePosition.append_attribute("test").set_value("test");
				nodeCase.append_child("terrain").text().set(caseModele->getTerrain()._to_string());
				nodeCase.append_child("obstacle").text().set(caseModele->getObstacle()._to_string());
			}
		}

		pugi::xml_node nodeUnites = nodeRacine.append_child("unites");

		for (Modele::Unite* unite: grille->getUnites())
		{
			pugi::xml_node nodeUnite = nodeUnites.append_child("unite");
			nodeUnite.append_attribute("nom").set_value(unite->getNom().c_str());
			
			Modele::Vecteur2<int> position = unite->getPosition();
			pugi::xml_node nodePosition = nodeUnite.append_child("position");
			nodePosition.append_attribute("x").set_value(position.x);
			nodePosition.append_attribute("y").set_value(position.y);

			nodeUnite.append_child("equipe").text().set(unite->getEquipe()._to_string());
			nodeUnite.append_child("classe").text().set(unite->getClasse()._to_string());
		}

		std::stringstream flux;
		document.print(flux);
		return flux.str();
	}

	Modele::Grille* DonneeServeur::initialiserGrilleDepuisChaineXML(std::string xml)
	{
		pugi::xml_document document;
		document.load_string(xml.c_str());

		pugi::xml_node nodePaquet = document.child("paquet").child("initialisation");
		pugi::xml_node nodeGrille = nodePaquet.child("grille");

		pugi::xml_node nodeDimension = nodeGrille.child("dimension");
		Modele::Vecteur2<int> dimension(nodeDimension.attribute("x").as_int(), nodeDimension.attribute("y").as_int());
		std::vector<std::vector<Modele::Case*>> cases(dimension.x, std::vector<Modele::Case*>(dimension.y, nullptr));
		std::set<Modele::Unite*, Modele::ComparateurPointeurUniteNom> unites;

		for(pugi::xml_node nodeCase : nodeGrille)
		{
			if (std::string(nodeCase.name()) != "case") continue;;

			pugi::xml_node nodePosition = nodeCase.child("position");
			Modele::Vecteur2<int> position(nodePosition.attribute("x").as_int(), nodePosition.attribute("y").as_int());
			
			Modele::Terrain terrain = Modele::Terrain::_from_string_nocase(nodeCase.child("terrain").text().as_string());
			Modele::Obstacle obstacle = Modele::Obstacle::_from_string_nocase(nodeCase.child("obstacle").text().as_string());

			Modele::Case* caseModele = new Modele::Case
			(
				position,
				terrain,
				obstacle
			);
			cases[position.y][position.x] = caseModele;
			
		}

		pugi::xml_node nodeUnites = nodePaquet.child("unites");
		for (pugi::xml_node nodeUnite : nodeUnites)
		{
			pugi::xml_node nodePosition = nodeUnite.child("position");
			
			std::string nom = nodeUnite.attribute("nom").as_string();
			Modele::Vecteur2<int> position = Modele::Vecteur2<int>(nodePosition.attribute("x").as_int(), nodePosition.attribute("y").as_int());
			Modele::Equipe equipe = Modele::Equipe::_from_string_nocase(nodeUnite.child("equipe").text().as_string());
			Modele::Classe classe = Modele::Classe::_from_string_nocase(nodeUnite.child("classe").text().as_string());
			
			switch(classe)
			{
				case Modele::Classe::Tank:
					unites.insert(new Modele::Tank(nom, equipe, position));
					break;
				case Modele::Classe::Archer:
					unites.insert(new Modele::Archer(nom, equipe, position));
					break;
				case Modele::Classe::Soldat:
					unites.insert(new Modele::Soldat(nom, equipe, position));
					break;
			}
		}

		return new Modele::Grille(cases, unites);
	}
}
