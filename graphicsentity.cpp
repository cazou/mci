#include "graphicsentity.h"
#include "graphicspadcontainer.h"
#include "entity.h"
#include "pad.h"

#include <QPainter>
#include <QDebug>

GraphicsEntity::GraphicsEntity(QGraphicsItem* parent)
 : QGraphicsItem(parent)
{
	m_size = QSizeF(140, 70);
	m_padSize = 20;
	m_entity = 0;
	m_pos = QPointF(0, 0);
	m_space = 40;
	m_highlighted = false;
	m_outPadsContainer = 0;
	m_inPadsContainer = 0;
}

GraphicsEntity::~GraphicsEntity()
{

}

void GraphicsEntity::setSize(qreal size)
{
	m_padSize = size / 7;
	if (m_entity && m_entity->padCount() > size/2/m_padSize)
		m_size = QSizeF(size, m_entity->padCount() * m_padSize);
	else
		m_size = QSizeF(size, size/2);
}

void GraphicsEntity::setPos(int px, int py)
{
	m_pos = QPointF((px * m_size.width()) + (px * m_space), (py * m_size.height()) + (py * m_space));

	if (!m_entity || m_entity->type() == Entity::Node)
		return;
	
	if (!m_inPadsContainer)
		m_inPadsContainer = new GraphicsPadContainer(m_entity->pads(), QPointF(0, 0), QSizeF(m_padSize, m_size.height()), Pad::In, this);
	else
		m_inPadsContainer->setPos(m_pos);
	
	if (!m_outPadsContainer)
		m_outPadsContainer = new GraphicsPadContainer(m_entity->pads(), QPointF(m_size.width() - m_padSize, 0), QSizeF(m_padSize, m_size.height()), Pad::Out, this);
	else
		m_outPadsContainer->setPos(m_pos + QPointF(m_size.width() - m_padSize, 0));
}

int GraphicsEntity::currentPosX()
{
	return static_cast<int>(m_pos.x() / (m_space + m_size.width()));
}

int GraphicsEntity::currentPosY()
{
	return static_cast<int>(m_pos.y() / (m_space + m_size.height()));
}

void GraphicsEntity::setEntity(Entity* e)
{
	m_entity = e;

	if (m_entity->type() != Entity::Node)
	{
		delete m_inPadsContainer;
		delete m_outPadsContainer;
		m_inPadsContainer = new GraphicsPadContainer(m_entity->pads(), QPointF(0, 0), QSizeF(m_padSize, m_size.height()), Pad::In, this);
		m_outPadsContainer = new GraphicsPadContainer(m_entity->pads(), QPointF(m_size.width() - m_padSize, 0), QSizeF(m_padSize, m_size.height()), Pad::Out, this);
	}
}

QRectF GraphicsEntity::boundingRect() const
{
	if (m_entity->type() == Entity::Node)
	{
		QPointF textPos(m_pos.x(), m_size.height());
		return QRectF(m_pos, m_size) | QRectF(textPos, m_size);
	}
	else
		return QRectF(m_pos, m_size);
}

QPointF GraphicsEntity::padPosition(Pad* p)
{
	if (m_entity->id() != p->entity())
		return QPointF(-1, -1);
	
	if (m_entity->type() == Entity::Node)
	{
		switch (p->type())
		{
		case Pad::In :
			return QPointF(m_pos.x() + m_size.height()/2, m_pos.y() + m_size.height()/2);
			break;
		case Pad::Out :
			return QPointF(m_pos.x() + m_size.height()*3/4, m_pos.y() + m_size.height()/2);
			break;
		}
	}

	if (p->type() == Pad::In)
		return m_inPadsContainer->padPosition(p) + QPointF(m_pos.x(), m_pos.y());
	else
		return m_outPadsContainer->padPosition(p) + QPointF(m_pos.x() + m_size.width() - m_padSize, m_pos.y());
}

void GraphicsEntity::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
	qDebug() << "Draw entity";
	if (m_entity->type() == Entity::Node)
	{
		// Node
		if (m_highlighted)
		{
                	QPen pen = painter->pen();
                	pen.setColor(Qt::blue);
                	pen.setWidth(3);
                	painter->setPen(pen);
			painter->setBrush(Qt::darkBlue);
		}
		else
		{
			painter->setBrush(Qt::darkBlue);
			painter->setPen(Qt::darkBlue);
		}
		painter->drawEllipse(m_pos.x() + m_size.height()/2, m_pos.y(), m_size.height(), m_size.height());
		QPointF textPos(m_pos.x(), m_size.height());
		painter->setPen(Qt::black);

		painter->drawText(QRectF(textPos, m_size), Qt::AlignHCenter | Qt::AlignTop | Qt::TextWordWrap, m_entity->name().replace('_', " "));
	}
	else
	{
		// Subdev
		if (m_highlighted)
		{
                	QPen pen = painter->pen();
                	pen.setColor(Qt::green);
                	pen.setWidth(3);
                	painter->setPen(pen);
			painter->setBrush(Qt::darkGreen);
		}
		else
		{
			painter->setBrush(Qt::darkGreen);
			painter->setPen(Qt::darkGreen);
		}
		painter->drawRoundedRect(QRectF(m_pos.x(), m_pos.y(), m_size.width(), m_size.height()), 10, 10);

		painter->setPen(Qt::black);

		QSizeF textSize(m_size.width() - m_padSize * 2 - 4, m_size.height());
		QPointF textPos(m_pos.x() + m_padSize + 2, m_pos.y());

		QFontMetrics fMetrics = painter->fontMetrics();
		while(fMetrics.width(m_entity->name()) + 4 > m_size.width() - (2 * m_padSize))
		{
			QFont font = painter->font();
			font.setPointSize(font.pointSize() - 1);
			painter->setFont(font);
			fMetrics = painter->fontMetrics();
		}

		painter->drawText(QRectF(textPos, textSize), Qt::AlignCenter | Qt::TextWordWrap, m_entity->name());
	}
}

void GraphicsEntity::setHighlighted(bool h)
{
	m_highlighted = h;
}
