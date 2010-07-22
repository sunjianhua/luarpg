//
//
//

#include	"game.h"

int width=640;
int height=480;
CGame::CGame()
{
	dpos=core::position2d<s32>(0,0);
}

CGame::~CGame()
{
}

bool CGame::setScene(int num)
{
	IGUISkin* skin = guienv->getSkin();
	video::ITexture* images;
	IGUIFont* font;
	int w;
	int h;
	DTexture * texture;
	switch(num)
	{
	case 0:
		images = driver->getTexture("../../data/background/background01.jpg");
		background=new DTexture();
		background->setDriver(driver);
		background->setDevice(g_pIrr);
		background->insert(images,core::position2d<s32>(0,0),core::rect<s32>(0,0,640,480),1);
		background->setSize(640,480);
		font = guienv->getFont("../../media/fonthaettenschweiler.bmp");
		skin->setFont(guienv->getBuiltInFont(), EGDF_TOOLTIP);
		guienv->addButton(rect<s32>(412*width/1024,440*height/768,612*width/1024,(440 + 32)*height/768), 0, GUI_ID_START_BUTTON,
				L"Start Games", L"Start Program");
		guienv->addButton(rect<s32>(412*width/1024,480*height/768,612*width/1024,(480 + 32)*height/768), 0, GUI_ID_SET_BUTTON,
				L"Set Games", L"Setting");
		guienv->addButton(rect<s32>(412*width/1024,520*height/768,612*width/1024,(520 + 32)*height/768), 0, GUI_ID_QUIT_BUTTON,
				L"Quit Games", L"Exit Program");
		g_pIrr->setEventReceiver(&receiver);
		break;
	case 1:
		images = driver->getTexture("../../data/character/character02.png");
		w=images->getSize().Width/4;
		h=images->getSize().Height/4;
		character=new DTexture();
		character->setDriver(driver);
		character->setDevice(g_pIrr);
		character->setSize(w,h);
		for(int j=0;j<4;j++)
		{
			for(int i=0;i<4;i++)
			{
				character->insert(images,core::position2d<s32>(320,240),core::rect<s32>(i*w,j*h,(i+1)*w,(j+1)*h),1);
			}
		}
		character->setState(1);
		images = driver->getTexture("../../data/item/item01.png");
		texture=new DTexture();
		texture->setDriver(driver);
		texture->setDevice(g_pIrr);
		texture->insert(images,core::position2d<s32>(0,0),core::rect<s32>(0,images->getSize().Height/2,images->getSize().Width,images->getSize().Height),1);
		texture->setSize(images->getSize().Width,images->getSize().Height/2);
		texturearray.push_back(texture);
		break;
	case 2:
		images = driver->getTexture("../../data/gameover/gameover01.jpg");
		background=new DTexture();
		background->setDriver(driver);
		background->setDevice(g_pIrr);
		background->setSize(640,480);
		background->insert(images,core::position2d<s32>(0,0),core::rect<s32>(0,0,640,480),1);
		font = guienv->getFont("../../media/fonthaettenschweiler.bmp");
		skin->setFont(guienv->getBuiltInFont(), EGDF_TOOLTIP);
		guienv->addButton(rect<s32>(312*width/1024,440*height/768,512*width/1024,(440 + 32)*height/768), 0, GUI_ID_QUIT_YES_BUTTON,
				L"Yes", L"Quit Program");
		guienv->addButton(rect<s32>(512*width/1024,440*height/768,712*width/1024,(440 + 32)*height/768), 0, GUI_ID_QUIT_NO_BUTTON,
				L"No", L"Return Back");
		g_pIrr->setEventReceiver(&receiver);
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
	driver->beginScene(true,true,SColor(0,0,0,0));
	switch(receiver.state)
	{
	case 0:
		background->draw();
		break;
	case 1:
		for(int i=0;i<texturearray.size();i++)
		{
			texturearray[i]->setPos(dpos);
			texturearray[i]->draw();
		}
		character->draw();
		break;
	case 2:
		background->draw();
		break;
	case 3:
		exit(0);
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
		if(receiver.state==1)
		{
			if(receiver.IsKeyDown(irr::KEY_KEY_W))
			{
				character->setState(3);
				bool result=true;
				for(int i=0;i<texturearray.size();i++)
				{
					if((texturearray[i]->getPos().Y+texturearray[i]->getH())==(character->getPos().Y)&&(character->getPos().X+character->getW())>texturearray[i]->getPos().X&&(character->getPos().X)<(texturearray[i]->getPos().X+texturearray[i]->getW()))
					{
						result=false;
						break;
					}
				}
				if(result)
					dpos.Y++;
			}
			else if(receiver.IsKeyDown(irr::KEY_KEY_S))
			{
				character->setState(0);
				bool result=true;
				for(int i=0;i<texturearray.size();i++)
				{
					if(texturearray[i]->getPos().Y==(character->getPos().Y+character->getH())&&(character->getPos().X+character->getW())>texturearray[i]->getPos().X&&(character->getPos().X)<(texturearray[i]->getPos().X+texturearray[i]->getW()))
					{
						result=false;
						break;
					}
				}
				if(result)
					dpos.Y--;
			}
			if(receiver.IsKeyDown(irr::KEY_KEY_A))
			{
				character->setState(1);
				bool result=true;
				for(int i=0;i<texturearray.size();i++)
				{
					if((texturearray[i]->getPos().X+texturearray[i]->getW())==(character->getPos().X)&&(character->getPos().Y+character->getH())>texturearray[i]->getPos().Y&&(character->getPos().Y)<(texturearray[i]->getPos().Y+texturearray[i]->getH()))
					{
						result=false;
						break;
					}
				}
				if(result)
					dpos.X++;
			}
			if(receiver.IsKeyDown(irr::KEY_KEY_D))
			{
				character->setState(2);
				bool result=true;
				for(int i=0;i<texturearray.size();i++)
				{
					if((texturearray[i]->getPos().X)==(character->getPos().X+character->getW())&&(character->getPos().Y+character->getH())>texturearray[i]->getPos().Y&&(character->getPos().Y)<(texturearray[i]->getPos().Y+texturearray[i]->getH()))
					{
						result=false;
						break;
					}
				}
				if(result)
					dpos.X--;
			}
		}

	return true;
}