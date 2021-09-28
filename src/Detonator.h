#pragma once
#ifndef __DETONATOR__
#define __DETONATOR__
#include "DisplayObject.h"

class Detonator final : public DisplayObject
{
public:
	// constructors
	Detonator();

	// destructor
	~Detonator();

	// life cycle functions
	void draw() override;
	void update() override;
	void clean() override;
private:

};

#endif /* defined (__Detonator__) */