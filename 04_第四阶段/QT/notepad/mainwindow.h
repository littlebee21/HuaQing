#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    // about
    void slotShowAboutDlg();
    // 打开文件
    void slotOpenDlg();
    // 查找对话框
    void slotShowFindDlg();

private:
    Ui::MainWindow *ui;
    // 文本内容
    QString m_strFileText;
};
#endif // MAINWINDOW_H
