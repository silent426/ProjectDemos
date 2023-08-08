#pragma execution_character_set("utf-8") 

#include "CountAlgorithm.h"
#include "CountBaseManage.h"
#include <HalconCpp.h>
using namespace HalconCpp;

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
		qDebug() << "CountAlgorithm 响应 start消息";
		qDebug() << "响应的数据是" << data;
		QImage qimage = data.value<QImage>();
		notify("UiFace", "countNumber", QVariant::fromValue(countStart(qimage)));
	}
	if (mes == "completeSet")
	{
		//QMap<QString, int> qmap = .toMap();
		// 输出 
		completeSet(data);
		qDebug() << data.toMap().value("binThreshold").toInt();
		
		
	}

}

// QImage 转换成HObject

HObject CountAlgorithm::QImage2HObject(QImage qimage)
{
	HObject hv_image;
	int width = qimage.width();
	int height = qimage.height();
	QImage::Format format = qimage.format();
	if (format == QImage::Format_RGB32 ||
		format == QImage::Format_ARGB32 ||
		format == QImage::Format_ARGB32_Premultiplied)
	{
		GenImageInterleaved(&hv_image, (Hlong)qimage.bits(), "bgrx", qimage.width(), qimage.height(), 0, "byte", width, height, 0, 0, 8, 0);
	}
	else if (format == QImage::Format_RGB888)
	{
		GenImageInterleaved(&hv_image, (Hlong)qimage.bits(), "bgr", qimage.width(), qimage.height(), 0, "byte", width, height, 0, 0, 8, 0);
	}
	else if (format == QImage::Format_Grayscale8 || format == QImage::Format_Indexed8)
	{
		GenImage1(&hv_image, "byte", width, height, (Hlong)qimage.bits());
	}
	return hv_image;
}


int CountAlgorithm::countStart(const QImage& image)
{
	//QImage qimage = image;
	//QImageToHOjbect(qimage, &ho_image);
	ho_image = QImage2HObject(image);
	//ReadImage(&ho_image, "C:/Users/Public/Documents/MVTec/HALCON-19.11-Progress/examples/images/pellets.png");
	// 图像计数处理
	BinaryThreshold(ho_image, &ho_LightRegion, "max_separability", "light", &ho_UsedThreshold);
	OpeningCircle(ho_LightRegion, &ho_Region, 3);
	ErosionCircle(ho_Region, &ho_RegionErosion, 7);
	Connection(ho_RegionErosion, &ho_ConnectionRegions);
	DilationCircle(ho_ConnectionRegions, &ho_RegionDilation, 7.5);
	CountObj(ho_RegionDilation, &ho_blobNumber);

	//SelectShape(ho_RegionDilation, &ho_SelectedRegions, "area", "and", 600, 2000);
	//CountObj(ho_SelectedRegions, &ho_Number1);

	//SelectShape(ho_RegionDilation, &ho_SelectedRegions1, "area", "and", 2000, 5000);
	//CountObj(ho_SelectedRegions1, &ho_Number2);
	//ho_totalNumber = ho_Number1 + ho_Number2 * 2;
	ho_totalNumber = 0;
	int numbers = 0;
	// 指定单体面积
	ho_SingleMin = 1000;
	ho_SingleMax = 1900;

	for (int i = 1; i <= ho_blobNumber; i++)
	{
		SelectObj(ho_RegionDilation, &ho_objectSelected, i);
		AreaCenter(ho_objectSelected, &ho_objectArea, &ho_objectRow, &ho_objectCol);

		ho_BnMin = ho_objectArea / ho_SingleMin;
		ho_BnMax = (ho_objectArea + ho_SingleMax) / ho_SingleMax;
		qDebug() << "第" << i << "个斑块面积 "
			<< ho_objectArea[0].I()
			<< "\n最小值 " << ho_BnMin.I()
			<< "\n最大值 " << ho_BnMax.I();
		/*
			选择分割方式
		*/
		// 第一种方式 面积估计法平均
		//ho_totalNumber[i] =(ho_BnMin + ho_BnMax) / 2;
		// 2 面积估计法偏小
		//ho_totalNumber[i] = ho_BnMin;
		// 3 面积估计法 偏大
		ho_totalNumber[i] = ho_BnMax;
		numbers = numbers + ho_totalNumber[i].I();
		qDebug() << "当前分割方式的计数为：" << numbers;
		// 在斑块位置显示  此时坐标不对 TODO
		//SetTposition(ho_WindowID, ho_objectRow, ho_objectRow);
		//WriteString(ho_WindowID, "hello");

	}

	return numbers;
}
void CountAlgorithm::DoStart()
{

}

void CountAlgorithm::completeSet(QVariant &data)
{
	qmap["binThreshold"] = data.toMap().value("binThreshold").toInt();
	qDebug() << "CountAlgorithm completeSet " << qmap["binThreshold"].toInt();
}


