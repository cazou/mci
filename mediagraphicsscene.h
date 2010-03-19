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
#ifndef MEDIAGRAPHICSSCENE_H
#define MEDIAGRAPHICSSCENE_H

#include <QGraphicsScene>

class MediaDevice;
class GraphicsEntity;
class GraphicsArrow;
class QResizeEvent;
class Entity;

class MediaGraphicsScene : public QGraphicsScene
{
	Q_OBJECT
public:
	MediaGraphicsScene(QObject *parent = 0);
	~MediaGraphicsScene();

	void setMediaDevice(MediaDevice*);
	
	QSizeF sceneSize() const;

protected:
	void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent);

signals:
	void entityClicked(const Entity*);

private:
	MediaDevice *m_mediaDevice;

	QList<GraphicsEntity*> graphicsEntityList;
	QList<GraphicsArrow*> graphicsArrowList;
	bool sortingDone;
	GraphicsEntity *highlighted;
};

#endif
