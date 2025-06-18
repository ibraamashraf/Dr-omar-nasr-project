#include "registerwindow.h"
#include "ui_registerwindow.h"
#include "mainwindow.h"
#include <QMessageBox>

RegisterWindow::RegisterWindow(QWidget *parent, UserManager* manager)
    : QDialog(parent), ui(new Ui::RegisterWindow), userManager(manager)
{
    ui->setupUi(this);
}

RegisterWindow::~RegisterWindow()
{
    delete ui;
}

void RegisterWindow::on_pushButton_register_clicked()
{
    QString username = ui->lineEdit_username->text();
    QString password = ui->lineEdit_password->text();

    if (username.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "خطأ", "كل الخانات مطلوبة");
        return;
    }

    if (userManager->registerUser(username, password)) {
        QMessageBox::information(this, "تم", "تم إنشاء الحساب بنجاح");
        this->close();
    } else {
        QMessageBox::warning(this, "خطأ", "اسم المستخدم موجود بالفعل");
    }
}

void RegisterWindow::on_pushButton_back_clicked()
{
    MainWindow *mainWin = new MainWindow(this); // ✅ FIX: only pass the parent
    mainWin->show();
    this->hide();
}
