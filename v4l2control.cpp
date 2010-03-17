#include "v4l2control.h"

#include "subdevice.h"

#include <QSpinBox>
#include <QSlider>
#include <QCheckBox>
#include <QLineEdit>
#include <QComboBox>

// Kernel includes
#define __user
#include <linux/videodev.h>

V4l2Control::V4l2Control(const v4l2_queryctrl& ctrl, int value, SubDevice *parent)
{
	m_parent = parent;
	m_name = QString((char*)ctrl.name);
	m_id = ctrl.id;
	m_value = value;
	m_max = ctrl.maximum;
	m_min = ctrl.minimum;
	m_default = ctrl.default_value;
	m_changer = 0;
	
	switch(ctrl.type)
	{
	case V4L2_CTRL_TYPE_INTEGER:
		m_type = Integer;
		break;
	case V4L2_CTRL_TYPE_BOOLEAN:
		m_type = Boolean;
		break;
	case V4L2_CTRL_TYPE_MENU:
		m_type = Menu;
		break;
	default:
		m_type = Unknown;
	}
}

V4l2Control::~V4l2Control()
{
	delete m_changer;
}

bool V4l2Control::setMax()
{
	return setValue(m_max);
}

bool V4l2Control::setMin()
{
	return setValue(m_min);
}

bool V4l2Control::setDefault()
{
	return setValue(m_default);
}

void V4l2Control::addMenuItem(const QString& name)
{
	m_menuitems << name;
}

bool V4l2Control::setValue(int v)
{
	if (v == m_value)
		return true;

	if (m_parent)
	{
		int oldVal = m_value;
		m_value = v;
		if (m_parent->setControlValue(this))
			return true;
		else
		{
			m_value = oldVal;
			return false;
		}
	}

	return false;
}

void V4l2Control::setBoolValue(int v)
{
	if (v == Qt::Checked)
		setValue(1);
	else
		setValue(0);
}

QWidget* V4l2Control::changer()
{
	if (m_changer)
		return m_changer;

	switch (m_type)
	{
	case Integer:
		{
			QSlider *ret = new QSlider();
			ret->setOrientation(Qt::Horizontal);
			ret->setTracking(false);
			ret->setMinimum(m_min);
			ret->setMaximum(m_max);
			ret->setValue(m_value);
			m_changer = ret;
			connect(m_changer, SIGNAL(valueChanged(int)), SLOT(setValue(int)));
			break;
		}
	case Boolean:
		{
			QCheckBox *ret = new QCheckBox();
			ret->setChecked(m_value == 1 ? true : false);
			m_changer = ret;
			connect(m_changer, SIGNAL(stateChanged(int)), SLOT(setBoolValue(int)));
			break;
		}
	case Menu:
		{
			QComboBox *ret = new QComboBox();
			ret->addItems(m_menuitems);
			ret->setCurrentIndex(m_value);
			m_changer = ret;
			connect(m_changer, SIGNAL(currentIndexChanged(int)), SLOT(setValue(int)));
			break;
		}
	case Unknown:
		m_changer = new QLineEdit("(Unknown)");
		break;
	}

	return m_changer;
}
