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
