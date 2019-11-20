#include <QApplication>
#include "form.h"

void messageHandler(QtMsgType type, const QMessageLogContext& context, const QString& msg);

Form* form;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    form = new Form;

    qInstallMessageHandler(messageHandler);

    form->show();

    return a.exec();
}

void messageHandler(QtMsgType type, const QMessageLogContext& context, const QString& msg){
    form->messageHandler(type, context, msg);
}
