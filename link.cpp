#include "link.h"
#include "entity.h"

Link::Link(Pad *source, Pad *sink)
{
	m_source = source;
	m_sink = sink;
}

Link::~Link()
{

}
