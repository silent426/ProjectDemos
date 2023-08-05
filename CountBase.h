#pragma once
#include <QString>
#include <QVariant>

class CountBaseManage;
class CountBase
{
public:
	CountBase();
	~CountBase();

	// ��һ����Ϣת�������� ת����manage����崦��
	void notify(QString name, const QString &mes, QVariant &data);

	// ���麯�� ��const = 0  const Ϊ����������Ϊ������Ա�������������޸���ĳ�Ա������
	virtual QString getName() const = 0;
	// ���麯������ ���������ʵ�ּ�����Ϣ
	virtual void listenMessage(const QString &mes, QVariant &data) = 0;
};

