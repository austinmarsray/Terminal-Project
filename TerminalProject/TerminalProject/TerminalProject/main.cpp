#include "TerminalProject.h"
#include "Map.h"
#include "Graph.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	//TerminalProject w;
	//w.show();

	Map m;
	m.sendmessage();
	m.show();
	

	return a.exec();
}