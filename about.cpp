#include "about.hpp"
#include "ui_about.h"

#include <QDesktopServices>
#include <QUrl>

About::About(QWidget *parent) :
    QDialog(parent, Qt::WindowSystemMenuHint | Qt::WindowTitleHint),
    ui(new Ui::About)
{
    ui->setupUi(this);
    ui->lblVersion->setText("Version: " + QApplication::applicationVersion());
}

About::~About()
{
    delete ui;
}

void About::on_commandLinkButton_clicked()
{
    QDesktopServices::openUrl(QUrl("https://www.github.com/tsymalla/mindmap-editor", QUrl::TolerantMode));
}
