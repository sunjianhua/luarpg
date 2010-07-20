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
	void setRect(core::rect<s32> rct);
	void setTexture(video::ITexture* images);
	void setDriver(IVideoDriver* driver);
	void draw();
private:
	IVideoDriver* driver;
	video::ITexture* images;
	core::position2d<s32> pos;
	core::rect<s32> rct;

};