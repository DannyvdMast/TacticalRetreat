
#include "stdafx.h"
using namespace std;

#include "GameScreen.h"

ISceneManager* GameScreen::smgr;
IVideoDriver* GameScreen::driver;
IGUIEnvironment* GameScreen::guienv;

GameScreen::GameScreen()
{
	flag = new StandardObject(vector3df(0,0,0),"../Assets/crane_driver_cabin.3ds","../Assets/r_flag3.tga");
	//StandardObject ran1flag(vector3df(-200,0,0));
	//StandardObject ran2flag(vector3df(0,0,-200),"../Assets/r_flag.md3","../Assets/r_flag3.tga");
	//StandardObject ran3flag(vector3df(0,0,200),"../Assets/r_flag.md3","../Assets/r_flag4.tga");
	//StandardObject ran4flag(vector3df(200,0,0),"../Assets/r_flag.md3","../Assets/r_flag5.tga");
	
	//Add SkyBox
	scene::ISceneNode* skydome=smgr->addSkyDomeSceneNode(driver->getTexture("../Assets/skydome2.jpg"),64,48,0.999f,5.0f,1000.0f);
	
	//smgr->addCameraSceneNodeFPS();
	//creates Camera
	smgr->addCameraSceneNode(flag->getNode(), core::vector3df(flag->getNode()->getPosition().X-40,flag->getNode()->getPosition().Y+90,flag->getNode()->getPosition().Z+250),core::vector3df(flag->getNode()->getPosition().X-60,flag->getNode()->getPosition().Y+80,flag->getNode()->getPosition().Z+240));
}

void GameScreen::Update(bool input[], f32 deltaTime)
{

	flag->Update(input,deltaTime);

}