#include "ShowProcess.h"
ShowProcess::ShowProcess(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	fileread();
	this->setAttribute(Qt::WA_TranslucentBackground);//设置窗口背景透明
	this->setWindowFlags(Qt::FramelessWindowHint);   //设置无边框窗口
	ui.frame->installEventFilter(this);
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
		int num;	//结点个数
		in >> num;
		number = num;//结点数
		v = new Node[num];	//创建顶点数组
		if (v == nullptr)
			return;
		for (int i = 0; i < num; i++) {
			QString lo, la;
			double weight;
			int level;
			in >> lo >> la >> weight >> level;
			int longitude = lo.toDouble();
			int latitude = la.toDouble() - 80;
			v[i].setinfo(i, level, longitude, latitude, weight);//保存结点信息
		}
		file.close();
	}
}

void ShowProcess::drawnode()
{
	QPainter painter(ui.frame);
	//绘制结点
	for (int i = 0; i < number; i++) {
		//指定画笔
		QPen pen(QColor(85, 85, 0));
		//设置笔宽
		pen.setWidth(2);
		painter.setPen(pen);
		//painter.setPen(QColor(Qt::black));
		painter.setPen(pen);
		painter.setBrush(QBrush(Qt::gray));
		if (v[i].gettype() == 1) {
			//1号结点
			painter.setBrush(QBrush(Qt::green));
		}
		if (v[i].gettype() == 2) {
			//2号结点
			painter.setBrush(QBrush(Qt::red));
		}
		painter.drawEllipse(v[i].getlongitude(), v[i].getlatitude(), 20, 20);
		painter.drawText(v[i].getlongitude() + 2, v[i].getlatitude() + 14, QString::number(i));
	}
}

void ShowProcess::drawline()
{
	QPainter painter(ui.frame);
	QFile file1("EdgeData.txt");
	if (!file1.open(QIODevice::ReadOnly | QIODevice::Text))
		return;
	else {
		QTextStream in(&file1);
		int num;	//边条数
		in >> num;
		//结点之间连线
		for (int i = 0; i < num; i++) {
			QBrush brush = QBrush();
			brush.setColor(Qt::white);
			brush.setStyle(Qt::SolidPattern);
			painter.setBrush(brush);
			int v1, v2;
			double weight;
			in >> v1 >> v2 >> weight;
			//指定画笔
			QPen pen(QColor(0, 0, 0));
			//设置笔宽
			pen.setWidth(2);
			painter.setPen(pen);
			//painter.setPen(QColor(Qt::black));
			/*if (flag == 2) {
				painter.setPen(QColor(0x00, 0xff, 0x00, 0x00));//无色
			}*/

			painter.drawLine(v[v1].getlongitude() + 5, v[v1].getlatitude() + 5, v[v2].getlongitude() + 5, v[v2].getlatitude() + 5);
			painter.drawText((v[v1].getlongitude() + v[v2].getlongitude()) / 2, (v[v1].getlatitude() + v[v2].getlatitude()) / 2, QString::number(weight));
		}
	}
	file1.close();
}

void ShowProcess::random_node()
{
	for (int i = 0; i < current_path; i++) {
		if (parent[i][0] >= 0 && parent[i][0] <= 56 && parent[i][1] >= 0 && parent[i][1] <= 56) {
			drawroad(parent[i][0], parent[i][1], 1);
		}
	}
	Node *p = path;
	int path_node[100];
	int k = 0;
	p = p->getnext();
	while (p->getnext() != nullptr) {
		path_node[k] = p->getcode();
		k++;
		p = p->getnext();
	}k--;
	for (int i = 0; i < k; i++) {
		drawroad(path_node[i], path_node[i + 1], 2);
	}

	if (v1.getcode() == v[path_node[k]].getcode()) {
		drawroad(v1.getcode(), v2.getcode(), 3);
	}
	if (v2.getcode() == v[path_node[k]].getcode()) {
		drawroad(v2.getcode(), v1.getcode(), 3);
	}
}

void ShowProcess::drawroad(int cur, int next, int num)
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

	QPainter painter(ui.frame);
	if (num == 1) {
		//指定画笔
		QPen pen(QColor(85, 170, 255));
		//设置笔宽
		pen.setWidth(3);
		painter.setPen(pen);
		painter.drawLine(x2, y2, x3, y3);
		painter.drawLine(x2, y2, x4, y4);
		painter.drawLine(x1, y1, x2, y2);
	}
	if (num == 2) {
		//指定画笔
		QPen pen(QColor(255, 0, 0));
		//设置笔宽
		pen.setWidth(3);
		painter.setPen(pen);
		//painter.setPen(QColor(Qt::red));
		painter.drawLine(x2, y2, x3, y3);
		painter.drawLine(x2, y2, x4, y4);
		painter.drawLine(x1, y1, x2, y2);
		painter.drawLine(x1, y1, v[next].getlongitude() + 5, v[next].getlatitude() + 5);
	}
	if (num == 3) {
		int x2 = v[cur].getlongitude() + (v[next].getlongitude() - v[cur].getlongitude())*0.4 + 5;
		int y2 = v[cur].getlatitude() + (v[next].getlatitude() - v[cur].getlatitude())*0.4 + 5;
		int x5 = v[cur].getlongitude() + (v[next].getlongitude() - v[cur].getlongitude())*0.3 + 5;
		int y5 = v[cur].getlatitude() + (v[next].getlatitude() - v[cur].getlatitude())*0.3 + 5;
		float l = 10.0;
		float a = 0.5;
		float x3 = x5 - l * cos(atan2((y5 - y1), (x5 - x1)) - a);
		float y3 = y5 - l * sin(atan2((y5 - y1), (x5 - x1)) - a);
		float x4 = x5 - l * sin(atan2((x5 - x1), (y5 - y1)) - a);
		float y4 = y5 - l * cos(atan2((x5 - x1), (y5 - y1)) - a);
		//指定画笔
		QPen pen(QColor(255, 0, 0));
		painter.setBrush(QBrush(Qt::yellow));
		//设置笔宽
		pen.setWidth(3);
		painter.setPen(pen);

		painter.drawLine(x5, y5, x3, y3);
		painter.drawLine(x5, y5, x4, y4);
		painter.drawLine(x1, y1, x5, y5);
		painter.setPen(QColor(0, 0, 0));
		painter.drawEllipse(x2 - 5, y2 - 5, 10, 10);

	}
}

void ShowProcess::getPath(Node *a)
{
	path = a;
}

bool ShowProcess::eventFilter(QObject *watched, QEvent *event)
{
	if (watched == ui.frame && event->type() == QEvent::Paint)
		paintEvent();
	return QWidget::eventFilter(watched, event);
}

void ShowProcess::getParent(int a[][2], int n)
{
	current_path = n;
	for (int i = 0; i < n; i++) {
		parent[i][0] = a[i][0];
		parent[i][1] = a[i][1];
	}
}

void ShowProcess::paintEvent()
{
	drawline();
	random_node();
	drawnode();
	//animation();
}

void ShowProcess::getNodes(int n1, int n2)
{
	v1 = v[n1];
	v2 = v[n2];
}

void ShowProcess::on_pushButton_clicked()
{
	close();
}

//动画演示
void ShowProcess::animation()
{
	//还原
	ui.xun->setGeometry(120, 20, 31, 31);
	ui.jiu->setGeometry(120, 60, 31, 31);
	ui.heart->setGeometry(160, 60, 31, 31);
	QSequentialAnimationGroup *animationgroup = new QSequentialAnimationGroup;
	ui.textEdit->clear();//清空textedit

	//把寻路过程加入动画组
	for (int i = 0; i < current_path; i++) {
		if (parent[i][0] >= 0 && parent[i][0] <= 56 && parent[i][1] >= 0 && parent[i][1] <= 56) {
			QPropertyAnimation *d = new QPropertyAnimation(ui.xun, "geometry");
			d->setDuration(100);//设置速度
			d->setStartValue(QRect(v[parent[i][0]].getlongitude(), v[parent[i][0]].getlatitude(), 30, 30));
			d->setEndValue(QRect(v[parent[i][1]].getlongitude(), v[parent[i][1]].getlatitude(), 30, 30));
			d->setEasingCurve(QEasingCurve::Linear);
			animationgroup->addAnimation(d);
		}
	}

	//获取最短路径
	Node *p = path->getnext();
	QString s = "救援最短路径：\n";
	int path_node[100];
	int k = 0;

	while (p->getnext() != nullptr) {
		path_node[k] = p->getcode();
		s = s + QString::number(path_node[k]);
		if (p->getnext() != nullptr) {
			s = s + "--->";
		}
		k++;
		p = p->getnext();
	}k--;
	s = s + "事故点\n";

	//把最短路径加入动画组
	for (int i = 0; i < k; i++) {
		QPropertyAnimation *d = new QPropertyAnimation(ui.jiu, "geometry");
		d->setDuration(100);//设置速度
		d->setStartValue(QRect(v[path_node[i]].getlongitude(), v[path_node[i]].getlatitude(), 30, 30));
		d->setEndValue(QRect(v[path_node[i + 1]].getlongitude(), v[path_node[i + 1]].getlatitude(), 30, 30));
		d->setEasingCurve(QEasingCurve::Linear);
		animationgroup->addAnimation(d);
	}

	//动画添加到事故点
	QPropertyAnimation *d = new QPropertyAnimation(ui.jiu, "geometry");
	d->setDuration(1000);//设置速度
	d->setStartValue(QRect(v[path_node[k]].getlongitude(), v[path_node[k]].getlatitude(), 30, 30));
	//int x1 = v[path_node[k]].getlongitude() + (v2.getlongitude() - v1.getlongitude())*0.4;//事故点经度
	//int y1 = v[path_node[k]].getlatitude() + (v2.getlatitude() - v1.getlatitude())*0.4;//事故点纬度
	int x1, y1;//事故点经度,事故点纬度
	if (v1.getcode() == v[path_node[k]].getcode()) {
		x1 = v[path_node[k]].getlongitude() + (v2.getlongitude() - v1.getlongitude())*0.4;//事故点经度
		y1 = v[path_node[k]].getlatitude() + (v2.getlatitude() - v1.getlatitude())*0.4;//事故点纬度
	}
	else {
		x1 = v[path_node[k]].getlongitude() + (v1.getlongitude() - v2.getlongitude())*0.4;//事故点经度
		y1 = v[path_node[k]].getlatitude() + (v1.getlatitude() - v2.getlatitude())*0.4;//事故点纬度
	}
	d->setEndValue(QRect(x1, y1, 30, 30));
	d->setEasingCurve(QEasingCurve::Linear);
	animationgroup->addAnimation(d);

	for (int i = 0; i < 12; i++) {
		QPropertyAnimation *d = new QPropertyAnimation(ui.heart, "geometry");
		d->setDuration(500);//设置速度
		if (i % 3 == 0) {
			d->setStartValue(QRect(750, 70, 140, 140));
			d->setEndValue(QRect(750, 70, 170, 170));
		}
		if (1 % 3 == 1) {
			d->setStartValue(QRect(750, 70, 170, 170));
			d->setEndValue(QRect(750, 70, 140, 140));
		}
		else {
			d->setStartValue(QRect(750, 70, 140, 140));
			d->setEndValue(QRect(750, 70, 110, 110));
		}
		d->setEasingCurve(QEasingCurve::InCubic);
		animationgroup->addAnimation(d);
	}

	animationgroup->start();
	ui.chick->setStyleSheet("border-image: url(:/pic/img/19.ico);");
	QPropertyAnimation *d1 = new QPropertyAnimation(ui.chick, "geometry");
	d1->setDuration(10000);//设置速度
	d1->setStartValue(QRect(1550, 380, 16, 16));
	d1->setEndValue(QRect(1840, 300, 32, 31));
	d1->setEasingCurve(QEasingCurve::InCubic);
	d1->start();

	ui.chick1->setStyleSheet("border-image: url(:/pic/img/19.ico);");
	QPropertyAnimation *d2 = new QPropertyAnimation(ui.chick1, "geometry");
	d2->setDuration(10000);//设置速度
	d2->setStartValue(QRect(1550, 380, 16, 16));
	d2->setEndValue(QRect(1840, 460, 31, 31));
	d2->setEasingCurve(QEasingCurve::InCubic);
	d2->start();

	s = s + "total_weight：" + QString::number(total_weight);
	ui.textEdit->setPlainText(s);
}

void ShowProcess::getLevel(int x)
{
	level = x;
	ui.lineEdit->setText(QString::number(level));
}

void ShowProcess::gettotal_widget(double value)
{
	total_weight = value;
}

void ShowProcess::closeEvent(QCloseEvent * event)
{
	emit closed();
}