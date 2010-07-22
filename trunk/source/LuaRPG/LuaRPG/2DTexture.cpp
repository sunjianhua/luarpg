#include "2DTexture.h"
DTexture::DTexture()
{
	pos.X=0;pos.Y=0;
	currentTexture=0;
	numTexture=0;
	u32 lasttime=-1;
}

void DTexture::insert(video::ITexture* images,core::position2d<s32> pos,core::rect<s32> rct, int time)
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
	if(lasttime==-1)
		lasttime=device->getTimer()->getTime();

	if(numTexture>0)
	{
		driver->makeColorKeyTexture(imagesarray[currentTexture], core::position2d<s32>(0,0));
		driver->draw2DImage(imagesarray[currentTexture],pos+posarray[currentTexture],
				rctarray[currentTexture], 0,
				video::SColor(255,255,255,255), true);
	}
	if((device->getTimer()->getTime()-lasttime)/500>=timearray[currentTexture])
	{
		lasttime=device->getTimer()->getTime();
		currentTexture++;
		if(currentTexture>=numTexture)
			currentTexture=0;
	}
}