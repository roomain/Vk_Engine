#pragma once

using FlagTest = unsigned int;

enum FlagTestBit
{
	First_bit = 1,
	Second_bit = 1 << 1,
	Third_bit = 1 << 2,
	Fourth_bit = 1 << 3
};