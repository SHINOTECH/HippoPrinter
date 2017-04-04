#include "PrinterConfigWidget.h"

#include <QVBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QGroupBox>
#include <QComboBox>

//************************************************************************
// ���ڣ�2016/12/26 
// ����: QWidget * parent
// ����: 
// ����: ���캯��
//************************************************************************

PrinterConfigWidget::PrinterConfigWidget(QWidget* parent)
	:QWidget(parent){
	InitWidgets();	//��ʼ���ؼ�
	InitLayout();	//��ʼ������ 
}


PrinterConfigWidget::~PrinterConfigWidget(){
}

//************************************************************************
// ���ڣ�2016/12/26 
// ����: void
// ����: ��ʼ���ؼ�
//************************************************************************

void PrinterConfigWidget::InitWidgets() {
	//��ʼ������
	printer_config_main_layout_ = new QVBoxLayout();
	printer_config_main_layout_->setSpacing(30);
	bed_size_config_layout_ = new QGridLayout();
	bed_size_config_layout_->setSpacing(20);
	firmware_config_layout_ = new QGridLayout();
	firmware_config_layout_->setSpacing(20);

	//�����ȴ�����
	size_config_groupbox_ = new QGroupBox(QString::fromLocal8Bit("�ȴ�����:"));

	//�ȴ��ߴ�����
	bed_size_label_ = new QLabel(QString::fromLocal8Bit("�ߴ�:"));
	size_x_spinbox_ = new QSpinBox();
	size_x_spinbox_->setMinimum(0);
	size_x_spinbox_->setMaximum(1000);
	size_x_spinbox_->setSingleStep(1);
	size_x_spinbox_->setWrapping(false);
	size_x_spinbox_->setPrefix(QString::fromLocal8Bit("x: "));
	size_x_spinbox_->setSuffix(QString::fromLocal8Bit("mm"));
	size_x_spinbox_->setValue(280);		//�ȴ�����
	size_y_spinbox_ = new QSpinBox();
	size_y_spinbox_->setMinimum(0);
	size_y_spinbox_->setSingleStep(1);
	size_y_spinbox_->setMaximum(1000);
	size_y_spinbox_->setWrapping(false);
	size_y_spinbox_->setPrefix(QString::fromLocal8Bit("y: "));
	size_y_spinbox_->setSuffix(QString::fromLocal8Bit("mm"));
	size_y_spinbox_->setValue(180);		//�ȴ����

	//�ȴ�ԭ������
	origin_label_ = new QLabel(QString::fromLocal8Bit("ԭ�㣺"));
	origin_x_spinbox_ = new QDoubleSpinBox();
	origin_x_spinbox_->setWrapping(false);
	origin_x_spinbox_->setPrefix(QString::fromLocal8Bit("x: "));
	origin_x_spinbox_->setSingleStep(0.01);
	origin_x_spinbox_->setValue(0);
	origin_y_spinbox_ = new QDoubleSpinBox();
	origin_y_spinbox_->setWrapping(false);
	origin_y_spinbox_->setPrefix(QString::fromLocal8Bit("y: "));
	origin_y_spinbox_->setSingleStep(0.01);
	origin_y_spinbox_->setValue(0);

	//���ô�ӡ���߶�
	printer_height_label_ = new QLabel(QString::fromLocal8Bit("��ӡ���߶�:"));
	printer_height_spinbox_ = new QSpinBox();
	printer_height_spinbox_->setMinimum(0);
	printer_height_spinbox_->setSingleStep(1);
	printer_height_spinbox_->setWrapping(false);
	printer_height_spinbox_->setSuffix(QString::fromLocal8Bit("mm"));
	printer_height_spinbox_->setValue(180);		//��ӡ���߶�

	//������ֱƫ����
	z_offset_label_ = new QLabel(QString::fromLocal8Bit("��ֱƫ����:"));
	z_offset_spinbox_ = new QDoubleSpinBox();
	z_offset_spinbox_->setWrapping(false);
	z_offset_spinbox_->setSuffix(QString::fromLocal8Bit("mm"));
	z_offset_spinbox_->setSingleStep(0.01);
	z_offset_spinbox_->setValue(0);

	//���ù̼�����
	firmware_config_groupbox_ = new QGroupBox(QString::fromLocal8Bit("�̼�����:"));
	gcode_flavor_label_ = new QLabel(QString::fromLocal8Bit("GCode���ͣ� "));
	gcode_flavor_combobox_ = new QComboBox();
	gcode_flavor_combobox_->setSizeAdjustPolicy(QComboBox::AdjustToContents);
	gcode_flavor_combobox_->addItem(QString::fromLocal8Bit("Teacup"));
	gcode_flavor_combobox_->addItem(QString::fromLocal8Bit("RepRap(Marlin/Sprinter/Repetier)"));
	gcode_flavor_combobox_->addItem(QString::fromLocal8Bit("MakerWare (MakerBot)"));
	gcode_flavor_combobox_->addItem(QString::fromLocal8Bit("Sailfish (MakerBot)"));
	gcode_flavor_combobox_->addItem(QString::fromLocal8Bit("Mach3/LinuxCNC"));
	gcode_flavor_combobox_->addItem(QString::fromLocal8Bit("3D Machinekit"));
	gcode_flavor_combobox_->addItem(QString::fromLocal8Bit("No extrusion"));
	gcode_flavor_combobox_->setCurrentIndex(0);	//Ĭ��ֵ

	//��������뾶
	nozzle_diameter_label_ = new QLabel(QString::fromLocal8Bit("�����С:"));
	nozzle_diameter_spinbox_ = new QDoubleSpinBox();
	nozzle_diameter_spinbox_->setWrapping(false);
	nozzle_diameter_spinbox_->setSingleStep(0.1);
	nozzle_diameter_spinbox_->setSuffix(QString::fromLocal8Bit("mm"));
	nozzle_diameter_spinbox_->setMinimum(0.0);
	nozzle_diameter_spinbox_->setValue(0.5);

	//���ûس鳤��
	retract_length_label_ = new QLabel(QString::fromLocal8Bit("�س鳤��:"));
	retract_length_spinbox_ = new QDoubleSpinBox();
	retract_length_spinbox_->setWrapping(false);
	retract_length_spinbox_->setSingleStep(0.1);
	retract_length_spinbox_->setSuffix(QString::fromLocal8Bit("mm"));
	retract_length_spinbox_->setMinimum(0.0);
	retract_length_spinbox_->setValue(0);

	//���ûس�ĸ߶�
	lift_z_label_ = new QLabel(QString::fromLocal8Bit("�س�߶�:"));
	lift_z_spinbox_ = new QDoubleSpinBox();
	lift_z_spinbox_->setWrapping(false);
	lift_z_spinbox_->setSingleStep(0.01);
	lift_z_spinbox_->setSuffix(QString::fromLocal8Bit("mm"));
	lift_z_spinbox_->setValue(0.0);


	//�Ƿ����س飬���ڻس�ʱ�ƶ���ͷ
	wipe_retracting_label_ = new QLabel(QString::fromLocal8Bit("�����س�:"));
	wipe_retracting_combobox_ = new QComboBox();
	wipe_retracting_combobox_->addItem(QString::fromLocal8Bit("��"));
	wipe_retracting_combobox_->addItem(QString::fromLocal8Bit("��"));
	wipe_retracting_combobox_->setCurrentIndex(0);
	
}

//************************************************************************
// ���ڣ�2016/12/26 
// ����: void
// ����: ���ô��ڲ���
//************************************************************************

void PrinterConfigWidget::InitLayout() {
	bed_size_config_layout_->addWidget(bed_size_label_, 0, 0);
	bed_size_config_layout_->addWidget(size_x_spinbox_, 1, 0);
	bed_size_config_layout_->addWidget(size_y_spinbox_, 1, 1);
	bed_size_config_layout_->addWidget(origin_label_, 2, 0);
	bed_size_config_layout_->addWidget(origin_x_spinbox_, 3, 0);
	bed_size_config_layout_->addWidget(origin_y_spinbox_, 3, 1);
	bed_size_config_layout_->addWidget(printer_height_label_, 4, 0);
	bed_size_config_layout_->addWidget(printer_height_spinbox_, 4, 1);
	bed_size_config_layout_->addWidget(z_offset_label_, 5, 0);
	bed_size_config_layout_->addWidget(z_offset_spinbox_, 5, 1);
	size_config_groupbox_->setLayout(bed_size_config_layout_);

	firmware_config_layout_->addWidget(gcode_flavor_label_, 0, 0);
	firmware_config_layout_->addWidget(gcode_flavor_combobox_, 1,0,1,2);
	firmware_config_layout_->addWidget(nozzle_diameter_label_, 2, 0);
	firmware_config_layout_->addWidget(nozzle_diameter_spinbox_, 2, 1);
	firmware_config_layout_->addWidget(retract_length_label_, 3, 0);
	firmware_config_layout_->addWidget(retract_length_spinbox_, 3, 1);
	firmware_config_layout_->addWidget(lift_z_label_, 4, 0);
	firmware_config_layout_->addWidget(lift_z_spinbox_, 4, 1);
	firmware_config_layout_->addWidget(wipe_retracting_label_, 5, 0);
	firmware_config_layout_->addWidget(wipe_retracting_combobox_, 5, 1);
	firmware_config_groupbox_->setLayout(firmware_config_layout_);

	printer_config_main_layout_->addWidget(size_config_groupbox_);
	printer_config_main_layout_->addWidget(firmware_config_groupbox_);
	printer_config_main_layout_->addStretch(1);
	setLayout(printer_config_main_layout_);
}