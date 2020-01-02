#pragma once
#pragma execution_character_set("utf-8")
#include <QWidget>
#include<QtGui>
#include<qfile.h>
#include<qpropertyanimation.h>
#include<qabstractanimation.h>
#include<qanimationgroup.h>
#include <QCloseEvent> 
#include "ui_ShowProcess.h"
#include"Node.h"

class ShowProcess : public QWidget
{
	Q_OBJECT

public:
	ShowProcess(QWidget *parent = Q_NULLPTR);
	~ShowProcess();

	void fileread();//读取文件结点
	void drawnode();//画结点
	void drawline();//画线
	void paintEvent();//绘图
	bool eventFilter(QObject *watched, QEvent *event);//过滤事件
	void getPath(Node *a);//获取最短路径
	void drawroad(int x1, int x2, int num, float length);//画寻路连点

private:
	Ui::ShowProcess ui;
	Node *v;//存储结点
	Node *path;//存储最短路径
	int number;//结点数

private slots:
	void on_pushButton_clicked();
signals:
	void closed();
protected:
	void closeEvent(QCloseEvent *event);

};
