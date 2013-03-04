
#include "stdafx.h"
using namespace std;

#include "StandardObject.h"

	ISceneManager* StandardObject::smgr;
	IVideoDriver* StandardObject::driver;
	const f32 MOVEMENT_SPEED= 50.0f;
	const f32 ROTATION_SPEED= 1.0f;
	//default constructor
	StandardObject::StandardObject()
	{
		//is empty 
	}
	//default constructor where you need to set the filename for mesh and texture
	StandardObject::StandardObject(const io::path & meshFilename,const io::path & textureFilename)
	{
		setMesh(meshFilename);
		if (!mesh)
		{
			//device->drop();
			//return 1;
		}
		node = smgr->addAnimatedMeshSceneNode( mesh );
	
		if (node)
		{
			node->setMaterialFlag(EMF_LIGHTING, false);
			node->setMD2Animation(scene::EMAT_STAND);
			setTexture(textureFilename);
		}

	}
	// constructor with position and other atributes
	StandardObject::StandardObject(vector3df position)
	{
		setMesh("../Assets/r_flag.md3");
		if (!mesh)
		{
			//device->drop();
			//return 1;
		}
		node = smgr->addAnimatedMeshSceneNode( mesh );
	
		if (node)
		{
			node->setMaterialFlag(EMF_LIGHTING, false);
			node->setMD2Animation(scene::EMAT_STAND);
			setTexture("../Assets/r_flag2.tga");
			node->setPosition(position);
			
		}

	}
	// constructor with position and other atributes + filename of mesh and texture
	StandardObject::StandardObject(vector3df position,const io::path & meshFilename,const io::path & textureFilename)
	{ 
		setMesh(meshFilename);
		if (!mesh)
		{
			//device->drop();
			//return 1;
		}
		node = smgr->addAnimatedMeshSceneNode( mesh );
	
		if (node)
		{
			node->setMaterialFlag(EMF_LIGHTING, false);
			node->setMD2Animation(scene::EMAT_STAND);
			setTexture(textureFilename);
			node->setPosition(position);
		}

	}
	/*Update function
	*/
	void StandardObject::Update(bool input[], f32 deltaTime)
	{
		vector3df tempPosition = node->getPosition();
		vector3df tempRotation = node->getRotation();

		core::vector3df forward = core::vector3df(0, 0, 1);
		core::vector3df right = core::vector3df(1, 0, 0);
		core::vector3df up = core::vector3df(0, 1, 0);
  
		core::matrix4 NodeRotation =
		core::matrix4().setRotationDegrees(tempRotation);

		NodeRotation.transformVect(forward);
		NodeRotation.transformVect(right);
		NodeRotation.transformVect(up);

		//Forward
		if(input[irr::KEY_KEY_W]){
			tempPosition -= forward*MOVEMENT_SPEED*deltaTime;
		}
		//BackWards
		if(input[irr::KEY_KEY_S]){
		
			tempPosition += forward*MOVEMENT_SPEED*deltaTime;
		}
		//Left
		if(input[KEY_KEY_A]) {
			tempPosition += right * MOVEMENT_SPEED*deltaTime;
			
		}
		//Right
		if(input[KEY_KEY_D]) {
			tempPosition -= right * MOVEMENT_SPEED*deltaTime;
			
		}
		f32 yawChange = 0;
		f32 pitchChange = 0;
		f32 rollChange = 0;

		//PitchUP
		if(input[irr::KEY_UP]) {
			 pitchChange += ROTATION_SPEED*deltaTime;
		}
		//PitchDown
		if(input[irr::KEY_DOWN]) { 
			pitchChange -= ROTATION_SPEED*deltaTime;
		}
		//yawLeft
		if(input[irr::KEY_LEFT]) {
			 yawChange -= ROTATION_SPEED*deltaTime;
		}
		//yawRight
		if(input[irr::KEY_RIGHT]) {
			 yawChange += ROTATION_SPEED*deltaTime;
		}
		// calculate the orientation from ypr
		 core::quaternion orientation (tempRotation * core::DEGTORAD); 

		// calculate the change in orientation
		 core::quaternion newOrientation (pitchChange, yawChange, rollChange);

		// apply change in orientation
		orientation *= newOrientation;

		// set new orientation
		orientation.toEuler(tempRotation * core::RADTODEG);
		core::vector3df newRotation; 
		orientation.toEuler(newRotation);

		//Setting the node's position
		node->setPosition(tempPosition);
		node->setRotation(newRotation * core::RADTODEG);
  
		//Creating the target
		core::vector3df target = core::vector3df();
		target += node->getPosition();
		target += forward;
  
		//Setting the camera
		smgr->getActiveCamera()->setTarget(target);
		smgr->getActiveCamera()->setUpVector(up);
		smgr->getActiveCamera()->setRotation(node->getRotation());
		
	}

	//Unimportant crap Left over from Old project
	void StandardObject::AddForce(vector3df force)
	{
		this->forceAccumulated += force;
	}

	// A setter so that the programmer has the ability to set the mesh after constructor
	void StandardObject::setMesh(const io::path & filename)
	{
		mesh = smgr->getMesh(filename);
	}
	// A setter so that the programmer has the ability to set the texture after constructor
	void StandardObject::setTexture(const io::path & filename)
	{
		node->setMaterialTexture(0, driver->getTexture(filename) );
	}
	// a getter that returns the mesh of this object
	IAnimatedMesh* StandardObject::getMesh()
	{
		return mesh;
	}
	// a getter that returns the node of this object, usefull for changing position and stuff
	IAnimatedMeshSceneNode* StandardObject::getNode()
	{
		return node;
	}
	//obsolete
	void StandardObject::drawall()
	{

	}