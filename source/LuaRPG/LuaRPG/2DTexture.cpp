#include "2DTexture.h"
DTexture::DTexture()
{
	pos.X=0;pos.Y=0;
	currentTexture=0;
	numTexture=0;
	u32 lasttime=-1;
	state=0;
	character=1;
}
void DTexture::setSize(int w,int h)
{
	this->w=w;
	this->h=h;
}
int DTexture::getW()
{
	return w;
}
int DTexture::getH()
{
	return h;
}
void DTexture::insert(video::ITexture* images,core::position2d<s32> pos,core::rect<s32> rct, int time)
{
	imagesarray.push_back(images);
	posarray.push_back(pos);
	rctarray.push_back(rct);
	timearray.push_back(time);
	numTexture++;
}
core::position2d<s32> DTexture::getPos()
{
	return pos+posarray[currentTexture+state*4];
}
void DTexture::setState(int state)
{
	this->state=state;
	character=4;
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
		driver->makeColorKeyTexture(imagesarray[currentTexture+state*4], core::position2d<s32>(0,0));
		driver->draw2DImage(imagesarray[currentTexture+state*4],pos+posarray[currentTexture+state*4],
				rctarray[currentTexture+state*4], 0,
				video::SColor(255,255,255,255), true);
	}
	if((device->getTimer()->getTime()-lasttime)/500>=timearray[currentTexture+state*4])
	{
		lasttime=device->getTimer()->getTime();
		currentTexture++;
		if(currentTexture>=numTexture&&character==1)
			currentTexture=0;
		else if(character==4&&currentTexture%character==0)
			currentTexture=0;
	}
}