// FirstPrototype.cpp : Defines the entry point for the console application.
//

#include <irrlicht.h>
#include "stdafx.h"
#include <iostream>

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace gui;

#if defined(_MSC_VER)
	#pragma comment (lib,"Irrlicht.lib");
#endif

int main(int argc, _TCHAR* argv[]){

	// Initialize window and screenmanager
	IrrlichtDevice* device = createDevice(EDT_OPENGL, dimension2d<u32>(640,480));
	if(!device) { 
		return 1; 
	}

	IVideoDriver* video = device->getVideoDriver();
	ISceneManager* smgr = device->getSceneManager();
	smgr->addCameraSceneNodeFPS();
	
	device->getCursorControl()->setVisible(false);

	// Add viking
	IMesh* mesh = smgr->getMesh("./Media/Normandy_SR2_Ceberus.max");
	IMeshSceneNode* node = smgr->addMeshSceneNode(mesh);
	if(node) {
		node->setPosition(vector3df(0,0,100));
		node->setMaterialFlag(EMF_LIGHTING, false);
		//node->setMaterialTexture(0,video->getTexture("./Media/sydney.bmp"));
	}



	while(device->run() && device) {

		video->beginScene(true, true, video::SColor(255,0,0,255));
		smgr->drawAll();
		video->endScene();
	}

	device->drop();


	return 0;
}

