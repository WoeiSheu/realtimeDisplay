#ifndef _H_UDPSOCKET
#define _H_UDPSOCKET

#include <QObject>
#include <QThread>
#include <vector>
#include <map>
#include <QMetaType>
#include <QString>
#include <QSemaphore>
#include <QtNetwork/QUdpSocket>

class  SocketUdp : public QThread
{
	Q_OBJECT

public:
	SocketUdp(void);
	~SocketUdp(void);
	bool Init(int port);

signals:
	void sendData2View(char *,int);   //修改：添加一个字节数

	private slots:
		void ReadDatagram();

private:
	QUdpSocket _pSocket;
	double ForKindDouble(double dIn);//标准化double
};

#endif //_H_UDPSOCKET