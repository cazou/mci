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
#ifndef V4L2CONTROL_H
#define V4L2CONTROL_H

#include <QString>
#include <QObject>

struct v4l2_queryctrl;
class SubDevice;

class V4l2Control : public QObject
{
	Q_OBJECT
public:
	typedef enum Type {
		Integer = 0,
		Boolean,
		Menu,
		Unknown
	} Type;

	V4l2Control(const v4l2_queryctrl&, int, SubDevice *parent = 0);
	~V4l2Control();

	QString name() const {return m_name;}
	int id() const {return m_id;}
	int value() const {return m_value;}

	bool setMax();
	bool setMin();
	bool setDefault();

	Type type() const {return m_type;}

	QWidget* changer();

	void addMenuItem(const QString&);

public slots:
	bool setValue(int);

private slots:
	void setBoolValue(int);

private:
	QString m_name;
	int m_id;
	int m_value;
	SubDevice *m_parent;
	int m_max;
	int m_min;
	int m_default;
	Type m_type;
	QWidget *m_changer;
	QList<QString> m_menuitems;
};

#endif
