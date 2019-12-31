#pragma once
#include "document.h"
#include <QWidget>
#include <QtWebEngine>
#include <QtWebChannel>
#include <QtWebEngineWidgets>
#include <QWebEngineView>
#include <QPushButton>


class Map : public QWidget
{
	Q_OBJECT

public:
	Map(QWidget *parent = Q_NULLPTR);
	~Map();
	QWebEngineView *map;
	Document *m_content;
	void sendmessage();

	Document *getdocument();
	QWebEngineView *getmap();
};