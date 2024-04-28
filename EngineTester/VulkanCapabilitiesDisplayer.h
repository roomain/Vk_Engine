#pragma once
/***********************************************
* @headerfile VulkanCapabilitiesDisplayer.h
* @date 27 / 04 / 2024
* @author Roomain
************************************************/
#include "IRHICapabilitiesDisplayer.h"

class VulkanCapabilitiesDisplayer : public IRHICapabilitiesDisplayer
{
private:
	std::string m_spacer;
	int m_catCounter = 0;

	void setupSeparator();

public:
	void pushCategory(const std::string& a_category) override;
	void popCategory() override;
	void setCapability(const std::string& a_property, const bool a_value) override;
	void setCapability(const std::string& a_property, const int a_value) override;
	void setCapability(const std::string& a_property, const unsigned int a_value) override;
	void setCapability(const std::string& a_property, const float a_value) override;
	void setCapability(const std::string& a_property, const double& a_value) override;
	void setCapability(const std::string& a_property, const size_t& a_value) override;
	void setCapability(const std::string& a_property, const std::string& a_value) override;

	void setCapability(const std::string& a_property, const int* a_value, const int a_size) override;
	void setCapability(const std::string& a_property, const unsigned int* a_value, const int a_size) override;
	void setCapability(const std::string& a_property, const float* a_value, const int a_size) override;
	void setCapability(const std::string& a_property, const double* a_value, const int a_size) override;
};

