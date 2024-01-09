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
#include "pad.h"

Pad::Pad(unsigned int index, PadType type, unsigned int entity)
{
	m_index = index;
	m_type = type;
	m_entity = entity;
}

Pad::Pad(const media_pad_desc& pad)
{
	m_index = pad.index;
	// FIXME: These are flags now, could be a sink AND source
	m_type = pad.flags & MEDIA_PAD_FL_SINK ? In : Out;
	m_entity = pad.entity;
}

Pad::~Pad()
{

}

Pad& Pad::operator=(const Pad& o)
{
	m_entity = o.m_entity;
	m_index = o.m_index;
	m_type = o.m_type;
	return *this;
}

bool Pad::operator==(const Pad& other)
{
	if (m_index == other.index() &&
	    m_type == other.type() &&
	    m_entity == other.entity())
	    	return true;
	
	return false;
}
