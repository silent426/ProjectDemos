
#include "materialmanagedialog.h"
#include "ui_materialmanagedialog.h"
#include "uiFace.h"

MaterialManageDialog::MaterialManageDialog(UiFace* uiface, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MaterialManageDialog)
{
    ui->setupUi(this);
	m_uiface = uiface;

	map.insert("binThreshold", 128);
	
	connect(ui->binThreshold_Btn, SIGNAL(clicked), this, SLOT(on_binThreshold_Btn_clicked()));
	connect(ui->binThreshold_spinBox, SIGNAL(editingFinished()), this, SLOT(on_binThreshold_spinBox_editingFinished()));

	connect(ui->completeSet_Btn, SIGNAL(clicked), this, SLOT(on_completeSet_Btn_clicked()));

}

MaterialManageDialog::~MaterialManageDialog()
{
    delete ui;
}

void MaterialManageDialog::on_pushButton_11_clicked()
{
    this->accept();
}

void MaterialManageDialog::on_binThreshold_Btn_clicked()
{
	qDebug() << "hello";

}
void MaterialManageDialog::on_binThreshold_spinBox_editingFinished()
{
	map["binThreshold"] = ui->binThreshold_spinBox->text().toInt();

}

void MaterialManageDialog::on_completeSet_Btn_clicked()
{
	qDebug() << "complete";

	m_uiface->completeSet(QVariant(map));
}



