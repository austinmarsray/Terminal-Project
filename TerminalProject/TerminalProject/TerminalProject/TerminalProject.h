#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_TerminalProject.h"

class TerminalProject : public QMainWindow
{
	Q_OBJECT

public:
	TerminalProject(QWidget *parent = Q_NULLPTR);
	~TerminalProject();

private:
	Ui::TerminalProjectClass ui;
};
