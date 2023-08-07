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
	//BinaryThreshold(ho_image, &ho_LightRegion, "max_separability", "light", &ho_UsedThreshold);
	//OpeningCircle(ho_LightRegion, &ho_Region, 3);
	//ErosionCircle(ho_Region, &ho_RegionErosion, 7);
	//Connection(ho_RegionErosion, &ho_ConnectionRegions);
	//DilationCircle(ho_ConnectionRegions, &ho_RegionDilation, 7.5);
	//CountObj(ho_RegionDilation, &ho_blobNumber);
	//SelectShape(ho_RegionDilation, &ho_SelectedRegions, "area", "and", 600, 2000);
	//CountObj(ho_SelectedRegions, &ho_Number1);

	//SelectShape(ho_RegionDilation, &ho_SelectedRegions1, "area", "and", 2000, 5000);
	//CountObj(ho_SelectedRegions1, &ho_Number2);
	//ho_totalNumber = ho_Number1 + ho_Number2 * 2;
	//ho_totalNumber = 0;
	//int numbers = 0;
	//// 指定单体面积
	//ho_SingleMin = 1000;
	//ho_SingleMax = 1900;

	//for (int i = 1; i <= ho_blobNumber; i++)
	//{
	//	SelectObj(ho_RegionDilation, &ho_objectSelected, i);
	//	AreaCenter(ho_objectSelected, &ho_objectArea, &ho_objectRow, &ho_objectCol);
	//	
	//	ho_BnMin = ho_objectArea / ho_SingleMin;
	//	ho_BnMax = (ho_objectArea + ho_SingleMax) / ho_SingleMax;
	//	qDebug() <<"第"<< i <<"个斑块面积 "
	//			<< ho_objectArea[0].I()
	//			<<"\n最小值 " << ho_BnMin.I()
	//			<< "\n最大值 " <<ho_BnMax.I();
	//	/*
	//		选择分割方式
	//	*/
	//	// 第一种方式 面积估计法平均
	//	//ho_totalNumber[i] =(ho_BnMin + ho_BnMax) / 2;
	//	// 2 面积估计法偏小
	//	//ho_totalNumber[i] = ho_BnMin;
	//	// 3 面积估计法 偏大
	//	ho_totalNumber[i] = ho_BnMax;
	//	numbers = numbers + ho_totalNumber[i].I();
	//	qDebug() << "当前分割方式的计数为：" << numbers;
	//	// 在斑块位置显示  此时坐标不对 TODO
	//	//SetTposition(ho_WindowID, ho_objectRow, ho_objectRow);
	//	//WriteString(ho_WindowID, "hello");
	//	
	//}

	////int numbers = ho_totalNumber[0].I();
	//qDebug() << ho_totalNumber[0].I();
	//if (HDevWindowStack::IsOpen())
	//{
	//	SetColor(HDevWindowStack::GetActive(), "red");
	//	DispObj(ho_RegionDilation, HDevWindowStack::GetActive());
	//	//qDebug() << "一共" << ho_totalNumber[0].I() << "个pellets";
	//	SetTposition(ho_WindowID, 12, 12);
	//	SetColor(ho_WindowID, "black");
	//	SetLineWidth(ho_WindowID, 3);
	//	WriteString(ho_WindowID, "检测到" + ho_totalNumber + "个pellets");
	//}
	ui->lcdNumber->setMode(QLCDNumber::Dec);
	ui->lcdNumber->setDigitCount(3);
	ui->lcdNumber->setSegmentStyle(QLCDNumber::Flat);
	qDebug() << "返回计数值为：" << m_uiface->returnNumber();
	ui->lcdNumber->display(m_uiface->returnNumber());


}

