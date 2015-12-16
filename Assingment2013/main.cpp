#define WIN32_LEAN_AND_MEAN
#define WIN32_EXTRA_LEAN

#define GLX_GLXEXT_LEGACY //Must be declared so that our local glxext.h is picked up, rather than the system one


#include <windows.h>
#include "windowOGL.h"
#include "GameConstants.h"
#include "cWNDManager.h"
#include "cInputMgr.h"
#include "cSoundMgr.h"
#include "cFontMgr.h"
#include "cSprite.h"
#include "cFighter2.h"
#include "asteroidsGame.h"
#include "cButton.h"


int WINAPI WinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPSTR cmdLine,
                   int cmdShow)
{

    //Set our window settings
    const int windowWidth = 1024;
    const int windowHeight = 768;
    const int windowBPP = 16;



    //This is our window
	static cWNDManager* pgmWNDMgr = cWNDManager::getInstance();

	// This is the input manager
	static cInputMgr* theInputMgr = cInputMgr::getInstance();

	// This is the sound manager
	static cSoundMgr* theSoundMgr = cSoundMgr::getInstance();

	// This is the Font manager
	static cFontMgr* theFontMgr = cFontMgr::getInstance();

	//The example OpenGL code
    windowOGL theOGLWnd;
	
    //Attach our the OpenGL window
	pgmWNDMgr->attachOGLWnd(&theOGLWnd);

	// Attach the keyboard manager
	pgmWNDMgr->attachInputMgr(theInputMgr);

    //Attempt to create the window
	if (!pgmWNDMgr->createWND(windowWidth, windowHeight, windowBPP))
    {
        //If it fails

        MessageBox(NULL, "Unable to create the OpenGL Window", "An error occurred", MB_ICONERROR | MB_OK);
		pgmWNDMgr->destroyWND(); //Reset the display and exit
        return 1;
    }

	if (!theOGLWnd.initOGL(windowWidth, windowHeight)) //Initialize our example
    {
        MessageBox(NULL, "Could not initialize the application", "An error occurred", MB_ICONERROR | MB_OK);
		pgmWNDMgr->destroyWND(); //Reset the display and exit
        return 1;
    }

	//Clear key buffers
	theInputMgr->clearBuffers(theInputMgr->KEYS_DOWN_BUFFER | theInputMgr->KEYS_PRESSED_BUFFER);

	/* initialize random seed: */
	srand((unsigned int)time(NULL));

	// load game sounds
	// Load Sound
	LPCSTR gameSounds[3] = { "Audio/who10Edit.wav", "Audio/shot007.wav", "Audio/explosion2.wav" };

	//theSoundMgr->add("Theme", gameSounds[0]);
	theSoundMgr->add("Shot", gameSounds[1]);
	theSoundMgr->add("Explosion", gameSounds[2]);

	// load game fontss
	// Load Fonts
	LPCSTR gameFonts[2] = { "Fonts/digital-7.ttf", "Fonts/space age.ttf"};

	theFontMgr->addFont("SevenSeg", gameFonts[0], 24);
	theFontMgr->addFont("Space", gameFonts[1], 24);

	vector<cTexture*> textureBkgList;
	LPCSTR bkgTexturesToUse[] = { "Images\\titlebkg.jpg", "Images\\cityscape.gif", "Images\\endbkg.gif" };
	for (int tCount = 0; tCount < 3; tCount++)
	{
		textureBkgList.push_back(new cTexture());
		textureBkgList[tCount]->createTexture(bkgTexturesToUse[tCount]);
	}

	cBkGround titleBkgd;
	titleBkgd.setSpritePos(glm::vec2(0.0f, 0.0f));
	titleBkgd.setTexture(textureBkgList[0]->getTexture());
	titleBkgd.setTextureDimensions(textureBkgList[0]->getTWidth(), textureBkgList[0]->getTHeight());

	cBkGround gameBkgd;
	gameBkgd.setSpritePos(glm::vec2(0.0f, 0.0f));
	gameBkgd.setTexture(textureBkgList[1]->getTexture());
	gameBkgd.setTextureDimensions(textureBkgList[1]->getTWidth(), textureBkgList[1]->getTHeight());

	cBkGround endBkgd;
	endBkgd.setSpritePos(glm::vec2(0.0f, 0.0f));
	endBkgd.setTexture(textureBkgList[2]->getTexture());
	endBkgd.setTextureDimensions(textureBkgList[2]->getTWidth(), textureBkgList[2]->getTHeight());

	vector<cTexture*> btnTextureList;
	LPCSTR btnTexturesToUse[] = { "Images/Buttons/exit.png", "Images/Buttons/fight.png", "Images/Buttons/FA.png", "Images/Buttons/end.png" };
	for (int tCount = 0; tCount < 4; tCount++)
	{
		btnTextureList.push_back(new cTexture());
		btnTextureList[tCount]->createTexture(btnTexturesToUse[tCount]);
	}

	cButton saveButton;
	saveButton.attachInputMgr(theInputMgr);
	saveButton.setTexture(btnTextureList[2]->getTexture());
	saveButton.setTextureDimensions(btnTextureList[2]->getTWidth(), btnTextureList[2]->getTHeight());

	cButton exitButton;
	exitButton.attachInputMgr(theInputMgr);
	exitButton.setTexture(btnTextureList[0]->getTexture());
	exitButton.setTextureDimensions(btnTextureList[0]->getTWidth(), btnTextureList[0]->getTHeight());

	cButton playButton;
	playButton.attachInputMgr(theInputMgr);
	playButton.setTexture(btnTextureList[1]->getTexture());
	playButton.setTextureDimensions(btnTextureList[1]->getTWidth(), btnTextureList[1]->getTHeight());

	cButton endButton;
	endButton.attachInputMgr(theInputMgr);
	endButton.setTexture(btnTextureList[3]->getTexture());
	endButton.setTextureDimensions(btnTextureList[3]->getTWidth(), btnTextureList[3]->getTHeight());

	//Fighter1 
	cTexture fighter1Txt;
	fighter1Txt.createTexture("Images\\fighter.gif");
	cFighter1 fighter1Sprite;
	fighter1Sprite.attachInputMgr(theInputMgr); // Attach the input manager to the sprite
	fighter1Sprite.setSpritePos(glm::vec2(90.0f, 600.0f));
	fighter1Sprite.setTexture(fighter1Txt.getTexture());
	fighter1Sprite.setTextureDimensions(fighter1Txt.getTWidth(), fighter1Txt.getTHeight());
	fighter1Sprite.setSpriteCentre();
	//fighter1Sprite.setRocketVelocity(glm::vec2(0.0f, 0.0f));

	//Fighter2
	cTexture fighter2Txt;
	fighter2Txt.createTexture("Images\\fighter2.gif");
	cFighter2 fighter2Sprite;
	fighter2Sprite.attachInputMgr(theInputMgr); // Attach the input manager to the sprite
	fighter2Sprite.setSpritePos(glm::vec2(940.0f, 600.0f));
	fighter2Sprite.setTexture(fighter2Txt.getTexture());
	fighter2Sprite.setTextureDimensions(fighter2Txt.getTWidth(), fighter2Txt.getTHeight());
	fighter2Sprite.setSpriteCentre();
	//fighter2Sprite.setRocketVelocity(glm::vec2(0.0f, 0.0f));

	//Fighter2
	cTexture fistTxt;
	fistTxt.createTexture("Images\\fistB.png");


	// Attach sound manager to fighter sprite
	fighter1Sprite.attachSoundMgr(theSoundMgr);

	fighter2Sprite.attachSoundMgr(theSoundMgr);

		gameState theGameState = MENU;
		btnTypes theBtnType = EXIT;
		int score = 0;
		string outputMsg;
		string strMsg[] = { "Create and Save your own Track!", "Drag and Drop the tiles.", "Road Mapper", "Thanks for playing!", "See you again soon!" };

	while (pgmWNDMgr->isWNDRunning())
	{

		pgmWNDMgr->processWNDEvents(); //Process any window events


		//We get the time that passed since the last frame
		float elapsedTime = pgmWNDMgr->getElapsedSeconds();

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//This is the mainloop, we render frames until isRunning returns false
			
			switch (theGameState)
			{
			case MENU:
			
						 titleBkgd.render();

						 playButton.setSpritePos(glm::vec2(400.0f, 300.0f));
						 exitButton.setSpritePos(glm::vec2(400.0f, 500.0f));
						 playButton.render();
						 exitButton.render();

						 theGameState = playButton.update(theGameState, PLAYING);
						 exitButton.update();


						 outputMsg = strMsg[2];
						 theFontMgr->getFont("Space")->printText(outputMsg.c_str(), FTPoint(10, 15, 0.0f));
						 outputMsg = strMsg[0];
						 theFontMgr->getFont("Space")->printText(outputMsg.c_str(), FTPoint(100, 100, 0.0f));
						 outputMsg = strMsg[1];
						 theFontMgr->getFont("Space")->printText(outputMsg.c_str(), FTPoint(100, 150, 0.0f));
						 if (exitButton.getClicked())
						 {
							 SendMessage(pgmWNDMgr->getWNDHandle(), WM_CLOSE, NULL, NULL);
						 }
			
				break;
			case PLAYING:
				gameBkgd.render();

				endButton.setSpritePos(glm::vec2(400.0f, 0.0f));
				endButton.render();
				theGameState = endButton.update(theGameState, END);
				

				fighter1Sprite.update(elapsedTime, fistTxt, &fighter2Sprite);
				fighter2Sprite.update(elapsedTime);

				{
					vector<cFist*>::iterator fistIterator = theFists.begin();
					while (fistIterator != theFists.end())
					{

						if ((*fistIterator)->isActive() == false)
						{
							theFontMgr->getFont("Space")->printText("HIT", FTPoint(20.0f, -50.0f, 0.0f));
							fistIterator = theFists.erase(fistIterator);
						}
						else
						{
							(*fistIterator)->update(elapsedTime);
							(*fistIterator)->render();
							++fistIterator;

						}
					}
				}
				fighter1Sprite.render();
				fighter2Sprite.render();

				theFontMgr->getFont("Space")->printText("Flying Fists of Fury", FTPoint(0.0f, -1.0f, 0.0f));

				theInputMgr->clearBuffers(theInputMgr->KEYS_DOWN_BUFFER | theInputMgr->KEYS_PRESSED_BUFFER);

				break;
			case END:
				endBkgd.render();

				playButton.setClicked(false);
				exitButton.setClicked(false);

				playButton.setSpritePos(glm::vec2(400.0f, 300.0f));
				exitButton.setSpritePos(glm::vec2(400.0f, 500.0f));
				playButton.render();
				exitButton.render();

				theGameState = playButton.update(theGameState, PLAYING);
				exitButton.update();

				outputMsg = strMsg[2];
				theFontMgr->getFont("Space")->printText(outputMsg.c_str(), FTPoint(10, 15, 0.0f));
				outputMsg = strMsg[3];
				theFontMgr->getFont("Space")->printText(outputMsg.c_str(), FTPoint(100, 100, 0.0f));
				outputMsg = strMsg[4];
				theFontMgr->getFont("Space")->printText(outputMsg.c_str(), FTPoint(100, 150, 0.0f));
				if (exitButton.getClicked())
				{
					SendMessage(pgmWNDMgr->getWNDHandle(), WM_CLOSE, NULL, NULL);
				}

				break;
			}
			pgmWNDMgr->swapBuffers();

		}
	

	theOGLWnd.shutdown(); //Free any resources
	pgmWNDMgr->destroyWND(); //Destroy the program window

    return 0; //Return success
}
