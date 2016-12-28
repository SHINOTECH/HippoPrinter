#include "FilamentConfigWidget.h"

#include <QGridLayout>
#include <QLabel>
#include <QSpinBox>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QDoubleSpinBox>
#include <QDebug>

//************************************************************************
// 日期：2016/12/26 
// 参数: QWidget * parent
// 返回: 
// 功能: 构造函数
//************************************************************************

FilamentConfigWidget::FilamentConfigWidget(QWidget* parent)
	:QWidget(parent)
{
	InitWidgets();
	InitLayout();
}

//************************************************************************
// 日期：2016/12/26 
// 返回: 
// 功能:析构函数
//************************************************************************

FilamentConfigWidget::~FilamentConfigWidget()
{
}

//TODO:参数初始化为之前设置的值
//************************************************************************
// 日期：2016/12/26 
// 返回: void
// 功能: 初始化控件
//************************************************************************

void FilamentConfigWidget::InitWidgets() {
	//初始化布局
	filacofig_main_layout_ = new QVBoxLayout();
	filacofig_main_layout_->setSpacing(30);
	fila_config_layout_ = new QGridLayout();
	fila_config_layout_->setSpacing(20);
	temp_config_layout_ = new QGridLayout();
	temp_config_layout_->setSpacing(20);

	//初始化分组
	fila_config_groupbox_ = new QGroupBox(QString::fromLocal8Bit("耗材设置"));
	temp_config_groupbox_ = new QGroupBox(QString::fromLocal8Bit("温度设置"));

	//初始化耗材半径设置
	diameter_label_ = new QLabel(QString::fromLocal8Bit("耗材半径："));
	diameter_spinbox_ = new QDoubleSpinBox();
	diameter_spinbox_->setRange(0, 3);
	diameter_spinbox_->setWrapping(false);
	diameter_spinbox_->setSuffix(QString::fromLocal8Bit("mm"));
	diameter_spinbox_->setSingleStep(0.01);
	diameter_spinbox_->setValue(1.75);	//默认值
	 
	//喷头挤出系数
	extru_multi_label_ = new QLabel(QString::fromLocal8Bit("喷头挤出系数："));
	extru_multi_spinbox_ = new QDoubleSpinBox();
	extru_multi_spinbox_->setRange(0.9, 1.1);
	extru_multi_spinbox_->setWrapping(false);
	extru_multi_spinbox_->setSingleStep(0.01);
	extru_multi_spinbox_->setValue(1);	//默认值

	//初始化喷头设置控件
	extruder_temp_label_ = new QLabel(QString::fromLocal8Bit("喷头温度设置:"));
	extruder_first_temp_spinbox_ = new QSpinBox();
	extruder_first_temp_spinbox_->setRange(0, 300);
	extruder_first_temp_spinbox_->setWrapping(false);
	extruder_first_temp_spinbox_->setSingleStep(1);
	extruder_first_temp_spinbox_->setPrefix(QString::fromLocal8Bit("第一层："));
	extruder_first_temp_spinbox_->setSuffix(QString::fromLocal8Bit("℃"));
	extruder_first_temp_spinbox_->setValue(205);	//默认值
	extruder_other_temp_spinbox_ = new QSpinBox();
	extruder_other_temp_spinbox_->setRange(0, 300);
	extruder_other_temp_spinbox_->setWrapping(false);
	extruder_other_temp_spinbox_->setSingleStep(1);
	extruder_other_temp_spinbox_->setPrefix(QString::fromLocal8Bit("其他层："));
	extruder_other_temp_spinbox_->setSuffix(QString::fromLocal8Bit("℃"));
	extruder_other_temp_spinbox_->setValue(205);	//默认值

	//初始化热床温度设置控件
	bed_temp_label_ = new QLabel(QString::fromLocal8Bit("热床温度:"));
	bed_first_temp_spinbox_ = new QSpinBox();
	bed_first_temp_spinbox_->setRange(0, 100);
	bed_first_temp_spinbox_->setWrapping(false);
	bed_first_temp_spinbox_->setSingleStep(1);
	bed_first_temp_spinbox_->setPrefix(QString::fromLocal8Bit("第一层："));
	bed_first_temp_spinbox_->setSuffix(QString::fromLocal8Bit("℃"));
	bed_first_temp_spinbox_->setValue(55);	//默认值
	bed_other_temp_spinbox_ = new QSpinBox();
	bed_other_temp_spinbox_->setRange(0, 100);
	bed_other_temp_spinbox_->setWrapping(false);
	bed_other_temp_spinbox_->setSingleStep(1);
	bed_other_temp_spinbox_->setPrefix(QString::fromLocal8Bit("其他层："));
	bed_other_temp_spinbox_->setSuffix(QString::fromLocal8Bit("℃"));
	bed_other_temp_spinbox_->setValue(55);	//默认值

}


//************************************************************************
// 日期：2016/12/26 
// 返回: void
// 功能: 初始化控件布局
//************************************************************************

void FilamentConfigWidget::InitLayout() {
	//初始化耗材参数设置控件的布局
	fila_config_layout_->addWidget(diameter_label_, 0, 0);
	fila_config_layout_->addWidget(diameter_spinbox_, 0, 1);
	fila_config_layout_->addWidget(extru_multi_label_, 1, 0);
	fila_config_layout_->addWidget(extru_multi_spinbox_, 1, 1);
	fila_config_groupbox_->setLayout(fila_config_layout_);

	//初始化温度参数设置控件的布局
	temp_config_layout_->addWidget(extruder_temp_label_, 0, 0);
	temp_config_layout_->addWidget(extruder_first_temp_spinbox_, 1, 0);
	temp_config_layout_->addWidget(extruder_other_temp_spinbox_, 1, 1);
	temp_config_layout_->addWidget(bed_temp_label_, 2, 0);
	temp_config_layout_->addWidget(bed_first_temp_spinbox_, 3, 0);
	temp_config_layout_->addWidget(bed_other_temp_spinbox_, 3, 1);
	temp_config_groupbox_->setLayout(temp_config_layout_);

	//初始化控件全局布局
	filacofig_main_layout_->addWidget(fila_config_groupbox_);
	filacofig_main_layout_->addWidget(temp_config_groupbox_);
	filacofig_main_layout_->addStretch(1);
	setLayout(filacofig_main_layout_);
}