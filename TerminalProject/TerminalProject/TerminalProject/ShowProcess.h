#pragma once
#pragma execution_character_set("utf-8")
#include <QWidget>
#include<QtGui>
#include<qfile.h>
#include<qpropertyanimation.h>
#include<qabstractanimation.h>
#include<qanimationgroup.h>
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
	void random_node();//随机事故点
	void getNodes(int n1, int n2);//获取事故点左右结点
	void drawroad(int x1, int x2, int num);//画寻路连点
	void getParent(int a[][2], int n);//获取中间过程parent数组
	void animation();//动画演示
	void gettotal_widget(double value);//获取总路径
	void getLevel(int x);//获取事故等级
private:
	Ui::ShowProcess ui;
	Node *v;//存储结点
	Node v1, v2;//事故点左右结点
	Node *path;//存储最短路径
	int number;//结点数
	int level;//事故等级
	int parent[500][2];//存储寻路过程
	int current_path;//当前寻路中间数 
	double total_weight;//最短总路径

private slots:
	void on_pushButton_clicked();

signals:
	void closed();
protected:
	void closeEvent(QCloseEvent *event);

};
