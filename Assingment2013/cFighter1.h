
#ifndef _CFIGHTER1_H
#define _CFIGHTER1_H

#include "cSprite.h"
#include "cFighter2.h"
#include "asteroidsGame.h"

class cFighter1 : public cSprite
{
private:
	glm::vec2 rocketVelocity = glm::vec2(0.0f, 0.0f);

public:
	void render();		// Default render function
	void update(float deltaTime);		// Rocket update method
	void update(float deltaTime, cTexture fist);		// Rocket update method
	void update(float deltaTime, cTexture fist, cFighter2* theOpponent);		// Rocket update method

	//void setRocketVelocity(glm::vec2 rocketVel);   // Sets the velocity for the rocket
	//glm::vec2 getRocketVelocity();				 // Gets the rocket velocity

};
#endif