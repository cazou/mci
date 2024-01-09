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
#include <QFile>

#include "subdevicepool.h"
#include "subdevice.h"

static SubDevicePool *m_self = 0;

SubDevicePool::SubDevicePool()
{
	for (int i = 0; QFile::exists(QString("/dev/subdev%1").arg(i)); i++)
	{
		m_subdevList << new SubDevice(QString("/dev/subdev%1").arg(i));
	}
}

SubDevicePool::~SubDevicePool()
{
	foreach(SubDevice *sd, m_subdevList)
	{
		delete sd;
	}
}

SubDevice* SubDevicePool::subDevice(unsigned int major, unsigned int minor)
{
	foreach(SubDevice *sd, m_subdevList)
	{
		if (sd->major() == major && sd->minor() == minor)
			return sd;
	}

	return 0;
}

void SubDevicePool::update()
{
	for (int i = m_subdevList.count(); QFile::exists(QString("/dev/subdev%1").arg(i)); i++)
	{
		m_subdevList << new SubDevice(QString("/dev/subdev%1").arg(i));
	}
}

SubDevicePool* SubDevicePool::self()
{
	if (m_self == 0)
		m_self = new SubDevicePool();
	else
		m_self->update();

	return m_self;
}

