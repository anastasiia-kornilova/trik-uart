#include <QCoreApplication>
#include <QtCore/QDebug>

#include <QSerialPort>
#include <QSerialPortInfo>
#include <QFile>

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);

	QFile file("test.js");
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
		qDebug() << "File is not opened";

	QSerialPort port("ttyUSB0");
	if(!port.setBaudRate(QSerialPort::Baud115200, QSerialPort::AllDirections))
		qDebug() << port.errorString();

	port.open(QIODevice::ReadWrite);

	port.write("save\n");
	while (!file.atEnd()) {
		QByteArray line = file.readLine();
		port.write(line);
		qDebug() << line;
	}
	port.write("saveend\n");

	return a.exec();
}
