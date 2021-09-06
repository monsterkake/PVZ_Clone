#pragma once
#include "technology.h"


class TechnologyTree
{
public:
	Technology technologies[TECHNOLOGY_TREE_LENGTH];
	TechnologyTree()
	{
		technologies[int(TechnologyID::Sticks)].setId(TechnologyID::Sticks);
		technologies[int(TechnologyID::Stones)].setId(TechnologyID::Stones);
		technologies[int(TechnologyID::SticksAndStones)].setId(TechnologyID::SticksAndStones);
		//std::cout << requirementsIsReached(TechnologyID::SticksAndStones) << std::endl;
	}
	bool requirementsIsReached(TechnologyID id)
	{
		switch (id)
		{
		case TechnologyID::Sticks:
			return true;
			break;
		case TechnologyID::Stones:
			return true;
			break;
		case TechnologyID::SticksAndStones:
			if (technologies[int(TechnologyID::Sticks)].isResearched() && technologies[int(TechnologyID::Stones)].isResearched())
				return true;
			else
				return false;
			break;
		case TechnologyID::none:
			break;
		default:
			break;
		}
		return false;
	}
};