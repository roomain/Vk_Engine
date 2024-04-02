#pragma once

#ifdef RHI_LIB
#define RHI_EXPORT __declspec(dllexport)
#else
#define RHI_EXPORT __declspec(dllimport)
#endif
