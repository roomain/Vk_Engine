#pragma once
/***********************************************
* @headerfile RHIFrameBuffer.h
* @date 18 / 04 / 2024
* @author Roomain
************************************************/

class RHIFrameBuffer
{
private:
	unsigned int m_width = 0;	/*!< frame buffer width*/
	unsigned int m_height = 0;	/*!< frame buffer height*/

public:
	[[nodiscard]] constexpr unsigned int width()const { return m_width; }
	[[nodiscard]] constexpr unsigned int height()const { return m_height; }
};
