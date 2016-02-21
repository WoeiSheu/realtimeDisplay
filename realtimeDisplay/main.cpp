#include "realtimedisplay.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	realtimeDisplay w;
	w.show();
	return a.exec();
}
