#include "mainwindow.hpp"
#include "ui_mainwindow.h"

#include "preference.hpp"

#include <QTimer>
#include <QTime>
#include <QMouseEvent>
#include <QMenu>
#include <QAction>
#include <QSettings>

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  setWindowTitle("LSD Clock");
  setAttribute(Qt::WA_TranslucentBackground);
  setWindowFlags(Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint | windowFlags());

  adjustSize();

  QSettings settings;
  restoreGeometry(settings.value("MainGeometry").toByteArray());
  restoreState(settings.value("MainState").toByteArray());

  connect(this, &MainWindow::customContextMenuRequested, this, &MainWindow::showContextmenu);

  QTimer* timer = new QTimer{this};
  connect(timer, &QTimer::timeout, this, &MainWindow::updateTime);
  timer->start(1000);

  updateTime();
}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::updateTime()
{
  QTime currentTime = QTime::currentTime();
  QString currentTimeText = currentTime.toString("hh:mm");
  if (currentTime.second() % 2 == 0) {
    currentTimeText[2] = ' ';
  }
  ui->lcdNumber->display(currentTimeText);
}

void MainWindow::showContextmenu(const QPoint& position)
{
  QMenu contextMenu;
  contextMenu.addAction("Exit", this, &MainWindow::close);
  contextMenu.addAction("Preference", this, &MainWindow::showPreference);
  contextMenu.exec(mapToGlobal(position));
}

void MainWindow::showPreference()
{
  Preference* pref = new Preference{this};
  pref->exec();
  setColor();
}

void MainWindow::setColor()
{
  QSettings  settings;
  int i = settings.value("Color").toInt();
  QPalette c;
  switch (i) {
  case 0: //black
    c.setColor(QPalette::Foreground, Qt::black);
    break;
  case 1: //white
    c.setColor(QPalette::Foreground, Qt::white);
    break;
  case 2: //green
    c.setColor(QPalette::Foreground, Qt::green);
    break;
  case 3: //red
    c.setColor(QPalette::Foreground, Qt::red);
    break;
  default:
    break;
  }

  ui->lcdNumber->setPalette(c);
  update();
}


void MainWindow::mouseReleaseEvent(QMouseEvent* event)
{
  if (event->button() == Qt::RightButton) {
    emit customContextMenuRequested(event->pos());
  } else {
    QMainWindow::mouseReleaseEvent(event);
  }
}


void MainWindow::mousePressEvent(QMouseEvent* event)
{
  _mousePosition = event->pos();
}

void MainWindow::mouseMoveEvent(QMouseEvent* event)
{
  move(event->globalPos() - _mousePosition);
}


void MainWindow::closeEvent(QCloseEvent* event)
{
  QSettings settings;
  settings.setValue("MainGeometry", saveGeometry());
  settings.setValue("MainState", saveState());
  event->accept();
}
