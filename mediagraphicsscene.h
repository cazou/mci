#ifndef MEDIAGRAPHICSSCENE_H
#define MEDIAGRAPHICSSCENE_H

#include <QGraphicsScene>

class MediaDevice;
class GraphicsEntity;
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
	bool sortingDone;
	GraphicsEntity *highlighted;
};

#endif
