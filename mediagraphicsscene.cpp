#include <QDebug>
#include <QResizeEvent>
#include <QGraphicsSceneMouseEvent>

#include "mediagraphicsscene.h"
#include "graphicsarrow.h"
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
	/*foreach(GraphicsEntity *ge, graphicsEntityList)
	{
		delete ge;
	}*/

	foreach(QGraphicsItem *gi, items())
	{
		delete gi;
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
	
	GraphicsEntity *ge = dynamic_cast<GraphicsEntity*>(itemAt(mouseEvent->scenePos()));
	if (!ge)
	{
		highlighted = 0;
		emit entityClicked(0);
		return;
	}

	ge->setHighlighted(true);
	
	//FIXME:update all items there (especially pad containers)
	update(ge->boundingRect());
	highlighted = ge;

	Entity *e = ge->entity();
	emit entityClicked(e);
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
			
			addItem(new GraphicsArrow(startPoint.x(), startPoint.y(), endPoint.x(), endPoint.y()));
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

void MediaGraphicsScene::resizeEvent(QResizeEvent *event)
{
	// FIXME:Does not happen.
	qDebug() << "resizeEvent";
	updatePositions();
}

void MediaGraphicsScene::updatePositions()
{

}
