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
#include <QDebug>
#include <QResizeEvent>
#include <QGraphicsSceneMouseEvent>

#include "mediagraphicsscene.h"
#include "graphicsarrow.h"
#include "graphicspadcontainer.h"
#include "mediadevice.h"
#include "graphicsentity.h"
#include "entity.h"
#include "link.h"
#include "pad.h"

MediaGraphicsScene::MediaGraphicsScene(QObject *parent)
 : QGraphicsScene(parent)
{
	m_mediaDevice = 0;
	sortingDone = 0;
	highlighted = 0;
}

MediaGraphicsScene::~MediaGraphicsScene()
{
	// Delete entities
	foreach(GraphicsEntity *ge, graphicsEntityList)
	{
		delete ge;
	}

	//Delete arrows
	foreach(GraphicsArrow *ga, graphicsArrowList)
	{
		delete ga;
	}
}

bool conflict(GraphicsEntity *g1, GraphicsEntity *g2)
{
	if (g1->currentPosX() == g2->currentPosX() && g1->currentPosY() == g2->currentPosY())
		return true;
	return false;
}

void MediaGraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
	if (highlighted)
	{
		highlighted->setHighlighted(false);
		update(highlighted->boundingRect());
	}
	
	GraphicsEntity *ge;
	GraphicsPadContainer *gpc;
	if ((ge = dynamic_cast<GraphicsEntity*>(itemAt(mouseEvent->scenePos(), QTransform())))
		|| (gpc = dynamic_cast<GraphicsPadContainer*>(itemAt(mouseEvent->scenePos(), QTransform()))))
	{
		if (!ge && gpc)
			ge = dynamic_cast<GraphicsEntity*>(gpc->parentItem());
		if (!ge)
			return;

		ge->setHighlighted(true);
		
		update(ge->boundingRect());
		
		if (highlighted == ge)
			return;

		highlighted = ge;

		Entity *e = ge->entity();
		emit entityClicked(e);
		return;
	}

	GraphicsArrow *ga;
	if ((ga = dynamic_cast<GraphicsArrow*>(itemAt(mouseEvent->scenePos(), QTransform()))))
	{

	}

	highlighted = 0;
	emit entityClicked(0);
	return;
}

void MediaGraphicsScene::setMediaDevice(MediaDevice* dev)
{
	m_mediaDevice = dev;
	if (!dev)
		return;

	foreach (Entity *e, m_mediaDevice->entities())
	{
		GraphicsEntity *ge = new GraphicsEntity();
		graphicsEntityList << ge;
		ge->setEntity(e);
	}
	
	// Width positionning.
	bool changes;
	do
	{
		changes = false;
		foreach(GraphicsEntity *graphicRightEntity, graphicsEntityList)
		{
			Entity *rightEntity = graphicRightEntity->entity();
			foreach(GraphicsEntity *graphicLeftEntity, graphicsEntityList)
			{
				Entity *leftEntity = graphicLeftEntity->entity();

				if (rightEntity == leftEntity)
					continue;
				
				foreach(Pad *p, rightEntity->pads())
				{
					if (p->type() == Pad::Out)
						continue;
					
					foreach(Pad *cPad, leftEntity->pads())
					{
						if (cPad->type() == Pad::In)
							continue;

						if (leftEntity->hasLink(cPad, p))
						{
							int rightPos = graphicRightEntity->currentPosX();
							int leftPos = graphicLeftEntity->currentPosX();
	
							if (rightPos <= leftPos)
							{
								graphicRightEntity->setPos(leftPos + 1, 0);
								changes = true;
							}
						}
					}
				}
			}
		}
	} while (changes);

	// Height positioning.
	do
	{
		changes = false;
		foreach(GraphicsEntity *graphicEntity, graphicsEntityList)
		{
			foreach(GraphicsEntity *graphicSameLevelEntity, graphicsEntityList)
			{
				if (graphicSameLevelEntity == graphicEntity)
					continue;

				if (conflict(graphicEntity, graphicSameLevelEntity))
				{
					int x = graphicEntity->currentPosX();
					int y = graphicEntity->currentPosY();
					graphicSameLevelEntity->setPos(x, y + 1);
					changes = true;
				}
			}
		}
	} while (changes);

	// Actually drawing items.
	foreach (GraphicsEntity *ge, graphicsEntityList)
	{
		addItem(ge);
	}

	// Drawing links
	//FIXME:don't overlap on boxes !
	foreach(GraphicsEntity *ge, graphicsEntityList)
	{
		Entity *e = ge->entity();
		foreach(Link *l, e->links())
		{
			QPointF startPoint = ge->padPosition(l->source());
			QPointF endPoint = graphicsEntityList[l->sink()->entity() - 1]->padPosition(l->sink());
			
			QGraphicsItem *ga = new GraphicsArrow(startPoint.x(), startPoint.y(), endPoint.x(), endPoint.y());
			graphicsArrowList << dynamic_cast<GraphicsArrow*>(ga);
			addItem(ga);
		}
	}
}

QSizeF MediaGraphicsScene::sceneSize() const
{
	QRectF ret;

	foreach(QGraphicsItem *gi, items())
	{
		ret |= gi->boundingRect();
	}
	
	return ret.size();
}

