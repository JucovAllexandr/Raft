#ifndef FORM_H
#define FORM_H

#include <QtRemoteObjects>
#include <raftreplica.h>
#include <raftsource.h>

#include <QWidget>

namespace Ui {
class Form;
}

class Form : public QWidget
{
    Q_OBJECT
    QRemoteObjectHost src;
    RaftSource raftSource;
    QString port;
public:
    explicit Form(QWidget *parent = nullptr);
    void messageHandler(QtMsgType type, const QMessageLogContext&, const QString& msg);
    ~Form();

private slots:
    void on_pushButton_bind_clicked();

    void on_pushButton_connect_clicked();

    void on_pushButton_send_clicked();
    void changeRole(Role role);
private:
    Ui::Form *ui;
};

#endif // FORM_H
