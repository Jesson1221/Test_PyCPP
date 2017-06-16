#ifndef NEWSSPIDER_H
#define NEWSSPIDER_H

#include <QtGui/QMainWindow>
#include "ui_mainwindow.h"

class NewsSpider : public QMainWindow
{
	Q_OBJECT

public:
	NewsSpider(QWidget *parent = 0, Qt::WFlags flags = 0);
	~NewsSpider();

	void testPy();

private:
	Ui::NewsSpiderClass ui;
};

#endif // NEWSSPIDER_H
