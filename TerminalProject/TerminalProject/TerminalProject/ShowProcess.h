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

	void fileread();//��ȡ�ļ����
	void drawnode();//�����
	void drawline();//����
	void paintEvent();//��ͼ
	bool eventFilter(QObject *watched, QEvent *event);//�����¼�
	void getPath(Node *a);//��ȡ���·��
	void drawroad(int x1, int x2, int num, float length);//��Ѱ·����

private:
	Ui::ShowProcess ui;
	Node *v;//�洢���
	Node *path;//�洢���·��
	int number;//�����

private slots:
	void on_pushButton_clicked();
signals:
	void closed();
protected:
	void closeEvent(QCloseEvent *event);

};
