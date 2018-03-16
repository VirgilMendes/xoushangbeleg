#pragma once

#include "DonneeServeur.h"

namespace Controleur {

	void DonneeServeur::decodeXml(std::string str) {
		pugi::xml_document doc;
		pugi::xml_parse_result result = doc.load_buffer(str.c_str(), str.length());
		pugi::xml_node root = doc.document_element();
		std::cout << (std::string)root.first_child().name() << std::endl;
		//verification du premier node
		if ((std::string)root.first_child().name() == "deplacement")
		{
			deplacerXml(root);
		}
		else if ((std::string)root.first_child().name() == "initialisation")
		{
			initialiserXml(root);
		}
		else
		{

		}


	}
	void DonneeServeur::deplacerXml(pugi::xml_node root) {
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

	void DonneeServeur::initialiserXml(pugi::xml_node root) {
		std::cout << "1" << std::endl;
		//Gerer la carte
		//root.child("carte")...

		//Unites
		//Variables pour les unites
		std::string nomUnite;
		Modele::Classe classeUnite;
		Modele::Equipe equipeUnite;
		Modele::Vecteur2<int> positionUnite;
		pugi::xml_node::iterator it;
		
		std::cout << root.child("initialisation").last_child().first_child().name() << std::endl;
		std::cout << root.child("initialisation").last_child().last_child().name() << std::endl;

		//Cas a part pour chaque unite
		for (it = root.child("initialisation").last_child().begin(); it != root.child("initialisation").last_child().end(); ++it) {
			//for (pugi::xml_node uniteXml = root.child("initialisation").child("unites").first_child(); uniteXml; uniteXml = uniteXml.next_sibling()) {
			pugi::xml_node uniteXml = *it;
			std::cout << "2" << std::endl;
			nomUnite = uniteXml.name();
			std::cout << "2.1" << std::endl;
			//classeUnite = Modele::Classe::_from_string(uniteXml.child("classe").child_value());
			std::cout << "2.2" << std::endl;
			//equipeUnite = Modele::Equipe::_from_string(uniteXml.child("equipe").child_value());
			//positionUnite.x = stoi((std::string)uniteXml.child("position").child("x").child_value());
			//positionUnite.y = stoi((std::string)uniteXml.child("position").child("y").child_value());
			/*if (classeUnite == Modele::Classe::_from_string("Archer")) {
			Modele::Archer uniteCree(nomUnite, equipeUnite, positionUnite);
			//grille.ajouterUnite(&uniteCree);
			}
			else if (classeUnite == Modele::Classe::_from_string("Soldat")) {
			Modele::Soldat uniteCree(nomUnite, equipeUnite, positionUnite);
			//grille.ajouterUnite(&uniteCree);
			}
			else {
			Modele::Tank uniteCree(nomUnite, equipeUnite, positionUnite);
			//grille.ajouterUnite(&uniteCree);
			}*/
		}
		std::cout << "3" << std::endl;
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
	std::string DonneeServeur::initialisatonCarteUnite() {
		pugi::xml_document doc;
		auto root = doc.append_child("paquet");
		pugi::xml_node nodeInitialisation = root.append_child("initialisation");
		pugi::xml_node nodeCarte = nodeInitialisation.append_child("carte");
		pugi::xml_node nodeNomCarte = nodeCarte.append_child("nom");
		pugi::xml_node nodeListeUnite = nodeInitialisation.append_child("unites");
		pugi::xml_node nodeUnite;
		pugi::xml_node nodeClasseUnite;
		pugi::xml_node nodeEquipeUnite;
		pugi::xml_node nodePositionUnite;
		pugi::xml_node nodePositionXUnite;
		pugi::xml_node nodePositionYUnite;
		Modele::Vecteur2<int> position;
		Modele::Grille grille = Fenetre::getProchaineGrille()->getGrilleModele();
		std::set<Modele::Unite*> listeUnite_ = grille.getUnites();
		//utiliser listeUnite de Carte.h{
		for (auto iterateur(listeUnite_.begin()); iterateur != listeUnite_.end(); iterateur++) {
			Modele::Unite *unite = const_cast<Modele::Unite*>(*iterateur);
			position = unite->getPosition();

			nodeUnite = nodeListeUnite.append_child(unite->getNom().c_str());

			nodeClasseUnite = nodeUnite.append_child("classe");
			nodeClasseUnite.text().set(unite->getClasse()._to_string());

			nodeEquipeUnite = nodeUnite.append_child("equipe");
			nodeEquipeUnite.text().set(unite->getEquipe()._to_string());

			nodePositionUnite = nodeUnite.append_child("position");

			nodePositionXUnite = nodePositionUnite.append_child("x");
			nodePositionXUnite.text().set(position.x);

			nodePositionYUnite = nodePositionUnite.append_child("x");
			nodePositionYUnite.text().set(position.y);
		}
		std::stringstream flux;
		doc.print(flux);
		return flux.str();
	}
}