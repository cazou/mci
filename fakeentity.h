/*
 *      Media Controller Inspector
 *
 *      Copyright 2010 - 2024
 *          Detlev Casanova <dc@detlev.ca>
 *
 *      This program is free software; you can redistribute it and/or modify
 *      it under the terms of the GNU General Public License version 3 as
 *      published by the Free Software Foundation.
 *
 */
#ifndef FAKEENTITY_H
#define FAKEENTITY_H

#include "entity.h"

class FakeEntity : public Entity
{
public:
	FakeEntity(int id);
	~FakeEntity();
};

#endif
