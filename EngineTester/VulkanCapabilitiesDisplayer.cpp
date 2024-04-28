#include "pch.h"
#include <iostream>
#include "VulkanCapabilitiesDisplayer.h"

void VulkanCapabilitiesDisplayer::setupSeparator()
{
	m_spacer = "";
	for (int i = 0; i < m_catCounter; ++i)
		m_spacer += '\t';
}

void VulkanCapabilitiesDisplayer::pushCategory(const std::string& a_category)
{
	IRHICapabilitiesDisplayer::pushCategory(a_category);
	std::cout << m_spacer << a_category << "\n";
	m_catCounter++;
	setupSeparator();
}

void VulkanCapabilitiesDisplayer::popCategory()
{
	IRHICapabilitiesDisplayer::popCategory();
	m_catCounter--;
	setupSeparator();
}

void VulkanCapabilitiesDisplayer::setCapability(const std::string& a_property, const bool a_value)
{
	std::cout << std::boolalpha << m_spacer << a_property << ": " << a_value << std::endl;
}

void VulkanCapabilitiesDisplayer::setCapability(const std::string& a_property, const int a_value)
{
	std::cout << m_spacer << a_property << ": " << a_value << std::endl;
}

void VulkanCapabilitiesDisplayer::setCapability(const std::string& a_property, const unsigned int a_value)
{
	std::cout << m_spacer << a_property << ": " << a_value << std::endl;
}

void VulkanCapabilitiesDisplayer::setCapability(const std::string& a_property, const float a_value)
{
	std::cout << m_spacer << a_property << ": " << a_value << std::endl;
}

void VulkanCapabilitiesDisplayer::setCapability(const std::string& a_property, const double& a_value)
{
	std::cout << m_spacer << a_property << ": " << a_value << std::endl;
}

void VulkanCapabilitiesDisplayer::setCapability(const std::string& a_property, const size_t& a_value)
{
	std::cout << m_spacer << a_property << ": " << a_value << std::endl;
}

void VulkanCapabilitiesDisplayer::setCapability(const std::string& a_property, const std::string& a_value)
{
	std::cout << m_spacer << a_property << ": " << a_value << std::endl;
}

void VulkanCapabilitiesDisplayer::setCapability(const std::string& a_property, const int* a_value, const int a_size)
{
	std::cout << m_spacer << a_property << ": " << a_value << std::endl;
}

void VulkanCapabilitiesDisplayer::setCapability(const std::string& a_property, const unsigned int* a_value, const int a_size)
{
	for (int i = 0; i < a_size; ++i)
	{
		std::cout << m_spacer << a_property << "["<< i << "]: " << a_value[i] << std::endl;
	}	
}

void VulkanCapabilitiesDisplayer::setCapability(const std::string& a_property, const float* a_value, const int a_size)
{
	for (int i = 0; i < a_size; ++i)
	{
		std::cout << m_spacer << a_property << "[" << i << "]: " << a_value[i] << std::endl;
	}
}

void VulkanCapabilitiesDisplayer::setCapability(const std::string& a_property, const double* a_value, const int a_size)
{
	for (int i = 0; i < a_size; ++i)
	{
		std::cout << m_spacer << a_property << "[" << i << "]: " << a_value[i] << std::endl;
	}
}
