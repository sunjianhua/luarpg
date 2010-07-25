//
//
//


#ifndef	GAME_H
#define	GAME_H

#include <irrlicht.h>
#include "2DTexture.h"
using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;


enum
{
	GUI_ID_START_BUTTON = 101,
	GUI_ID_SET_BUTTON,
	GUI_ID_QUIT_BUTTON,
	GUI_ID_QUIT_YES_BUTTON,
	GUI_ID_QUIT_NO_BUTTON
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
							state=1;
							change=true;
							break;
						case GUI_ID_SET_BUTTON:
							break;

						case GUI_ID_QUIT_BUTTON:
							state=2;
							change=true;
							break;
						case GUI_ID_QUIT_YES_BUTTON:
							state=3;
							change=true;
							break;
						case GUI_ID_QUIT_NO_BUTTON:
							state=0;
							change=true;
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

	virtual bool IsKeyDown(EKEY_CODE keyCode) const
	{
		return KeyIsDown[keyCode];
	}
	MyEventReceiver()
	{
		for (u32 i=0; i<KEY_KEY_CODES_COUNT; ++i)
			KeyIsDown[i] = false;
	}	
	int state;
	bool change;
private:
	bool KeyIsDown[KEY_KEY_CODES_COUNT];

};


class	CGame
{
public:
	CGame();
	~CGame();
	virtual	bool	Initialize(irr::IrrlichtDevice*	g_pIrr,IVideoDriver* driver,ISceneManager* smgr,IGUIEnvironment* guienv);
	virtual	bool	Update();
	virtual	bool	Render();
	virtual bool Reset();
	virtual  bool setScene(int num);
protected:
private:
	core::array<DTexture*> texturearray;   //trees  ,rocks
	core::array<DTexture*> housearray;     //building
	core::array<DTexture*> npcarray;         //npc
	core::array<video::ITexture*> itemarray;		//battles items
	DTexture *background;
	DTexture *character;
	MyEventReceiver receiver;
	irr::IrrlichtDevice*	g_pIrr;
	IVideoDriver* driver;
	ISceneManager* smgr;
	IGUIEnvironment* guienv;
	core::position2d<s32> dpos;
};

#endif