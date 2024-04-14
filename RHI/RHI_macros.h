#pragma once
/***********************************************
* @headerfile RHI_macros.h
* @date 09 / 04 / 2024
* @author Roomain
************************************************/
#include "RHIManager.h"
#include "RHIType_traits.h"
#pragma message(__FILE__ "Don't forget REFLECT macro and include generated header") \
/*@brief macro to initialize class from Json data*/

/*@brief declares init static function of reflective class*/
#define INIT_REFLECT_CLASS_DECLARE(classname) \
friend Is_reflective<classname>; \
friend class RHIReflectData; \
private: \
static void init_reflect(classname& a_this); \
public: \
static std::string reflectName(); \


/*@brief implements init static function of reflective class*/
#define INIT_REFLECT_CLASS_IMPL(classname) \
void classname::init_reflect(classname& a_this) \
{ \
	if(auto pConfig = RHIManager::instance().configuration()) \
	{ \
		if (auto iterClass = pConfig->find(#classname); iterClass != pConfig->cend()) \
		{ \
			_INIT_##classname \
		} \
	} \
} \
\
std::string classname::reflectName() \
{ \
	return #classname; \
}

/*@brief declares ctor of reflective class*/
#define DECLARE_REFLECT_CTOR(classname) classname();

/*@brief implements ctor of reflective class*/
#define IMPLEMENT_REFLECT_CTOR(classname) \
classname::classname()\
{\
	classname::init_reflect(*this);\
}

/*@brief declare reflective class*/
#define DECLARE_REFLECT_CLASS(classname) \
INIT_REFLECT_CLASS_DECLARE(classname) \
public: \
DECLARE_REFLECT_CTOR(classname) \

/*@brief implements reflective class*/
#define IMPLEMENT_REFLECT_CLASS(classname) \
INIT_REFLECT_CLASS_IMPL(classname)\
\
IMPLEMENT_REFLECT_CTOR(classname)

/*@brief reflects macro used for code generation*/
#define REFLECT_CLASS(classname)
#define REFLECT_MEMBER