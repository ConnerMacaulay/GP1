#include "cFighter1.h"
#include "cFontMgr.h"
#include "cSound.h"
#include "cSoundMgr.h"
#include  <sstream>

/*
== == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == =
Update the sprite position
== == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == =
*/
static cFontMgr* theFontMgr = cFontMgr::getInstance();
int score;
string outputMsg;


void cFighter1::update(float deltaTime)
{
	if (m_InputMgr->isKeyDown(VK_RIGHT))
	{
		spritePos2D.x += 8.0f;
	}
	if (m_InputMgr->isKeyDown(VK_LEFT))
	{
		spritePos2D.x -= 8.0f;
	}
	//if (m_InputMgr->isKeyDown(VK_UP))3
	//{
	//	spriteTranslation = (glm::vec2(2.0f, 2.0f));
	//}
	//if (m_InputMgr->isKeyDown(VK_DOWN))
	//{
	//	spriteTranslation = -(glm::vec2(2.0f, 2.0f));
	//}
	//if (m_InputMgr->isKeyDown(int('A')))
	//{
	//	spriteScaling += 0.2f;
	//}
	//if (m_InputMgr->isKeyDown(int('S')))
	//{
	//	spriteScaling -= 0.2f;
	//}

	if (m_InputMgr->isKeyDown(VK_SPACE))
		{
			// Add new bullet sprite to the vector array
			theFists.push_back(new cFist);
			int numBullets = theFists.size() - 1;
			theFists[numBullets]->setSpritePos(glm::vec2(spritePos2D.x, spritePos2D.y));
			theFists[numBullets]->setSpriteTranslation(glm::vec2(2.0f, 2.0f));
			theFists[numBullets]->setTexture(theGameTextures[4]->getTexture());
			theFists[numBullets]->setTextureDimensions(theGameTextures[4]->getTWidth(), theGameTextures[4]->getTHeight());
			theFists[numBullets]->setSpriteCentre();
			//	theRocketBullets[numBullets]->setBulletVelocity(glm::vec2(0.0f, 0.0f));
			//theRocketBullets[numBullets]->setSpriteRotation(getSpriteRotation());
			theFists[numBullets]->setActive(true);
			theFists[numBullets]->setMdlRadius();
			//play the firing sound
			m_SoundMgr->getSnd("Shot")->playAudio(AL_TRUE);
		}

	if (spriteRotation > 360)
	{
		spriteRotation -= 360.0f;
	}

	glm::vec2 spriteVelocityAdd = glm::vec2(0.0f, 0.0f);
	spriteVelocityAdd.x = (glm::sin(glm::radians(spriteRotation)));
	spriteVelocityAdd.y = -(glm::cos(glm::radians(spriteRotation)));

	spriteVelocityAdd *= spriteTranslation;

	rocketVelocity += spriteVelocityAdd;

	spritePos2D += rocketVelocity * deltaTime;

	rocketVelocity *= 0.95;

	/*
	==============================================================
	| Check for collisions
	==============================================================
	*/
	for (vector<cFist*>::iterator fistIterartor = theFists.begin(); fistIterartor != theFists.end(); ++fistIterartor)
	{
		(*fistIterartor)->update(deltaTime);
		for (vector<cFist*>::iterator asteroidIterator = theAsteroids.begin(); asteroidIterator != theAsteroids.end(); ++asteroidIterator)
		{
			if ((*asteroidIterator)->collidedWith((*asteroidIterator)->getBoundingRect(), (*fistIterartor)->getBoundingRect()))
			{
				// if a collision set the bullet and asteroid to false
				(*asteroidIterator)->setActive(false);
				(*fistIterartor)->setActive(false);

			}
		}
	}

	vector<cFist*>::iterator fistIterartor = theFists.begin();
	while (fistIterartor != theFists.end())
	{
		if ((*fistIterartor)->isActive() == false)
		{
			fistIterartor = theFists.erase(fistIterartor);
			// play the explosion sound.
			m_SoundMgr->getSnd("Explosion")->playAudio(AL_TRUE);
			
		}
		else
		{
			//(*bulletIterartor)->update(deltaTime);
			(*fistIterartor)->render();
			++fistIterartor;
		}
	}
}

void cFighter1::render()
{
	glPushMatrix();

	glTranslatef(spritePos2D.x, spritePos2D.y, 0.0f);
	glRotatef(spriteRotation, 0.0f, 0.0f, 1.0f);
	glScalef(spriteScaling.x, spriteScaling.y, 1.0f);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, GLTextureID); // Binding of GLtexture name 

	glBegin(GL_QUADS);
	glColor3f(255.0f, 255.0f, 255.0f);
	glTexCoord2f(spriteTexCoordData[0].x, spriteTexCoordData[0].y);
	glVertex2f(-(textureWidth / 2), -(textureHeight / 2));
	glTexCoord2f(spriteTexCoordData[1].x, spriteTexCoordData[1].y);
	glVertex2f((textureWidth / 2), -(textureHeight / 2));
	glTexCoord2f(spriteTexCoordData[2].x, spriteTexCoordData[2].y);
	glVertex2f((textureWidth / 2), (textureHeight / 2));
	glTexCoord2f(spriteTexCoordData[3].x, spriteTexCoordData[3].y);
	glVertex2f(-(textureWidth / 2), (textureHeight / 2));

	glEnd();
	glDisable(GL_TEXTURE_2D);

	glPopMatrix();
}


void cFighter1::update(float deltaTime, cTexture fist)
{
	if (m_InputMgr->isKeyDown(VK_RIGHT))
	{
		spritePos2D.x += 8.0f;
	}
	if (m_InputMgr->isKeyDown(VK_LEFT))
	{
		spritePos2D.x -= 8.0f;
	}
	//if (m_InputMgr->isKeyDown(VK_UP))3
	//{
	//	spriteTranslation = (glm::vec2(2.0f, 2.0f));
	//}
	//if (m_InputMgr->isKeyDown(VK_DOWN))
	//{
	//	spriteTranslation = -(glm::vec2(2.0f, 2.0f));
	//}
	//if (m_InputMgr->isKeyDown(int('A')))
	//{
	//	spriteScaling += 0.2f;
	//}
	//if (m_InputMgr->isKeyDown(int('S')))
	//{
	//	spriteScaling -= 0.2f;
	//}

	if (m_InputMgr->isKeyDown(VK_SPACE))
	{
		// Add new bullet sprite to the vector array
		theFists.push_back(new cFist);
		int numBullets = theFists.size() - 1;
		theFists[numBullets]->setSpritePos(glm::vec2(spritePos2D.x, spritePos2D.y));
		theFists[numBullets]->setSpriteTranslation(glm::vec2(2.0f, 2.0f));
		theFists[numBullets]->setTexture(fist.getTexture());
		theFists[numBullets]->setTextureDimensions(fist.getTWidth(), fist.getTHeight());
		theFists[numBullets]->setSpriteCentre();
		//theRocketBullets[numBullets]->setBulletVelocity(glm::vec2(0.0f, 0.0f));
		//theRocketBullets[numBullets]->setSpriteRotation(getSpriteRotation());
		theFists[numBullets]->setActive(true);
		theFists[numBullets]->setMdlRadius();
		// play the firing sound
		m_SoundMgr->getSnd("Shot")->playAudio(AL_TRUE);
	}

	if (spriteRotation > 360)
	{
		spriteRotation -= 360.0f;
	}

	glm::vec2 spriteVelocityAdd = glm::vec2(0.0f, 0.0f);
	spriteVelocityAdd.x = (glm::sin(glm::radians(spriteRotation)));
	spriteVelocityAdd.y = -(glm::cos(glm::radians(spriteRotation)));

	spriteVelocityAdd *= spriteTranslation;

	rocketVelocity += spriteVelocityAdd;

	spritePos2D += rocketVelocity * deltaTime;

	rocketVelocity *= 0.95;

	/*
	==============================================================
	| Check for collisions
	==============================================================
	*/
	for (vector<cFist*>::iterator fistIterartor = theFists.begin(); fistIterartor != theFists.end(); ++fistIterartor)
	{
		(*fistIterartor)->update(deltaTime);
		for (vector<cFist*>::iterator asteroidIterator = theAsteroids.begin(); asteroidIterator != theAsteroids.end(); ++asteroidIterator)
		{
			if ((*asteroidIterator)->collidedWith((*asteroidIterator)->getBoundingRect(), (*fistIterartor)->getBoundingRect()))
			{
				// if a collision set the bullet and asteroid to false
				(*asteroidIterator)->setActive(false);
				(*fistIterartor)->setActive(false);
			}
		}
	}

	vector<cFist*>::iterator fistIterartor = theFists.begin();
	while (fistIterartor != theFists.end())
	{
		if ((*fistIterartor)->isActive() == false)
		{
			fistIterartor = theFists.erase(fistIterartor);
			// play the explosion sound.
			m_SoundMgr->getSnd("Explosion")->playAudio(AL_TRUE);
		}
		else
		{
			//(*bulletIterartor)->update(deltaTime);
			(*fistIterartor)->render();
			++fistIterartor;
		}
	}
}

void cFighter1::update(float deltaTime, cTexture fist, cFighter2* theOpponent)
{
	if (m_InputMgr->isKeyDown(VK_RIGHT))
	{
		spritePos2D.x += 8.0f;
	}
	if (m_InputMgr->isKeyDown(VK_LEFT))
	{
		spritePos2D.x -= 8.0f;
	}
	//if (m_InputMgr->isKeyDown(VK_UP))3
	//{
	//	spriteTranslation = (glm::vec2(2.0f, 2.0f));
	//}
	//if (m_InputMgr->isKeyDown(VK_DOWN))
	//{
	//	spriteTranslation = -(glm::vec2(2.0f, 2.0f));
	//}
	//if (m_InputMgr->isKeyDown(int('A')))
	//{
	//	spriteScaling += 0.2f;
	//}
	//if (m_InputMgr->isKeyDown(int('S')))
	//{
	//	spriteScaling -= 0.2f;
	//}

	if (m_InputMgr->isKeyDown(VK_SPACE))
	{
		// Add new bullet sprite to the vector array
		theFists.push_back(new cFist);
		int numBullets = theFists.size() - 1;
		theFists[numBullets]->setSpritePos(glm::vec2(spritePos2D.x, spritePos2D.y));
		theFists[numBullets]->setSpriteTranslation(glm::vec2(2.0f, 2.0f));
		theFists[numBullets]->setTexture(fist.getTexture());
		theFists[numBullets]->setTextureDimensions(fist.getTWidth(), fist.getTHeight());
		theFists[numBullets]->setSpriteCentre();
		//theRocketBullets[numBullets]->setBulletVelocity(glm::vec2(0.0f, 0.0f));
		//theRocketBullets[numBullets]->setSpriteRotation(getSpriteRotation());
		theFists[numBullets]->setActive(true);
		theFists[numBullets]->setMdlRadius();
		//play the firing sound
		m_SoundMgr->getSnd("Shot")->playAudio(AL_TRUE);
	}

	if (spriteRotation > 360)
	{
		spriteRotation -= 360.0f;
	}

	glm::vec2 spriteVelocityAdd = glm::vec2(0.0f, 0.0f);
	spriteVelocityAdd.x = (glm::sin(glm::radians(spriteRotation)));
	spriteVelocityAdd.y = -(glm::cos(glm::radians(spriteRotation)));

	spriteVelocityAdd *= spriteTranslation;

	rocketVelocity += spriteVelocityAdd;

	spritePos2D += rocketVelocity * deltaTime;

	rocketVelocity *= 0.95;

	/*
	==============================================================
	| Check for collisions
	==============================================================
	*/
	for (vector<cFist*>::iterator fistIterartor = theFists.begin(); fistIterartor != theFists.end(); ++fistIterartor)
	{
		(*fistIterartor)->update(deltaTime);
		//for (vector<cFist*>::iterator asteroidIterator = theAsteroids.begin(); asteroidIterator != theAsteroids.end(); ++asteroidIterator)
		//{
		if ((theOpponent)->collidedWith((theOpponent)->getBoundingRect(), (*fistIterartor)->getBoundingRect()))
			{
				// if a collision set the bullet and asteroid to false
			(theOpponent)->setActive(false);
				(*fistIterartor)->setActive(false);
				theFontMgr->getFont("Space")->printText("HIT", FTPoint(20.0f, -1.0f, 0.0f));
				
			}
		/*}*/
	}

	vector<cFist*>::iterator fistIterartor = theFists.begin();
	while (fistIterartor != theFists.end())
	{
		if ((*fistIterartor)->isActive() == false)
		{
			fistIterartor = theFists.erase(fistIterartor);
			//play the explosion sound.
			m_SoundMgr->getSnd("Explosion")->playAudio(AL_TRUE);
		}
		else
		{
			//(*bulletIterartor)->update(deltaTime);
			(*fistIterartor)->render();
			++fistIterartor;
		}
	}
}