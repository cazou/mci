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
	
	virtual void resizeEvent(QResizeEvent *event);

	QSizeF sceneSize() const;

signals:
	void entityClicked(const Entity*);

protected:
	void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent);

private:
	MediaDevice *m_mediaDevice;

	void updatePositions();
	QList<GraphicsEntity*> graphicsEntityList;
	bool sortingDone;
	GraphicsEntity *highlighted;
};

#endif
