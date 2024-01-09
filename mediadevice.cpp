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
#include <linux/types.h>
#include <linux/ioctl.h>
#include <linux/media.h>

// System includes
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>

// Qt includes
#include <QDebug>

// Project includes
#include "mediadevice.h"
#include "entity.h"

MediaDevice::MediaDevice(const QString& devName)
{
	m_devName = devName;
}

MediaDevice::~MediaDevice()
{
	foreach(Entity *e, m_entities)
	{
		delete e;
	}

	close();
}

void MediaDevice::close()
{
	::close(dev);
}

void MediaDevice::setEntities(QList<Entity*> en)
{
	m_entities << en;
}

int MediaDevice::open()
{
	dev = ::open(m_devName.toUtf8().constData(), O_RDWR);

	if (dev < 0)
		return EXIT_FAILURE;

	int i = 1;
	// Look for entities on the device
	do
	{
		int ret;
		media_entity_desc entity;
		memset(&entity, 0, sizeof entity);
		entity.id = i++;
		ret = ioctl(dev, MEDIA_IOC_ENUM_ENTITIES, &entity);

		if (ret < 0 && errno != 22)
		{
			qDebug() << "Error getting entities : " << errno;
			break;
		}
		else if (ret < 0)
		{
			break;
		}

		m_entities << new Entity(entity);
	} while (1);

	foreach(Entity *e, m_entities)
	{
		// Look for links (links are out links only)
		int ret;
		media_links_enum links;
		memset(&links, 0, sizeof links);
		links.entity = e->id();
		links.pads = new media_pad_desc[e->padCount()];
		links.links = new media_link_desc[e->linkCount()];
		ret = ioctl(dev, MEDIA_IOC_ENUM_LINKS, &links);
		if (ret < 0)
		{
			qDebug() << "Error getting links for entity" << e->id() << ":" << errno;
			continue;
		}

		e->setPads(links.pads);
		e->setLinks(links.links);
	}

	return EXIT_SUCCESS;
}

QString MediaDevicesetDevName();

void update()
{

}
