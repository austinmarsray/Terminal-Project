#pragma once

#include <QtWidgets/QMainWindow>
#include<qfile.h>
#include<string>
#include"Graph.h"
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

	QString getEdgeText(int Path[]);

	void Generator();

signals:
	void signal_map_showpath();


private:
	Ui::TerminalProjectClass ui;
};
