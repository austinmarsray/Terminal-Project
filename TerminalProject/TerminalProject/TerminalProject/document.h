#pragma once

#ifndef DOCUMENT_H
#define DOCUMENT_H

#include <QObject>
#include <QString>
#include <QFile>
#include <QTextStream>

class Document : public QObject
{
	Q_OBJECT
		Q_PROPERTY(QString text MEMBER s_text NOTIFY sendText)

public:
	explicit Document(QObject *parent = nullptr) : QObject(parent) {}

	void setText(const QString &text);

	void SendText_F();
signals:
	void sendText(const QString &text);
	void TextSetted();

public slots:
	void  receiveText(const QString &r_text);

private:
	QString s_text;
};

#endif // DOCUMENT_H
