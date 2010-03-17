#include <QApplication>

#include "mediaviewerwindow.h"

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	MediaViewerWindow *mvw = new MediaViewerWindow();
	mvw->show();

	int ret = app.exec();

	return ret;
}
