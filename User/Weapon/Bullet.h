#pragma once
#include "Object3d.h"

class Bullet
{
public:
	int tribe;
	int weapon;

	
	std::unique_ptr<Object3d> bulletObj_;
	std::unique_ptr<Model> bulletModel_;
public:



};

