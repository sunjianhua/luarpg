//
//
//


#ifndef	GAME_H
#define	GAME_H

#include <irrlicht.h>

//using	namespace	irr;

class	CGame
{
public:
	CGame();

	~CGame();

	//
	virtual	bool	Initialize();
	virtual	bool	Update();
	virtual	bool	Render();
protected:
private:
};

#endif