#include "document.h"
#include <qdebug.h>

void Document::setSendTextText()
{
	emit sendText(s_text);
}

void Document::receiveText(const QString &r_text)
{
	qDebug() << r_text << endl;	//"true"
	//if (r_text == "true")

}

void Document::getEdgeText(int start, int end)
{
	QString fileName = QString("./Resources/")+QString::number(start) + "-" + QString::number(end) + QString(".txt");
	//qDebug() << fileName << endl;
	QFile file(fileName);
	if (file.open(QIODevice::ReadOnly | QIODevice::Text) != true)
	{
		qDebug() << "cannot open file." << endl;
	}
	else
	{
		QTextStream fin(&file);
		s_text = QString(file.readAll());
		qDebug() << s_text;
	}
}
