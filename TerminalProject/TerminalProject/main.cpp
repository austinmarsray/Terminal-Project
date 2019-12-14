#include "TerminalProject.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	TerminalProject w;
	w.show();
	return a.exec();
}
