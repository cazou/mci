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

#include "controlwidget.h"
#include "subdevice.h"
#include "v4l2control.h"

ControlWidget::ControlWidget(QWidget *parent)
 : QWidget(parent)
{
	ui.setupUi(this);
}

ControlWidget::~ControlWidget()
{

}

void ControlWidget::reset()
{

}

void ControlWidget::setSubDevice(const SubDevice* sd)
{
	for(int i = 1; i < ui.verticalLayout->count() - 1; i++)
	{
		QLabel *l = dynamic_cast<QLabel*>(ui.verticalLayout->itemAt(i)->widget());
		if (!l)
		{
			ui.verticalLayout->itemAt(i)->widget()->hide();
			ui.verticalLayout->removeItem(ui.verticalLayout->itemAt(i));
			i--;
			continue;
		}

		delete l;
		i--;
	}

	if (!sd)
	{
		ui.controlLabel->setText("");
		return;
	}

	if (sd->controls().count() > 0)
		ui.controlLabel->setText("Controls :");
	else
		ui.controlLabel->setText("No control");
	
	foreach(V4l2Control *ctrl, sd->controls())
	{
		// Control Name
		QLabel *label = new QLabel(ctrl->name(), this);
		ui.verticalLayout->insertWidget(ui.verticalLayout->count() - 1, label);

		// Control Changer
		QWidget *changer = ctrl->changer();
		if (!changer)
			continue;
		
		ui.verticalLayout->insertWidget(ui.verticalLayout->count() - 1, changer);
		changer->show();

	}

}
