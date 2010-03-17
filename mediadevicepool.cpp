// System includes
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

#include "mediadevicepool.h"
#include "mediadevice.h"
#include "fakemedia.h"

MediaDevicePool::MediaDevicePool()
{
	for(int i = 0; i < 15; i++)
	{
		MediaDevice *m = new MediaDevice(QString("/dev/media%1").arg(i));
		if (m->open() == 0)
		{
			m->close();
			m_devices << m;
		}
		else
			delete m;
	}
	
	FakeMedia *fmd = new FakeMedia();
	m_devices << fmd;

	connect(&timer, SIGNAL(timeout()), this, SLOT(checkDevices()));
	timer.setInterval(5000);
	timer.start();
}

MediaDevicePool::~MediaDevicePool()
{

}

int MediaDevicePool::count() const
{
	return m_devices.count();
}

bool fileExists(const QString& fileName)
{
	int fd = ::open(fileName.toUtf8().constData(), O_RDONLY);
	if (fd == -1 && errno == ENODEV)
		return false;
	
	close(fd);
	return true;
}

void MediaDevicePool::checkDevices()
{
	bool changes = false;
	for(int i = 0; i < 15; i++)
	{
		QString devName = QString("/dev/media%1").arg(i);
		
		// Check if we already have it.
		bool found = false;
		foreach(MediaDevice *md, m_devices)
		{
			if (md->devName() == devName)
			{
				found = true;
				break;
			}
		}
		if (found)
			continue;
		
		// Check if it exists
		MediaDevice *m = new MediaDevice(QString("/dev/media%1").arg(i));
		if (m->open() == 0)
		{
			m->close();
			changes = true;
			m_devices << m;
		}
		else
			delete m;
	}

	/*for(int i = 0; i < m_devices.count(); i++)
	{
		if (!fileExists(m_devices.at(i)->devName()))
			m_devices.removeAt(i--);
	}*/
	
	if (changes)
		emit newDevices();
}
