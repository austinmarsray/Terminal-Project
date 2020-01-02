#include "TerminalProject.h"

int TerminalProject::count = 0;

TerminalProject::TerminalProject(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	this->showMaximized();
	
	//��ȡ�¹���Ϣ
	QString filepath;
	filepath = QString("./Accident.txt");
	//qDebug() << filepath;
	QFile file(filepath);
	if (file.open(QIODevice::ReadOnly | QIODevice::Text) != true)
	{
		qDebug() << "cannot open file." << endl;
	}
	else
	{
		QTextStream fin(&file);
		AccidentNum = 0;
		while (!file.atEnd())
		{
			arr[AccidentNum++] = QString(file.readLine());
		}
	}

	//����ť����������
	connect(ui.action_generaotr,&QAction::triggered,
		[=]()
	{
		Generator();
	});
}

TerminalProject::~TerminalProject()
{
}



QString TerminalProject::getEdgeText(int Path[], int NodeNum, int v1, int v2, double longitude, double latitude)
{
	QString s_text;

	int i = 1;
	while (1)
	{
		QString fileName;
		
		//�¹ʽ������·������
		if (Path[i] == NodeNum)
		{
			if(Path[i-1] == v1)
				fileName = QString("./Resources/") + QString::number(v1) + "-" + QString::number(v2) + QString(".txt");
			if(Path[i-1] == v2)
				fileName = QString("./Resources/") + QString::number(v2) + "-" + QString::number(v1) + QString(".txt");

			//qDebug() << fileName;
			QString Info = QString::number(longitude, 'f', 6) + "," + QString::number(latitude, 'f', 6);
			//qDebug() << Info;
			
			QFile file(fileName);
			if (file.open(QIODevice::ReadOnly | QIODevice::Text) != true)
			{
				qDebug() << "cannot open file." << endl;
			}
			else
			{
				while (!file.atEnd())
				{
					QString info = QString(file.readLine());
					//qDebug() << info;
					if (info != Info+"\n")
						s_text += QString(info);
					else
					{
						qDebug() << "Find it!";
						s_text += QString(Info);
						break;
					}	
				}
			}
		}
		//��ͨ·������
		else
		{
			fileName = QString("./Resources/") + QString::number(Path[i - 1]) + "-" + QString::number(Path[i]) + QString(".txt");
			//qDebug() << fileName;
			QFile file(fileName);
			if (file.open(QIODevice::ReadOnly | QIODevice::Text) != true)
			{
				qDebug() << "cannot open file." << endl;
			}
			else
			{
				s_text += QString(file.readAll());
			}
		}

		//ĩβ���з�����
		i++;
		if (Path[i] == -1)
			break;
		else
			s_text += QString("\n");
	}

	//qDebug() << s_text;
	return s_text;
}

void TerminalProject::Generator()
{
	//�����¹���Ϣ
	QString accidentInfo = arr[count];
	count = (++count) % (AccidentNum );
	qDebug() << count << "   " << AccidentNum;

	//�����¹���Ϣ
	QStringList list = accidentInfo.split(" ");
	double longitude = list[0].toDouble();
	double latitude = list[1].toDouble();
	int level = list[2].toInt();
	int v1 = list[3].toInt();		int v2 = list[5].toInt();
	double w1 = list[4].toDouble();	double w2 = list[6].toDouble();
	//qDebug() << fixed << qSetRealNumberPrecision(7) << longitude << fixed << qSetRealNumberPrecision(7) << latitude << level << v1 << w1 << v2 << w2;

	//����ͼ����
	Graph g;
	//����¹���Ϣ
	g.addAccident(longitude, latitude);
	g.addAccidentEdge(v1,w1,v2,w2);

	//��ȡ���·�������·��Ȩ��
	Node *path;
	path = g.SelectPath(g.getNodeNum() - 1, 2);
	double totalweight = path->getweight();

	//·������ת����
	int Path[100], i = 0;
	for (int i = 0; i <= 99; i++)
	{
		Path[i] = -1;
	}
	Node *cur = path->getnext();
	while (cur != nullptr)
	{
		Path[i] = cur->getcode();
		cur = cur->getnext();
		i++;
	}

	//����չʾ
	if (ui.action_switch->isChecked())
	{
		//showprocess��������дcloseevent����������һ���ź�
		//�˴����յ��źţ��ٴ�����Ϣ����ҳ
		ShowProcess *s = new ShowProcess();
		s->show();
		int Switch =0;
		//connect(s,&ShowProcess::closed,
		//	[=]()
		//{
		//	Switch = 1;
		//});
		ui.centralWidget->getdocument()->setText(getEdgeText(Path, g.getNodeNum() - 1, v1, v2, longitude, latitude)
			+ QString("\n") + QString::number(totalweight, 'f', 4) + QString(",") + QString::number(level));
	}
	else
	{
		ui.centralWidget->getdocument()->setText(getEdgeText(Path, g.getNodeNum() - 1, v1, v2, longitude, latitude)
			+ QString("\n") + QString::number(totalweight, 'f', 4) + QString(",") + QString::number(level));
	}
}
