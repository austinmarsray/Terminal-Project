#include "TerminalProject.h"
#include "Map.h"
#include "Graph.h"
#include <QtWidgets/QApplication>
#include"ShowProcess.h"

int main(int argc, char *argv[])
{
	//≥Ã–Ú∆Ù∂Ø
	QApplication a(argc, argv);
	
	TerminalProject w;
	w.show();
	return a.exec();
}