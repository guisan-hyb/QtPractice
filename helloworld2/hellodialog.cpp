#include "hellodialog.h"

HelloDialog::HelloDialog() : _ui(new Ui::Dialog()) {
    _ui->setupUi(this);
}

HelloDialog::~HelloDialog(){
    delete _ui;
}
