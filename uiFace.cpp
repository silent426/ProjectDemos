#include "uiFace.h"
#include "CountBaseManage.h"
#include "mainwindow.h"
#include <HalconCpp.h>
using namespace HalconCpp;

UiFace::UiFace()
{
	countName = "uiface";
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
	
}

void UiFace::DoStart()
{
    qDebug() << "UIface ��ʼ����";
    notify("CountAlgorithm","start",QVariant());
	
	


}


