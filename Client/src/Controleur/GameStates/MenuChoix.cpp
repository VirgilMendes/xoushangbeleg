#pragma once

#include "MenuChoix.h"

namespace Controleur
{
	MenuChoix::MenuChoix(std::vector<Choix> choix) : choix_(choix), vue_(new Vue::MenuChoix(choix, this))
	{
		interfaceUtilisateur_ = true;
		
		choixCourant_ = 0;
		Choix choixMenu = choix_[0];
		
		for (int i(0); i < choix_.size(); ++i)
		{
			choixMenu = choix_[i];
			if (!choixMenu.actif)
				vue_->desactiverChoix(i);
		}
		
		choixMenu = choix_[0];

		while (!choixMenu.actif)
		{
			++choixCourant_;
			if (choixCourant_ == choix_.size())
				break;
			choixMenu = choix_[choixCourant_];
		}
		if (choixCourant_ != choix_.size())
			vue_->setChoixCourant(choixCourant_);
		
	}

	MenuChoix::~MenuChoix()
	{
		delete vue_;
	}

	void MenuChoix::deplacerAuChoixPrecedant()
	{
		int choixSource = choixCourant_;
		if (choixCourant_ != choix_.size())
		{
			if (choixCourant_ == 0)
				choixCourant_ = choix_.size() - 1;
			else
				--choixCourant_;
		}
		else { choixCourant_ = choix_.size()-1; }
		Choix choix = choix_[choixCourant_];

		int nombreChoixParcourue=0;
		while (!choix.actif)
		{
			++nombreChoixParcourue;
			if (nombreChoixParcourue == choix_.size())
			{
				choixCourant_ = choix_.size();
				return;
			}
			
			--choixCourant_;
			if (choixCourant_ == -1)
				choixCourant_ = choix_.size() - 1;;
			if (choixCourant_ == choixSource)
			{
				break;
			}
			choix = choix_[choixCourant_];
		}
		vue_->changerChoixCourant(choixCourant_);
	}

	void MenuChoix::deplacerAuChoixSuivant()
	{
		int choixSource = choixCourant_;
		if (choixCourant_ != choix_.size())
		{
			if (choixCourant_ == choix_.size() - 1)
				choixCourant_ = 0;
			else
				++choixCourant_;
		}
		else{ choixCourant_ = 0; }
		Choix choix = choix_[choixCourant_];
		int nombreChoixParcourue = 0;
		while (!choix.actif)
		{
			++nombreChoixParcourue;
			if (nombreChoixParcourue == choix_.size())
			{
				choixCourant_ = choix_.size();
				return;
			}

			++choixCourant_;
			if (choixCourant_ == choix_.size())
				choixCourant_ = 0;
			if (choixCourant_ == choixSource)
			{
				break;
			}
			choix = choix_[choixCourant_];
		}
		vue_->changerChoixCourant(choixCourant_);
	}

	void MenuChoix::positionnerSurChoix()
	{
	}

	void MenuChoix::desactiverChoix(int index)
	{
		choix_.at(index).actif = false;
		vue_->desactiverChoix(index);
		if (index == choixCourant_)
		{
			int choixSource = choixCourant_;
			if (choixCourant_ != choix_.size())
			{
				if (choixCourant_ == choix_.size() - 1)
					choixCourant_ = 0;
				else
					++choixCourant_;
			}
			else { choixCourant_ = 0; }
			Choix choix = choix_[choixCourant_];
			int nombreChoixParcourue = 0;
			while (!choix.actif)
			{
				++nombreChoixParcourue;
				if (nombreChoixParcourue == choix_.size())
				{
					choixCourant_ = choix_.size();
					return;
				}

				++choixCourant_;
				if (choixCourant_ == choix_.size())
					choixCourant_ = 0;
				if (choixCourant_ == choixSource)
				{
					break;
				}
				choix = choix_[choixCourant_];
			}
			vue_->setChoixCourant(choixCourant_);
		}
	}

	void MenuChoix::activerChoix(int index)
	{
		choix_.at(index).actif = true;
		vue_->activerChoix(index);
	}

	void MenuChoix::handleEvent()
	{
		vue_->handleEvent();
	}

	void MenuChoix::update()
	{
		vue_->update();
	}

	void MenuChoix::afficher()
	{
		vue_->afficher();
	}

	void MenuChoix::enclencherActionDeplacement(const ActionDeplacement& action)
	{
		switch(action)
		{
			case ActionDeplacement::Haut:
				deplacerAuChoixPrecedant();
				break;
			case ActionDeplacement::Bas:
				deplacerAuChoixSuivant();
				break;
			default:
				break;
		}
	}

	void MenuChoix::enclencherActionValidation()
	{
		choix_[choixCourant_].fonction();
	}

	void MenuChoix::enclancherActionRetour()
	{
	}

	void MenuChoix::enclancherActionMenu()
	{
	}

	void MenuChoix::enclancherActionSpecial()
	{
	}
}
