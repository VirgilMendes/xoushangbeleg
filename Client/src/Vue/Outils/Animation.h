#pragma once
#pragma once 
#include <vector> 
#include "SFML/Graphics.hpp" 
#include "SFML/System.hpp" 
#include <memory> 
#include "../Constante.h"
#include <iostream>

namespace Vue
{
	class Animation
	{
	public:

	enum Type
	{
		Boucle,
		UneFois
	};

		Animation(std::vector<sf::IntRect> frames, int interval, Type type) : frames_(frames), frameIndex_(0), type_(type),
			interval_(interval)
		{
			horloge_ = new sf::Clock;
		}
		
		Animation() : interval_(0), frameIndex_(0), type_(Type::Boucle)
		{
			horloge_ = new sf::Clock;
		}

		~Animation()
		{
			delete horloge_;
		}

		void initialiser(const std::vector<sf::IntRect>& frames, int interval, Type type = Type::Boucle)
		{
			frames_ = frames;
			interval_ = interval;
			type_ = type;
		}

		sf::IntRect getFrame()
		{
			if (horloge_->getElapsedTime().asMilliseconds() >= interval_)
			{
				frameIndex_ += 1;
				if (frameIndex_ >= frames_.size())
				{
					switch (type_)
					{
					case Boucle:
						frameIndex_ = 0;
						break;
					case UneFois:
						return finAnimation;
						break;
					}
				}
				horloge_->restart();
			}
			return frames_[frameIndex_];
		}

		void restart()
		{
			frameIndex_ = 0;
			horloge_->restart();
		}

		const static sf::IntRect finAnimation;

	private:

		Type type_;

		std::vector<sf::IntRect> frames_;
		sf::Clock* horloge_;
		int frameIndex_;
		int interval_;

	};
}
