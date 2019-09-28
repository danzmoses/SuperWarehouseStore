#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "member.h"
#include "member_container.h"
#include "item_container.h"
#include <QMainWindow>
#include <QDebug>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <ctime>
#include <QFontDatabase>
#include <cstdlib>


const QFont fixedFont = QFontDatabase::systemFont(QFontDatabase::FixedFont);

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    MemberContainer member_list = MemberContainer("D:\\Qt\\CS8\\SuperWarehouseStore\\warehouseShoppers.txt");
    ItemContainer item_list = ItemContainer("D:\\Qt\\CS8\\SuperWarehouseStore\\items.txt");
    ItemContainer cart;
    Date current_date;

private slots:

    // member functions
    void add_member();
    void remove_member();

    void add_sale_information();
    void add_to_cart();
    void confirm_sale();

    // reports
    void view_member_purchases();
    void view_sales_report();
    void view_item_report();

    void switch_to_add_member();
    void switch_to_remove_member();
    void switch_to_add_sale();

};

#endif // MAINWINDOW_H
