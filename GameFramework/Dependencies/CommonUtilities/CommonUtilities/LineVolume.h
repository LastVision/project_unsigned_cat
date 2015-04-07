#pragma once
#include "Line.h"
#include "Vector.h"
#include "GrowingArray.h"

namespace CommonUtilities
{
	template <typename Type>
	class LineVolume
	{
	public:
		LineVolume();
		LineVolume(GrowingArray<Line<Type>> aLineList);
		~LineVolume();
		void AddLine(Line<Type> aLine);
		void RemoveLine(Line<Type> aLine);
		bool Inside(Vector2<Type> aPosition);
	private:
		GrowingArray<Line<Type>> myLineList;
	};
	template <typename Type>
	LineVolume<Type>::LineVolume()
	{
		myLineList.Init(1);
	}
	template <typename Type>
	LineVolume<Type>::LineVolume(GrowingArray<Line<Type>> aLineList)
	{
		myLineList = aLineList;
	}
	template <typename Type>
	LineVolume<Type>::~LineVolume()
	{

	}
	template <typename Type>
	void LineVolume<Type>::AddLine(Line<Type> aLine)
	{
		myLineList.Add(aLine);
	}
	template <typename Type>
	void LineVolume<Type>::RemoveLine(Line<Type> aLine)
	{
		myLineList.RemoveCyclic(aLine);
	}
	template <typename Type>
	bool LineVolume<Type>::Inside(Vector2<Type> aPosition)
	{
		for (unsigned short i = 0; i < myLineList.Size(); ++i)
		{
			if (myLineList[i].Inside(aPosition) == false)
			{
				return false;
			}
		}
		return true;
	}
}
namespace CU = CommonUtilities;
template class CU::LineVolume < int > ;
template class CU::Line < int > ;