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
	setPads(pads);
	setPos(pos);
}

void GraphicsPadContainer::setPads(const QList<Pad*>& pads)
{
	// Take pads which are in the right direction.
	foreach (Pad *p, pads)
	{
		if (p->type() == m_dir)
			m_pads << p;
	}
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
	if (m_pads.count() != 0)
		return QRectF(pos(), m_size);
	else
		return QRectF(pos(), QSizeF(0, 0));
}

void GraphicsPadContainer::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
	if (m_pads.count() == 0)
		return;

	if (m_dir == Pad::In)
	{
		//painter->drawLine(QPointF(m_size.width(), pos().y() + 2),
		//		  QPointF(m_size.width(), pos().y() + m_size.height() - 2));
		painter->drawLine(QPointF(m_size.width(), 2),
				  QPointF(m_size.width(), m_size.height() - 2));
	}
	else
	{
		painter->drawLine(QPointF(0, 2),
				  QPointF(0, m_size.height() - 2));
	}
}
