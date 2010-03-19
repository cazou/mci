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
#ifndef MEDIAVIEWERWINDOW_H
#define MEDIAVIEWERWINDOW_H

#include "ui_mediaviewerwindow.h"

class MediaDevice;
class MediaDevicePool;
class Entity;
class QResizeEvent;
class MediaGraphicsScene;

class MediaViewerWindow : public QMainWindow
{
	Q_OBJECT
public:
	MediaViewerWindow(QWidget *parent = 0);
	~MediaViewerWindow();

private slots:
	void slotEntityClicked(const Entity*);
	void slotUpdateDevices();
	void updateDevicesComboBox();
	void changeShowingDevice(int index);

protected:
	virtual void resizeEvent(QResizeEvent*);

private:
	Ui::mediaViewerWindow ui;
	MediaDevice *currentMediaDevice;
	MediaDevicePool *m_devPool;
	void resizeSceneInView();

	MediaGraphicsScene *m_scene;
};

#endif
