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
private:
	u32 lasttime;
	int numTexture;
	int currentTexture;
	irr::IrrlichtDevice*	device;
	IVideoDriver* driver;
	core::position2d<s32> pos;
	core::array<video::ITexture*> imagesarray;
	core::array<core::position2d<s32>>  posarray;
	core::array<core::rect<s32>>  rctarray;
	core::array<int> timearray;
};