#include "realtimedisplay.h"
#include <QtGui/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	realtimeDisplay w;
	w.showMaximized();
	w.show();
	return a.exec();
}
