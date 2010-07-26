#include <irrlicht.h>
using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

class DTexture
{
public:
	DTexture();
	~DTexture();
	void setPos(core::position2d<s32> pos);
	void setDriver(IVideoDriver* driver);
	void setDevice(irr::IrrlichtDevice*	device);
	void insert(video::ITexture* images,core::position2d<s32> pos,core::rect<s32> rct,int time);
	void draw();
	void setState(int state);
	void setSize(int w,int h);
	void setAI(int i);
	core::position2d<s32> getPos();
	int getW();
	int getH();
	bool AIenable;
private:
	u32 lasttime;
	int state;//0,1,2,3;
	int numTexture;
	int character;
	int currentTexture;
	irr::IrrlichtDevice*	device;
	IVideoDriver* driver;
	core::position2d<s32> pos;
	core::array<video::ITexture*> imagesarray;
	core::array<core::position2d<s32>>  posarray;
	core::array<core::rect<s32>>  rctarray;
	core::array<int> timearray;
	int time;
	int h;
	int w;
};