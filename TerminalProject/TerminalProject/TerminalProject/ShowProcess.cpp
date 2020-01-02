#include "ShowProcess.h"

ShowProcess::ShowProcess(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	fileread();
	//this->setAttribute(Qt::WA_TranslucentBackground);//���ô��ڱ���͸��
	//this->setWindowFlags(Qt::FramelessWindowHint);   //�����ޱ߿򴰿�
	ui.widget->installEventFilter(this);
	ui.textEdit->setPlainText("lalalalalalalalallalala");
}

ShowProcess::~ShowProcess()
{
}

void ShowProcess::fileread()
{
	QFile file("node.txt");
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
		return;
	else {
		QTextStream in(&file);
		int num;	//������
		in >> num;
		number = num;//�����
		v = new Node[num];	//������������
		if (v == nullptr)
			return;
		for (int i = 0; i < num; i++) {
			QString lo, la;
			double weight;
			int level;
			in >> lo >> la >> weight >> level;
			int longitude = lo.toDouble();
			int latitude = la.toDouble() - 80;
			v[i].setinfo(i, level, longitude, latitude, weight);//��������Ϣ
		}
		file.close();
	}
}

void ShowProcess::drawnode()
{
	QPainter painter(ui.widget);
	//���ƽ��
	for (int i = 0; i < number; i++) {
		//ָ������
		QPen pen(QColor(85, 85, 0));
		//���ñʿ�
		pen.setWidth(2);
		painter.setPen(pen);
		//painter.setPen(QColor(Qt::black));
		painter.setPen(pen);
		painter.setBrush(QBrush(Qt::lightGray));
		if (v[i].gettype() == 1) {
			//1�Ž��
			painter.setBrush(QBrush(Qt::green));
		}
		if (v[i].gettype() == 2) {
			//2�Ž��
			painter.setBrush(QBrush(Qt::red));
		}
		painter.drawEllipse(v[i].getlongitude(), v[i].getlatitude(), 20, 20);
		painter.drawText(v[i].getlongitude() + 2, v[i].getlatitude() + 14, QString::number(i));
	}

}

void ShowProcess::drawline()
{
	QPainter painter(ui.widget);
	QFile file1("EdgeData.txt");
	if (!file1.open(QIODevice::ReadOnly | QIODevice::Text))
		return;
	else {
		QTextStream in(&file1);
		int num;	//������
		in >> num;
		//���֮������
		for (int i = 0; i < num; i++) {
			QBrush brush = QBrush();
			brush.setColor(Qt::white);
			brush.setStyle(Qt::SolidPattern);
			painter.setBrush(brush);
			int v1, v2;
			double weight;
			in >> v1 >> v2 >> weight;
			//ָ������
			QPen pen(QColor(0, 0, 0));
			//���ñʿ�
			pen.setWidth(2);
			painter.setPen(pen);
			//painter.setPen(QColor(Qt::black));
			/*if (flag == 2) {
				painter.setPen(QColor(0x00, 0xff, 0x00, 0x00));//��ɫ
			}*/

			painter.drawLine(v[v1].getlongitude() + 5, v[v1].getlatitude() + 5, v[v2].getlongitude() + 5, v[v2].getlatitude() + 5);
			painter.drawText((v[v1].getlongitude() + v[v2].getlongitude()) / 2, (v[v1].getlatitude() + v[v2].getlatitude()) / 2, QString::number(weight));
		}
	}
	file1.close();
}

void ShowProcess::drawroad(int cur, int next, int num, float length)
{
	int x1 = v[cur].getlongitude() + 5;
	int y1 = v[cur].getlatitude() + 5;
	int x2 = v[cur].getlongitude() + (v[next].getlongitude() - v[cur].getlongitude())*0.7 + 5;
	int y2 = v[cur].getlatitude() + (v[next].getlatitude() - v[cur].getlatitude())*0.7 + 5;
	float l = 10.0;
	float a = 0.5;
	float x3 = x2 - l * cos(atan2((y2 - y1), (x2 - x1)) - a);
	float y3 = y2 - l * sin(atan2((y2 - y1), (x2 - x1)) - a);
	float x4 = x2 - l * sin(atan2((x2 - x1), (y2 - y1)) - a);
	float y4 = y2 - l * cos(atan2((x2 - x1), (y2 - y1)) - a);

	QPainter painter(ui.widget);
	if (num == 1) {
		//ָ������
		QPen pen(QColor(85, 170, 255));
		//���ñʿ�
		pen.setWidth(3);
		painter.setPen(pen);
		painter.drawLine(x2, y2, x3, y3);
		painter.drawLine(x2, y2, x4, y4);
		painter.drawLine(x1, y1, x2, y2);
	}
	if (num == 2) {
		//ָ������
		QPen pen(QColor(255, 0, 0));
		//���ñʿ�
		pen.setWidth(3);
		painter.setPen(pen);
		//painter.setPen(QColor(Qt::red));
		painter.drawLine(x2, y2, x3, y3);
		painter.drawLine(x2, y2, x4, y4);
		painter.drawLine(x1, y1, x2, y2);
		painter.drawLine(x1, y1, v[next].getlongitude() + 5, v[next].getlatitude() + 5);
	}
}

void ShowProcess::closeEvent(QCloseEvent * event)
{
	emit closed();
}

void ShowProcess::getPath(Node *a)
{
	path = a;
}

bool ShowProcess::eventFilter(QObject *watched, QEvent *event)
{
	if (watched == ui.widget && event->type() == QEvent::Paint)
		paintEvent();
	return QWidget::eventFilter(watched, event);
}

void ShowProcess::paintEvent()
{
	drawline();
	drawnode();

	Node *p = path;

	/*int path_node[100];
	int k = 0;
	p = p->getnext();
	while (p != nullptr) {
		path_node[k] = p->getcode();
		k++;
		p = p->getnext();
	}k--;
	for (int i = 0; i < k; i++) {
		drawroad(path_node[i], path_node[i + 1], 2, 0.9);
	}*/
}

void ShowProcess::on_pushButton_clicked()
{
	close();
}