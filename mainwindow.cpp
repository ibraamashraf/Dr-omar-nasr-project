#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "homewindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , userManager(new UserManager("users.json")) // Load user manager from JSON
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete userManager;
}

void MainWindow::on_loginButton_clicked()
{
    QString username = ui->usernameLineEdit->text().trimmed();
    QString password = ui->passwordLineEdit->text();

    // ✅ Input validation
    if (username.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "خطأ", "الرجاء إدخال اسم المستخدم وكلمة المرور");
        return;
    }

    // ✅ Use correct method name: authenticateUser
    if (userManager->authenticateUser(username, password)) {
        HomeWindow *home = new HomeWindow(this, userManager);
        home->show();
        this->hide();
    } else {
        QMessageBox::warning(this, "خطأ", "اسم المستخدم أو كلمة المرور غير صحيحة");
    }
}

void MainWindow::on_registerButton_clicked()
{
    QString username = ui->usernameLineEdit->text().trimmed();
    QString password = ui->passwordLineEdit->text();

    // ✅ Input validation
    if (username.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "خطأ", "الرجاء إدخال اسم المستخدم وكلمة المرور");
        return;
    }

    if (userManager->registerUser(username, password)) {
        QMessageBox::information(this, "تم", "تم تسجيل المستخدم بنجاح");
    } else {
        QMessageBox::warning(this, "خطأ", "اسم المستخدم مستخدم بالفعل");
    }
}
