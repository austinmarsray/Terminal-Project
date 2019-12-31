#include "Map.h"


Map::Map(QWidget *parent)
	: QWidget(parent)
{
	this->showMaximized();
	map = new QWebEngineView(this);
	map->resize(1900, 1000);
	map->page()->setUrl(QUrl("C:/Users/Austin/Desktop/index1.html"));
	map->show();

	m_content = new Document(this);

	QWebChannel *channel = new QWebChannel(this);
	channel->registerObject(QStringLiteral("content"), m_content);
	map->page()->setWebChannel(channel);

	//发送文本一旦更新，重新加载网页，加载完成发送文本
	connect(this->m_content, &Document::TextSetted,
		[=]()
		{
			map->page()->setUrl(QUrl("C:/Users/Austin/Desktop/index1.html"));
			connect(map->page(), &QWebEnginePage::loadFinished, this->m_content, &Document::SendText_F);
			qDebug() << "commit succeess!";
		});
}




Map::~Map()
{
}

void Map::sendmessage()
{
	m_content->SendText_F();
}

Document * Map::getdocument()
{
	return m_content;
}

QWebEngineView * Map::getmap()
{
	return map;
}
