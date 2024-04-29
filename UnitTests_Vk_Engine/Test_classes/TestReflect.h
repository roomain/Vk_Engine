#pragma once
#include "RHI_macros.h"
#include "TestReflectFlag.h"
#include "Test_From_string.h"
#include <vector>

REFLECT_CLASS(ReflectiveStruct)
struct ReflectiveStruct
{
	REFLECT_MEMBER
	int m_memberI;

	REFLECT_MEMBER
	float m_memberF;

private:
	DECLARE_REFLECT_CLASS(ReflectiveStruct)
};

REFLECT_CLASS(SubTestReflect)
class SubTestReflect
{
private:
	REFLECT_MEMBER
	int m_memberI; // member int

	REFLECT_FLAG(FlagTestBit)
	FlagTest m_flag = 0;

	REFLECT_MEMBER
	/*
	* little comment
	*/
	float m_memberF; /*member float*/

	DECLARE_REFLECT_CLASS(SubTestReflect)

public:
	int getMemberI()const;
	float getMemberF()const;
	FlagTest getFlag()const;
};

REFLECT_CLASS(TestReflect)
class TestReflect
{
private:
	REFLECT_MEMBER
	int m_memberI;

	REFLECT_MEMBER
	float m_memberF;

	REFLECT_MEMBER
	std::vector<int> m_memberV;

	REFLECT_MEMBER
	SubTestReflect m_subMember;

	DECLARE_REFLECT_CLASS(TestReflect)

public:
	int getMemberI()const;
	float getMemberF()const;
	const std::vector<int>& memberV()const;
	const SubTestReflect& subMember()const;
};
