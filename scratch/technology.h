#pragma once
#include "TechnologyID.h"
#include "defValues.h"
#include <iostream>

class Technology 
{
//protected:
public:
	float progress = 0;
	float totalProgressNeeded = 100;
	bool researchStatus = false;
	TechnologyID id;
//public:
	TechnologyID getId()
	{
		return id;
	}
	void setId(TechnologyID id)
	{
		this->id = id;
	}
	bool isResearched() 
	{
		return researchStatus;
	}
	void addPoints(int points) 
	{
		if (progress >= totalProgressNeeded) 
		{
			researchStatus = true;
		}
		else
		{
			progress += points;
		}
	}
};


