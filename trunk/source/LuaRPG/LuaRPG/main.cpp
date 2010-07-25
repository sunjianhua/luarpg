//
//
//
#include <irrlicht.h>
#include	"game.h"
using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;
irr::IrrlichtDevice*	g_pIrr;
IVideoDriver* driver;
ISceneManager* smgr;
IGUIEnvironment* guienv;
CGame*	g_pGame;

//enum
//{
//	GUI_ID_START_BUTTON = 101,
//	GUI_ID_QUIT_BUTTON
//};
//
//class MyEventReceiver : public IEventReceiver
//{
//public:
//	//MyEventReceiver(SAppContext & context) : Context(context) { }
//	// This is the one method that we have to implement
//	virtual bool OnEvent(const SEvent& event)
//	{
//		// Remember whether each key is down or up
//		if (event.EventType == irr::EET_KEY_INPUT_EVENT)
//			KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;
//
//		if (event.EventType == EET_GUI_EVENT)
//		{
//			s32 id = event.GUIEvent.Caller->getID();
//			//IGUIEnvironment* env = Context.device->getGUIEnvironment();
//
//			switch(event.GUIEvent.EventType)
//			{
//				case EGET_BUTTON_CLICKED:
//					switch(id)
//					{
//						case GUI_ID_START_BUTTON:
//							break;
//
//						case GUI_ID_QUIT_BUTTON:
//							break;
//						default:
//							return false;
//					}
//					break;
//				default:
//					break;
//			}
//		}
//		return false;
//	}
//
//	// This is used to check whether a key is being held down
//	virtual bool IsKeyDown(EKEY_CODE keyCode) const
//	{
//		return KeyIsDown[keyCode];
//	}
//	
//	MyEventReceiver()
//	{
//		for (u32 i=0; i<KEY_KEY_CODES_COUNT; ++i)
//			KeyIsDown[i] = false;
//	}
//
//private:
//	// We use this array to store the current state of each key
//	bool KeyIsDown[KEY_KEY_CODES_COUNT];
//};


int	main()
{
	g_pIrr = createDevice( video::EDT_DIRECT3D9,	core::dimension2d<u32>(640,480) ,16, false, false, false,0);
	driver=g_pIrr->getVideoDriver();
	smgr=g_pIrr->getSceneManager();
	guienv=g_pIrr->getGUIEnvironment();
	g_pGame = new CGame;
	g_pGame->Initialize(g_pIrr,driver,smgr,guienv);
	while ( g_pIrr->run() )
	{
		g_pGame->Update();
 		g_pGame->Render();
	}
	g_pIrr->drop();
	return 0;
}