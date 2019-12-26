#include "Map.h"


Map::Map(QWidget *parent)
	: QWidget(parent)
{
	this->showMaximized();
	this->setWindowTitle(QString("高速公路救援系统demo-演示"));
	map = new QWebEngineView(this);
	map->resize(1900, 1020);
	//map->load(QUrl("C:/Users/Austin/Desktop/index1.html"));
	map->page()->setUrl(QUrl("C:/Users/Austin/Desktop/index.html"));
	map->show();

	m_content = new Document(this);
	btn = new QPushButton(QString("PUSH"),this);
	btn->setGeometry(1000, 600, 50, 25);
	btn->show();

	QWebChannel *channel = new QWebChannel(this);
	channel->registerObject(QStringLiteral("content"), m_content);
	map->page()->setWebChannel(channel);

	//connect(btn, &QPushButton::clicked, this, &Map::sendmessage);
	connect(map->page(), &QWebEnginePage::loadFinished, this, &Map::sendmessage);
}




Map::~Map()
{
}

void Map::sendmessage()
{
	m_content->getEdgeText(0, 1);
	m_content->setSendTextText();
}
