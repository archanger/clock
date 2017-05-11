#include "preference.hpp"
#include "ui_preference.h"

#include <QSettings>

Preference::Preference(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::Preference)
{
  ui->setupUi(this);
  adjustSize();
  setFixedSize(frameSize());

  QSettings  settings;
  ui->colorBox->setCurrentIndex(settings.value("Color").toInt());

  connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &Preference::onAccepted);
}

Preference::~Preference()
{
  delete ui;
}

void Preference::onAccepted()
{
  QSettings  settings;
  settings.setValue("Color", ui->colorBox->currentIndex());
}
