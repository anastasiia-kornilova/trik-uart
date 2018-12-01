#include <QCoreApplication>
#include <QtCore/QDebug>

#include <QSerialPort>
#include <QSerialPortInfo>
#include <QFile>

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);

	QTextStream out(stdout);
	const auto serialPortInfos = QSerialPortInfo::availablePorts();

	out << "Total number of ports available: " << serialPortInfos.count() << endl;

	const QString blankString = "N/A";
	QString description;
	QString manufacturer;
	QString serialNumber;
	QString portName;
	QString uartPort = "";

	for (const QSerialPortInfo &serialPortInfo : serialPortInfos) {
		portName = serialPortInfo.portName();
		description = serialPortInfo.description();
		manufacturer = serialPortInfo.manufacturer();
		serialNumber = serialPortInfo.serialNumber();
		out << endl
		<< "Port: " << portName << endl
		<< "Location: " << serialPortInfo.systemLocation() << endl
		<< "Description: " << (!description.isEmpty() ? description : blankString) << endl
		<< "Manufacturer: " << (!manufacturer.isEmpty() ? manufacturer : blankString) << endl
		<< "Serial number: " << (!serialNumber.isEmpty() ? serialNumber : blankString) << endl
		<< "Vendor Identifier: " << (serialPortInfo.hasVendorIdentifier()
				? QByteArray::number(serialPortInfo.vendorIdentifier(), 16)
				: blankString) << endl
		<< "Product Identifier: " << (serialPortInfo.hasProductIdentifier()
				? QByteArray::number(serialPortInfo.productIdentifier(), 16)
				: blankString) << endl
		<< "Busy: " << (serialPortInfo.isBusy() ? "Yes" : "No") << endl;

		if (description.contains("uart", Qt::CaseInsensitive)) {
			uartPort = portName;
		}
	}

	QFile file("test.js");
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
		out << "File is not opened";

	if (uartPort != "") {
		QSerialPort port(uartPort);
		if(!port.setBaudRate(QSerialPort::Baud115200, QSerialPort::AllDirections))
			out << port.errorString();

		port.open(QIODevice::ReadWrite);

		port.write("save example1.js\n");
		while (!file.atEnd()) {
			QByteArray line = file.readLine();
			port.write(line);
			out << line;
		}
		port.write("saveend\n");
	} else {
		out << "UART port not found";
	}

	return a.exec();
}
