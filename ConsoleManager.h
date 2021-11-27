/*
	Winter 2021
	Automate your work assignment
	Written by SeungGeon Kim

	Filename : ConsoleManager.h
	Edited : 2021-11-27
*/

#pragma once

#define CONSOLE ConsoleManager::Instance()

#define P_POS ConsoleManager::Instance().PrintPosition

#define P_STRING ConsoleManager::Instance().PrintString
#define P_DOUBLE ConsoleManager::Instance().PrintDouble

#define C_DARKRED ConsoleManager::Color::DarkRed
#define C_GREEN ConsoleManager::Color::Green
#define C_BLUE ConsoleManager::Color::Blue
#define C_PROMPT ConsoleManager::Color::Prompt
#define C_PARAMETER ConsoleManager::Color::Parameter
#define C_ERROR ConsoleManager::Color::Error
#define C_SPECIAL ConsoleManager::Color::Special

#include "GlobalDefines.h"

#include <string>



class ConsoleManager
{

public:

	// Singleton pattern, placed deleted functions as public for better error messages
	static ConsoleManager& Instance() noexcept;
	ConsoleManager(const ConsoleManager&) = delete;
	void operator=(const ConsoleManager&) = delete;

	void SetupLocal();

	enum class Color
	{
		Green,
		Blue,
		Prompt,
		Parameter,
		Error,
		Special
	};

	void PrintPosition(int, int, Color = C_GREEN, bool = true);

	void PrintString(KR_STR, Color = C_GREEN, bool = true);
	void PrintString(std::string, Color = C_GREEN, bool = true);

	void PrintDouble(double, Color = C_GREEN, bool = true);
	void PrintDouble(int, Color = C_GREEN, bool = true);

private:

	// Making it private to prevent multiple copies of this appearing
	ConsoleManager() = default;

	template <class T>
	void PrintHelper(T&&, Color, bool);

	int ReturnColor(Color);

	void CheckTimer();

	int mClearTimer;

};