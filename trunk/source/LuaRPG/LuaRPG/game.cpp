//
//
//

#include	"game.h"

CGame::CGame()
{
}

CGame::~CGame()
{
}

bool CGame::setScene(int num)
{
	IGUISkin* skin = guienv->getSkin();
	video::ITexture* images;
	IGUIFont* font;
	switch(num)
	{
	case 0:
		font = guienv->getFont("../../media/fonthaettenschweiler.bmp");
		skin->setFont(guienv->getBuiltInFont(), EGDF_TOOLTIP);
		guienv->addButton(rect<s32>(412,440,612,440 + 32), 0, GUI_ID_START_BUTTON,
				L"Start Games", L"Start Program");
		guienv->addButton(rect<s32>(412,480,612,480 + 32), 0, GUI_ID_SET_BUTTON,
				L"Set Games", L"Setting");
		guienv->addButton(rect<s32>(412,520,612,520 + 32), 0, GUI_ID_QUIT_BUTTON,
				L"Quit Games", L"Exit Program");
		g_pIrr->setEventReceiver(&receiver);
		break;
	case 1:
		images = driver->getTexture("../../media/2ddemo.png");
		texture=new DTexture();
		texture->setDriver(driver);
		texture->setDevice(g_pIrr);
		texture->insert(images,core::position2d<s32>(0,0),core::rect<s32>(0,0,342,224),1);
		texture1=new DTexture();
		texture1->setDriver(driver);
		texture1->setDevice(g_pIrr);
		texture1->insert(images,core::position2d<s32>(0,0),core::rect<s32>(349,15,385,78),1);
		texture1->insert(images,core::position2d<s32>(0,0),core::rect<s32> (387,15,423,78),1);
		break;
	default:
		break;
	}
	return true;
}
bool	CGame::Initialize(irr::IrrlichtDevice*	g_pIrr,IVideoDriver* driver,ISceneManager* smgr,IGUIEnvironment* guienv)
{
	this->g_pIrr=g_pIrr;
	this->driver=driver;
	this->smgr=smgr;
	this->guienv=guienv;
	this->setScene(0);
	receiver.state=0;
	receiver.change=false;
	return true;
}


bool	CGame::Render()
{
	driver->beginScene(true,true,SColor(255,100,101,140));
	if(receiver.state==1)
	{
		texture->draw();
		texture1->draw();
	}
	smgr->drawAll();
	guienv->drawAll();
	driver->endScene();
	return true;
}
bool CGame::Reset()
{
	smgr->clear();
	guienv->clear();
	return true;
}

bool	CGame::Update()
{
		if(receiver.change)
		{
			this->Reset();
			this->setScene(receiver.state);
			receiver.change=false;
		}

	return true;
}