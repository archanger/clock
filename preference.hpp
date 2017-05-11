#ifndef PREFERENCE_HPP
#define PREFERENCE_HPP

#include <QDialog>

namespace Ui {
  class Preference;
}

class Preference : public QDialog
{
  Q_OBJECT

public:
  explicit Preference(QWidget *parent = nullptr);
  ~Preference();

private slots:
  void onAccepted();

private:
  Ui::Preference *ui;
};

#endif // PREFERENCE_HPP
