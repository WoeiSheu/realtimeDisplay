#include "realtimedisplay.h"

realtimeDisplay::realtimeDisplay(QWidget *parent)
	: QMainWindow(parent)
{
	QTextCodec::setCodecForCStrings(QTextCodec::codecForName("System"));  //设置编码格式,防止乱码, before Qt5
	/* 1. Initialize variables */
	ui.setupUi(this);
	scene = new QGraphicsScene;
	timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(timerUpdate()));
	timestep = 50;

	targetnum = 0;
	realnum   = 0;
	areaxmax  = 0;
	areaxmin  = 0;
	areaymax  = 0;
	areaymin  = 0;
	viewx = 800;
	viewy = 600;
	flag  = 0;
	timeCount = 0;

	ui.label->setText("Display locus");

	for (int i=0;i<NUMMAX;i++)
	{
		targetNames[i] = "0";
		realPositions[i][0] = 0;
		resultPositions[i][0] = 0;
	}

	tableInitial();		// Initialize table
	ui.listWidget->addItem(QString("Log"));		// Initialize listWidget
	for(int i = 0; i < 2*NUMMAX; i++)
	{
		ui.listWidget->addItem("");
		
		m_svgItem[i] = new QGraphicsSvgItem("tank.svg");
		m_svgItem[i]->setFlags(QGraphicsItem::ItemClipsToShape);
		m_svgItem[i]->setCacheMode(QGraphicsItem::NoCache);
		m_svgItem[i]->setZValue(0);
		m_svgItem[i]->setScale(16);

		m_backgroundItem[i] = new QGraphicsRectItem(m_svgItem[i]->boundingRect());
		m_backgroundItem[i]->setBrush(Qt::white);
		m_backgroundItem[i]->setPen(Qt::NoPen);
		m_backgroundItem[i]->setVisible(true);
		m_backgroundItem[i]->setZValue(-1);
		m_backgroundItem[i]->setScale(16);

		m_outlineItem[i] = new QGraphicsRectItem(m_svgItem[i]->boundingRect());
		QColor c((20+13*i)%255,(70+29*i)%255,255-(17*i)%255);
		QPen outline( c, 2, Qt::DotLine );
		outline.setCosmetic(true);
		m_outlineItem[i]->setPen(outline);
		m_outlineItem[i]->setBrush(Qt::NoBrush);
		m_outlineItem[i]->setVisible(true);
		m_outlineItem[i]->setZValue(1);
		m_outlineItem[i]->setScale(16);
	}

	scene->setSceneRect(-1340000,5310000,20000,30000);
	//ui.graphicsView->centerOn(-100,100);
	//ui.graphicsView->scale( ui.graphicsView->size().width()/100.0, ui.graphicsView->size().height()/100.0 );
	/* 1. End */

	_udpServer = new SocketUdp;	//收数据初始化
	//修改：通过配置文件来设置修改监听的端口号,配置文件放在生成的exe目录下的config文件加下
	QString ipConfigFile = QCoreApplication::applicationDirPath()+"/config"+"/UdpConfig.ini";
	QSettings setting( ipConfigFile,QSettings::IniFormat);
	setting.setIniCodec( QTextCodec::codecForName( "System" ) );
	int port = setting.value("IpConfig/Port","8000").toInt();
	_udpServer->Init(port);
	connect(_udpServer,SIGNAL(sendData2View(char *,int )),this,SLOT(slotReciveData2View(char *,int))); //修改：添加一个字节数

	timer->start(timestep);		// start timer
}

realtimeDisplay::~realtimeDisplay()
{

}

void realtimeDisplay::tableInitial()
{
	ui.label_2->setText(QString("Data"));
	ui.tableWidget->verticalHeader()->setVisible(false);
	rows = 21;
	columns = 5;
	ui.tableWidget->setRowCount(rows);
	ui.tableWidget->setColumnCount(columns);
	QStringList header;
	header<<QString("Target Name")
		<<QString("X")
		<<QString("Y")
		<<QString("Z")
		<<QString("time");
	ui.tableWidget->setHorizontalHeaderLabels(header);
	
	ui.tableWidget->horizontalHeader()->setStyleSheet(
		"QHeaderView::section {color: black;border: 1px solid #cccccc;}");

	ui.tableWidget->horizontalHeader()->setResizeMode(QHeaderView::Stretch);			// before qt 5
	//ui.tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);		// qt 5

	for(int i = 0; i < rows; i+=3)
	{
		ui.tableWidget->setSpan(i,0,3,1);	// merge cells
	}

	ui.tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void realtimeDisplay::parseResultData(ResultInfo resultInfo)
{
	int num,k;
	num = findLocate(targetNames,resultInfo.sName);
	if (num < 0) //该目标未在表格中显示
	{
		//targetnum++;
		num = findZeroLocate(targetNames);
		//num = targetnum - 1;
		targetNames[num]=resultInfo.sName;  //写入数组
		resultPositions[num][0] = 1;
		resultPositions[num][3] = resultInfo.dLocX;
		resultPositions[num][4] = resultInfo.dLocY;
		if ( resultInfo.dLocX>areaxmax)
		{
			areaxmax = resultInfo.dLocX;
		} 
	    if( resultInfo.dLocX < areaxmin)
		{
			areaxmin = resultInfo.dLocX;
		}
		if(resultInfo.dLocY > areaymax)
			areaymax = resultInfo.dLocY;
		if(resultInfo.dLocY < areaymin)
			areaymin = resultInfo.dLocY;
		targetnum = num;
		k=3*num;
		if (k>=rows)
		{
			ui.tableWidget->insertRow(k);  //增加三行
			ui.tableWidget->insertRow(k+1);
			ui.tableWidget->insertRow(k+2);
			ui.tableWidget->setSpan(k,0,3,1);
			rows+=3;
		}

		ui.tableWidget->setItem(k,0,new QTableWidgetItem(resultInfo.sName));
		ui.tableWidget->setItem(k,1,new QTableWidgetItem(QString::number(resultInfo.dLocX,'f')));
		ui.tableWidget->setItem(k,2,new QTableWidgetItem(QString::number(resultInfo.dLocY,'f')));
		ui.tableWidget->setItem(k,3,new QTableWidgetItem(QString::number(resultInfo.dLocZ,'f')));
		ui.tableWidget->setItem(k,4,new QTableWidgetItem(QString::number(resultInfo.dt,'f')));
		for(int i = 0; i < columns; i++) {
			ui.tableWidget->item(k,i)->setTextAlignment(Qt::AlignCenter);
		}
	}
	else
	{
		if(targetnum < num) {
			targetnum = num;
		}
		k=3*num;

		resultPositions[num][1] = resultPositions[num][3];
		resultPositions[num][2] = resultPositions[num][4];
		resultPositions[num][3] = resultInfo.dLocX;
		resultPositions[num][4] = resultInfo.dLocY;
		resultPositions[num][0] = 2;
		
		if ( resultInfo.dLocX>areaxmax)
			areaxmax = resultInfo.dLocX;
		if( resultInfo.dLocX<areaxmin)
			areaxmin = resultInfo.dLocX;
		
		if(resultInfo.dLocY > areaymax)
			areaymax = resultInfo.dLocY;
		if(resultInfo.dLocY<areaymin)
			areaymin = resultInfo.dLocY;
			
		ui.tableWidget->setItem(k,1,new QTableWidgetItem(QString::number(resultInfo.dLocX,'f')));
		ui.tableWidget->setItem(k,2,new QTableWidgetItem(QString::number(resultInfo.dLocY,'f')));
		ui.tableWidget->setItem(k,3,new QTableWidgetItem(QString::number(resultInfo.dLocZ,'f')));
		ui.tableWidget->setItem(k,4,new QTableWidgetItem(QString::number(resultInfo.dt,'f')));
		for(int i = 0; i < columns; i++) {
			ui.tableWidget->item(k,i)->setTextAlignment(Qt::AlignCenter);
		}
		if (realPositions[num][0]>0)
		{
			double t = ui.tableWidget->item(k+1,4)->text().toDouble();
			ui.tableWidget->setItem(k+2,4,new QTableWidgetItem(QString::number(resultInfo.dt - t)));
			if (resultInfo.dt-t<0.08&&resultInfo.dt-t>-0.08)
			{
				double x = ui.tableWidget->item(k+1,1)->text().toDouble();
				ui.tableWidget->setItem(k+2,1,new QTableWidgetItem(QString::number(resultInfo.dLocX - x)));
				x = ui.tableWidget->item(k+1,2)->text().toDouble();
				ui.tableWidget->setItem(k+2,2,new QTableWidgetItem(QString::number(resultInfo.dLocY - x)));
				x = ui.tableWidget->item(k+1,3)->text().toDouble();
				ui.tableWidget->setItem(k+2,3,new QTableWidgetItem(QString::number(resultInfo.dLocZ - x)));
				for(int i = 1; i < columns; i++) {
					ui.tableWidget->item(k+2,i)->setTextAlignment(Qt::AlignCenter);
				}
			}
			
		}
	}
}

void realtimeDisplay::parseSourcedata(FlyTargetInfo flyTargetinfo)
{
	int num,k;
	num = findLocate(targetNames, flyTargetinfo.sName);
	if (num<0) //该目标未在表格中显示
	{
		num = findZeroLocate(targetNames);
		targetNames[num] = flyTargetinfo.sName; //名字写入数组
		realPositions[num][3] = flyTargetinfo.dX;
		realPositions[num][4] = flyTargetinfo.dY;
		realPositions[num][0] = 1;
		
		if(areaxmax < flyTargetinfo.dX)
			areaxmax = flyTargetinfo.dX;
		if(areaxmin > flyTargetinfo.dX)
			areaxmin = flyTargetinfo.dX;
		if (areaymax < flyTargetinfo.dY)
			areaymax = flyTargetinfo.dY;
		if (areaymin > flyTargetinfo.dY)
			areaymin = flyTargetinfo.dY;
		realnum = num;
		k=3*num;
		if (k>=rows)
		{
			ui.tableWidget->insertRow(k);  //增加三行
			ui.tableWidget->insertRow(k+1);
			ui.tableWidget->insertRow(k+2);
			ui.tableWidget->setSpan(k,0,3,1);
			rows+=3;
		}
		ui.tableWidget->setItem(k,0,new QTableWidgetItem(flyTargetinfo.sName));
		ui.tableWidget->setItem(k+1,1,new QTableWidgetItem(QString::number(flyTargetinfo.dX,'f')));
		ui.tableWidget->setItem(k+1,2,new QTableWidgetItem(QString::number(flyTargetinfo.dY,'f')));
		ui.tableWidget->setItem(k+1,3,new QTableWidgetItem(QString::number(flyTargetinfo.dZ,'f')));
		ui.tableWidget->setItem(k+1,4,new QTableWidgetItem(QString::number(flyTargetinfo.dpulsetime,'f')));
		ui.tableWidget->item(k,0)->setTextAlignment(Qt::AlignCenter);
		for(int i = 1; i < columns; i++) {
			ui.tableWidget->item(k+1,i)->setTextAlignment(Qt::AlignCenter);
		}
	}
	else
	{
		//ui.listWidget->item(num+2)->setText(flyTargetinfo.sName);
		if(realnum < num) {
			realnum = num;
		}
		k=3*num;
		realPositions[num][0]++;

		realPositions[num][1] = realPositions[num][3];
		realPositions[num][2] = realPositions[num][4];
		realPositions[num][3] = flyTargetinfo.dX;
		realPositions[num][4] = flyTargetinfo.dY;
		realPositions[num][0] = 2;

		if(areaxmax < flyTargetinfo.dX)
			areaxmax = flyTargetinfo.dX;
		if(areaxmin > flyTargetinfo.dX)
			areaxmin = flyTargetinfo.dX;
		if (areaymax < flyTargetinfo.dY)
			areaymax = flyTargetinfo.dY;
		if (areaymin > flyTargetinfo.dY)
			areaymin = flyTargetinfo.dY;

		ui.tableWidget->setItem(k+1,1,new QTableWidgetItem(QString::number(flyTargetinfo.dX,'f')));
		ui.tableWidget->setItem(k+1,2,new QTableWidgetItem(QString::number(flyTargetinfo.dY,'f')));
		ui.tableWidget->setItem(k+1,3,new QTableWidgetItem(QString::number(flyTargetinfo.dZ,'f')));
		ui.tableWidget->setItem(k+1,4,new QTableWidgetItem(QString::number(flyTargetinfo.dpulsetime,'f')));
		for(int i = 1; i < columns; i++) {
			ui.tableWidget->item(k+1,i)->setTextAlignment(Qt::AlignCenter);
		}
		//if (resultPositions[num][0]>0)
		//{
		//	double t = ui.tableWidget->item(k,4)->text().toDouble();
		//	if (flyTargetinfo.dpulsetime-t<0.008&&flyTargetinfo.dpulsetime-t>-0.008)//时间是否相等
		//	{
		//		double x = ui.tableWidget->item(k,1)->text().toDouble();
		//		ui.tableWidget->setItem(k+2,1,new QTableWidgetItem(QString::number(flyTargetinfo.dX - x)));
		//		x = ui.tableWidget->item(k,2)->text().toDouble();
		//		ui.tableWidget->setItem(k+2,2,new QTableWidgetItem(QString::number(flyTargetinfo.dY - x)));
		//		x = ui.tableWidget->item(k,3)->text().toDouble();
		//		ui.tableWidget->setItem(k+2,3,new QTableWidgetItem(QString::number(flyTargetinfo.dZ - x)));
		//		ui.tableWidget->item(k+2,1)->setTextAlignment(Qt::AlignCenter);
		//		ui.tableWidget->item(k+2,2)->setTextAlignment(Qt::AlignCenter);
		//		ui.tableWidget->item(k+2,3)->setTextAlignment(Qt::AlignCenter);
		//	}
		//}
	}
}

void realtimeDisplay::timerUpdate()
{	
	timeCount++;

	for (int i=0; i<=targetnum; i++)
	{
		if (resultPositions[i][0] == 2 )
		{
			scene->addLine(resultPositions[i][1],resultPositions[i][2],resultPositions[i][3],resultPositions[i][4]);
			flag = 1;
		}
	}
	for (int i=0; i<=realnum; i++)
	{
		if (realPositions[i][0] == 2)
		{
			scene->addLine(realPositions[i][1],realPositions[i][2],realPositions[i][3],realPositions[i][4]);
			flag = 1;	
		}
	}

	/*if ((areaxmax-areaxmin)>viewx || (areaymax-areaymin>viewy)&&flag==1)
	{
		ui.graphicsView->scale(viewx/(areaxmax-areaxmin),viewy/(areaymax-areaymin)); 
		viewx = areaxmax-areaxmin;
		viewy = areaymax-areaymin;
	}*/

	// The following lines are for test
	m_backgroundItem[0]->setPos(-1340000+100*timeCount,5310000+100*timeCount);
	m_svgItem[0]->setPos(-1340000+100*timeCount,5310000+100*timeCount);
	m_outlineItem[0]->setPos(-1340000+100*timeCount,5310000+100*timeCount);
	m_backgroundItem[1]->setPos(-1320000-100*timeCount,5340000-100*timeCount);
	m_svgItem[1]->setPos(-1320000-100*timeCount,5340000-100*timeCount);
	m_outlineItem[1]->setPos(-1320000-100*timeCount,5340000-100*timeCount);
	scene->addItem(m_backgroundItem[0]);
	scene->addItem(m_svgItem[0]);
	scene->addItem(m_outlineItem[0]);
	//scene->addLine(-1340000+100*timeCount,5310000+100*timeCount,-1339000+100*timeCount,5311000+100*timeCount);
	scene->addItem(m_backgroundItem[1]);
	scene->addItem(m_svgItem[1]);
	scene->addItem(m_outlineItem[1]);
	//scene->addLine(-1320000-100*timeCount,5340000-100*timeCount,-1321000-100*timeCount,5339000-100*timeCount);
	// Test end

	ui.graphicsView->fitInView(scene->sceneRect(), Qt::KeepAspectRatio);
	ui.graphicsView->setScene(scene);
	
	// Print log for debug
	ui.listWidget->item(1)->setText("Target Num: " + QString::number(targetnum) + ", Fly Num: " + QString::number(realnum));
	ui.listWidget->item(2)->setText("Size width: " + QString::number( ui.graphicsView->size().width() )
		+ ", Size height: " + QString::number( ui.graphicsView->size().height() ) );
	ui.listWidget->item(3)->setText("Scene width: " + QString::number( scene->width() )
		+ ", Scene height: " + QString::number( scene->height() ) );
	// Log end
}

void realtimeDisplay::slotReciveData2View(char * rBuf,int size)
{
	int offset = 0;
	
	if (size % sizeof(FlyTargetInfo) == 0)	// 判断当前接收到的数据不是探测结果数据, 直接返回
	{
		int flyCount = size / sizeof(FlyTargetInfo);	// 计算当前接收到的坦克探测结果数据个数
		for (int index = 0; index < flyCount; index++)
		{
			FlyTargetInfo flyTargetInfo;
			memcpy(&flyTargetInfo, rBuf+offset, sizeof(FlyTargetInfo));
			offset += sizeof(FlyTargetInfo);
			parseSourcedata(flyTargetInfo);
		}
	
	}

	if (size % sizeof(ResultInfo) == 0) 
	{
		int getCount = size / sizeof(ResultInfo);		 // 计算当前接收到的坦克探测结果数据个数
		for (int index = 0; index < getCount; index++)
		{
			ResultInfo resultInfo;
			memcpy(&resultInfo, rBuf+offset, sizeof(ResultInfo));
			offset += sizeof(ResultInfo);
			parseResultData(resultInfo);
		}
	}
}

int realtimeDisplay::findLocate(QString s[NUMMAX], char name[30])
{
	int i=0;
	while (i<NUMMAX)
	{
		if (QString::compare(name,s[i],Qt::CaseInsensitive)==0)
		{
			return i;
		}
		i++;
	}
	return -1;
}

int realtimeDisplay::findZeroLocate(QString s[NUMMAX])
{
	int i=0;
	while (i<NUMMAX)
	{
		if (QString::compare("0",s[i],Qt::CaseInsensitive)==0)
		{
			return i;
		}
		i++;
	}
	return -1;
}