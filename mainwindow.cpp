#pragma execution_character_set("utf-8")  
#include "mainwindow.h"

#include "ui_mainwindow.h"
#include"materialmanagedialog.h"
#include "uiFace.h"
#include <HalconCpp.h>
#include <Halcon.h>
using namespace HalconCpp;


MainWindow::MainWindow(UiFace* uiface,QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_uiface = uiface;
	



}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_8_clicked()
{
    MaterialManageDialog* d = new MaterialManageDialog(this);
    d->exec();

}


void MainWindow::on_start_Btn_clicked()
{
    qDebug() << "槽函数触发开始运行";
    m_uiface->DoStart();

	// 读取一个图片显示出来
	Hlong winId = ui->image_widget->winId();
	ReadImage(&ho_image, "C:/Users/Public/Documents/MVTec/HALCON-19.11-Progress/examples/images/pellets.png");
	GetImageSize(ho_image, &ho_Width, &ho_Height);
	if (HDevWindowStack::IsOpen() == false)
	{
		OpenWindow(0, 0, ho_Width, ho_Height, winId, "visible", "black", &ho_WindowID);
		HDevWindowStack::Push(ho_WindowID);
		
	}
	if (HDevWindowStack::IsOpen)
	{
		DispObj(ho_image, HDevWindowStack::GetActive());
	}
	

	// 图像计数处理
	BinaryThreshold(ho_image, &ho_LightRegion, "max_separability", "light", &ho_UsedThreshold);
	OpeningCircle(ho_LightRegion, &ho_Region, 3);
	ErosionCircle(ho_Region, &ho_RegionErosion, 7);
	Connection(ho_RegionErosion, &ho_ConnectionRegions);
	DilationCircle(ho_ConnectionRegions, &ho_RegionDilation, 7.5);
	SelectShape(ho_RegionDilation, &ho_SelectedRegions, "area", "and", 600, 2000);
	CountObj(ho_SelectedRegions, &ho_Number1);

	SelectShape(ho_RegionDilation, &ho_SelectedRegions1, "area", "and", 2000, 5000);
	CountObj(ho_SelectedRegions1, &ho_Number2);
	ho_totalNumbers = ho_Number1 + ho_Number2 * 2;

	if (HDevWindowStack::IsOpen())
	{
		SetColor(HDevWindowStack::GetActive(), "red");
		DispObj(ho_RegionDilation, HDevWindowStack::GetActive());
		qDebug() << "一共" << ho_totalNumbers[0].I() << "个pellets";
		SetTposition(ho_WindowID, 12, 12);
		SetColor(ho_WindowID, "black");
		SetLineWidth(ho_WindowID, 3);
		WriteString(ho_WindowID, "检测到" + ho_totalNumbers + "个pellets");
	}
	ui->lcdNumber->setMode(QLCDNumber::Dec);
	ui->lcdNumber->setDigitCount(3);
	ui->lcdNumber->setSegmentStyle(QLCDNumber::Flat);
	ui->lcdNumber->display(ho_totalNumbers[0].I());


}

