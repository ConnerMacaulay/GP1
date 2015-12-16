
#ifndef _CFIGHTER2_H
#define _CFIGHTER2_H
#include "cSprite.h"
//#include "asteroidsGame.h"

class cFighter2 : public cSprite
{
private:
	glm::vec2 rocketVelocity = glm::vec2(0.0f, 0.0f);

public:
	void render();		// Default render function
	void update(float deltaTime);		// Rocket update method
	//void setRocketVelocity(glm::vec2 rocketVel);   // Sets the velocity for the rocket
	//glm::vec2 getRocketVelocity();				 // Gets the rocket velocity

};
#endif