#include "TerminalProject.h"

#include <QtWebEngineWidgets/QWebEngineView>
#include <QtWebEngineWidgets/QWebEnginePage>
#include <QtWebEngineWidgets/QWebEngineSettings>

TerminalProject::TerminalProject(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	QWebEngineView* webview = new QWebEngineView;
	QUrl url = QUrl("file:///E:/DataStructureProject/Project/TerminalProject/TerminalProject/TerminalProject/map.html");
	webview->page()->load(url);
	webview->setParent(ui.centralWidget);
}

TerminalProject::~TerminalProject()
{
	//delete ui;
}
