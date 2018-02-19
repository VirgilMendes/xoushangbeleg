#pragma once
#pragma once 
#include <vector> 
#include "SFML/Graphics.hpp" 
#include "SFML/System.hpp" 
#include <memory> 

namespace Vue
{
	class Animation
	{
	public:
		Animation(std::vector<sf::IntRect> frames, int interval) : frames_(frames),
			interval_(interval)
		{
			frameIndex_ = new int(0);
			horloge_ = new sf::Clock;
		}
		Animation() : interval_(0)
		{
			frameIndex_ = new int(0);
			horloge_ = new sf::Clock();
		}

		void initialiser(const std::vector<sf::IntRect>& frames, int interval)
		{
			frames_ = frames;
			interval_ = interval;
		}

		~Animation()
		{
		}

		sf::IntRect getFrame() const
		{
			if (horloge_->getElapsedTime().asMilliseconds() >= interval_)
			{
				*frameIndex_ += 1;
				if (*frameIndex_ >= frames_.size())
					*frameIndex_ = 0;
				horloge_->restart();
			}
			return frames_[*frameIndex_];
		}
	private:

		std::vector<sf::IntRect> frames_;
		sf::Clock* horloge_;
		int* frameIndex_;
		int interval_;

	};
}