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
#ifndef MEDIADEVICE
#define MEDIADEVICE

#include <QList>
#include <QString>

class Entity;

class MediaDevice
{
public:
	MediaDevice(const QString&);
	~MediaDevice();

	void setEntities(QList<Entity*>);
	QList<Entity*> entities() const { return m_entities; }
	void update();
	QString devName() const {return m_devName;}

	int open();
	void close();
private:
	QList<Entity*> m_entities;
	int dev;
	QString m_devName;
};

#endif
