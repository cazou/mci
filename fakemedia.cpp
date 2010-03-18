#include "fakemedia.h"
#include "fakeentity.h"
#include "pad.h"
#include "link.h"

#include <QList>

FakeMedia::FakeMedia()
 : MediaDevice("Fake Media Device")
{
	Entity *e1 = new FakeEntity(1);

	QList<Pad*> padList1;
	padList1 << new Pad(0, Pad::Out, 1);
	e1->setPads(padList1);
	
	
	Entity *e2 = new FakeEntity(2);

	QList<Pad*> padList2;
	padList2 << new Pad(0, Pad::In, 2) << new Pad(1, Pad::Out, 2);
	e2->setPads(padList2);

	
	Entity *e4 = new FakeEntity(4);

	QList<Pad*> padList4;
	padList4 << new Pad(0, Pad::In, 4);
	e4->setPads(padList4);


	Entity *e3 = new FakeEntity(3);

	QList<Pad*> padList3;
	padList3 << new Pad(0, Pad::In, 3) << new Pad(1, Pad::In, 3) << new Pad(2, Pad::In, 3)  << new Pad(3, Pad::In, 3)
		 << new Pad(4, Pad::In, 3) << new Pad(5, Pad::In, 3);
	e3->setPads(padList3);

	QList<Link*> linkList1;
	linkList1 << new Link(padList1[0], padList2[0]) << new Link(padList1[0], padList3[0]) << new Link(padList1[0], padList4[0]);
	e1->setLinks(linkList1);
	
	QList<Link*> linkList2;
	linkList2 << new Link(padList2[1], padList3[1]) << new Link(padList2[1], padList3[2]) << new Link(padList2[1], padList3[3]);
	e2->setLinks(linkList2);
	
	QList<Entity*> en;
	en << e1 << e2 << e3 << e4;
	setEntities(en);
}

FakeMedia::~FakeMedia()
{

}
