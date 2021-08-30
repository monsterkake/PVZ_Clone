#pragma once
#include "patterns.h"

class Label : public Moveable 
{
public:
	std::string string;
	Label() 
	{
		string = "Label";
	}
	void setString(std::string string)
	{
		this->string = string;
	}
	std::string getString()
	{
		return string;
	}
};