#include "FilamentConfigWidget.h"

#include <QGridLayout>
#include <QLabel>
#include <QSpinBox>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QDoubleSpinBox>
#include <QDebug>

//************************************************************************
// ���ڣ�2016/12/26 
// ����: QWidget * parent
// ����: 
// ����: ���캯��
//************************************************************************

FilamentConfigWidget::FilamentConfigWidget(QWidget* parent)
	:QWidget(parent)
{
	InitWidgets();
	InitLayout();
}

//************************************************************************
// ���ڣ�2016/12/26 
// ����: 
// ����:��������
//************************************************************************

FilamentConfigWidget::~FilamentConfigWidget()
{
}

//TODO:������ʼ��Ϊ֮ǰ���õ�ֵ
//************************************************************************
// ���ڣ�2016/12/26 
// ����: void
// ����: ��ʼ���ؼ�
//************************************************************************

void FilamentConfigWidget::InitWidgets() {
	//��ʼ������
	filacofig_main_layout_ = new QVBoxLayout();
	filacofig_main_layout_->setSpacing(30);
	fila_config_layout_ = new QGridLayout();
	fila_config_layout_->setSpacing(20);
	temp_config_layout_ = new QGridLayout();
	temp_config_layout_->setSpacing(20);

	//��ʼ������
	fila_config_groupbox_ = new QGroupBox(QString::fromLocal8Bit("�Ĳ�����"));
	temp_config_groupbox_ = new QGroupBox(QString::fromLocal8Bit("�¶�����"));

	//��ʼ���Ĳİ뾶����
	diameter_label_ = new QLabel(QString::fromLocal8Bit("�Ĳİ뾶��"));
	diameter_spinbox_ = new QDoubleSpinBox();
	diameter_spinbox_->setRange(0, 3);
	diameter_spinbox_->setWrapping(false);
	diameter_spinbox_->setSuffix(QString::fromLocal8Bit("mm"));
	diameter_spinbox_->setSingleStep(0.01);
	diameter_spinbox_->setValue(1.75);	//Ĭ��ֵ
	 
	//��ͷ����ϵ��
	extru_multi_label_ = new QLabel(QString::fromLocal8Bit("��ͷ����ϵ����"));
	extru_multi_spinbox_ = new QDoubleSpinBox();
	extru_multi_spinbox_->setRange(0.9, 1.1);
	extru_multi_spinbox_->setWrapping(false);
	extru_multi_spinbox_->setSingleStep(0.01);
	extru_multi_spinbox_->setValue(1);	//Ĭ��ֵ

	//��ʼ����ͷ���ÿؼ�
	extruder_temp_label_ = new QLabel(QString::fromLocal8Bit("��ͷ�¶�����:"));
	extruder_first_temp_spinbox_ = new QSpinBox();
	extruder_first_temp_spinbox_->setRange(0, 300);
	extruder_first_temp_spinbox_->setWrapping(false);
	extruder_first_temp_spinbox_->setSingleStep(1);
	extruder_first_temp_spinbox_->setPrefix(QString::fromLocal8Bit("��һ�㣺"));
	extruder_first_temp_spinbox_->setSuffix(QString::fromLocal8Bit("��"));
	extruder_first_temp_spinbox_->setValue(205);	//Ĭ��ֵ
	extruder_other_temp_spinbox_ = new QSpinBox();
	extruder_other_temp_spinbox_->setRange(0, 300);
	extruder_other_temp_spinbox_->setWrapping(false);
	extruder_other_temp_spinbox_->setSingleStep(1);
	extruder_other_temp_spinbox_->setPrefix(QString::fromLocal8Bit("�����㣺"));
	extruder_other_temp_spinbox_->setSuffix(QString::fromLocal8Bit("��"));
	extruder_other_temp_spinbox_->setValue(205);	//Ĭ��ֵ

	//��ʼ���ȴ��¶����ÿؼ�
	bed_temp_label_ = new QLabel(QString::fromLocal8Bit("�ȴ��¶�:"));
	bed_first_temp_spinbox_ = new QSpinBox();
	bed_first_temp_spinbox_->setRange(0, 100);
	bed_first_temp_spinbox_->setWrapping(false);
	bed_first_temp_spinbox_->setSingleStep(1);
	bed_first_temp_spinbox_->setPrefix(QString::fromLocal8Bit("��һ�㣺"));
	bed_first_temp_spinbox_->setSuffix(QString::fromLocal8Bit("��"));
	bed_first_temp_spinbox_->setValue(55);	//Ĭ��ֵ
	bed_other_temp_spinbox_ = new QSpinBox();
	bed_other_temp_spinbox_->setRange(0, 100);
	bed_other_temp_spinbox_->setWrapping(false);
	bed_other_temp_spinbox_->setSingleStep(1);
	bed_other_temp_spinbox_->setPrefix(QString::fromLocal8Bit("�����㣺"));
	bed_other_temp_spinbox_->setSuffix(QString::fromLocal8Bit("��"));
	bed_other_temp_spinbox_->setValue(55);	//Ĭ��ֵ

}


//************************************************************************
// ���ڣ�2016/12/26 
// ����: void
// ����: ��ʼ���ؼ�����
//************************************************************************

void FilamentConfigWidget::InitLayout() {
	//��ʼ���ĲĲ������ÿؼ��Ĳ���
	fila_config_layout_->addWidget(diameter_label_, 0, 0);
	fila_config_layout_->addWidget(diameter_spinbox_, 0, 1);
	fila_config_layout_->addWidget(extru_multi_label_, 1, 0);
	fila_config_layout_->addWidget(extru_multi_spinbox_, 1, 1);
	fila_config_groupbox_->setLayout(fila_config_layout_);

	//��ʼ���¶Ȳ������ÿؼ��Ĳ���
	temp_config_layout_->addWidget(extruder_temp_label_, 0, 0);
	temp_config_layout_->addWidget(extruder_first_temp_spinbox_, 1, 0);
	temp_config_layout_->addWidget(extruder_other_temp_spinbox_, 1, 1);
	temp_config_layout_->addWidget(bed_temp_label_, 2, 0);
	temp_config_layout_->addWidget(bed_first_temp_spinbox_, 3, 0);
	temp_config_layout_->addWidget(bed_other_temp_spinbox_, 3, 1);
	temp_config_groupbox_->setLayout(temp_config_layout_);

	//��ʼ���ؼ�ȫ�ֲ���
	filacofig_main_layout_->addWidget(fila_config_groupbox_);
	filacofig_main_layout_->addWidget(temp_config_groupbox_);
	filacofig_main_layout_->addStretch(1);
	setLayout(filacofig_main_layout_);
}