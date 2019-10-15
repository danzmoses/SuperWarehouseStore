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
    void load();
    void save();

private:
    Ui::MainWindow *ui;
    MemberContainer member_list;
    ItemContainer item_list;
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
    void view_single_member_purchases();
    void view_sales_report();
    void view_item_report();
    void view_total_member_purchases();
    void view_annual_dues();
    void view_membership_expirations();
    void view_member_rebates();


    void switch_to_add_member();
    void switch_to_remove_member();
    void switch_to_add_sale();

    void remove_member_information();

};

#endif // MAINWINDOW_H
