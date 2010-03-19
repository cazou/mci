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
#include <QPainter>
#include <QDebug>

#include "graphicspadcontainer.h"
#include "pad.h"

GraphicsPadContainer::GraphicsPadContainer(QGraphicsItem *parent)
 : QGraphicsItem(parent)
{
}

GraphicsPadContainer::GraphicsPadContainer(const QList<Pad*>& pads, const QPointF& pos, const QSizeF& s, const Pad::PadType dir, QGraphicsItem *parent)
 : QGraphicsItem(parent)
{
	m_size = s;
	m_dir = dir;
	setPos(pos);
	setPads(pads);
}

GraphicsPadContainer::~GraphicsPadContainer()
{

}

void GraphicsPadContainer::setPads(const QList<Pad*>& pads)
{
	// Take pads which are in the right direction.
	foreach (Pad *p, pads)
	{
		if (p->type() == m_dir)
			m_pads << p;
	}

	if (m_pads.count() == 0)
	{
		prepareGeometryChange();
		m_size = QSizeF(0, 0);
		setPos(QPointF(0, 0));
	}
}

QPointF GraphicsPadContainer::padPosition(const Pad* p)
{
	if (p->type() != m_dir)
		return QPointF(-1, -1);

	qreal yPos = m_size.height() / (m_pads.count() * 2);
	foreach (Pad* pad, m_pads)
	{
		if (pad->index() != p->index())
		{
			yPos += m_size.height() / (m_pads.count());
		}
		else
			break;
	}

	return QPointF(m_dir == Pad::In ? 0 : m_size.width(), yPos);
}

Pad* GraphicsPadContainer::padAt(qreal x, qreal y)
{
	return 0;
}

Pad* GraphicsPadContainer::padAtAbsolute(qreal x, qreal y)
{
	return 0;
}

void GraphicsPadContainer::setDirection(const Pad::PadType)
{
}

QRectF GraphicsPadContainer::boundingRect() const
{
	return QRectF(mapFromItem(parentItem(), pos()), m_size);
}

void GraphicsPadContainer::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
	//FIXME:it's too much computing for paint()
	if (m_pads.count() == 0)
		return;

	if (m_dir == Pad::In)
	{
		painter->drawLine(QPointF(m_size.width(), 2),
				  QPointF(m_size.width(), m_size.height() - 2));
		int i = 0;
		qreal posX = 0;
		qreal posY;
		int in = m_pads.count();
		foreach(Pad *p, m_pads)
		{
			posY = (++i * m_size.height()/(2 * in)) - m_size.width()/2;
			
			if (i != 1)
			{
				painter->drawLine(QPointF(2, (qreal)(i-1)/(2*in) * m_size.height()),
						  QPointF(m_size.width(), (qreal)(i-1)/(2*in) * m_size.height()));
			}

			i += 1;

			QRectF padRect(posX, posY, m_size.width(), m_size.width());
			painter->drawText(padRect, Qt::AlignCenter | Qt::TextWordWrap, QString("%1").arg(p->index()));
		}
	}
	else
	{
		painter->drawLine(QPointF(0, 2),
				  QPointF(0, m_size.height() - 2));
		int i = 0;
		qreal posX = 0;
		qreal posY;
		int out = m_pads.count();
		foreach(Pad *p, m_pads)
		{
			posY = (++i * m_size.height()/(2 * out)) - m_size.width()/2;
			
			if (i != 1)
			{
				painter->drawLine(QPointF(2, (qreal)(i-1)/(2 * out) * m_size.height()),
						  QPointF(m_size.width(), (qreal)(i-1)/(2*out) * m_size.height()));
			}

			i += 1;

			QRectF padRect(posX, posY, m_size.width(), m_size.width());
			painter->drawText(padRect, Qt::AlignCenter | Qt::TextWordWrap, QString("%1").arg(p->index()));
		}
	}
}
