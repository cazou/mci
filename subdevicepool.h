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
