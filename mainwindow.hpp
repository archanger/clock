#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>

namespace Ui {
  class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

// QWidget interface
protected:
  void mouseReleaseEvent(QMouseEvent* event) override;
  void mousePressEvent(QMouseEvent* event) override;
  void mouseMoveEvent(QMouseEvent* event) override;
  void closeEvent(QCloseEvent* event) override;

private slots:
  void updateTime();
  void showContextmenu(const QPoint& position);
  void showPreference();

private:
  void setColor();

private:
  Ui::MainWindow *ui;
  QPoint _mousePosition;

};

#endif // MAINWINDOW_HPP
