#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include "DL_StackWalker.h"
#define DL_ASSERT(__string__) DL_DEBUG::Debug::GetInstance()->AssertMessage(__FILE__,__LINE__,__FUNCTION__,__string__);
#define DL_PRINT(__string__)  DL_DEBUG::Debug::GetInstance()->PrintMessage(__string__);
#define DL_DEBUG( ... )  DL_DEBUG::Debug::GetInstance()->DebugMessage(__LINE__,__FILE__,__VA_ARGS__);

#define DL_CHAR_TO_WCHAR(__char__,__wchar__) {wchar_t * vOut = new wchar_t[strlen(__char__) + 1]; mbstowcs_s(NULL, vOut, strlen(__char__) + 1, __char__, strlen(__char__)); __wchar__ = vOut;}

namespace DL_DEBUG
{
	class Debug
	{
	public:
		static bool Create(std::string aFile = "DebugLogger.txt");
		static bool Destroy();
		static Debug* GetInstance();
		void AssertMessage(const char *aFileName, int aLine, const char *aFunctionName, const char *aString);
		void PrintMessage(const char *aString);
		void DebugMessage(const int aLine, const char *aFileName, const char *aFormattedString, ...);
	private:
		Debug();
		~Debug();
		bool OpenFile(std::string aFileName);
		bool CloseFile();
		std::wofstream myDebugFile;
		static Debug *ourInstance;
	};
}