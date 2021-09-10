#include "enemy.h"

class Scout : public Enemy
{
public:
	Scout() 
	{
		hp = 0.2 * hp;

	}
};


