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
	void drawroad(int x1, int x2, int num);//Ѱ·�Ķ�̬��ʾ
	void random_node();//��������¹ʵ�

private:
	Ui::TerminalProjectClass ui;
	Node *v;
};
