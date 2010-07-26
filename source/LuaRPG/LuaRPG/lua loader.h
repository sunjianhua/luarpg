//
//
//
#ifndef LUA_LOADER_H 
#define LUA_LOADER_H

#define LUA_LOADER_STACK_NUM	300

#include <vector>
#include <string>
#include <lua.hpp>
#include <lauxlib.h>
#include <lualib.h>

//using	std::string;

class CLuaLoader
{
public:
	CLuaLoader();

	virtual	~CLuaLoader();

	virtual	bool	Init();		
	virtual	int	LoadFile( int code, const std::string& file_name );
	//virtual	int	CacheFile( int code, const std::string& file_name ); 
	//virtual	int	CacheRam( int code, const std::string& file_name );
	//virtual	int	StepCache( int code );

	//
	virtual	bool	Erase( int code );
	//virtual	bool	Clean();

	//
	virtual	int	GetInt( int code, const std::string& val_name );
	//virtual	double	GetDouble( int code, const std::string& val_name );
	virtual	std::string	GetString( int code, const std::string& val_name );

	//
	//virtual	int	GetIntFromFile( int* code,	const std::string& file_name, const std::string& val_name );
	//virtual	double	GetDoubleFromFile( int* code, std::string& file_name, const std::string& val_name );
	//virtual	std::string	GetStringFromFile( int* code, std::string& file_name, const std::string& val_name );


protected:
	virtual	int	ValidCode( int code );

private:
	std::vector<lua_State*>		m_vLuaStates;
};


#endif


