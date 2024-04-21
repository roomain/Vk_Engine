#pragma once
/***********************************************
* @headerfile IRHICapabilitiesDisplayer.h
* @date 20 / 04 / 2024
* @author Roomain
************************************************/
#include <string>
#include <stack>

/*@brief capability displayer interface*/
class IRHICapabilitiesDisplayer
{
private:
	std::stack<std::string> m_currentCategoryStack;	/*!< current capability category*/

public:
	virtual void pushCategory(const std::string& a_category) { m_currentCategoryStack.push(a_category); }
	virtual void popCategory() { m_currentCategoryStack.pop(); }
	[[nodiscard]] std::string currentCategory()const noexcept { return m_currentCategoryStack.top(); }

	virtual void setCapability(const std::string& a_property, const bool a_value) = 0;
	virtual void setCapability(const std::string& a_property, const int a_value) = 0;
	virtual void setCapability(const std::string& a_property, const unsigned int a_value) = 0;
	virtual void setCapability(const std::string& a_property, const float a_value) = 0;
	virtual void setCapability(const std::string& a_property, const double& a_value) = 0;
	virtual void setCapability(const std::string& a_property, const size_t& a_value) = 0;
	virtual void setCapability(const std::string& a_property, const std::string& a_value) = 0;

	virtual void setCapability(const std::string& a_property, const int* a_value, const int a_size) = 0;
	virtual void setCapability(const std::string& a_property, const unsigned int* a_value, const int a_size) = 0;
	virtual void setCapability(const std::string& a_property, const float* a_value, const int a_size) = 0;
	virtual void setCapability(const std::string& a_property, const double* a_value, const int a_size) = 0;

};