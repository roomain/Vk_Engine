#include "pch.h"
#include "TestReflect.h"
#include "TestReflect.generated.h"

IMPLEMENT_REFLECT_CLASS(ReflectiveStruct)

IMPLEMENT_REFLECT_CLASS(SubTestReflect)

int SubTestReflect::getMemberI()const
{
	return m_memberI;
}

float SubTestReflect::getMemberF()const
{
	return m_memberF;
}

FlagTest SubTestReflect::getFlag()const
{
	return m_flag;
}

IMPLEMENT_REFLECT_CLASS(TestReflect)

int TestReflect::getMemberI()const
{
	return m_memberI;
}

float TestReflect::getMemberF()const
{
	return m_memberF;
}

const std::vector<int>& TestReflect::memberV()const
{
	return m_memberV;
}

const SubTestReflect& TestReflect::subMember()const
{
	return m_subMember;
}