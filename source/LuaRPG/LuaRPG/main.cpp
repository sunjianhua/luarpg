//
//
//
#include <irrlicht.h>
#include	"game.h"
#include "2DTexture.h"
using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;
irr::IrrlichtDevice*	g_pIrr;
CGame*	g_pGame;
IVideoDriver* driver;
ISceneManager* smgr;
IGUIEnvironment* guienv;
enum
{
	GUI_ID_START_BUTTON = 101,
	GUI_ID_QUIT_BUTTON
};

class MyEventReceiver : public IEventReceiver
{
public:
	//MyEventReceiver(SAppContext & context) : Context(context) { }
	// This is the one method that we have to implement
	virtual bool OnEvent(const SEvent& event)
	{
		// Remember whether each key is down or up
		if (event.EventType == irr::EET_KEY_INPUT_EVENT)
			KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;

		if (event.EventType == EET_GUI_EVENT)
		{
			s32 id = event.GUIEvent.Caller->getID();
			//IGUIEnvironment* env = Context.device->getGUIEnvironment();

			switch(event.GUIEvent.EventType)
			{
				case EGET_BUTTON_CLICKED:
					switch(id)
					{
						case GUI_ID_START_BUTTON:
							break;

						case GUI_ID_QUIT_BUTTON:
							break;
						default:
							return false;
					}
					break;
				default:
					break;
			}
		}
		return false;
	}

	// This is used to check whether a key is being held down
	virtual bool IsKeyDown(EKEY_CODE keyCode) const
	{
		return KeyIsDown[keyCode];
	}
	
	MyEventReceiver()
	{
		for (u32 i=0; i<KEY_KEY_CODES_COUNT; ++i)
			KeyIsDown[i] = false;
	}

private:
	// We use this array to store the current state of each key
	bool KeyIsDown[KEY_KEY_CODES_COUNT];
	//SAppContext & Context;
};


int	main()
{
	MyEventReceiver receiver;
	g_pIrr = createDevice( video::EDT_DIRECT3D9,	core::dimension2d<u32>(1024,768) ,16, false, false, false,&receiver);
	driver=g_pIrr->getVideoDriver();
	smgr=g_pIrr->getSceneManager();
	guienv=g_pIrr->getGUIEnvironment();
	g_pGame = new CGame;
	g_pGame->Initialize();
	IGUISkin* skin = guienv->getSkin();
	video::ITexture* images = driver->getTexture("../../media/2ddemo.png");
	DTexture *texture=new DTexture();
	texture->setDriver(driver);texture->setPos(core::position2d<s32>(0,0));
	texture->setRect(core::rect<s32>(0,0,342,224));texture->setTexture(images);
	IGUIFont* font = guienv->getFont("../../media/fonthaettenschweiler.bmp");
	skin->setFont(guienv->getBuiltInFont(), EGDF_TOOLTIP);

	guienv->addButton(rect<s32>(412,440,612,440 + 32), 0, GUI_ID_START_BUTTON,
			L"Start Games", L"Start Program");

	guienv->addButton(rect<s32>(412,480,612,480 + 32), 0, GUI_ID_QUIT_BUTTON,
			L"Quit Games", L"Exit Program");
	g_pIrr->setEventReceiver(&receiver);
	/*
	guienv->addStaticText(L"adfafdadf",rect<int>(10,10,260,22),true);
	scene::ISceneNode * node = smgr->addSphereSceneNode();
	if (node)
	{
		node->setPosition(core::vector3df(0,0,30));
		node->setMaterialTexture(0, driver->getTexture("../../media/wall.bmp"));
		node->setMaterialFlag(video::EMF_LIGHTING, false);
	}
	scene::ISceneNode* n = smgr->addCubeSceneNode();

	if (n)
	{
		n->setMaterialTexture(0, driver->getTexture("../../media/t351sml.jpg"));
		n->setMaterialFlag(video::EMF_LIGHTING, false);
		scene::ISceneNodeAnimator* anim =
			smgr->createFlyCircleAnimator(core::vector3df(0,0,30), 20.0f);
		if (anim)
		{
			n->addAnimator(anim);
			anim->drop();
		}
	}
	scene::IAnimatedMeshSceneNode* anms =
		smgr->addAnimatedMeshSceneNode(smgr->getMesh("../../media/ninja.b3d"));

	if (anms)
	{
		scene::ISceneNodeAnimator* anim =
			smgr->createFlyStraightAnimator(core::vector3df(100,0,60),
			core::vector3df(-100,0,60), 3500, true);
		if (anim)
		{
			anms->addAnimator(anim);
			anim->drop();
		}

		anms->setMaterialFlag(video::EMF_LIGHTING, false);

		anms->setFrameLoop(0, 13);
		anms->setAnimationSpeed(15);

		anms->setScale(core::vector3df(2.f,2.f,2.f));
		anms->setRotation(core::vector3df(0,-90,0));

	}

	smgr->addCameraSceneNodeMaya();
	g_pIrr->getCursorControl()->setVisible(false);

	gui::IGUIStaticText* diagnostics = g_pIrr->getGUIEnvironment()->addStaticText(
		L"", core::rect<s32>(10, 10, 400, 20));
	diagnostics->setOverrideColor(video::SColor(255, 255, 255, 0));

	int lastFPS = -1;
	const f32 MOVEMENT_SPEED = 5.f;
	*/
	smgr->addCameraSceneNodeMaya();
	core::position2d<s32> pos=core::position2d<s32>(0,0);
	while ( g_pIrr->run() )
	{
		g_pGame->Update();
		g_pGame->Render();
		driver->beginScene(true,true,SColor(255,100,101,140));
		/*driver->draw2DImage(images, core::position2d<s32>(50,50),
				core::rect<s32>(0,0,342,224), 0,
				video::SColor(255,255,255,255), true);*/
		if(receiver.IsKeyDown(irr::KEY_KEY_W))
			pos.Y -= 1;
		else if(receiver.IsKeyDown(irr::KEY_KEY_S))
			pos.Y += 1;

		if(receiver.IsKeyDown(irr::KEY_KEY_A))
			pos.X -= 1;
		else if(receiver.IsKeyDown(irr::KEY_KEY_D))
			pos.X += 1;
		texture->setPos(pos);
		texture->draw();
		/*core::vector3df nodePosition = node->getPosition();

		if(receiver.IsKeyDown(irr::KEY_KEY_W))
			nodePosition.Y += 1;
		else if(receiver.IsKeyDown(irr::KEY_KEY_S))
			nodePosition.Y -= 1;

		if(receiver.IsKeyDown(irr::KEY_KEY_A))
			nodePosition.X -= 1;
		else if(receiver.IsKeyDown(irr::KEY_KEY_D))
			nodePosition.X += 1;

		node->setPosition(nodePosition);*/
		smgr->drawAll();
		guienv->drawAll();
		driver->endScene();
	}
	g_pIrr->drop();
	return 0;
}