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
#include <errno.h>

#include <QDebug>

#include "entity.h"
#include "pad.h"
#include "link.h"
#include "subdevice.h"
#include "subdevicepool.h"

Entity::Entity(int id)
{
	m_id = id;
	m_type = Subdev;
	m_name = QString("Fake.entity.%1.long.name").arg(id);
	m_subtype = Unknown;
	m_subDev = 0;
}

Entity::Entity(media_entity_desc& e)
{
	m_id = e.id;
	//m_type = e.type == MEDIA_ENTITY_TYPE_NODE ? Node : Subdev;
	m_padCount = e.pads;
	m_linkCount = e.links;
	m_name = QString(e.name);

	m_subtype = Unknown;
	
/*	if (m_type == Node)
	{
		switch (e.subtype)
		{
		case MEDIA_NODE_TYPE_V4L:
			m_subtype = V4l;
			break;
		case MEDIA_NODE_TYPE_FB:
			m_subtype = FB;
			break;
		case MEDIA_NODE_TYPE_ALSA:
			m_subtype = Alsa;
			break;
		case MEDIA_NODE_TYPE_DVB:
			m_subtype = DVB;
			break;
		default:
			m_subtype = Unknown;
		}
	}
	else
	{
		switch (e.subtype)
		{
		case MEDIA_SUBDEV_TYPE_VID_DECODER:
			m_subtype = Decoder;
			break;
		case MEDIA_SUBDEV_TYPE_VID_ENCODER:
			m_subtype = Encoder;
			break;
		case MEDIA_SUBDEV_TYPE_MISC:
			m_subtype = Misc;
			break;
		default:
			m_subtype = Unknown;
		}
	}
*/
	if (m_subtype == V4l || m_type == Subdev)
		m_subDev = SubDevicePool::self()->subDevice((unsigned int)e.v4l.major, (unsigned int)e.v4l.minor);
	/*else if (m_subtype == FB)
	{
		qDebug() << "Getting subdev" << (unsigned int)e.fb.major << (unsigned int)e.fb.minor;
		m_subDev = SubDevicePool::self()->subDevice((unsigned int)e.fb.major, (unsigned int)e.fb.minor);
	}*/
	else
		m_subDev = 0;
}

Entity::~Entity()
{

}

void Entity::setPads(QList<Pad*> pads)
{
	m_pads << pads;
	m_padCount = pads.count();
}

void Entity::setLinks(QList<Link*> links)
{
	m_links << links;
	m_linkCount = links.count();
}

void Entity::setPads(media_pad_desc *pads)
{
	for (unsigned int i = 0; i < m_padCount; i++)
	{
		m_pads << new Pad(pads[i]);
	}
}

void Entity::setLinks(media_link_desc *links)
{
	for (unsigned int i = 0; i < m_linkCount; i++)
	{
		Pad *src;
		foreach (Pad *p, m_pads)
		{
			if (links[i].source.index == p->index())
			{
				src = p;
				break;
			}
		}

		m_links << new Link(src, new Pad(links[i].sink));
	}
}

bool Entity::hasLink(Pad* source, Pad* sink)
{
	foreach(Link *link, m_links)
	{
		if (*(link->source()) == *source && *(link->sink()) == *sink)
			return true;
	}

	return false;
}

