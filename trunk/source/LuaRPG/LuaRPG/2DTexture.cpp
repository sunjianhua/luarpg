#include "2DTexture.h"

DTexture::DTexture()
{
	pos.X=0;pos.Y=0;
	rct=core::rect<s32>(0,0,0,0);
}
void DTexture::setPos(core::position2d<s32> p)
{
	this->pos=p;
}
void DTexture::setRect(core::rect <s32> r)
{
	this->rct=r;
}
void DTexture::setTexture(video::ITexture* i)
{
	this->images=i;
}
void DTexture::setDriver(irr::video::IVideoDriver *driver)
{
	this->driver=driver;
}

void DTexture::draw()
{
	driver->makeColorKeyTexture(images, core::position2d<s32>(0,0));
	driver->draw2DImage(images, pos,
				rct, 0,
				video::SColor(255,255,255,255), true);
}