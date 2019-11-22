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
    ui->timeEdit->setTime(QTime::currentTime());
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    connect(&raftSource, &RaftSource::roleChanged, this, &Form::changeRole);
    connect(&src, &QRemoteObjectHost::remoteObjectAdded, this, &Form::remoteObjectConnected);
    connect(&raftSource, &RaftSource::termChanged, this, &Form::changeTerm);
    //connect(&timer, &QTimer::timeout, this, &Form::run);
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
    repNode->setProperty("ip", "tcp://127.0.0.1:"+port);

    RaftReplica *rp = new RaftReplica(repNode->acquire<RaftProtocolReplica>(), &raftSource);
    connect(rp, &RaftReplica::connected, this, &Form::clientConnected);

    QTableWidgetItem *newUuid = new QTableWidgetItem(rp->sourceId().toString());
    QTableWidgetItem *newIp = new QTableWidgetItem("tcp://127.0.0.1:"+port);

    ui->tableWidget->setRowCount(ui->tableWidget->rowCount() + 1);
    ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 0, newUuid);
    ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 1, newIp);

    connections.push_back(QPair<QRemoteObjectNode*, RaftReplica*>(repNode, rp));
}

void Form::on_pushButton_send_clicked()
{
    qDebug()<<"Elapsed timer run";
    QElapsedTimer timer;
    QTime timeTo = ui->timeEdit->time();
    timer.start();
    int ms = 100;
    while(!timer.hasExpired(ms)){
        ms = QTime::currentTime().msecsTo(timeTo);
        if(ms < 0){
            break;
        }
    }
    run();
}

void Form::changeRole(Role role)
{
    ui->label_role->setText(Helper::roleToString(role));
}

void Form::changeTerm(uint term)
{
    ui->label_term->setNum(static_cast<int>(term));
}

void Form::clientConnected(RaftReplica *rp)
{
    for(auto i = connections.begin(); i != connections.end(); ++i){
        if(i->second == rp){
            for(int r = 0; r < ui->tableWidget->rowCount(); r++){
                if(ui->tableWidget->item(r, 1)->text().compare(i->first->property("ip").toString()) == 0){
                    ui->tableWidget->item(r, 0)->setText(rp->sourceId().toString());
                }
            }
        }
    }
}

void Form::run()
{
    raftSource.timerStart();
}

void Form::on_pushButton_clicked()
{
    raftSource.timerStop();
}
