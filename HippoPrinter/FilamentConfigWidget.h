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

	void InitWidgets();		//��ʼ���ؼ�
	void InitLayout();		//��ʼ������

private:
	
	QVBoxLayout* filacofig_main_layout_;		//�ؼ����岼��
	QGridLayout* fila_config_layout_;	//�ĲĲ������ò���
	QGridLayout* temp_config_layout_;	//�¶����ò���

	QGroupBox* fila_config_groupbox_;	//�Ĳ�����
	QGroupBox* temp_config_groupbox_;		//�¶�����

	//���úĲİ뾶
	QLabel* diameter_label_;
	QDoubleSpinBox* diameter_spinbox_;

	//��ͷ����ϵ��
	QLabel* extru_multi_label_;
	QDoubleSpinBox* extru_multi_spinbox_;
	

	//��ͷ�¶�����
	QLabel* extruder_temp_label_;
	QSpinBox* extruder_first_temp_spinbox_;
	QSpinBox* extruder_other_temp_spinbox_;

	//�ȴ��¶�����
	QLabel* bed_temp_label_;
	QSpinBox* bed_first_temp_spinbox_;
	QSpinBox* bed_other_temp_spinbox_;
};

