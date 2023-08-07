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

int CountAlgorithm::QImageToHOjbect(QImage &image, HObject *Object)
{
	if (image.format() == QImage::Format_RGB888
		|| image.format() == QImage::Format_RGB32
		|| image.format() == QImage::Format_Indexed8)
	{

	}
	else
	{
		return -1;
	}
	int ret = 0;
	unsigned char  *image_red = nullptr;
	unsigned char  *image_green = nullptr;
	unsigned char  *image_blue = nullptr;
	int r, c;

	int w = image.width();
	int h = image.height();
	try
	{
		image_red = (unsigned char  *)malloc(w*h);
		if (image.format() == QImage::Format_RGB888
			|| image.format() == QImage::Format_RGB32)
		{
			image_green = (unsigned char  *)malloc(w*h);
			image_blue = (unsigned char  *)malloc(w*h);
		}
	}
	catch (...)
	{
		free(image_red);
		free(image_green);
		free(image_blue);
		return -1;
	}


	if (image.format() == QImage::Format_RGB888)
	{
		for (r = 0; r < h; r++)
		{
			uchar* pRow = image.scanLine(r);
			for (c = 0; c < w; c++)
			{
				image_red[r*w + c] = pRow[3 * c + 0];
				image_green[r*w + c] = pRow[3 * c + 1];
				image_blue[r*w + c] = pRow[3 * c + 2];
			}
		}
		GenImage3Extern(Object, "byte", w, h, (Hlong)image_red, (Hlong)image_green, (Hlong)image_blue, (Hlong)free);
		free(image_red); free(image_green); free(image_blue);

	}
	else if (image.format() == QImage::Format_RGB32)
	{
		for (r = 0; r < h; r++)
		{
			uchar* pRow = image.scanLine(r);
			for (c = 0; c < w; c++)
			{
				image_red[r*w + c] = pRow[4 * c + 2];
				image_green[r*w + c] = pRow[4 * c + 1];
				image_blue[r*w + c] = pRow[4 * c + 0];
			}
		}
		GenImage3Extern(Object, "byte", w, h, (Hlong)image_red, (Hlong)image_green, (Hlong)image_blue, (Hlong)free);
	}
	else if (image.format() == QImage::Format_Indexed8)
	{
		for (r = 0; r < h; r++)
		{
			uchar* pRow = image.scanLine(r);
			for (c = 0; c < w; c++)
			{
				image_red[r*w + c] = pRow[c];
				//image_red[r*w + c] = 0.30 * pBmp[3 * (c + r*w) + 0] + 0.59 * pBmp[3 * (c + r*w) + 1] + 0.11 *pBmp[3 * (c + r*w) + 2];
			}
		}
		GenImage1Extern(Object, "byte", w, h, (Hlong)image_red, (Hlong)free);
	}
	return ret;
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


