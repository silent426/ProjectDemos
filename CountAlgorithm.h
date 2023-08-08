#pragma once
#include <QString>
#include <QVariant>
#include <QDebug>
#include <QMap>
#include "CountBase.h"
#include <QMainWindow>
#include <HalconCpp.h>
using namespace HalconCpp;
class UiFace;


class CountAlgorithm :
	public CountBase
{
public:
	CountAlgorithm();
	~CountAlgorithm();
	//  子类的
	virtual QString getName() const override;
	void listenMessage(const QString &mes, QVariant &data);
	int countStart(const QImage& image);

	// QImage HImage类型转换
	HObject QImage2HObject(QImage qimage);

    void DoStart();
	void completeSet(QVariant &data);

private:
	QString countName;
	QMap<QString, QVariant> qmap;
	HTuple ho_Width, ho_Height;
	HTuple ho_WindowID;
	HObject ho_image;

	HObject ho_LightRegion;
	HObject ho_Region;
	HObject ho_RegionErosion;
	HObject ho_RegionDilation;
	HObject ho_ConnectionRegions;
	HObject ho_SelectedRegions;
	HObject ho_objectSelected;

	HObject ho_SelectedRegions1;

	HTuple ho_UsedThreshold;

	HTuple ho_blobNumber;
	HTuple ho_Number1;
	HTuple ho_Number2;
	HTuple ho_Number3;
	HTuple ho_objectArea;
	HTuple ho_objectRow;
	HTuple ho_objectCol;

	HTuple ho_totalNumber;
	HTuple ho_BnMin, ho_BnMax;
	HTuple ho_SingleMin, ho_SingleMax;
};

