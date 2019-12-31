#pragma once

#include <QtWidgets/QMainWindow>
#include <QFile>
#include <QString>
#include "Graph.h"
#include "Map.h"
#include "ShowProcess.h"
#include "ui_TerminalProject.h"
using namespace std;

class TerminalProject : public QMainWindow
{
	Q_OBJECT

public:
	TerminalProject(QWidget *parent = Q_NULLPTR);
	~TerminalProject();

	QString getEdgeText(int Path[], int NodeNum, int v1, int v2, double longitude, double latitude);

	void Generator();

signals:
	void signal_map_showpath();


private:
	Ui::TerminalProjectClass ui;
	QString arr[20];
	static int count;
	int AccidentNum;
};

