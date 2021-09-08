#pragma once
#include "TechnologyID.h"
#include "defValues.h"
#include <iostream>

class Technology 
{
public:
	float progress = 0;
	float totalProgressNeeded = 100;
	bool researchStatus = false;
	TechnologyID id;
	std::string description;
	Technology() 
	{
		description = "defaultDescription";
	}
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
		if(progress < totalProgressNeeded)
		{
			progress += points;
		}
		if (progress >= totalProgressNeeded)
		{
			progress = totalProgressNeeded;
			researchStatus = true;
		}
	}
	void setDescription(std::string description)
	{
		this->description = description;
	}
	std::string getDescription() 
	{
		return this->description;
	}
	float getProgressPercentage() 
	{
		return progress / totalProgressNeeded;
	}
};


