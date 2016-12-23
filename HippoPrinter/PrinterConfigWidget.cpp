#include "PrinterConfigWidget.h"

#include <QVBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QGroupBox>
#include <QComboBox>

PrinterConfigWidget::PrinterConfigWidget(QWidget* parent)
	:QWidget(parent){
	InitWidgets();	//初始化控件
	InitLayout();	//初始化布局 
}


PrinterConfigWidget::~PrinterConfigWidget(){
}

//初始化控件
void PrinterConfigWidget::InitWidgets() {
	//初始化布局
	printer_config_main_layout_ = new QVBoxLayout();
	printer_config_main_layout_->setSpacing(30);
	bed_size_config_layout_ = new QGridLayout();
	bed_size_config_layout_->setSpacing(20);
	firmware_config_layout_ = new QGridLayout();
	firmware_config_layout_->setSpacing(20);

	//设置热床参数
	size_config_groupbox_ = new QGroupBox(QString::fromLocal8Bit("热床参数设置："));

	//热床尺寸设置
	bed_size_label_ = new QLabel(QString::fromLocal8Bit("尺寸："));
	size_x_spinbox_ = new QSpinBox();
	size_x_spinbox_->setMinimum(0);
	size_x_spinbox_->setSingleStep(1);
	size_x_spinbox_->setWrapping(false);
	size_x_spinbox_->setPrefix(QString::fromLocal8Bit("x: "));
	size_x_spinbox_->setSuffix(QString::fromLocal8Bit("mm"));
	size_x_spinbox_->setValue(280);		//热床长度
	size_y_spinbox_ = new QSpinBox();
	size_y_spinbox_->setMinimum(0);
	size_y_spinbox_->setSingleStep(1);
	size_y_spinbox_->setWrapping(false);
	size_y_spinbox_->setPrefix(QString::fromLocal8Bit("y: "));
	size_y_spinbox_->setSuffix(QString::fromLocal8Bit("mm"));
	size_y_spinbox_->setValue(180);		//热床宽度

										//热床原点设置
	origin_label_ = new QLabel(QString::fromLocal8Bit("原点："));
	origin_x_spinbox_ = new QDoubleSpinBox();
	origin_x_spinbox_->setWrapping(false);
	origin_x_spinbox_->setPrefix(QString::fromLocal8Bit("x:　"));
	origin_x_spinbox_->setSingleStep(0.01);
	origin_x_spinbox_->setValue(0);
	origin_y_spinbox_ = new QDoubleSpinBox();
	origin_y_spinbox_->setWrapping(false);
	origin_y_spinbox_->setPrefix(QString::fromLocal8Bit("y:　"));
	origin_y_spinbox_->setSingleStep(0.01);
	origin_y_spinbox_->setValue(0);

	//设置打印机高度
	printer_height_label_ = new QLabel(QString::fromLocal8Bit("打印机高度："));
	printer_height_spinbox_ = new QSpinBox();
	printer_height_spinbox_->setMinimum(0);
	printer_height_spinbox_->setSingleStep(1);
	printer_height_spinbox_->setWrapping(false);
	printer_height_spinbox_->setSuffix(QString::fromLocal8Bit("mm"));
	printer_height_spinbox_->setValue(180);		//打印机高度

												//设置竖直偏移量
	z_offset_label_ = new QLabel(QString::fromLocal8Bit("竖直偏移量："));
	z_offset_spinbox_ = new QDoubleSpinBox();
	z_offset_spinbox_->setWrapping(false);
	z_offset_spinbox_->setSuffix(QString::fromLocal8Bit("mm"));
	z_offset_spinbox_->setSingleStep(0.01);
	z_offset_spinbox_->setValue(0);

	//设置固件参数
	firmware_config_groupbox_ = new QGroupBox(QString::fromLocal8Bit("固件参数设置："));
	gcode_flavor_label_ = new QLabel(QString::fromLocal8Bit("GCode类型： "));
	gcode_flavor_combobox_ = new QComboBox();
	gcode_flavor_combobox_->addItem(QString::fromLocal8Bit("RepRap (Marlin/Sprinter/Repetier)"));
	gcode_flavor_combobox_->addItem(QString::fromLocal8Bit("Teacup"));
	gcode_flavor_combobox_->addItem(QString::fromLocal8Bit("MakerWare (MakerBot)"));
	gcode_flavor_combobox_->addItem(QString::fromLocal8Bit("Sailfish (MakerBot)"));
	gcode_flavor_combobox_->addItem(QString::fromLocal8Bit("Mach3/LinuxCNC"));
	gcode_flavor_combobox_->addItem(QString::fromLocal8Bit("3D Machinekit"));
	gcode_flavor_combobox_->addItem(QString::fromLocal8Bit("No extrusion"));
	gcode_flavor_combobox_->setCurrentIndex(0);	//默认值


}

void PrinterConfigWidget::InitLayout() {
	bed_size_config_layout_->addWidget(bed_size_label_, 0, 0);
	bed_size_config_layout_->addWidget(size_x_spinbox_, 0, 1);
	bed_size_config_layout_->addWidget(size_y_spinbox_, 0, 2);
	bed_size_config_layout_->addWidget(origin_label_, 1, 0);
	bed_size_config_layout_->addWidget(origin_x_spinbox_, 1, 1);
	bed_size_config_layout_->addWidget(origin_y_spinbox_, 1, 2);
	bed_size_config_layout_->addWidget(printer_height_label_, 2, 0);
	bed_size_config_layout_->addWidget(printer_height_spinbox_, 2, 1);
	bed_size_config_layout_->addWidget(z_offset_label_, 3, 0);
	bed_size_config_layout_->addWidget(z_offset_spinbox_, 3, 1);
	size_config_groupbox_->setLayout(bed_size_config_layout_);

	firmware_config_layout_->addWidget(gcode_flavor_label_, 0, 0);
	firmware_config_layout_->addWidget(gcode_flavor_combobox_, 0, 1);
	firmware_config_layout_->addWidget(nozzle_diameter_label_, 1, 0);
	firmware_config_layout_->addWidget(nozzle_diameter_spinbox_, 1, 1);
	firmware_config_layout_->addWidget(retract_length_label_, 2, 0);
	firmware_config_layout_->addWidget(retract_length_spinbox_, 2, 1);
	firmware_config_layout_->addWidget(lift_z_label_, 3, 0);
	firmware_config_layout_->addWidget(lift_z_spinbox_, 3, 1);
	firmware_config_layout_->addWidget(wipe_retracting_label_, 4, 0);
	firmware_config_layout_->addWidget(wipe_retracting_spinbox_, 4, 1);
	firmware_config_groupbox_->setLayout(firmware_config_layout_);

	printer_config_main_layout_->addWidget(size_config_groupbox_);
	printer_config_main_layout_->addWidget(firmware_config_groupbox_);

}