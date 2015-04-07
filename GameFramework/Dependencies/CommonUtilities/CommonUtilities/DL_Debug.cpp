#include "DL_Debug.h"
#include "DL_Assert.h"

DL_DEBUG::Debug *DL_DEBUG::Debug::ourInstance = nullptr;

DL_DEBUG::Debug::Debug()
{

}

DL_DEBUG::Debug::~Debug()
{

}

bool DL_DEBUG::Debug::Create(std::string aFile)
{
	assert(ourInstance == nullptr && "Debugobject already created");
	ourInstance = new Debug();
	if (ourInstance->OpenFile(aFile) == false)
	{
		ourInstance->CloseFile();
		return false;
	}
	if (ourInstance == nullptr)
	{
		return false;
	}
	return true;
}

bool DL_DEBUG::Debug::Destroy()
{
	if (ourInstance->CloseFile() == false)
	{
		return false;
	}
	delete ourInstance;
	ourInstance = nullptr;
	return true;
}

DL_DEBUG::Debug* DL_DEBUG::Debug::GetInstance()
{
	return ourInstance;
}

void DL_DEBUG::Debug::AssertMessage(const char *aFileName, int aLine, const char *aFucntionName, const char *aString)
{
	myDebugFile << "Error at: " << aFucntionName << "\n" << "Line: " << aLine << "\n" << "File: " << aFileName << "\n" << "Message: " << aString << "\n";
	DL_Debug::StackWalker aStack;
	aStack.ShowCallstack();
	myDebugFile.flush();
	wchar_t *wassertString = 0;
	wchar_t *wassertFileName = 0;
	DL_CHAR_TO_WCHAR(aString, wassertString);
	DL_CHAR_TO_WCHAR(aFileName, wassertFileName);
	_wassert(wassertString, wassertFileName, aLine);
}

void DL_DEBUG::Debug::PrintMessage(const char *aString)
{
	myDebugFile << aString << "\n";
	myDebugFile.flush();
}

void DL_DEBUG::Debug::DebugMessage(const int aLine, const char *aFileName, const char *aFormattedString, ...)
{
	char buffer[1024];
	va_list args;
	va_start(args, aFormattedString);
	std::stringstream ss;
	ss.flush();
	ss << "Debug Info at line: " << aLine << "\n" << "File: " << aFileName << "\n" << "Message: ";
	ss << vsprintf_s(buffer, aFormattedString, args);
	//perror(buffer);
	va_end(args);

	myDebugFile << ss.str().c_str() << buffer;
	myDebugFile.flush();
}

bool DL_DEBUG::Debug::OpenFile(std::string aFileName)
{
	if (myDebugFile.is_open() == false)
	{
		myDebugFile.open(aFileName);
		return true;
	}
	return false;
}

bool DL_DEBUG::Debug::CloseFile()
{
	if (myDebugFile.is_open() == true)
	{
		myDebugFile.flush();
		myDebugFile.close();
		return true;
	}
	return false;
}