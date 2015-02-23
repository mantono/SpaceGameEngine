#include "Player.h"

namespace engine
{

	Player::Player(Window* window, std::string imagePath, signed int x, signed int y, int width, int height, bool pixelCollision)
	:Moveable(window, imagePath, x, y, width, height, 10000, pixelCollision),
	rightKeyPressed(false), leftKeyPressed(false), upKeyPressed(false), downKeyPressed(false),
	score(0)
	{}

	void Player::keepInsideWindow(SDL_Window* window)
	{
		honorHorizontalBorders(window);
		honorVerticalBorders(window);
	}

	signed int Player::getScore() const
	{
		return score;
	}

	void Player::addScore(signed int score)
	{
		this->score += score;
	}

	Player::~Player()
	{}

}
