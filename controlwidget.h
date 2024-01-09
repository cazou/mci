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
#ifndef CONTROLWIDGET_H
#define CONTROLWIDGET_H

#include "ui_controlwidget.h"

class SubDevice;

class ControlWidget : public QWidget
{
public:
	ControlWidget(QWidget *parent = 0);
	~ControlWidget();

	void reset();
	void setSubDevice(const SubDevice*);
private:
	Ui::controlWidget ui;
	SubDevice *m_subdevice;
};

#endif
