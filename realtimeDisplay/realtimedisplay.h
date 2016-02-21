#ifndef REALTIMEDISPLAY_H
#define REALTIMEDISPLAY_H

#define NUMMAX 20

#include <QtWidgets/QMainWindow>
// #include <QtGUI/QMainWindow>		// before Qt 5
#include "ui_realtimedisplay.h"

#include <QTimer>
#include <QTableWidget>
#include <QTextCodec>
#include <iostream>
#include <QSettings>
#include <QTextCodec>
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <QGraphicsSvgItem>

#include "SocketUdp.h"
#include "PackageDataDefine.h"

class realtimeDisplay : public QMainWindow
{
	Q_OBJECT

public:
	realtimeDisplay(QWidget *parent = 0);
	~realtimeDisplay();
	
	void tableInitial();
	void parseResultData(ResultInfo);
	void parseSourcedata(FlyTargetInfo);

	int findLocate(QString s[NUMMAX], char name[30]);
	int findZeroLocate(QString s[NUMMAX]);
private:
	Ui::realtimeDisplayClass ui;
	QGraphicsScene *scene;
	QTimer *timer;
	SocketUdp * _udpServer;
	int timestep;
	QString targetNames[NUMMAX];			// Store target names
	double realPositions[NUMMAX][5];
	double resultPositions[NUMMAX][5];		// Calculate result
	int targetnum;
	int realnum;							 // Ŀ������,�����軭ͼ����
	double areaxmax;
	double areaxmin;
	double areaymax;
	double areaymin;
	double viewx;
	double viewy;
	int flag;
	int timeCount;

	int rows;
	int columns;

	QGraphicsItem *m_svgItem;
    QGraphicsRectItem *m_backgroundItem;
    QGraphicsRectItem *m_outlineItem;

	private slots:
		void slotReciveData2View(char * rBuf,int size);
		void timerUpdate();
};

#endif // REALTIMEDISPLAY_H