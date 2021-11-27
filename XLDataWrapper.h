/*
    Winter 2021
    Automate your work assignment
    Written by SeungGeon Kim

	Filename : XLDataWrapper.h
	Edited : 2021-11-27
*/

#pragma once

#define XL_DW XLDataWrapper::Instance()

#include "GlobalDefines.h"



class XLDataWrapper
{

public:

	// Singleton pattern, placed deleted functions as public for better error messages
	static XLDataWrapper& Instance() noexcept;
	XLDataWrapper(const XLDataWrapper&) = delete;
	void operator=(const XLDataWrapper&) = delete;

	// Prints a brief description of the file corresponding to the given filename
	void ScanXLSX(KR_STR);

private:

	// Making it private to prevent multiple copies of this appearing
	XLDataWrapper() = default;

	template <class T>
	T CreateXLSXBook();

};