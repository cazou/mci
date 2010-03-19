/*
 *      Media Controller Inspector
 *
 *      Copyright (C) 2010
 *          Detlev Casanova (detlev.casanova@gmail.com)
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

Pad::Pad(const media_user_pad& pad)
{
	m_index = pad.index;
	m_type = pad.type == MEDIA_PAD_TYPE_INPUT ? In : Out;
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
