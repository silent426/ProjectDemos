#ifndef MATERIALMANAGEDIALOG_H
#define MATERIALMANAGEDIALOG_H

#include <QDialog>
#include <QDebug>
#include <QMap>
#include <QString>
#include <QVariant>

class UiFace;

namespace Ui {
class MaterialManageDialog;
}

class MaterialManageDialog : public QDialog
{
    Q_OBJECT

public:
	explicit MaterialManageDialog(UiFace* uiface,  QWidget *parent = nullptr);
    ~MaterialManageDialog();

private slots:
    void on_pushButton_11_clicked();
	void on_binThreshold_Btn_clicked();

	void on_binThreshold_spinBox_editingFinished();

	void on_completeSet_Btn_clicked();

private:
    Ui::MaterialManageDialog *ui;
	UiFace* m_uiface;
	QMap<QString, QVariant> map;

};

#endif // MATERIALMANAGEDIALOG_H
