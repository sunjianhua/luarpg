//
//
//

#include	"game.h"

int width=640;
int height=480;
bool out=false;
int hp=100;
int enemy=200;
core::array<int> del;
CGame::CGame()
{
	dpos=core::position2d<s32>(0,0);
	loader = new CLuaLoader;
	loader->Init();
	int code = loader->LoadFile( -1, "init.lua" );
	treenumber = loader->GetInt( code, "treenumber" );
	tree=new std::string[treenumber];
	loader->GetArrayString( code, "tree", tree, 1, treenumber );


	housenumber=loader->GetInt( code, "housenumber" );
	house=new std::string[housenumber];
	loader->GetArrayString( code, "house", house, 1, housenumber );

	characternumber=loader->GetInt( code, "characternumber" );
	cha=new std::string[characternumber];
	loader->GetArrayString( code, "character", cha, 1, characternumber );

	shopbackgroundnumber=loader->GetInt( code, "shopbackgroundnumber" );
	shopbackground=new std::string[shopbackgroundnumber];
	loader->GetArrayString( code, "shopbackground", shopbackground, 1, shopbackgroundnumber );

	loader = new CLuaLoader;
	loader->Init();
	code = loader->LoadFile( -1, "setting.lua" );

	treenumber01 = loader->GetInt( code, "treenumber" );
	tree01=new int[treenumber01];
	treepos01=new int[treenumber01*2];
	loader->GetArrayInt( code, "tree", tree01, 1, treenumber01 );
	loader->GetArrayInt( code, "treepos", treepos01, 1, treenumber01*2 );

	housenumber01=loader->GetInt( code, "housenumber" );
	house01=new int[housenumber01];
	housepos01=new int[housenumber01*2];
	loader->GetArrayInt( code, "house", house01, 1, housenumber01 );
	loader->GetArrayInt( code, "housepos", housepos01, 1, housenumber01*2 );

	characternumber01=loader->GetInt( code, "characternumber" );
	cha01=new int[characternumber01];
	chapos01=new int[characternumber01*2];
	loader->GetArrayInt( code, "character", cha01, 1, characternumber01 );
	loader->GetArrayInt( code, "characterpos", chapos01, 1, characternumber01*2 );

	npcnumber01=loader->GetInt( code, "npcnumber" );
	npc01=new int[npcnumber01];
	npcpos01=new int[npcnumber01*2];
	loader->GetArrayInt( code, "npc", npc01, 1,npcnumber01 );
	loader->GetArrayInt( code, "npcpos", npcpos01, 1, npcnumber01*2 );


	shopbackgroundnumber01=loader->GetInt( code, "shopbackgroundnumber" );

	/*
	int y = loader->GetInt( code, "y" );
	std::string x = loader->GetString( code, "x" );
	double z = loader->GetDouble( code, "z" );
	loader->GetFieldBegin( code, "a" );
	loader->GetFieldInt( code, 1, y );
	loader->GetFieldString( code, "xyu", x );
	loader->GetFieldDouble( code, 2, z );
	loader->GetFieldEnd( code );
	int* arr = new int[5];
	double* arr_double = new double[5];
	std::string* arr_string = new std::string[5];
	loader->GetArrayInt( code, "b", arr, 1, 3 );
	loader->GetArrayDouble( code, "c", arr_double, 2, 5 );
	loader->GetArrayString( code, "d", arr_string, 3, 4 );
	*/
}

CGame::~CGame()
{
}

bool CGame::setScene(int num)
{
	int code;
	IGUISkin* skin = guienv->getSkin();
	video::ITexture* images;
	IGUIFont* font;
	int w;
	int h;
	DTexture * texture;
	irr::gui::IGUIButton* button;
	int x=0;int y=0;
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
		//main character
		loader = new CLuaLoader;
		loader->Init();
		code = loader->LoadFile( -1, "setting.lua" );

		treenumber01 = loader->GetInt( code, "treenumber" );
		tree01=new int[treenumber01];
		treepos01=new int[treenumber01*2];
		loader->GetArrayInt( code, "tree", tree01, 1, treenumber01 );
		loader->GetArrayInt( code, "treepos", treepos01, 1, treenumber01*2 );

		housenumber01=loader->GetInt( code, "housenumber" );
		house01=new int[housenumber01];
		housepos01=new int[housenumber01*2];
		loader->GetArrayInt( code, "house", house01, 1, housenumber01 );
		loader->GetArrayInt( code, "housepos", housepos01, 1, housenumber01*2 );

		characternumber01=loader->GetInt( code, "characternumber" );
		cha01=new int[characternumber01];
		chapos01=new int[characternumber01*2];
		loader->GetArrayInt( code, "character", cha01, 1, characternumber01 );
		loader->GetArrayInt( code, "characterpos", chapos01, 1, characternumber01*2 );

		npcnumber01=loader->GetInt( code, "npcnumber" );
		npc01=new int[npcnumber01];
		npcpos01=new int[npcnumber01*2];
		loader->GetArrayInt( code, "npc", npc01, 1,npcnumber01 );
		loader->GetArrayInt( code, "npcpos", npcpos01, 1, npcnumber01*2 );


		shopbackgroundnumber01=loader->GetInt( code, "shopbackgroundnumber" );


		for(int a=0;a<characternumber01;a++)
		{
			images = driver->getTexture(cha[cha01[a]].c_str());
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
					character->insert(images,core::position2d<s32>(chapos01[a*2],chapos01[a*2+1]),core::rect<s32>(i*w,j*h,(i+1)*w,(j+1)*h),1);
				}
			}
			character->setState(1);
		}
		//npc
		for(int a=0;a<npcnumber01;a++)
		{
			images = driver->getTexture(cha[npc01[a]].c_str());
			w=images->getSize().Width/4;
			h=images->getSize().Height/4;
			texture=new DTexture();
			texture->setDriver(driver);
			texture->setDevice(g_pIrr);
			texture->setSize(w,h);
			for(int j=0;j<4;j++)
			{
				for(int i=0;i<4;i++)
				{
					texture->insert(images,core::position2d<s32>(npcpos01[a*2],npcpos01[a*2+1]),core::rect<s32>(i*w,j*h,(i+1)*w,(j+1)*h),1);
				}
			}
			texture->setState(1);
			npcarray.push_back(texture);
		}
		//trees
		for(int a=0;a<treenumber01;a++)
		{
			images = driver->getTexture(tree[tree01[a]].c_str());
			texture=new DTexture();
			texture->setDriver(driver);
			texture->setDevice(g_pIrr);
			/*texture->insert(images,core::position2d<s32>(0,0),core::rect<s32>(0,images->getSize().Height/2+80,images->getSize().Width,images->getSize().Height),1);
			texture->setSize(images->getSize().Width,images->getSize().Height/2-80);*/
			texture->insert(images,core::position2d<s32>(treepos01[a*2],treepos01[a*2+1]),core::rect<s32>(0,0,images->getSize().Width,images->getSize().Height),1);
			texture->setSize(images->getSize().Width,images->getSize().Height);
			texturearray.push_back(texture);
		}
		//house
		for(int a=0;a<housenumber01;a++)
		{
			images = driver->getTexture(house[house01[a]].c_str());
			texture=new DTexture();
			texture->setDriver(driver);
			texture->setDevice(g_pIrr);
			/*texture->insert(images,core::position2d<s32>(500,0),core::rect<s32>(0,images->getSize().Height/2+130,images->getSize().Width-100,images->getSize().Height),1);
			texture->setSize(images->getSize().Width-100,images->getSize().Height/2-130);*/
			texture->insert(images,core::position2d<s32>(housepos01[a*2],housepos01[a*2+1]),core::rect<s32>(0,0,images->getSize().Width,images->getSize().Height),1);
			texture->setSize(images->getSize().Width,images->getSize().Height);
			housearray.push_back(texture);
		}
		//gate to outdoors
		images = driver->getTexture("../../data/house/house01.png");
		texture=new DTexture();
		texture->setDriver(driver);
		texture->setDevice(g_pIrr);
		texture->insert(images,core::position2d<s32>(500,400),core::rect<s32>(0,0,images->getSize().Width,images->getSize().Height),1);
		texture->setSize(images->getSize().Width,images->getSize().Height);
		gatearray.push_back(texture);
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
	case 4:
		images = driver->getTexture("../../data/background/shopbackground01.jpg");
		background=new DTexture();
		background->setDriver(driver);
		background->setDevice(g_pIrr);
		background->insert(images,core::position2d<s32>((640-images->getSize().Width)/2,(480-images->getSize().Height)/2),core::rect<s32>(0,0,images->getSize().Width,images->getSize().Height),1);
		background->setSize(images->getSize().Width,images->getSize().Height);


		guienv->addButton(rect<s32>(412*width/1024,520*height/768,612*width/1024,(520 + 32)*height/768), 0, GUI_ID_START_BUTTON,
				L"Buy", L"Buy");
		guienv->addButton(rect<s32>(412*width/1024,560*height/768,612*width/1024,(560 + 32)*height/768), 0,GUI_ID_START_BUTTON,
				L"Return", L"Return Game");

		images = driver->getTexture("../../data/battleitem/001-Weapon01.png");
		itemarray.push_back(images);
		images = driver->getTexture("../../data/battleitem/002-Weapon02.png");
		itemarray.push_back(images);

		font = guienv->getFont("../../media/fonthaettenschweiler.bmp");
		skin->setFont(guienv->getBuiltInFont(), EGDF_TOOLTIP);
		for(int i=0;i<itemarray.size();i++)
		{
			button=guienv->addButton(rect<s32>(x,y,x+itemarray[i]->getSize().Width,y+itemarray[i]->getSize().Height), 0, GUI_ID_QUIT_YES_BUTTON,
				L"a", L"a");
			button->setImage(itemarray[i],rect<s32>(0,0,itemarray[i]->getSize().Width,itemarray[i]->getSize().Height));
			x+=itemarray[i]->getSize().Width;
		}
		g_pIrr->setEventReceiver(&receiver);
		break;
	case 5:
		//main character
		/*images = driver->getTexture("../../data/character/character02.png");
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

		images = driver->getTexture("../../data/character/character01.png");
		w=images->getSize().Width/4;
		h=images->getSize().Height/4;
		texture=new DTexture();
		texture->setDriver(driver);
		texture->setDevice(g_pIrr);
		texture->setSize(w,h);
		for(int j=0;j<4;j++)
		{
			for(int i=0;i<4;i++)
			{
				texture->insert(images,core::position2d<s32>(300,240),core::rect<s32>(i*w,j*h,(i+1)*w,(j+1)*h),1);
			}
		}
		texture->setState(1);
		npcarray.push_back(texture);

		images = driver->getTexture("../../data/item/item01.png");
		texture=new DTexture();
		texture->setDriver(driver);
		texture->setDevice(g_pIrr);
		texture->insert(images,core::position2d<s32>(0,0),core::rect<s32>(0,images->getSize().Height/2+80,images->getSize().Width,images->getSize().Height),1);
		texture->setSize(images->getSize().Width,images->getSize().Height/2-80);
		texturearray.push_back(texture);

		images = driver->getTexture("../../data/house/house01.png");
		texture=new DTexture();
		texture->setDriver(driver);
		texture->setDevice(g_pIrr);
		texture->insert(images,core::position2d<s32>(500,400),core::rect<s32>(0,images->getSize().Height/2+40,images->getSize().Width-200,images->getSize().Height/2+130),1);
		texture->setSize(images->getSize().Width-200,90);
		gatearray.push_back(texture);
		break;*/
		loader = new CLuaLoader;
		loader->Init();
		code = loader->LoadFile( -1, "settingbattle1.lua" );

		treenumber01 = loader->GetInt( code, "treenumber" );
		tree01=new int[treenumber01];
		treepos01=new int[treenumber01*2];
		loader->GetArrayInt( code, "tree", tree01, 1, treenumber01 );
		loader->GetArrayInt( code, "treepos", treepos01, 1, treenumber01*2 );

		housenumber01=loader->GetInt( code, "housenumber" );
		house01=new int[housenumber01];
		housepos01=new int[housenumber01*2];
		loader->GetArrayInt( code, "house", house01, 1, housenumber01 );
		loader->GetArrayInt( code, "housepos", housepos01, 1, housenumber01*2 );

		characternumber01=loader->GetInt( code, "characternumber" );
		cha01=new int[characternumber01];
		chapos01=new int[characternumber01*2];
		loader->GetArrayInt( code, "character", cha01, 1, characternumber01 );
		loader->GetArrayInt( code, "characterpos", chapos01, 1, characternumber01*2 );

		npcnumber01=loader->GetInt( code, "npcnumber" );
		npc01=new int[npcnumber01];
		npcpos01=new int[npcnumber01*2];
		loader->GetArrayInt( code, "npc", npc01, 1,npcnumber01 );
		loader->GetArrayInt( code, "npcpos", npcpos01, 1, npcnumber01*2 );


		shopbackgroundnumber01=loader->GetInt( code, "shopbackgroundnumber" );


		for(int a=0;a<characternumber01;a++)
		{
			images = driver->getTexture(cha[cha01[a]].c_str());
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
					character->insert(images,core::position2d<s32>(chapos01[a*2],chapos01[a*2+1]),core::rect<s32>(i*w,j*h,(i+1)*w,(j+1)*h),1);
				}
			}
			character->setState(1);
		}
		//npc
		for(int a=0;a<npcnumber01;a++)
		{
			images = driver->getTexture(cha[npc01[a]].c_str());
			w=images->getSize().Width/4;
			h=images->getSize().Height/4;
			texture=new DTexture();
			texture->setDriver(driver);
			texture->setDevice(g_pIrr);
			texture->setSize(w,h);
			for(int j=0;j<4;j++)
			{
				for(int i=0;i<4;i++)
				{
					texture->insert(images,core::position2d<s32>(npcpos01[a*2],npcpos01[a*2+1]),core::rect<s32>(i*w,j*h,(i+1)*w,(j+1)*h),1);
				}
			}
			texture->setState(1);
			npcarray.push_back(texture);
		}
		for(int a=0;a<del.size();a++)
		{
			npcarray.erase(del[a]);
		}
		//trees
		for(int a=0;a<treenumber01;a++)
		{
			images = driver->getTexture(tree[tree01[a]].c_str());
			texture=new DTexture();
			texture->setDriver(driver);
			texture->setDevice(g_pIrr);
			/*texture->insert(images,core::position2d<s32>(0,0),core::rect<s32>(0,images->getSize().Height/2+80,images->getSize().Width,images->getSize().Height),1);
			texture->setSize(images->getSize().Width,images->getSize().Height/2-80);*/
			texture->insert(images,core::position2d<s32>(treepos01[a*2],treepos01[a*2+1]),core::rect<s32>(0,0,images->getSize().Width,images->getSize().Height),1);
			texture->setSize(images->getSize().Width,images->getSize().Height);
			texturearray.push_back(texture);
		}
		//house
		for(int a=0;a<housenumber01;a++)
		{
			images = driver->getTexture(house[house01[a]].c_str());
			texture=new DTexture();
			texture->setDriver(driver);
			texture->setDevice(g_pIrr);
			/*texture->insert(images,core::position2d<s32>(500,0),core::rect<s32>(0,images->getSize().Height/2+130,images->getSize().Width-100,images->getSize().Height),1);
			texture->setSize(images->getSize().Width-100,images->getSize().Height/2-130);*/
			texture->insert(images,core::position2d<s32>(housepos01[a*2],housepos01[a*2+1]),core::rect<s32>(0,0,images->getSize().Width,images->getSize().Height),1);
			texture->setSize(images->getSize().Width,images->getSize().Height);
			housearray.push_back(texture);
		}
		//gate to outdoors
		images = driver->getTexture("../../data/house/house01.png");
		texture=new DTexture();
		texture->setDriver(driver);
		texture->setDevice(g_pIrr);
		texture->insert(images,core::position2d<s32>(500,400),core::rect<s32>(0,0,images->getSize().Width,images->getSize().Height),1);
		texture->setSize(images->getSize().Width,images->getSize().Height);
		gatearray.push_back(texture);
		break;
	case 6:
		images = driver->getTexture("../../data/Battlebacks/002-Woods01.jpg");
		background=new DTexture();
		background->setDriver(driver);
		background->setDevice(g_pIrr);
		background->insert(images,core::position2d<s32>((640-images->getSize().Width)/2,(480-images->getSize().Height)/2),core::rect<s32>(0,0,images->getSize().Width,images->getSize().Height),1);
		background->setSize(images->getSize().Width,images->getSize().Height);
		images = driver->getTexture("../../data/Battlers/004-Fighter04.png");
		texture=new DTexture();
		texture->setDriver(driver);
		texture->setDevice(g_pIrr);
		texture->insert(images,core::position2d<s32>(700*width/1024,204*height/768),core::rect<s32>(0,0,images->getSize().Width,images->getSize().Height),1);
		texture->setSize(images->getSize().Width,images->getSize().Height);
		texturearray.push_back(texture);

		images = driver->getTexture("../../data/Battlers/099-Monster13.png");
		texture=new DTexture();
		texture->setDriver(driver);
		texture->setDevice(g_pIrr);
		texture->insert(images,core::position2d<s32>(-100*width/1024,44*height/768),core::rect<s32>(0,0,images->getSize().Width,images->getSize().Height),1);
		texture->setSize(images->getSize().Width,images->getSize().Height);
		texturearray.push_back(texture);
		dpos.X=5;

		font = guienv->getFont("../../media/fonthaettenschweiler.bmp");
		skin->setFont(guienv->getBuiltInFont(), EGDF_TOOLTIP);
		g_pIrr->setEventReceiver(&receiver);
		enemy=100;
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
		for(int i=0;i<housearray.size();i++)
		{
		
			housearray[i]->setPos(dpos);
			housearray[i]->draw();
		}
		for(int i=0;i<npcarray.size();i++)
		{
			npcarray[i]->setAI(i%3);
			npcarray[i]->setPos(dpos);
			npcarray[i]->draw();
		}
		for(int i=0;i<gatearray.size();i++)
		{
		
			gatearray[i]->setPos(dpos);
			gatearray[i]->draw();
		}
		character->draw();
		break;
	case 2:
		background->draw();
		break;
	case 3:
		exit(0);
		break;
	case 4:
		background->draw();
		break;
	case 5:
		for(int i=0;i<texturearray.size();i++)
		{
			texturearray[i]->setPos(dpos);
			texturearray[i]->draw();
		}
		for(int i=0;i<npcarray.size();i++)
		{
			npcarray[i]->setAI(i%3);
			npcarray[i]->setPos(dpos);
			npcarray[i]->draw();
		}
		for(int i=0;i<gatearray.size();i++)
		{
			gatearray[i]->setPos(dpos);
			gatearray[i]->draw();
		}
		character->draw();
		break;
	case 6:
		background->draw();
		
		for(int i=0;i<texturearray.size();i++)
		{
			texturearray[i]->setPos(dpos);
			texturearray[i]->draw();
		}
		for(int i=0;i<npcarray.size();i++)
		{
			npcarray[i]->setPos(dpos);
			npcarray[i]->draw();
		}
		break;
	}
	smgr->drawAll();
	guienv->drawAll();
	driver->endScene();
	return true;
}
bool CGame::Reset()
{
	gatearray.clear();
	texturearray.clear();
	housearray.clear();
	npcarray.clear();
	itemarray.clear();
	smgr->clear();
	guienv->clear();
	dpos.X=0;
	dpos.Y=0;
	return true;
}
bool clic=false;
bool	CGame::Update()
{
		video::ITexture* images;
		IGUIFont* font;
		int w;
		int h;
		DTexture * texture;
		if(receiver.state==5)
		{
			bool result=false;
			for(int i=0;i<npcarray.size();i++)
			{
				if(abs(npcarray[i]->getPos().Y+npcarray[i]->getH()/2-character->getPos().Y-character->getH()/2)<=s32_max(character->getH()/2,npcarray[i]->getH()/2)&&abs(npcarray[i]->getPos().X+npcarray[i]->getW()/2-character->getPos().X-character->getW()/2)<=s32_max(character->getW()/2,npcarray[i]->getW()/2))
				{
					del.push_back(i);
					receiver.state=6;
					receiver.change=true;
					break;
				}
			}
			if(receiver.IsKeyDown(irr::KEY_KEY_J))
			{
				//out the city
				if(out)
				{
					receiver.state=1;
					receiver.change=true;
				}
			}
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
				for(int i=0;i<housearray.size();i++)
				{
					if((housearray[i]->getPos().Y+housearray[i]->getH())==(character->getPos().Y)&&(character->getPos().X+character->getW())>housearray[i]->getPos().X&&(character->getPos().X)<(housearray[i]->getPos().X+housearray[i]->getW()))
					{
						result=false;
						break;
					}
				}
				for(int i=0;i<npcarray.size();i++)
				{
					if((npcarray[i]->getPos().Y+npcarray[i]->getH())==(character->getPos().Y)&&(character->getPos().X+character->getW())>npcarray[i]->getPos().X&&(character->getPos().X)<(npcarray[i]->getPos().X+npcarray[i]->getW()))
					{
						result=false;
						break;
					}
				}
				for(int i=0;i<gatearray.size();i++)
				{
					if((gatearray[i]->getPos().Y+gatearray[i]->getH())==(character->getPos().Y)&&(character->getPos().X+character->getW())>gatearray[i]->getPos().X&&(character->getPos().X)<(gatearray[i]->getPos().X+gatearray[i]->getW()))
					{
						out=true;
						result=false;
						break;
					}
				}
				if(result)
				{
					out=false;
					dpos.Y++;
				}
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
				for(int i=0;i<housearray.size();i++)
				{
					if(housearray[i]->getPos().Y==(character->getPos().Y+character->getH())&&(character->getPos().X+character->getW())>housearray[i]->getPos().X&&(character->getPos().X)<(housearray[i]->getPos().X+housearray[i]->getW()))
					{
						result=false;
						break;
					}
				}
				for(int i=0;i<npcarray.size();i++)
				{
					if(npcarray[i]->getPos().Y==(character->getPos().Y+character->getH())&&(character->getPos().X+character->getW())>npcarray[i]->getPos().X&&(character->getPos().X)<(npcarray[i]->getPos().X+npcarray[i]->getW()))
					{
						result=false;
						break;
					}
				}
				for(int i=0;i<gatearray.size();i++)
				{
					if(gatearray[i]->getPos().Y==(character->getPos().Y+character->getH())&&(character->getPos().X+character->getW())>gatearray[i]->getPos().X&&(character->getPos().X)<(gatearray[i]->getPos().X+gatearray[i]->getW()))
					{
						out=true;
						result=false;
						break;
					}
				}
				if(result)
				{
					out=false;
					dpos.Y--;
				}
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
				for(int i=0;i<housearray.size();i++)
				{
					if((housearray[i]->getPos().X+housearray[i]->getW())==(character->getPos().X)&&(character->getPos().Y+character->getH())>housearray[i]->getPos().Y&&(character->getPos().Y)<(housearray[i]->getPos().Y+housearray[i]->getH()))
					{
						result=false;
						break;
					}
				}
				for(int i=0;i<npcarray.size();i++)
				{
					if((npcarray[i]->getPos().X+npcarray[i]->getW())==(character->getPos().X)&&(character->getPos().Y+character->getH())>npcarray[i]->getPos().Y&&(character->getPos().Y)<(npcarray[i]->getPos().Y+npcarray[i]->getH()))
					{
						result=false;
						break;
					}
				}
				for(int i=0;i<gatearray.size();i++)
				{
					if((gatearray[i]->getPos().X+gatearray[i]->getW())==(character->getPos().X)&&(character->getPos().Y+character->getH())>gatearray[i]->getPos().Y&&(character->getPos().Y)<(gatearray[i]->getPos().Y+gatearray[i]->getH()))
					{
						out=true;
						result=false;
						break;
					}
				}
				if(result)
				{
					out=false;
					dpos.X++;
				}
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
				for(int i=0;i<housearray.size();i++)
				{
					if((housearray[i]->getPos().X)==(character->getPos().X+character->getW())&&(character->getPos().Y+character->getH())>housearray[i]->getPos().Y&&(character->getPos().Y)<(housearray[i]->getPos().Y+housearray[i]->getH()))
					{
						result=false;
						break;
					}
				}
				for(int i=0;i<npcarray.size();i++)
				{
					if((npcarray[i]->getPos().X)==(character->getPos().X+character->getW())&&(character->getPos().Y+character->getH())>npcarray[i]->getPos().Y&&(character->getPos().Y)<(npcarray[i]->getPos().Y+npcarray[i]->getH()))
					{
						result=false;
						break;
					}
				}
				for(int i=0;i<gatearray.size();i++)
				{
					if((gatearray[i]->getPos().X)==(character->getPos().X+character->getW())&&(character->getPos().Y+character->getH())>gatearray[i]->getPos().Y&&(character->getPos().Y)<(gatearray[i]->getPos().Y+gatearray[i]->getH()))
					{
						out=true;
						result=false;
						break;
					}
				}
				if(result)
				{
					out=false;
					dpos.X--;
				}
			}
		}
		else if(receiver.state==6)
		{
			if(receiver.IsKeyDown(irr::KEY_KEY_J)&&!clic)
			{
				clic=true;
				images = driver->getTexture("../../data/Animations/001-Action01.png");
				int w=images->getSize().Width/5;
				int h=images->getSize().Height/2;
				texture=new DTexture();
				texture->setDriver(driver);
				texture->setDevice(g_pIrr);
				texture->setSize(w,h);
				for(int i=0;i<4;i++)
				{
					for(int j=0;j<4;j++)
					{
						texture->insert(images,core::position2d<s32>(100*width/1024,234*height/768),core::rect<s32>((j+1)*w,0,(j+2)*w,h),1);
					}
				}
				texture->setState(0);
				npcarray.push_back(texture);
				

			}
			else if(receiver.IsKeyDown(irr::KEY_KEY_K)&&!clic)
			{
				clic=true;
				images = driver->getTexture("../../data/Animations/003-Attack01.png");
				int w=images->getSize().Width/5;
				int h=images->getSize().Height/2;
				texture=new DTexture();
				texture->setDriver(driver);
				texture->setDevice(g_pIrr);
				texture->setSize(w,h);
				for(int i=0;i<4;i++)
				{
					for(int j=0;j<4;j++)
					{
						texture->insert(images,core::position2d<s32>(100*width/1024,234*height/768),core::rect<s32>((j+1)*w,0,(j+2)*w,h),1);
					}
				}
				texture->setState(0);
				npcarray.push_back(texture);


			}
			else if(receiver.IsKeyDown(irr::KEY_KEY_L)&&!clic)
			{
				clic=true;
				images = driver->getTexture("../../data/Animations/015-Fire01.png");
				int w=images->getSize().Width/5;
				int h=images->getSize().Height/2;
				texture=new DTexture();
				texture->setDriver(driver);
				texture->setDevice(g_pIrr);
				texture->setSize(w,h);
				for(int i=0;i<4;i++)
				{
					for(int j=0;j<4;j++)
					{
						texture->insert(images,core::position2d<s32>(100*width/1024,234*height/768),core::rect<s32>((j+0)*w,0,(j+1)*w,h),1);
					}
				}
				texture->setState(0);
				npcarray.push_back(texture);


			}
			
			if(enemy<0)
			{
				receiver.state=5;
				receiver.change=true;

			}
		}
		else if(receiver.state==1)
		{
			bool result=false;
			if(receiver.IsKeyDown(irr::KEY_KEY_J))
			{
				for(int i=0;i<housearray.size();i++)
				{
					if((housearray[i]->getPos().Y+housearray[i]->getH())==(character->getPos().Y)&&(character->getPos().X+character->getW())>(housearray[i]->getPos().X+housearray[i]->getW()/2)&&(character->getPos().X)<(housearray[i]->getPos().X+housearray[i]->getW()/2))
					{
						result=true;
						break;
					}
				}
				if(result)
				{
					receiver.state=4;
					receiver.change=true;
				}
				//out the city
				if(out)
				{
					receiver.state=5;
					receiver.change=true;
					
					/*this->dpos.X=320-gatearray[0]->getW()/2-gatearray[0]->getPos().X;
					this->dpos.Y=240-gatearray[0]->getH()-gatearray[0]->getPos().Y;*/
				}
			}
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
				for(int i=0;i<housearray.size();i++)
				{
					if((housearray[i]->getPos().Y+housearray[i]->getH())==(character->getPos().Y)&&(character->getPos().X+character->getW())>housearray[i]->getPos().X&&(character->getPos().X)<(housearray[i]->getPos().X+housearray[i]->getW()))
					{
						result=false;
						break;
					}
				}
				for(int i=0;i<npcarray.size();i++)
				{
					if((npcarray[i]->getPos().Y+npcarray[i]->getH())==(character->getPos().Y)&&(character->getPos().X+character->getW())>npcarray[i]->getPos().X&&(character->getPos().X)<(npcarray[i]->getPos().X+npcarray[i]->getW()))
					{
						result=false;
						break;
					}
				}
				for(int i=0;i<gatearray.size();i++)
				{
					if((gatearray[i]->getPos().Y+gatearray[i]->getH())==(character->getPos().Y)&&(character->getPos().X+character->getW())>gatearray[i]->getPos().X&&(character->getPos().X)<(gatearray[i]->getPos().X+gatearray[i]->getW()))
					{
						out=true;
						result=false;
						break;
					}
				}
				if(result)
				{
					out=false;
					dpos.Y++;
				}
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
				for(int i=0;i<housearray.size();i++)
				{
					if(housearray[i]->getPos().Y==(character->getPos().Y+character->getH())&&(character->getPos().X+character->getW())>housearray[i]->getPos().X&&(character->getPos().X)<(housearray[i]->getPos().X+housearray[i]->getW()))
					{
						result=false;
						break;
					}
				}
				for(int i=0;i<npcarray.size();i++)
				{
					if(npcarray[i]->getPos().Y==(character->getPos().Y+character->getH())&&(character->getPos().X+character->getW())>npcarray[i]->getPos().X&&(character->getPos().X)<(npcarray[i]->getPos().X+npcarray[i]->getW()))
					{
						result=false;
						break;
					}
				}
				for(int i=0;i<gatearray.size();i++)
				{
					if(gatearray[i]->getPos().Y==(character->getPos().Y+character->getH())&&(character->getPos().X+character->getW())>gatearray[i]->getPos().X&&(character->getPos().X)<(gatearray[i]->getPos().X+gatearray[i]->getW()))
					{
						out=true;
						result=false;
						break;
					}
				}
				if(result)
				{
					out=false;
					dpos.Y--;
				}
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
				for(int i=0;i<housearray.size();i++)
				{
					if((housearray[i]->getPos().X+housearray[i]->getW())==(character->getPos().X)&&(character->getPos().Y+character->getH())>housearray[i]->getPos().Y&&(character->getPos().Y)<(housearray[i]->getPos().Y+housearray[i]->getH()))
					{
						result=false;
						break;
					}
				}
				for(int i=0;i<npcarray.size();i++)
				{
					if((npcarray[i]->getPos().X+npcarray[i]->getW())==(character->getPos().X)&&(character->getPos().Y+character->getH())>npcarray[i]->getPos().Y&&(character->getPos().Y)<(npcarray[i]->getPos().Y+npcarray[i]->getH()))
					{
						result=false;
						break;
					}
				}
				for(int i=0;i<gatearray.size();i++)
				{
					if((gatearray[i]->getPos().X+gatearray[i]->getW())==(character->getPos().X)&&(character->getPos().Y+character->getH())>gatearray[i]->getPos().Y&&(character->getPos().Y)<(gatearray[i]->getPos().Y+gatearray[i]->getH()))
					{
						out=true;
						result=false;
						break;
					}
				}
				if(result)
				{
					out=false;
					dpos.X++;
				}
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
				for(int i=0;i<housearray.size();i++)
				{
					if((housearray[i]->getPos().X)==(character->getPos().X+character->getW())&&(character->getPos().Y+character->getH())>housearray[i]->getPos().Y&&(character->getPos().Y)<(housearray[i]->getPos().Y+housearray[i]->getH()))
					{
						result=false;
						break;
					}
				}
				for(int i=0;i<npcarray.size();i++)
				{
					if((npcarray[i]->getPos().X)==(character->getPos().X+character->getW())&&(character->getPos().Y+character->getH())>npcarray[i]->getPos().Y&&(character->getPos().Y)<(npcarray[i]->getPos().Y+npcarray[i]->getH()))
					{
						result=false;
						break;
					}
				}
				for(int i=0;i<gatearray.size();i++)
				{
					if((gatearray[i]->getPos().X)==(character->getPos().X+character->getW())&&(character->getPos().Y+character->getH())>gatearray[i]->getPos().Y&&(character->getPos().Y)<(gatearray[i]->getPos().Y+gatearray[i]->getH()))
					{
						out=true;
						result=false;
						break;
					}
				}
				if(result)
				{
					out=false;
					dpos.X--;
				}
			}
		}
	
		if(receiver.state==6&&!receiver.IsKeyDown(irr::KEY_KEY_J)&&!receiver.IsKeyDown(irr::KEY_KEY_K)&&!receiver.IsKeyDown(irr::KEY_KEY_L))
		{
			clic=false;
			npcarray.clear();
		}
		else if(receiver.state==6)
		{
			dpos.X=-dpos.X;
			if(receiver.IsKeyDown(irr::KEY_KEY_J))
			{
				enemy-=1;
			}
			if(receiver.IsKeyDown(irr::KEY_KEY_K))
			{
				enemy-=2;
			}
			if(receiver.IsKeyDown(irr::KEY_KEY_L))
			{
				enemy-=5;
			}
		}
		if(receiver.change)
		{
			this->Reset();
			this->setScene(receiver.state);
			out=false;
			receiver.change=false;
		}
	return true;
}