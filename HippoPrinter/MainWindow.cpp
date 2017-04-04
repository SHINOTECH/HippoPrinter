#include "mainwindow.h"
#include <iostream>

#include<QSize>
#include <QString>
#include <QDebug>

#include <QSplitter>
#include <QTabWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>

#include <QListWidget>
#include <QStackedWidget>
#include <QAction>
#include <QMenu>
#include <QMenuBar>
#include <QStatusBar>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	//ui.setupUi(this);
	setWindowTitle(QString::fromLocal8Bit("Hippo"));
	//setMinimumSize(QSize(1000, 800));
	
	//初始化菜单和菜单项
	InitActions();	
	InitMenus();
	InitWidgets();
	InitLayout();
	InitConnections();

	setContentsMargins(5, 5, 10, 5);
	statusBar()->showMessage(tr("Ready"));

	if (!isMaximized()) {
		showMaximized();
	}
}


void MainWindow::InitActions() {

	/*文件菜单下的操作*/
	//打开模型
	load_model_action_ = new QAction(QString::fromLocal8Bit("打开模型"));
	load_model_action_->setShortcut(tr("Ctrl+O"));
	load_model_action_->setStatusTip(QString::fromLocal8Bit("打开模型文件"));
	
	//保存模型
	save_model_action_ = new QAction(QString::fromLocal8Bit("保存模型"));
	save_model_action_->setShortcut(tr("Ctrl+S"));
	save_model_action_->setStatusTip(QString::fromLocal8Bit("保存模型文件"));

	//保存GCode文件
	save_GCode_action_ = new QAction(QString::fromLocal8Bit("保存G代码"));
	save_GCode_action_->setShortcut(tr("Ctrl+G"));
	save_GCode_action_->setStatusTip(QString::fromLocal8Bit("保存GCode文件"));

	//打印模型
	print_action_ = new QAction(QString::fromLocal8Bit("打印模型"));
	print_action_->setShortcut(tr("Ctrl+P"));
	print_action_->setStatusTip(QString::fromLocal8Bit("打印三维模型"));

	//清除平台
	clear_platform_action_ = new QAction(QString::fromLocal8Bit("清除平台"));
	clear_platform_action_->setStatusTip(QString::fromLocal8Bit("清除所有三维模型"));

	//退出程序
	quit_action_ = new QAction(QString::fromLocal8Bit("退出"));
	quit_action_->setShortcut(tr("Ctrl+Q"));
	quit_action_->setStatusTip(QString::fromLocal8Bit("退出程序"));


	/*设置菜单下的操作*/
	//设置打印参数
	global_setting_action_ = new QAction(QString::fromLocal8Bit("打印机设置"));
	global_setting_action_->setStatusTip(QString::fromLocal8Bit("设置打印机相关参数"));


	/*帮助菜单下的操作*/
	//获取Hippo资料
	about_hippo_action_ = new QAction(QString::fromLocal8Bit("关于Hippo"));
	about_hippo_action_->setStatusTip(QString::fromLocal8Bit("关于Hippo的资料"));

	//获取软件手册
	about_manual_action_ = new QAction(QString::fromLocal8Bit("使用手册"));
	about_manual_action_->setStatusTip(QString::fromLocal8Bit("软件使用手册"));

	//获取Qt资料
	about_qt_action_ = new QAction(QString::fromLocal8Bit("关于Qt"));
	about_qt_action_->setStatusTip(QString::fromLocal8Bit("获取关于Qt的资料"));
}

void MainWindow::SetupWindowStyle() {
	setWindowFlags(windowFlags() | Qt::FramelessWindowHint | Qt::X11BypassWindowManagerHint | Qt::Tool);
	setAttribute(Qt::WA_TranslucentBackground);
	setWindowState(Qt::WindowNoState | Qt::WindowFullScreen);
	setFocusPolicy(Qt::NoFocus);
	setWindowOpacity(1.0);

	setWindowIcon(QIcon("icon.png"));
}

//************************************
// 作者: big-hippo
// 日期：2016/12/19 
// 返回: void
// 功能: 初始化菜单栏
//************************************
void MainWindow::InitMenus() {
	//文件菜单
	file_menu_ = menuBar()->addMenu(QString::fromLocal8Bit("文件"));
	file_menu_->addAction(load_model_action_);
	file_menu_->addAction(save_model_action_);
	file_menu_->addAction(save_GCode_action_);
	file_menu_->addSeparator();
	file_menu_->addAction(print_action_);
	file_menu_->addAction(clear_platform_action_);
	file_menu_->addSeparator();
	file_menu_->addAction(quit_action_);

	//设置菜单
	setting_menu_ = menuBar()->addMenu(QString::fromLocal8Bit("设置"));
	setting_menu_->addAction(global_setting_action_);
	

	//帮助菜单
	help_menu_ = menuBar()->addMenu(QString::fromLocal8Bit("帮助"));
	help_menu_->addAction(about_hippo_action_);
	help_menu_->addAction(about_hippo_action_);
	help_menu_->addAction(about_hippo_action_);
}



//************************************
// 作者: big-hippo
// 日期：2016/12/19 
// 返回: void
// 功能:
//************************************
void MainWindow::InitWidgets() {
	print_config_widget_ = new PrintConfigWidget();
	fila_config_layout_ = new FilamentConfigWidget();
	printer_config_layout_ = new PrinterConfigWidget();

	left_tabWidget_ = new QTabWidget();
	left_tabWidget_->addTab(print_config_widget_, QString::fromLocal8Bit("打印设置"));
	left_tabWidget_->addTab(fila_config_layout_, QString::fromLocal8Bit("耗材设置"));
	left_tabWidget_->addTab(printer_config_layout_, QString::fromLocal8Bit("打印机设置"));
	
	show_widget_ = new ShowWidget();
	central_widget_ = new QWidget();
	central_widget_layout_ = new QHBoxLayout();
	central_widget_layout_->addWidget(left_tabWidget_,1);
	central_widget_layout_->addWidget(show_widget_,6);

}

//************************************************************************
// 日期：2016/12/26 
// 返回: void
// 功能: 设置窗口布局
//************************************************************************

void MainWindow::InitLayout() {
	central_widget_->setLayout(central_widget_layout_);
	setCentralWidget(central_widget_);
}

void MainWindow::InitConnections() {
	connect(load_model_action_, SIGNAL(triggered()), this, SLOT(OpenFile()));
}


void MainWindow::OpenFile() {
	QString file = QFileDialog::getOpenFileName(this, QString::fromLocal8Bit("打开文件"),"", "*.stl");
	show_widget_->LoadModel(file.toLatin1().data());
}