#pragma execution_character_set("utf-8") 

#include "CountAlgorithm.h"
#include "CountBaseManage.h"

CountAlgorithm::CountAlgorithm()
{
	countName = "CountAlgorithm";
}
CountAlgorithm::~CountAlgorithm()
{

}

QString CountAlgorithm::getName() const
{
	return countName;
}

void CountAlgorithm::listenMessage(const QString &mes, QVariant &data)
{
	if (mes == "start")
	{
		qDebug() << "CountAlgorithm ��Ӧ start��Ϣ";
		qDebug() << "��Ӧ��������" << data;
	}		
}

void CountAlgorithm::DoStart()
{

}


