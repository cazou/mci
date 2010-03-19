/*
 *      Media Controller Inspector
 *
 *      Copyright (C) 2010
 *          Detlev Casanova (detlev.casanova@gmail.com)
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
