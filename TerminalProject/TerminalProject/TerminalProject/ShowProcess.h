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

	void fileread();//��ȡ�ļ����
	void drawnode();//�����
	void drawline();//����
	void paintEvent();//��ͼ
	bool eventFilter(QObject *watched, QEvent *event);//�����¼�
	void getPath(Node *a);//��ȡ���·��
	void random_node();//����¹ʵ�
	void getNodes(int n1, int n2);//��ȡ�¹ʵ����ҽ��
	void drawroad(int x1, int x2, int num);//��Ѱ·����
	void getParent(int a[][2], int n);//��ȡ�м����parent����
	void animation();//������ʾ
	void gettotal_widget(double value);//��ȡ��·��
	void getLevel(int x);//��ȡ�¹ʵȼ�
private:
	Ui::ShowProcess ui;
	Node *v;//�洢���
	Node v1, v2;//�¹ʵ����ҽ��
	Node *path;//�洢���·��
	int number;//�����
	int level;//�¹ʵȼ�
	int parent[500][2];//�洢Ѱ·����
	int current_path;//��ǰѰ·�м��� 
	double total_weight;//�����·��

private slots:
	void on_pushButton_clicked();

signals:
	void closed();
protected:
	void closeEvent(QCloseEvent *event);

};
