//Lua Loader Class implentation
//Author: Swdgame
//Date: 7/26/2010

#include "lua loader.h"

using	std::string;

CLuaLoader::CLuaLoader()
{

}


CLuaLoader::~CLuaLoader()
{
	for ( int i = 0;	i < m_vLuaStates.size(); i++ )
	{
		if ( m_vLuaStates[i] != NULL )
		{
			lua_close( m_vLuaStates[i] );
			m_vLuaStates[i] = NULL;
		}
	}
	m_vLuaStates.clear();
}


bool	CLuaLoader::Init()
{
	//
	m_vLuaStates.resize( LUA_LOADER_STACK_NUM );

	for ( int i = 0;	i < m_vLuaStates.size();	i++ )
	{
		m_vLuaStates[i] = NULL;
	}

	return true;
}

int	CLuaLoader::LoadFile( int code, const std::string& file_name )
{
	int	return_val = -1;

	return_val = ValidCode(code);

	if ( return_val >= 0 )
	{
		lua_State*	state = m_vLuaStates[return_val];
		if ( luaL_loadfile( state, file_name.c_str() ) || lua_pcall( state, 0, 0, 0 ) )
		{
			Erase( code );
			return_val = -1;
		}
	}

	return return_val;
}


bool	CLuaLoader::Erase( int code )
{
	if ( ( code >= 0 ) && ( code < m_vLuaStates.size() ) && ( m_vLuaStates[code] != NULL ) )
	{
		lua_close( m_vLuaStates[code] );
		m_vLuaStates[code] = NULL;
	}
	
	return true;
}


int	CLuaLoader::GetInt( int code, const string& val_name )
{
	int return_val = 0;
	
	lua_State* state = m_vLuaStates[code];
	lua_getglobal( state, val_name.c_str() );
	if ( lua_isnumber( state,	-1 ) )
	{
		return_val = lua_tonumber( state, -1 );
		lua_pop( state, -1 );
	}
	return return_val;
}

string	CLuaLoader::GetString( int code, const string& val_name )
{
	string return_val("");
	
	lua_State*	state = m_vLuaStates[code];
	lua_getglobal( state,	val_name.c_str() );
	if ( lua_isstring( state,	-1 ) )
	{
		return_val = lua_tostring( state, -1 );
		lua_pop( state,	-1 );
	}

	return return_val;
}

int	CLuaLoader::ValidCode( int code )
{
	int return_val = -1;

	if ( ( code >= 0 ) && ( code < m_vLuaStates.size() ) )
	{
		return_val = code;
		if ( m_vLuaStates[code] == NULL )
		{
			m_vLuaStates[code] = luaL_newstate();
			luaL_openlibs( m_vLuaStates[code] );
			if ( m_vLuaStates[code] == NULL )
			{
				return_val = -1;
			}
		}
	}
	else
	{
		for ( int i = 0;	i < m_vLuaStates.size(); i++ )
		{
			if ( m_vLuaStates[i] == NULL )
			{
				return_val = i;
				break;
			}
		}
		if ( return_val == -1 )
		{
			return_val = m_vLuaStates.size();
			m_vLuaStates.resize( 2 * m_vLuaStates.size() );
		}

		if ( m_vLuaStates[return_val] == NULL )
		{
			m_vLuaStates[return_val] = luaL_newstate();
			luaL_openlibs( m_vLuaStates[return_val] );
			if ( m_vLuaStates[return_val] == NULL )
			{
				return_val = -1;
			}
		}
	}

	return return_val;
}