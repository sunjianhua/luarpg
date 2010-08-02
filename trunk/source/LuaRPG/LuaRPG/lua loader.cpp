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
		
	}
	lua_pop( state,	-1 );
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
		
	}
	lua_pop( state,	-1 );
	return return_val;
}


double	CLuaLoader::GetDouble( int code, const std::string& val_name )
{
	double return_val = 0.0f;

	lua_State*	state = m_vLuaStates[code];
	lua_getglobal( state,	val_name.c_str() );
	if ( lua_isnumber( state,	-1 ) )
	{
		return_val = lua_tonumber( state, -1 );
		
	}
	lua_pop( state,	-1 );
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


bool	CLuaLoader::GetInt( int code, const std::string& val_name, int& target )
{
	if ( ( code < 0 ) || ( code >= m_vLuaStates.size() ) )
		return false;
	lua_State* state = m_vLuaStates[code];
	if ( state == NULL )
	{
		return false;
	}
	lua_getglobal( state, val_name.c_str() );
	if ( lua_isnumber( state,	-1 ) )
	{
		target = lua_tonumber( state, -1 );
		lua_pop( state, -1 );
		return true;
	}
	else
	{
		lua_pop( state, -1 );
		return false;
	}
}


bool	CLuaLoader::GetDouble( int code, const std::string& val_name, double& target )
{
	if ( ( code < 0 ) || ( code >= m_vLuaStates.size() ) )
		return false;
	lua_State* state = m_vLuaStates[code];
	if ( state == NULL )
	{
		return false;
	}
	lua_getglobal( state, val_name.c_str() );
	if ( lua_isnumber( state,	-1 ) )
	{
		target = lua_tonumber( state, -1 );
		lua_pop( state, -1 );
		return true;
	}
	else
	{
		lua_pop( state, -1 );
		return false;
	}
}


bool	CLuaLoader::GetString( int code, const std::string& val_name, std::string& target )
{
	if ( ( code < 0 ) || ( code >= m_vLuaStates.size() ) )
		return false;
	lua_State* state = m_vLuaStates[code];
	if ( state == NULL )
	{
		return false;
	}
	lua_getglobal( state, val_name.c_str() );
	if ( lua_isnumber( state,	-1 ) )
	{
		target = lua_tonumber( state, -1 );
		lua_pop( state, -1 );
		return true;
	}
	else
	{
		lua_pop( state, -1 );
		return false;
	}
}

bool	CLuaLoader::GetFieldBegin( int code, const std::string& table_name )
{
	if ( ( code < 0 ) || ( code >= m_vLuaStates.size() ) )
	{
		return false;
	}
	lua_State* state = m_vLuaStates[code];
	if ( state == NULL )
		return false;
	lua_getglobal( state, table_name.c_str() );
	if ( !lua_istable( state, -1 ) )
		return false;
	
	return true;
}


bool	CLuaLoader::GetFieldEnd( int code )
{
	if ( ( code < 0 ) || ( code >= m_vLuaStates.size() ) )
		return false;
	lua_State* state = m_vLuaStates[code];
	if ( state == NULL )
		return false;
	lua_pop( state, -1 );
	return true;
}


bool	CLuaLoader::GetFieldInt( int code, const std::string& val_name, int& target )
{
	if ( ( code < 0 ) || ( code >= m_vLuaStates.size() ) )
		return false;
	lua_State* state = m_vLuaStates[code];
	if ( state == NULL )
		return false;
	if ( !lua_istable( state, -1 ) )
		return false;
	lua_pushstring( state, val_name.c_str() );
	lua_gettable( state, -2 );
	if ( lua_isnumber( state, -1 ) )
	{
		target = lua_tonumber( state, -1 );
		lua_pop( state, 1 );
		return true;
	}
	else
	{
		lua_pop( state, 1 );
		return false;
	}
}

bool	CLuaLoader::GetFieldInt( int code, const int& val_name, int& target )
{
	if ( ( code < 0 ) || ( code >= m_vLuaStates.size() ) )
		return false;
	lua_State* state = m_vLuaStates[code];
	if ( state == NULL )
		return false;
	if ( !lua_istable( state, -1 ) )
		return false;
	lua_pushnumber( state, val_name );
	lua_gettable( state, -2 );
	if ( lua_isnumber( state, -1 ) )
	{
		target = lua_tonumber( state, -1 );
		lua_pop( state, 1 );
		return true;
	}
	else
	{
		lua_pop( state, 1 );
		return false;
	}
}

bool	CLuaLoader::GetFieldDouble( int code, const std::string& val_name, double& target )
{
	if ( ( code < 0 ) || ( code >= m_vLuaStates.size() ) )
		return false;
	lua_State* state = m_vLuaStates[code];
	if ( state == NULL )
		return false;
	if ( !lua_istable( state, -1 ) )
		return false;
	lua_pushstring( state, val_name.c_str() );
	lua_gettable( state, -2 );
	if ( lua_isnumber( state, -1 ) )
	{
		target = lua_tonumber( state, -1 );
		lua_pop( state, 1 );
		return true;
	}
	else
	{
		lua_pop( state, 1 );
		return false;
	}
}


bool	CLuaLoader::GetFieldDouble( int code, const int& val_name, double& target )
{
	if ( ( code < 0 ) || ( code >= m_vLuaStates.size() ) )
		return false;
	lua_State* state = m_vLuaStates[code];
	if ( state == NULL )
		return false;
	if ( !lua_istable( state, -1 ) )
		return false;
	lua_pushnumber( state, val_name );
	lua_gettable( state, -2 );
	if ( lua_isnumber( state, -1 ) )
	{
		target = lua_tonumber( state, -1 );
		lua_pop( state, 1 );
		return true;
	}
	else
	{
		lua_pop( state, 1 );
		return false;
	}
}




bool	CLuaLoader::GetFieldString( int code, const std::string& val_name, std::string& target )
{
	if ( ( code < 0 ) || ( code >= m_vLuaStates.size() ) )
		return false;
	lua_State* state = m_vLuaStates[code];
	if ( state == NULL )
		return false;
	if ( !lua_istable( state, -1 ) )
		return false;
	lua_pushstring( state, val_name.c_str() );
	lua_gettable( state, -2 );
	if ( lua_isstring( state, -1 ) )
	{
		target = lua_tostring( state, -1 );
		lua_pop( state, 1 );
		return true;
	}
	else
	{
		lua_pop( state, 1 );
		return false;
	}
}


bool	CLuaLoader::GetFieldString( int code, const int& val_name, std::string& target )
{
	if ( ( code < 0 ) || ( code >= m_vLuaStates.size() ) )
		return false;
	lua_State* state = m_vLuaStates[code];
	if ( state == NULL )
		return false;
	if ( !lua_istable( state, -1 ) )
		return false;
	lua_pushnumber( state, val_name );
	lua_gettable( state, -2 );
	if ( lua_isstring( state, -1 ) )
	{
		target = lua_tostring( state, -1 );
		lua_pop( state, 1 );
		return true;
	}
	else
	{
		lua_pop( state, 1 );
		return false;
	}
}


bool	CLuaLoader::GetArrayInt( int code, const std::string& table_name, int* arr, int index_start, int index_end )
{
	if ( ( code < 0 ) || ( code >= m_vLuaStates.size() ) )
		return false;
	lua_State* state = m_vLuaStates[code];
	if ( state == NULL )
		return false;
	lua_getglobal( state, table_name.c_str() );
	if ( !lua_istable( state, -1 ) )
	{
		lua_pop( state, -1 );
	}

	for ( int i = index_start; i <= index_end; i++ )
	{
		lua_pushnumber( state, i );
		lua_gettable( state, -2 );
		if ( lua_isnumber( state, -1 ) )
		{
			arr[ i - index_start ] = lua_tonumber( state, -1 );
			lua_pop( state, 1 );
		}
		else
		{
			lua_pop( state, 1 );
			lua_pop( state, 1 );
			return false;
		}
	}

	lua_pop( state, -1 );
	return true;
}

bool	CLuaLoader::GetArrayDouble( int code, const std::string& table_name, double* arr, int index_start, int index_end )
{
	if ( ( code < 0 ) || ( code >= m_vLuaStates.size() ) )
		return false;
	lua_State* state = m_vLuaStates[code];
	if ( state == NULL )
		return false;
	lua_getglobal( state, table_name.c_str() );
	if ( !lua_istable( state, -1 ) )
	{
		lua_pop( state, -1 );
	}

	for ( int i = index_start; i <= index_end; i++ )
	{
		lua_pushnumber( state, i );
		lua_gettable( state, -2 );
		if ( lua_isnumber( state, -1 ) )
		{
			arr[ i - index_start ] = lua_tonumber( state, -1 );
			lua_pop( state, 1 );
		}
		else
		{
			lua_pop( state, 1 );
			lua_pop( state, 1 );
			return false;
		}
	}

	lua_pop( state, -1 );
	return true;	
}


bool	CLuaLoader::GetArrayString( int code, const std::string& table_name, std::string* arr, int index_start, int index_end )
{
	if ( ( code < 0 ) || ( code >= m_vLuaStates.size() ) )
		return false;
	lua_State* state = m_vLuaStates[code];
	if ( state == NULL )
		return false;
	lua_getglobal( state, table_name.c_str() );
	if ( !lua_istable( state, -1 ) )
	{
		lua_pop( state, -1 );
	}

	for ( int i = index_start; i <= index_end; i++ )
	{
		lua_pushnumber( state, i );
		lua_gettable( state, -2 );
		if ( lua_isstring( state, -1 ) )
		{
			arr[ i - index_start ] = lua_tostring( state, -1 );
			lua_pop( state, 1 );
		}
		else
		{
			lua_pop( state, 1 );
			lua_pop( state, 1 );
			return false;
		}
	}

	lua_pop( state, -1 );
	return true;
}