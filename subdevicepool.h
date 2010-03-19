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
#ifndef SUBDEVICEPOOL_H
#define SUBDEVICEPOOL_H

#include <QList>

class SubDevice;

class SubDevicePool
{
public:
	SubDevicePool();
	~SubDevicePool();

	SubDevice* subDevice(unsigned int, unsigned int);

	static SubDevicePool* self();
private:
	QList<SubDevice*> m_subdevList;
	void update();
};

#endif
