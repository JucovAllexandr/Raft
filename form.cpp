#include "form.h"
#include "ui_form.h"

Form::Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form)
{
    ui->setupUi(this);
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

}

void Form::on_pushButton_connect_clicked()
{
    QString port = ui->lineEdit_connect->text();
    QRemoteObjectNode *repNode = new QRemoteObjectNode();
    repNode->connectToNode(QUrl("tcp://127.0.0.1:"+port));

    RaftReplica *rp = new RaftReplica();
    rp->setId(port);

    connect(repNode->acquire<RaftProtocolReplica>(), &RaftProtocolReplica::RequestVote, rp, &RaftReplica::showId);
}

void Form::on_pushButton_send_clicked()
{
    emit raftSource.RequestVote(port);
}
