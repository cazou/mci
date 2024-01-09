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
#include <QCoreApplication>

#include "mediaviewerwindow.h"

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	MediaViewerWindow *mvw = new MediaViewerWindow();
	mvw->show();

	int ret = app.exec();

	return ret;
}
