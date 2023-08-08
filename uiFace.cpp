#include "uiFace.h"
#include "CountBaseManage.h"
#include "mainwindow.h"
#include <HalconCpp.h>
using namespace HalconCpp;

UiFace::UiFace()
{
	countName = "UiFace";
}
UiFace::~UiFace()
{

}

QString UiFace::getName() const
{
	return "UiFace";
}

void UiFace::listenMessage(const QString &mes, QVariant &data)
{
	if (mes == "countNumber")
	{
		qDebug() << "CountAlgorithm ��Ӧ start��Ϣ";
		qDebug() << "��Ӧ��������" << data;
	
		m_countnumber = data.toInt();
	}
}

void UiFace::DoStart()
{
    qDebug() << "UIface ��ʼ����";
	QImage qimage;
	qimage.load("C:/Users/Public/Documents/MVTec/HALCON-19.11-Progress/examples/images/pellets.png");

    notify("CountAlgorithm","start", QVariant::fromValue(qimage));


}

int UiFace::returnNumber()
{
	return m_countnumber;
}

void UiFace::completeSet(QVariant &var)
{
	notify("CountAlgorithm", "completeSet", var);
}


