#ifndef LINK_H
#define LINK_H

class Pad;

class Link
{
public:
	Link(Pad *source, Pad *sink);
	~Link();

	Pad* sink() const {return m_sink;}
	Pad* source() const {return m_source;}

private:
	Pad *m_sink;
	Pad *m_source;
};

#endif
