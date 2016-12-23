#ifndef __MAINWINDOW_H
#define __MAINWINDOW_H


#include <QtWidgets/QMainWindow>
//#include "ui_mainwindow.h"

class QSplitter;
class QTabWidget;

class QMenu;
class QAction;
class QWidget;
class QLabel;
class QWidget;
class QVBoxLayout;

#include "ShowWidget.h"
#include "FilamentConfigWidget.h"
#include "PrintConfigWidget.h"
#include "PrinterConfigWidget.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = Q_NULLPTR);

private:
    //Ui::MainWindowClass ui;

private:
	void initActions();
	void initMenus();
	void initWidgets();
	void SetupWindowStyle();

private:
	QSplitter* mainSplitter;	//�ָ��
	QTabWidget* leftTabWidget;
	
	PrintConfigWidget* printConfigWidget;
	FilamentConfigWidget* filConfigWidget;
	PrinterConfigWidget* printerConfigWidget;

	ShowWidget* showWidget;

private:

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
	QAction* about_manual_action_;	//��ȡ���ʹ���ֲ�
	QAction* about_qt_action_;	//��ȡ�������
};



#endif	//!__MAINWINDOW_H
