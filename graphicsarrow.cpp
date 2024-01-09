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
#include "graphicsarrow.h"
#include "graphicsentity.h"
#include "entity.h"

#include <QPainter>
#include <QGraphicsScene>
#include <QDebug>

GraphicsArrow::GraphicsArrow(qreal x1, qreal y1, qreal x2, qreal y2, QGraphicsItem * parent)
 : QGraphicsItem(parent)
{
	m_start = QPointF(x1, y1);
	m_dest = QPointF(x2, y2);

	m_line = QLineF(m_start, m_dest);
}

GraphicsArrow::~GraphicsArrow()
{

}

QRectF GraphicsArrow::boundingRect() const
{
	return QRectF(m_start, m_dest); // Can be done here, Don't do this for any line.
}

void GraphicsArrow::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
	if (scene() == 0) //May not be necessary, paint shain't be called if the item hasn't been added in a scene.
		return;

	foreach(QGraphicsItem *item, scene()->items())
	{
		GraphicsArrow *ga = dynamic_cast<GraphicsArrow*>(item);
		if (ga == 0 || ga == this)
			continue;
		
		if (m_line.angle() == ga->line().angle() && collidesWithItem(ga))
		{
			m_start.setY(m_start.y() + 4);
			m_dest.setY(m_dest.y() + 4);
			m_line = QLineF(m_start, m_dest);
		}
	}

	QPen pen = painter->pen();
	pen.setWidth(2);
	painter->setPen(pen);

	painter->drawLine(m_start, m_dest);
}

