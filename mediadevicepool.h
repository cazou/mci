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
#ifndef MEDIADEVICEPOOL_H
#define MEDIADEVICEPOOL_H

#include <QObject>
#include <QTimer>

class MediaDevice;

class MediaDevicePool : public QObject
{
	Q_OBJECT
public:
	MediaDevicePool();
	~MediaDevicePool();

	int count() const;

	QList<MediaDevice*> devices() const {return m_devices;}

private slots:
	void checkDevices();

signals:
	void newDevices();

private:
	QList<MediaDevice*> m_devices;
	QTimer timer;
};

#endif
