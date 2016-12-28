/********************************************************************
	�ļ�����PrinterConfigWidget��
	����  ��20161219
	����  ��big-hippo
	����  ��
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
	void InitWidgets();	//��ʼ���ؼ�
	void InitLayout();	//��ʼ������


private:
	QVBoxLayout* printer_config_main_layout_;	//ȫ�ֲ���
	QGridLayout* bed_size_config_layout_;		//�ȴ����ÿؼ�����
	QGridLayout* firmware_config_layout_;	//�̼����ÿؼ�����
	
	//�ȴ��ߴ��������										
	QGroupBox* size_config_groupbox_;	

	//�ȴ��ߴ�����
	QLabel* bed_size_label_;	
	QSpinBox* size_x_spinbox_;
	QSpinBox* size_y_spinbox_;

	//�ȴ�����ԭ������
	QLabel* origin_label_;	
	QDoubleSpinBox* origin_x_spinbox_;
	QDoubleSpinBox* origin_y_spinbox_;

	//��ӡ���߶�
	QLabel* printer_height_label_;	
	QSpinBox* printer_height_spinbox_;

	//��ֱƫ����
	QLabel* z_offset_label_;	
	QDoubleSpinBox* z_offset_spinbox_;

	//���ù̼�����
	QGroupBox* firmware_config_groupbox_;	

	//����GCode����
	QLabel* gcode_flavor_label_;	
	QComboBox* gcode_flavor_combobox_;

	//��������뾶
	QLabel* nozzle_diameter_label_;		
	QDoubleSpinBox* nozzle_diameter_spinbox_;

	//���ûس鳤��
	QLabel* retract_length_label_;	
	QDoubleSpinBox* retract_length_spinbox_;	

	//�س�ĸ߶�
	QLabel* lift_z_label_;	
	QDoubleSpinBox* lift_z_spinbox_;

	//�Ƿ��ڻس�ʱ�ƶ���ͷ
	QLabel* wipe_retracting_label_;	
	QComboBox* wipe_retracting_combobox_;
};

#endif // PrinterConfigWidget_H__
