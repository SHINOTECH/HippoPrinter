#pragma once
#include "qwidget.h"

class QLabel;
class QGroupBox;
class QDoubleSpinBox;
class QSpinBox;
class QLineEdit;
class QComboBox;
class QCheckBox;
class QGridLayout;
class QVBoxLayout;


class PrintConfigWidget :
	public QWidget
{
	Q_OBJECT

public:
	PrintConfigWidget(QWidget* parent = 0);
	~PrintConfigWidget();
	void InitWidgets();	//初始化控件
	void InitLayout();	//初始化布局


	//窗口控件
private:
	
	QVBoxLayout* print_config_main_layout_;	//全局布局
	QGridLayout* general_config_layout_;	//基本参数设置布局
	QGridLayout* infill_config_layout_;		//填充参数设置布局
	QGridLayout* support_config_layout_;	//支撑参数设置布局
	QGridLayout* speed_config_layout_;		//速度参数设置布局

	//*基本参数设置
	QGroupBox* general_groupbox_;

	
	QLabel* layer_height_label_;	//层高
	QDoubleSpinBox* layer_height_spinbox_;

	
	QLabel* perimeters_label_;		//外壳层数
	QSpinBox* perimeter_spinbox_;

	
	QLabel* solid_layer_label_;		// 实心层数目
	QSpinBox* top_solid_spinbox_;	//顶层实心层数目
	QSpinBox* bottom_solid_spinbox_;	//底层实心曾数目


	
	QGroupBox* infill_groupbox_;	//*填充参数设置

	
	QLabel* fill_desnity_label_;		//填充密度
	QSpinBox* fill_desnity_spinbox_;

	
	QLabel* fill_pattern_label_;	//填充模式
	QComboBox* fill_pattern_combobox_;

	
	QLabel* top_fill_pattern_label_;	//顶层和底层填充模式
	QComboBox* top_fill_pattern_combobox_;

	//支撑参数设置
	QGroupBox* support_groupbox_;

	
	QLabel* gen_support_label_;		//是否生成支撑
	QComboBox* gen_support_combobox_;

	
	QLabel* pattern_spacing_label_;		//支撑材料之间的间隔
	QDoubleSpinBox* pattern_spacing_spinbox_;

	
	QLabel* contact_Zdistance_label_;		//支撑材料和模型之间的间隔
	QComboBox* contact_Zdistance_combobox_;

	
	QLabel* gen_bridge_label_;		//不生成Bridge结构
	QComboBox* gen_bridge_combobox_;

	
	QLabel* raft_layers_label_;		//模型底板高度
	QSpinBox* raft_layers_spinbox_;

	//速度参数设置
	QGroupBox* speed_groupbox_;

	
	QLabel* peri_speed_label_;		//边缘区域移动速度
	QSpinBox* peri_speed_spinbox_;

	
	QLabel* infill_speed_label_;	//填充区域移动速度	
	QSpinBox* infill_speed_spinbox_;

	
	QLabel* travel_speed_label_;	//打印间隔的移动速度
	QSpinBox* travel_speed_spinbox_;
};

