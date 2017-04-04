#ifndef __MAINWINDOW_H
#define __MAINWINDOW_H


#include <QtWidgets/QMainWindow>
//#include "ui_mainwindow.h"

class QTabWidget;

class QMenu;
class QAction;
class QWidget;
class QLabel;
class QWidget;
class QVBoxLayout;
class QHBoxLayout;

#include "ShowWidget.h"
#include "FilamentConfigWidget.h"
#include "PrintConfigWidget.h"
#include "PrinterConfigWidget.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = Q_NULLPTR);


    //Ui::MainWindowClass ui;

private:
	void InitActions();
	void InitMenus();
	void InitWidgets();
	void InitLayout();
	void InitConnections();
	void SetupWindowStyle();

private:
	QWidget* central_widget_;
	QHBoxLayout* central_widget_layout_;
	QTabWidget* left_tabWidget_;
	
	PrintConfigWidget* print_config_widget_;
	FilamentConfigWidget* fila_config_layout_;
	PrinterConfigWidget* printer_config_layout_;

	ShowWidget* show_widget_;

private slots:
	void OpenFile();

private:
	//�˵���
	QMenu* file_menu_;	//�ļ��˵�
	QMenu* setting_menu_;	//���ò˵�
	QMenu* help_menu_;	//�����˵�

private:
	/*�ļ��˵��µĲ���*/
	QAction* load_model_action_;	//��ȡģ���ļ�
	QAction* save_model_action_;	//����ģ���ļ�
	QAction* save_GCode_action_;	//����GCode�ļ�
	QAction* print_action_;	//��ӡģ��
	QAction* clear_platform_action_;	//ɾ������ģ��
	QAction* quit_action_;	//�˳�����

	/*���ò˵��µĲ���*/
	QAction* global_setting_action_;	//��ӡ������

	/*�����˵��µĲ���*/
	QAction* about_hippo_action_;	//��ȡHippo����
	QAction* about_manual_action_;	//��ȡ����ʹ���ֲ�
	QAction* about_qt_action_;	//��ȡ��������
};



#endif	//!__MAINWINDOW_H
