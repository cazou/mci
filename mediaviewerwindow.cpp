#include "mediaviewerwindow.h"
#include "mediadevice.h"
#include "mediagraphicsscene.h"
#include "entity.h"
#include "subdevice.h"
#include "v4l2control.h"
#include "mediadevicepool.h"
#include "subdevicepool.h"

#include <QGraphicsScene>
#include <QResizeEvent>
#include <QDebug>

#define MIN(x,y)	(x) > (y) ? (y) : (x)

MediaViewerWindow::MediaViewerWindow(QWidget *parent)
 : QMainWindow(parent)
{
	ui.setupUi(this);
	
	m_scene = 0;

	setWindowTitle("Media Controller Inspector");
	
	m_devPool = new MediaDevicePool();
	connect(m_devPool, SIGNAL(newDevices()), this, SLOT(slotUpdateDevices()));
	
	if (m_devPool->count() == 0)
		return;

	currentMediaDevice = m_devPool->devices().at(0);

	updateDevicesComboBox();

	m_scene = new MediaGraphicsScene(ui.mediaGraphicsView);
	m_scene->setMediaDevice(currentMediaDevice);
	ui.mediaGraphicsView->setScene(m_scene);
	connect(m_scene, SIGNAL(entityClicked(const Entity*)), this, SLOT(slotEntityClicked(const Entity*)));
	ui.mediaGraphicsView->setRenderHint(QPainter::Antialiasing, true);

	showMaximized();

	resizeSceneInView();
}

MediaViewerWindow::~MediaViewerWindow()
{
	delete m_devPool;
	delete SubDevicePool::self();
	delete m_devPool;
}

void MediaViewerWindow::resizeSceneInView()
{
	if (!m_scene)
		return;
	QSizeF viewSize = ui.mediaGraphicsView->rect().size();
	QSizeF sceneSize = ui.mediaGraphicsView->mapFromScene(m_scene->sceneRect()).boundingRect().size();
	sceneSize *= 1.1;
	
	qreal v = MIN(viewSize.height() / sceneSize.height(), viewSize.width() / sceneSize.width());
	
	ui.mediaGraphicsView->scale(v, v);
}

void MediaViewerWindow::resizeEvent(QResizeEvent *event)
{
	Q_UNUSED(event)

	resizeSceneInView();
}

void MediaViewerWindow::slotEntityClicked(const Entity *e)
{
	if (!e)
	{
		ui.nameLabel->setText("");
		ui.typeLabel->setText("");
		ui.controlWidget->setSubDevice(0);
		return;
	}
	else
	{
		ui.nameLabel->setText(e->name());
		QString type;
		switch(e->subtype())
		{
		case Entity::V4l:
			type = "V4l";
			break;
		case Entity::FB:
			type = "Frame Buffer";
			break;
		case Entity::Alsa:
			type = "Alsa";
			break;
		case Entity::DVB:
			type = "DVB";
			break;
		case Entity::Encoder:
			type = "Encoder";
			break;
		case Entity::Decoder:
			type = "Decoder";
			break;
		case Entity::Misc:
			type = "Misc";
			break;
		case Entity::Unknown:
			type = "Unknown";
		}

		ui.typeLabel->setText(QString("%1 : %2").arg(e->type() == Entity::Node ? "Node" : "Subdev").arg(type));
	}

	ui.controlWidget->setSubDevice(e->subDevice());
}

void MediaViewerWindow::slotUpdateDevices()
{
	updateDevicesComboBox();
	qDebug() << "New device(s) !";
}

void MediaViewerWindow::updateDevicesComboBox()
{
	disconnect(ui.devicesComboBox, SIGNAL(currentIndexChanged(int)));
	int index = -1;
	ui.devicesComboBox->clear();

	int i = 0;

	foreach(MediaDevice *dev, m_devPool->devices())
	{
		ui.devicesComboBox->addItem(dev->devName());
		if (dev->devName() == currentMediaDevice->devName())
			index = i;
		i++;
	}

	if (index == -1)
	{
		if (m_devPool->count() > 0)
		{
			index++;
			currentMediaDevice = m_devPool->devices().at(0);
		}
		else
			currentMediaDevice = 0;
		
		changeShowingDevice(index);
	}

	ui.devicesComboBox->setCurrentIndex(index);
	
	connect(ui.devicesComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(changeShowingDevice(int)));
}

void MediaViewerWindow::changeShowingDevice(int index)
{
	if (index == -1)
	{
		delete ui.mediaGraphicsView->scene();
		return;
	}
	
	currentMediaDevice = m_devPool->devices().at(index);
	
	delete ui.mediaGraphicsView->scene();

	m_scene = new MediaGraphicsScene(ui.mediaGraphicsView);
	m_scene->setMediaDevice(currentMediaDevice);
	ui.mediaGraphicsView->setScene(m_scene);
	connect(m_scene, SIGNAL(entityClicked(const Entity*)), this, SLOT(slotEntityClicked(const Entity*)));

	resizeSceneInView();
}
