#include "CountBase.h"

#include "CountBaseManage.h"

CountBase::CountBase()
{
	// ���๹�캯����ʼ��ʱ��������
	CountBaseManage::getInstance()->addCountBase(this);
}


CountBase::~CountBase()
{

}
void CountBase::notify(QString name, const QString &mes, QVariant &data)
{
	CountBaseManage::getInstance()->Notify(name, mes, data);
}

