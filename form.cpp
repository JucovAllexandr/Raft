#include "form.h"
#include "ui_form.h"
#include <helper.h>

Form::Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form)
{
    ui->setupUi(this);
    ui->label_role->setText(Helper::roleToString(raftSource.getRole()));
    ui->label_term->setNum(static_cast<int>(raftSource.getCurrentTerm()));
    ui->label_electionTimeout->setNum(static_cast<int>(raftSource.getElectionTimeout()));
    ui->tableWidget->setColumnCount(2);
    ui->tableWidget->setHorizontalHeaderLabels(QStringList()<<"Uuid"<<"Ip");
    connect(&raftSource, &RaftSource::roleChanged, this, &Form::changeRole);
    connect(&src, &QRemoteObjectHost::remoteObjectAdded, this, &Form::remoteObjectConnected);
}

void Form::messageHandler(QtMsgType type, const QMessageLogContext &, const QString &msg)
{
    switch (type) {
    case QtDebugMsg:
        ui->textEdit->append("Debug: "+msg);
        break;
    case QtInfoMsg:
        ui->textEdit->append("Info: "+msg);
        break;
    case QtFatalMsg:
        ui->textEdit->append("Fatal: "+msg);
        break;
    case QtWarningMsg:
        ui->textEdit->append("Warning: "+msg);
        break;
    case QtCriticalMsg:
        ui->textEdit->append("Critical: "+msg);
        break;
    }
}

Form::~Form()
{
    delete ui;
}

void Form::on_pushButton_bind_clicked()
{
    port = ui->lineEdit_bind->text();
    src.setHostUrl(QUrl("tcp://127.0.0.1:"+port));
    src.enableRemoting(&raftSource);
    ui->label_id->setText(raftSource.id().toString());

}

void Form::remoteObjectConnected(const QRemoteObjectSourceLocation &loc)
{
    qDebug()<<"RemoteObjectConnected "<<loc.first<<" "<<loc.second.hostUrl<<" "<<loc.second.typeName;
}

void Form::on_pushButton_connect_clicked()
{
    QString port = ui->lineEdit_connect->text();
    QRemoteObjectNode *repNode = new QRemoteObjectNode();
    repNode->connectToNode(QUrl("tcp://127.0.0.1:"+port));

    RaftReplica *rp = new RaftReplica(repNode->acquire<RaftProtocolReplica>(), &raftSource);

    QTableWidgetItem *newUuid = new QTableWidgetItem(rp->Id().toString());
    QTableWidgetItem *newIp = new QTableWidgetItem("tcp://127.0.0.1:"+port);

    ui->tableWidget->setRowCount(ui->tableWidget->rowCount() + 1);
    ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 0, newUuid);
    ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 1, newIp);
}

void Form::on_pushButton_send_clicked()
{
    //emit raftSource.RequestVote(port);
}

void Form::changeRole(Role role)
{
    ui->label_role->setText(Helper::roleToString(role));
}
