#ifndef FAKEMEDIA_H
#define FAKEMEDIA_H
#include "mediadevice.h"

class FakeMedia : public MediaDevice
{
public:
	FakeMedia();
	~FakeMedia();

	QString devName() const;
};

#endif
