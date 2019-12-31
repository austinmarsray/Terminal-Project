#include "TerminalProject.h"

//#include <QtWebEngineWidgets/QWebEngineView>
//#include <QtWebEngineWidgets/QWebEnginePage>
//#include <QtWebEngineWidgets/QWebEngineSettings>

TerminalProject::TerminalProject(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	this->showMaximized();

	//按按钮，触发函数
	connect(ui.action_generaotr,&QAction::triggered,
		[=]()
	{
		Generator();
	});
}

TerminalProject::~TerminalProject()
{
}






QString TerminalProject::getEdgeText(int Path[])
{
	QString s_text;

	int i = 1;
	while (1)
	{
		QString fileName;
		fileName = QString("./Resources/") + QString::number(Path[i - 1]) + "-" + QString::number(Path[i]) + QString(".txt");
		qDebug() << fileName;
		QFile file(fileName);
		if (file.open(QIODevice::ReadOnly | QIODevice::Text) != true)
		{
			qDebug() << "cannot open file." << endl;
		}
		else
		{ 
			QTextStream fin(&file);
			s_text += QString(file.readAll());
			//qDebug() << s_text;
		}
		i++;
		if (Path[i] == -1)
			break;
		else
			s_text += QString("\n");
	}
	return s_text;
}

void TerminalProject::Generator()
{
	//产生事故信息


	Graph g;
	////g.addAccident();
	////g.addAccidentEdge();

	Node *path;

	path = g.SelectPath(55, 2);
	double totalweight = path->getweight();


	int Path[100], i = 0;
	for (int i = 0; i <= 99; i++)
	{
		Path[i] = -1;
	}

	Node *cur = path->getnext();
	while (cur != nullptr)
	{
		Path[i] = cur->getcode();
		cur = cur->getnext();
		i++;
	}

	//过程展示

	//Path[0] = 0; Path[1] = 1; Path[2] = 23;
	ui.centralWidget->getdocument()->setText(getEdgeText(Path));
}
