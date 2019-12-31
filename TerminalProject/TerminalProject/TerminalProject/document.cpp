#include "document.h"
#include <qdebug.h>

void Document::setText(const QString &text)
{
	s_text = text;
	emit TextSetted();
	qDebug() << s_text;
}

void Document::SendText_F()
{
	emit sendText(s_text);
}

void Document::receiveText(const QString &r_text)
{
	qDebug() << r_text << endl;	//"true"
}
