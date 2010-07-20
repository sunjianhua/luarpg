//
//
//
#include <irrlicht.h>
#include	"game.h"

using namespace irr;

irr::IrrlichtDevice*	g_pIrr;
CGame*	g_pGame;


int	main()
{
	g_pIrr = createDevice( video::EDT_DIRECT3D9,	core::dimension2d<u32>(1024,768) );

	g_pGame = new CGame;
	g_pGame->Initialize();

	while ( g_pIrr->run() )
	{
		g_pGame->Update();
		g_pGame->Render();
	}

	return 0;
}