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
