﻿#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDebug>
#include <QVariant>
#include <QMainWindow>
#include "CountBase.h"
#include <HalconCpp.h>
using namespace HalconCpp;
class UiFace;


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(UiFace* uiface,QWidget *parent = nullptr);
    ~MainWindow();

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


private slots:
    void on_pushButton_8_clicked();


    void on_start_Btn_clicked();

private:
    Ui::MainWindow *ui;
    UiFace* m_uiface;


};
#endif // MAINWINDOW_H
