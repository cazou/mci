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
