#ifndef SUBDEVICE_H
#define SUBDEVICE_H

#include <QList>

class V4l2Control;

class SubDevice
{
public:
	SubDevice();
	SubDevice(const QString&);
	~SubDevice();

	unsigned int minor() const {return m_minor;}
	unsigned int major() const {return m_major;}

	QList<V4l2Control*> controls() const {return m_controls;}

	bool setControlValue(const V4l2Control*);

private:
	int dev;
	QList<V4l2Control*> m_controls;
	unsigned int m_minor;
	unsigned int m_major;
};

#endif //SUBDEVICE_H
