#include <QGraphicsItem>

class Entity;
class Pad;
class GraphicsPadContainer;

class GraphicsEntity : public QGraphicsItem
{
public:
	GraphicsEntity(QGraphicsItem* parent = 0);
	~GraphicsEntity();

	void setEntity(Entity*);
	void setSize(qreal);
	void setPos(int, int);

	Entity* entity() const {return m_entity;}

	virtual QRectF boundingRect() const;
	virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = 0);
	int currentPosX();
	int currentPosY();
	QPointF padPosition(Pad*);

	void setHighlighted(bool);

private:
	Entity *m_entity;
	QSizeF m_size;
	QPointF m_pos;
	QRectF m_boundingRect;
	qreal m_padSize;
	qreal m_space;
	bool m_highlighted;
	QList<Pad*> outPads;
	QList<Pad*> inPads;
	GraphicsPadContainer *m_inPadsContainer;
	GraphicsPadContainer *m_outPadsContainer;
};
