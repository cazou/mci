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
#ifndef ENTITY_H
#define ENTITY_H

#include <linux/types.h>
#include <linux/media.h>

#include <QString>
#include <QList>

class SubDevice;
class Pad;
class Link;

class Entity
{
public:
	typedef enum EntityType {
		Node,
		Subdev
	} EntityType;

	typedef enum EntitySubtype {
		V4l,
		FB,
		Alsa,
		DVB,
		Decoder,
		Encoder,
		Misc,
		Unknown
	} EntitySubtype;

	Entity(int);
	Entity(media_entity_desc&);
	~Entity();

	void setPads(QList<Pad*>);
	void setPads(media_pad_desc*);
	void setLinks(QList<Link*>);
	void setLinks(media_link_desc*);

	unsigned int id() const {return m_id;}
	unsigned int padCount() const {return m_padCount;}
	unsigned int linkCount() const {return m_linkCount;}
	EntityType type() const {return m_type;}
	EntitySubtype subtype() const {return m_subtype;}
	QString name() const {return m_name;}
	QList<Pad*> pads() const {return m_pads;}
	QList<Link*> links() const {return m_links;}
	bool hasLink(Pad*, Pad*);

	SubDevice* subDevice() const {return m_subDev;}

private:
	unsigned int m_id;
	EntityType m_type;
	EntitySubtype m_subtype;
	unsigned int m_padCount;
	unsigned int m_linkCount;
	QString m_name;

	SubDevice *m_subDev;

	QList<Pad*> m_pads;
	QList<Link*> m_links;
};

#endif
