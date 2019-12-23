#include "TerminalProject.h"

#include <QtWebEngineWidgets/QWebEngineView>
#include <QtWebEngineWidgets/QWebEnginePage>
#include <QtWebEngineWidgets/QWebEngineSettings>

TerminalProject::TerminalProject(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
}

TerminalProject::~TerminalProject()
{
	//delete ui;
}

void TerminalProject::fileread()
{
	QPainter painter(this);

	QFile file("NodeData.txt");
	int number;
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
		return;
	else {
		QTextStream in(&file);
		int num;	//结点个数
		in >> num;
		number = num;
		v = new Node[num];	//创建顶点数组
		if (v == nullptr)
			return;
		for (int i = 0; i < num; i++) {
			QString lo, la;
			double weight;
			int level;
			in >> lo >> la >> weight >> level;
			string o = lo.toStdString();
			string a = la.toStdString();
			double longitude = 0;
			double latitude = 0;
			for (int j = 0; j < lo.size(); j++) {
				if (o[j] != '0' && o[j] != '.') {
					longitude = longitude * 10 + (o[j] - '0');
				}
				if (a[j] != '0' && a[j] != '.') {
					latitude = latitude * 10 + (a[j] - '0');
				}
			}
			longitude = int(longitude) % 1080;
			latitude = int(latitude) % 960;
			v[i].setinfo(i, level, longitude, latitude, weight);
		}
		file.close();
	}
	QFile file1("EdgeData.txt");
	if (!file1.open(QIODevice::ReadOnly | QIODevice::Text))
		return;
	else {
		QTextStream in(&file1);
		int num;	//边条数
		in >> num;
		for (int i = 0; i < num; i++) {
			QBrush brush = QBrush();
			brush.setColor(Qt::black);
			brush.setStyle(Qt::SolidPattern);
			painter.setBrush(brush);
			int v1, v2;
			double weight;
			in >> v1 >> v2 >> weight;
			painter.drawLine(v[v1].getlongitude() + 5, v[v1].getlatitude() + 5, v[v2].getlongitude() + 5, v[v2].getlatitude() + 5);
			painter.drawText((v[v1].getlongitude() + v[v2].getlongitude()) / 2, (v[v1].getlatitude() + v[v2].getlatitude()) / 2, QString::number(weight));
		}
	}
	for (int i = 0; i < number; i++) {
		painter.setPen(QColor(Qt::blue));
		painter.setBrush(QBrush(Qt::gray));
		painter.drawEllipse(v[i].getlongitude(), v[i].getlatitude(), 20, 20);
		painter.drawText(v[i].getlongitude() + 5, v[i].getlatitude() + 14, QString::number(i));
		if (v[i].gettype() != 0) {
			painter.setPen(QColor(Qt::red));
			painter.drawText(v[i].getlongitude(), v[i].getlatitude(), QString::number(v[i].gettype()));
		}
	}

}

void TerminalProject::drawroad(int cur, int next, int num)
{
	double x1 = v[cur].getlongitude() + 5;
	double y1 = v[cur].getlatitude() + 5;
	double x2 = v[cur].getlongitude() + (v[next].getlongitude() - v[cur].getlongitude())*0.7 + 5;
	double y2 = v[cur].getlatitude() + (v[next].getlatitude() - v[cur].getlatitude())*0.7 + 5;
	float l = 10.0;
	float a = 0.5;
	float x3 = x2 - l * cos(atan2((y2 - y1), (x2 - x1)) - a);
	float y3 = y2 - l * sin(atan2((y2 - y1), (x2 - x1)) - a);
	float x4 = x2 - l * sin(atan2((x2 - x1), (y2 - y1)) - a);
	float y4 = y2 - l * cos(atan2((x2 - x1), (y2 - y1)) - a);
	QPainter painter(this);
	if (num == 1) {
		painter.setPen(QColor(Qt::blue));
		painter.drawLine(x2, y2, x3, y3);
		painter.drawLine(x2, y2, x4, y4);
		painter.drawLine(x1, y1, x2, y2);
		//painter.drawLine(x1, y1, v[next].getlongitude(), v[next].getlatitude());
	}
	if (num == 2) {
		painter.setPen(QColor(Qt::green));
		painter.drawLine(x2, y2, x3, y3);
		painter.drawLine(x2, y2, x4, y4);
		painter.drawLine(x1, y1, x2, y2);
		painter.drawLine(x1, y1, v[next].getlongitude() + 5, v[next].getlatitude() + 5);
	}
	//painter.setPen(QColor(Qt::red));
	//painter.drawLine(x2, y2, x3, y3);
	//painter.drawLine(x2, y2, x4, y4);
	//painter.drawLine(x1, y1, x2, y2);
}

void TerminalProject::random_node()
{
	Graph g;
	Node *path;

	path = g.SelectPath(0, 2);

	int a[500][2], n;
	g.getpath(a, n);
	for (int i = 0; i < n; i++) {
		drawroad(a[i][0], a[i][1], 1);
	}

	int path_node[100];
	int k = 0;
	path = path->getnext();
	while (path != nullptr) {
		path_node[k] = path->getcode();
		k++;
		path = path->getnext();
	}k--;
	for (k; k > 0; k--) {
		drawroad(path_node[k], path_node[k - 1], 2);
	}
}


void TerminalProject::paintEvent(QPaintEvent *)
{
	fileread();
	random_node();

	/*QPainter painter(this);
	static double wid = rect().width();
	static double hei = rect().height();

	painter.setRenderHints(QPainter::Antialiasing, true);//抗锯齿

	double new_wid = rect().width() / wid;
	double new_hei = rect().height() / hei;
	painter.scale(new_wid, new_hei);
	double min = qMin(new_wid, new_hei);
	painter.scale(min, min);*/
}
