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
#ifndef FAKEMEDIA_H
#define FAKEMEDIA_H
#include "mediadevice.h"

class FakeMedia : public MediaDevice
{
public:
	FakeMedia();
	~FakeMedia();

	QString devName() const;
};

#endif
