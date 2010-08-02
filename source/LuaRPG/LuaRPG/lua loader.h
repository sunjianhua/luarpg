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
	virtual	double	GetDouble( int code, const std::string& val_name );
	virtual	std::string	GetString( int code, const std::string& val_name );

	virtual	bool	GetInt( int code, const std::string& val_name, int& target );
	virtual	bool	GetDouble( int code, const std::string& val_name, double& target );
	virtual	bool	GetString( int code, const std::string& val_name, std::string& target );

	//
	//virtual	int	GetIntFromFile( int* code,	const std::string& file_name, const std::string& val_name );
	//virtual	double	GetDoubleFromFile( int* code, std::string& file_name, const std::string& val_name );
	//virtual	std::string	GetStringFromFile( int* code, std::string& file_name, const std::string& val_name );

	virtual	bool	GetFieldBegin( int code, const std::string& table_name );
	virtual	bool	GetFieldEnd( int code );
	virtual	bool	GetFieldInt( int code, const std::string& val_name, int& target );
	virtual	bool	GetFieldInt( int code, const int& val_name, int& target );
	virtual	bool	GetFieldDouble( int code, const std::string& val_name, double& target );
	virtual	bool	GetFieldDouble( int code, const int& val_name, double& target );
	virtual	bool	GetFieldString( int code, const std::string& val_name, std::string& target );
	virtual	bool	GetFieldString( int code, const int& val_name, std::string& target );
	
	
	virtual	bool	GetArrayInt( int code, const std::string& table_name, int* arr, int index_start, int index_end );
	virtual	bool	GetArrayDouble( int code, const std::string& table_name, double* arr, int index_start, int index_end );
	virtual	bool	GetArrayString( int code, const std::string& table_name, std::string* arr, int index_start, int index_end );
protected:
	virtual	int	ValidCode( int code );

private:
	std::vector<lua_State*>		m_vLuaStates;
};


#endif


