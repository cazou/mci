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
