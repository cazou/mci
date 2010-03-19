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
#ifndef PAD_H
#define PAD_H

#define __user
#include <linux/types.h>
#include <linux/media.h>

class Pad
{
public:
	typedef enum PadType {
		In,
		Out
	} PadType;

	Pad(unsigned int index, PadType type, unsigned int entity);
	Pad(const media_user_pad&);
	~Pad();
	unsigned int entity() const {return m_entity;}
	unsigned int index() const {return m_index;}
	PadType type() const {return m_type;}
	
	Pad& operator=(const Pad& o);
	bool operator==(const Pad&);

private:
	unsigned int m_index;
	unsigned int m_entity;
	PadType m_type;
};

#endif
