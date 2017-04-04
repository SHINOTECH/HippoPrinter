#pragma once
#include "qwidget.h"

class QGroupBox;
class QLabel;
class QSpinBox;
class QDoubleSpinBox;
class QGridLayout;
class QVBoxLayout;


class FilamentConfigWidget :
	public QWidget
{
	Q_OBJECT

public:
	FilamentConfigWidget(QWidget* parent = 0);
	~FilamentConfigWidget();

	void InitWidgets();		//初始化控件
	void InitLayout();		//初始化布局

private:
	
	QVBoxLayout* filacofig_main_layout_;		//控件整体布局
	QGridLayout* fila_config_layout_;	//耗材参数设置布局
	QGridLayout* temp_config_layout_;	//温度设置布局

	QGroupBox* fila_config_groupbox_;	//耗材设置
	QGroupBox* temp_config_groupbox_;		//温度设置

	//设置耗材半径
	QLabel* diameter_label_;
	QDoubleSpinBox* diameter_spinbox_;

	//喷头挤出系数
	QLabel* extru_multi_label_;
	QDoubleSpinBox* extru_multi_spinbox_;
	

	//喷头温度设置
	QLabel* extruder_temp_label_;
	QSpinBox* extruder_first_temp_spinbox_;
	QSpinBox* extruder_other_temp_spinbox_;

	//热床温度设置
	QLabel* bed_temp_label_;
	QSpinBox* bed_first_temp_spinbox_;
	QSpinBox* bed_other_temp_spinbox_;
};

