/********************************************************************
	文件名：PrinterConfigWidget类
	日期  ：20161219
	作者  ：big-hippo
	功能  ：
*********************************************************************/

#ifndef PrinterConfigWidget_H__
#define PrinterConfigWidget_H__
#pragma once
#include <QWidget>
class QVBoxLayout;
class QGridLayout;
class QLabel;
class QSpinBox;
class QDoubleSpinBox;
class QGroupBox;
class QComboBox;

class PrinterConfigWidget :
	public QWidget
{
	Q_OBJECT

public:
	PrinterConfigWidget(QWidget* parent = 0);
	~PrinterConfigWidget();
	void InitWidgets();	//初始化控件
	void InitLayout();	//初始化布局


private:
	QVBoxLayout* printer_config_main_layout_;	//全局布局
	QGridLayout* bed_size_config_layout_;		//热床设置控件布局
	QGridLayout* firmware_config_layout_;	//固件设置控件布局
	
	//热床尺寸参数设置										
	QGroupBox* size_config_groupbox_;	

	//热床尺寸设置
	QLabel* bed_size_label_;	
	QSpinBox* size_x_spinbox_;
	QSpinBox* size_y_spinbox_;

	//热床坐标原点设置
	QLabel* origin_label_;	
	QDoubleSpinBox* origin_x_spinbox_;
	QDoubleSpinBox* origin_y_spinbox_;

	//打印机高度
	QLabel* printer_height_label_;	
	QSpinBox* printer_height_spinbox_;

	//竖直偏移量
	QLabel* z_offset_label_;	
	QDoubleSpinBox* z_offset_spinbox_;

	//设置固件参数
	QGroupBox* firmware_config_groupbox_;	

	//设置GCode类型
	QLabel* gcode_flavor_label_;	
	QComboBox* gcode_flavor_combobox_;

	//设置喷嘴半径
	QLabel* nozzle_diameter_label_;		
	QDoubleSpinBox* nozzle_diameter_spinbox_;

	//设置回抽长度
	QLabel* retract_length_label_;	
	QDoubleSpinBox* retract_length_spinbox_;	

	//回抽的高度
	QLabel* lift_z_label_;	
	QDoubleSpinBox* lift_z_spinbox_;

	//是否在回抽时移动喷头
	QLabel* wipe_retracting_label_;	
	QComboBox* wipe_retracting_combobox_;
};

#endif // PrinterConfigWidget_H__
