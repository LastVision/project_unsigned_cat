#pragma once
#include <fstream>
#include <map>
#include <vector>
#include "Model.h"

namespace CommonUtilities
{
	namespace LoadModel
	{
		std::string GetWord(const char* aStr, int& aStartIndex);
		void LoadModel(const char* aFile, Model& aModel);
	}
} namespace CU = CommonUtilities;