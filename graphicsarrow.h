#ifndef GRAPHICSARROW_H
#define GRAPHICSARROW_H

#include <QGraphicsItem>

class GraphicsArrow : public QGraphicsItem
{
public:
	GraphicsArrow(qreal x1, qreal y1, qreal x2, qreal y2, QGraphicsItem * parent = 0);
	~GraphicsArrow();
	
	virtual QRectF boundingRect() const;
	virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = 0);

	QLineF line() const {return m_line;}
private:
	QPointF m_start;
	QPointF m_dest;
	QLineF m_line;
};

#endif
