#pragma once
/***********************************************
* @headerfile RHIDeserializer.h
* @date 27 / 03 / 2024
* @author Roomain
************************************************/
#include "RHI_globals.h"

/*@brief load Json file to fill serializable*/
class RHI_EXPORT RHIDeserializer
{
private:

public:
	RHIDeserializer() = default;
	virtual ~RHIDeserializer() = default;
	/*@brief load files in directory*/
	void loadFromDirectory(const char* a_directory);
	void loadFromFile(const char* a_file);
};

