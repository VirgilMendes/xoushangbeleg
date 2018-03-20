#pragma once

#include "DonneeServeur.h"

namespace Controleur {

	void DonneeServeur::decodeXml(std::string str) {
		pugi::xml_document doc;
		pugi::xml_parse_result result = doc.load_buffer(str.c_str(), str.length());
		pugi::xml_node root = doc.document_element();
		//verification du premier node
		if ((std::string)root.first_child().name() == "deplacement")
		{
			deplacerUniteDepuisXML(root);
		}
		else if ((std::string)root.first_child().name() == "initialisation")
		{
			//initialiserGrilleDepuisChaineXML(root);
		}
		else
		{

		}


	}
	void DonneeServeur::deplacerUniteDepuisXML(pugi::xml_node root) {
		//nom de l'unite
		std::string nomUnite = root.child("deplacement").child("unite").child("nom").child_value();

		Modele::Vecteur2<int> position;
		//position X de l'unite
		position.x = stoi((std::string)root.child("deplacement").child("position").child("x").child_value());
		//position Y de l'unite
		position.y = stoi((std::string)root.child("deplacement").child("position").child("y").child_value());

		//Vue::Combat* Combat = dynamic_cast<Vue::Combat*>(gameStates_.back());
		//Combat->deplacerUnite(nomUnite, position);
	}

	std::string DonneeServeur::deplacerUnite(std::string nom, Modele::Vecteur2<int> position)
	{
		//vueCombat->deplacerUnite(nom, position);

		pugi::xml_document doc;
		auto root = doc.append_child("paquet");
		pugi::xml_node nodeDeplacement = root.append_child("deplacement");
		pugi::xml_node nodeUnite = nodeDeplacement.append_child("unite");
		pugi::xml_node nodeNom = nodeUnite.append_child("nom");
		nodeNom.text().set(nom.c_str());
		pugi::xml_node nodePosition = nodeDeplacement.append_child("position");
		pugi::xml_node nodeX = nodePosition.append_child("x");
		nodeX.text().set((std::to_string(position.x).c_str()));
		pugi::xml_node nodeY = nodePosition.append_child("y");
		nodeY.text().set(std::to_string(position.y).c_str());
		std::stringstream flux;
		doc.print(flux);
		return flux.str();
	}
	
	std::string DonneeServeur::GrilleVersChaineXML(Modele::Grille* grille)
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
		std::set<Modele::Unite*> unites;

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
