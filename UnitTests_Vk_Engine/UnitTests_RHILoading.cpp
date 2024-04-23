#include "pch.h"
#include "CppUnitTest.h"
#include "TestReflect.h"
#include "RHIManager.h"
#include "RHIType_traits.h"
#include "RHIReflectData.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestsVkEngine
{
	TEST_CLASS(UnitTests_RHILoading)
	{
	public:
		TEST_METHOD(Test_TypeTraits)
		{
			Assert::IsTrue(Is_reflective_v<SubTestReflect>, L"not reflective");
			Assert::IsTrue(Has_reflectName_v<SubTestReflect>, L"not name");

			Assert::IsTrue(!Is_reflective_v<int>, L"is reflective");
			Assert::IsTrue(!Has_reflectName_v<int>, L"is name");
		}
		TEST_METHOD(Test_load)
		{
			RHIManager::instance().loadConfiguration("..\\..\\test_resources");
			TestReflect reflectObject;
			Assert::AreEqual(23, reflectObject.getMemberI(), L"Wrong int value");
			Assert::AreEqual(4.56f, reflectObject.getMemberF(), L"Wrong float value");
			const std::vector<int>& test = reflectObject.memberV();
			Assert::AreEqual(size_t(4), test.size(), L"Wrong size");
			Assert::AreEqual(3, test[0], L"Wrong value[0]");
			Assert::AreEqual(5, test[1], L"Wrong value[1]");
			Assert::AreEqual(7, test[2], L"Wrong value[2]");
			Assert::AreEqual(9, test[3], L"Wrong value[3]");

			//const SubTestReflect& subTest = reflectObject.subMember();
			//Assert::AreEqual(21, subTest.getMemberI(), L"Wrong int value");
			//Assert::AreEqual(5.6f, subTest.getMemberF(), L"Wrong float value");

			SubTestReflect testReflect;
			Assert::AreEqual(0, testReflect.getMemberI(), L"Wrong int value");
			Assert::AreEqual(1.0f, testReflect.getMemberF(), L"Wrong float value");
		}

		TEST_METHOD(Test_loadStruct)
		{
			RHIManager::instance().loadConfiguration("..\\..\\test_resources");
			ReflectiveStruct reflectStruct;
			Assert::AreEqual(6, reflectStruct.m_memberI, L"Wrong int value");
			Assert::AreEqual(8.56f, reflectStruct.m_memberF, L"Wrong float value");
		}
	};
}
