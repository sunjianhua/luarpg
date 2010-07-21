#include "2DTexture.h"

DTexture::DTexture()
{
	pos.X=0;pos.Y=0;
	currentTexture=0;
	numTexture=0;
}

void DTexture::insert(video::ITexture* images,core::position2d<s32> pos,core::rect<s32> rct,float time)
{
	imagesarray.push_back(images);
	posarray.push_back(pos);
	rctarray.push_back(rct);
	timearray.push_back(time);
	numTexture++;
}
void DTexture::setPos(core::position2d<s32> p)
{
	this->pos=p;
}
void DTexture::setDriver(irr::video::IVideoDriver *driver)
{
	this->driver=driver;
}
void DTexture::setDevice(irr::IrrlichtDevice*	device)
{
	this->device=device;
}
void DTexture::draw()
{
	/*core::rect<s32> imp1(349,15,385,78);
	core::rect<s32> imp2(387,15,423,78);
	u32 time =device->getTimer()->getTime();*/

	if(numTexture>0)
	{
		driver->makeColorKeyTexture(imagesarray[currentTexture], core::position2d<s32>(0,0));
		driver->draw2DImage(imagesarray[currentTexture], pos+posarray[currentTexture],
				rctarray[currentTexture], 0,
				video::SColor(255,255,255,255), true);
	}
	/*driver->makeColorKeyTexture(images, core::position2d<s32>(0,0));
	driver->draw2DImage(images, pos,
				rct, 0,
				video::SColor(255,255,255,255), true);

	driver->draw2DImage(images, core::position2d<s32>(164,125),
				(time/500 % 2) ? rctarray[0] : rctarray[1], 0,
				video::SColor(255,255,255,255), true);*/
}