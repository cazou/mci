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
// Kernel includes
#include <linux/videodev2.h>

// System includes
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/sysmacros.h>

#include <QDebug>

#include "subdevice.h"
#include "v4l2control.h"

SubDevice::SubDevice()
{
	dev = -1;
	m_major = 0;
	m_minor = 0;
}

SubDevice::SubDevice(const QString& devName)
{
	dev = ::open(devName.toUtf8().constData(), O_RDWR);
	if (dev < 0)
		return;

	struct stat buf;
	if (fstat(dev, &buf) == -1)
	{
		qDebug() << "Unable to get stats for file" << devName << "(error" << errno << ").";
		m_major = 0;
		m_minor = 0;
	}
	else
	{
		m_major = ::major(buf.st_rdev);
		m_minor = ::minor(buf.st_rdev);
	}

	v4l2_queryctrl queryctrl;
	int ret;
	int ctrl_idx = 0;
	do
	{
		// Query Control
		memset(&queryctrl, 0, sizeof queryctrl);
		queryctrl.id = V4L2_CTRL_FLAG_NEXT_CTRL | ctrl_idx;
		ret = ioctl(dev, VIDIOC_QUERYCTRL, &queryctrl);
		if (ret != 0 && errno != 22)
		{
			qDebug() << "Error getting controls :" << errno;
			break;
		}
		else if (ret != 0)
			break;
		
		// Get Control value
		v4l2_control ctrl;
		memset(&ctrl, 0, sizeof ctrl);
		ctrl.id = queryctrl.id;

		ret = ioctl(dev, VIDIOC_G_CTRL, &ctrl);
		int val;
		if (ret < 0)
		{
			qDebug() << "Unable to get control value";
			val = 0;
		}
		else
			val = ctrl.value;

		V4l2Control *v4l2ctrl = new V4l2Control(queryctrl, val, this);

		if (queryctrl.type == V4L2_CTRL_TYPE_MENU)
		{
			// Get enum values
			v4l2_querymenu querymenu;
			memset(&querymenu, 0, sizeof querymenu);
			querymenu.id = queryctrl.id;
			int i = 0;
			do
			{
				querymenu.index = i++;
				int ret = ioctl(dev, VIDIOC_QUERYMENU, &querymenu);
				if (ret != 0 && errno != 22)
				{
					qDebug() << "Error getting control menu :" << errno;
					break;
				}
				else if (ret != 0)
					break;
				
				v4l2ctrl->addMenuItem(QString((char*)querymenu.name));
			} while (1);
		}

		m_controls << v4l2ctrl;
		ctrl_idx = queryctrl.id;
	} while (1);
}

SubDevice::~SubDevice()
{
	foreach(V4l2Control *ctrl, m_controls)
	{
		delete ctrl;
	}

	close(dev);
}

bool SubDevice::setControlValue(const V4l2Control *ctrl)
{
	v4l2_control control;
	memset(&control, 0, sizeof control);
	control.id = ctrl->id();
	control.value = ctrl->value();

	int ret = ioctl(dev, VIDIOC_S_CTRL, &control);
	if (ret < 0)
	{
		qDebug() << "Error setting control :" << errno;
		return false;
	}

	return true;
}
