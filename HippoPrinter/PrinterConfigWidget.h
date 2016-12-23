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

	QLabel* bed_size_label_;	//�ȴ��ߴ�����
	QSpinBox* size_x_spinbox_;
	QSpinBox* size_y_spinbox_;

	QLabel* origin_label_;	//�ȴ�����ԭ������
	QDoubleSpinBox* origin_x_spinbox_;
	QDoubleSpinBox* origin_y_spinbox_;

	QLabel* printer_height_label_;	//��ӡ���߶�
	QSpinBox* printer_height_spinbox_;

	QLabel* z_offset_label_;	//��ֱƫ����
	QDoubleSpinBox* z_offset_spinbox_;

	//���ù̼�����
	QGroupBox* firmware_config_groupbox_;	

	QLabel* gcode_flavor_label_;	//����GCode����
	QComboBox* gcode_flavor_combobox_;

	QLabel* nozzle_diameter_label_;		//������ͷ�뾶
	QDoubleSpinBox* nozzle_diameter_spinbox_;

	QLabel* retract_length_label_;	//���ûس鳤��
	QDoubleSpinBox* retract_length_spinbox_;	

	QLabel* lift_z_label_;	//�س�ĸ߶�
	QDoubleSpinBox* lift_z_spinbox_;

	QLabel* wipe_retracting_label_;	//�Ƿ��ڻس�ʱ�ƶ���ͷ
	QSpinBox* wipe_retracting_spinbox_;
};

#endif // PrinterConfigWidget_H__
