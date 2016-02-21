#include "SocketUdp.h"
#include <QtCore/QTextCodec>
#include "qmath.h"
#include <atlstr.h>
#include <atlbase.h>
#include "PackageDataDefine.h"
#include <iostream>

using namespace std;

SocketUdp::SocketUdp(void)
{

}

SocketUdp::~SocketUdp(void)
{

}

bool SocketUdp::Init(int port)
{
	bool ret = _pSocket.bind(port, QUdpSocket::ShareAddress); 
	connect(&_pSocket,SIGNAL(readyRead()),this,SLOT(ReadDatagram()));
	return ret;
}

double SocketUdp::ForKindDouble(double dIn)//标准化double
{
	if(abs(dIn) <= 0.00001)
		return 0.0;
	else
		return dIn;
}

void SocketUdp::ReadDatagram()
{

	while(_pSocket.hasPendingDatagrams())  //只要拥有等待的数据报
	{
		//用于存放接收的数据报
		QByteArray datagram;
		//接收字节数
		int iDataSize = _pSocket.pendingDatagramSize();
		datagram.resize(iDataSize);//让datagram的大小为等待处理的数据报的大小，这样才能接收到完整的数据
		char *rBuf = datagram.data();
		qint64 iReceiveSize = _pSocket.readDatagram(rBuf,iDataSize);//接收数据报，将其存放到datagram中
		if (iReceiveSize !=0)
		{
			emit sendData2View(rBuf,iReceiveSize);
		}
	}
}
