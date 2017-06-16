#include "newsspider.h"
#include <QtGui/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	NewsSpider w;
	w.show();
	return a.exec();
}
