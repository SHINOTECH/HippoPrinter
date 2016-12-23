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
	QSplitter* mainSplitter;	//分割窗口
	QTabWidget* leftTabWidget;
	
	PrintConfigWidget* printConfigWidget;
	FilamentConfigWidget* filConfigWidget;
	PrinterConfigWidget* printerConfigWidget;

	ShowWidget* showWidget;

private:

private:
	//菜单项
	QMenu* file_menu_;	//文件菜单
	QMenu* setting_menu_;	//设置菜单
	QMenu* help_menu_;	//帮助菜单

private:
	/*文件菜单下的操作*/
	QAction* load_model_action_;	//读取模型文件
	QAction* save_model_action_;	//保存模型文件
	QAction* save_GCode_action_;	//保存GCode文件
	QAction* print_action_;	//打印模型
	QAction* clear_platform_action_;	//删除所有模型
	QAction* quit_action_;	//退出操作

	/*设置菜单下的操作*/
	QAction* global_setting_action_;	//打印机设置

	/*帮助菜单下的操作*/
	QAction* about_hippo_action_;	//获取Hippo资料
	QAction* about_manual_action_;	//获取软件使用手册
	QAction* about_qt_action_;	//获取相关资料
};



#endif	//!__MAINWINDOW_H
