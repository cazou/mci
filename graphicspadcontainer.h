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

#include <QGraphicsItem>
#include <QList>

#include "pad.h"

class GraphicsPadContainer : public QGraphicsItem
{
public:
	/**
	 * Creates an empty container
	 */
	GraphicsPadContainer(QGraphicsItem *parent = 0);

	/**
	 * Creates a container with the Pad list, a position, a size and a direction.
	 */
	GraphicsPadContainer(const QList<Pad*>&, const QPointF& pos, const QSizeF& s, const Pad::PadType, QGraphicsItem *parent = 0);

	~GraphicsPadContainer();

	/**
	 * Sets the pads for this container.
	 * Only the pads that have the right direction will be drawn.
	 */
	void setPads(const QList<Pad*>&);

	/**
	 * Return the Pad at the given position (x, y).
	 * The position is relative to the Pad container itself.
	 */
	Pad* padAt(qreal x, qreal y);

	/**
	 * Return the Pad at the given position (x, y).
	 * The position is relative to the scene, not the entity or
	 * the Pad container itself.
	 */
	Pad* padAtAbsolute(qreal x, qreal y);

	QPointF padPosition(const Pad* p);
	
	void setDirection(const Pad::PadType);
	Pad::PadType direction() const {return m_dir;}
	
	virtual QRectF boundingRect() const;
	virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = 0);

private:
	QList<Pad*> m_pads;
	Pad::PadType m_dir;
	QSizeF m_size;
};
