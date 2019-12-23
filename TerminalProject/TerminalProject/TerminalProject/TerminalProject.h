#pragma once

#include <QtWidgets/QMainWindow>
#include<qfile.h>
#include<string>
#include"Graph.h"
#include "ui_TerminalProject.h"
using namespace std;

class TerminalProject : public QMainWindow
{
	Q_OBJECT

public:
	TerminalProject(QWidget *parent = Q_NULLPTR);
	~TerminalProject();
	void paintEvent(QPaintEvent *);
	void fileread();
	void drawroad(int x1, int x2, int num);//寻路的动态演示
	void random_node();//随机生成事故点

private:
	Ui::TerminalProjectClass ui;
	Node *v;
};
