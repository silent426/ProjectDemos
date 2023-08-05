#include "CountBase.h"

#include "CountBaseManage.h"

CountBase::CountBase()
{
	// 父类构造函数初始化时，把所有
	CountBaseManage::getInstance()->addCountBase(this);
}


CountBase::~CountBase()
{

}
void CountBase::notify(QString name, const QString &mes, QVariant &data)
{
	CountBaseManage::getInstance()->Notify(name, mes, data);
}

