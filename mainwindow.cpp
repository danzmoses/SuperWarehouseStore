#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    // INITIALIZATION
    ui->setupUi(this);
    srand(time(0));
    for (int i = 0; i < this->member_list.size(); ++i)
        ui->member_list_widget->addItem(QString::fromStdString(this->member_list[i].get_name()));

    for (int i = 0; i < this->item_list.size(); ++i)
        ui->item_list_widget->addItem(QString::fromStdString(this->item_list[i].name));
    time_t now = time(0);
    tm *ltm = localtime(&now);
    Date current_date(1 + ltm->tm_mon, ltm->tm_mday, 1900 + ltm->tm_year);
    QString month = QString::number(current_date.get_month());
    QString day = QString::number(current_date.get_day());
    QString year = QString::number(current_date.get_year());
    ui->current_date_line_edit->setText("Date: " + month + '/' + day + '/' + year);
    this->current_date = current_date;


    // connect radio buttons to switching pages
    connect(ui->store_radio_button, SIGNAL(toggled(bool)), ui->store_page, SLOT(setVisible(bool)));
    connect(ui->member_radio_button, SIGNAL(toggled(bool)), ui->member_page, SLOT(setVisible(bool)));
    connect(ui->item_radio_button, SIGNAL(toggled(bool)), ui->item_page, SLOT(setVisible(bool)));

    // connect function buttons to switching pages for input
    connect(ui->add_member_button, SIGNAL(clicked(bool)), this, SLOT(switch_to_add_member()));
    connect(ui->add_sale_button, SIGNAL(clicked(bool)), this, SLOT(switch_to_add_sale()));
    connect(ui->remove_member_button, SIGNAL(clicked(bool)), this, SLOT(switch_to_remove_member()));

    // direct to output functions
    connect(ui->view_member_purchases_button, SIGNAL(clicked(bool)), this, SLOT(view_member_purchases()));

    // add member function
    connect(ui->add_member_confirm_button, SIGNAL(clicked(bool)), this, SLOT(add_member()));

    // add sale function
    connect(ui->member_list_widget, SIGNAL(itemSelectionChanged()), this, SLOT(add_sale_information()));
    connect(ui->item_list_widget, SIGNAL(itemSelectionChanged()), this, SLOT(add_sale_information()));
    connect(ui->add_sale_confirm_button, SIGNAL(clicked(bool)), this, SLOT(add_to_cart()));
    connect(ui->confirm_sale_button, SIGNAL(clicked(bool)), this, SLOT(confirm_sale()));

    // sales report function
    connect(ui->sales_report_button, SIGNAL(clicked(bool)), this, SLOT(view_sales_report()));
}

// private slots
void MainWindow::add_member()
{
    string name = ui->add_member_line_edit->text().toStdString();
    string type = ui->add_member_combobox->currentText().toStdString();
    int id = rand() % 10000 + 9999;
    while (id < 10000)
        id = rand() % 10000 + 9999;
    this->member_list.add_member(Member(name, id, type, this->current_date));
    string dashes(31, '-');
    stringstream ss;
    ss << "Successfully added a new member" << endl;
    ss << dashes << endl;
    ss << "Name: " << name << endl;
    ss << "Member ID: " << id << endl;
    ss << "Type: " << type << endl;

    ui->member_list_widget->addItem(QString::fromStdString(name));
    ui->output_box->setPlainText(QString::fromStdString(ss.str()));

}

void MainWindow::remove_member()
{
    this->member_list.remove_member(ui->member_list_widget->currentIndex().row());
}

void MainWindow::add_sale_information()
{
    QString name;
    QString item;
    QString price;

    if (ui->member_list_widget->currentItem() == NULL)
        name = QString::fromStdString(this->member_list[0].get_name());
    else
        name = ui->member_list_widget->currentItem()->text();

    if (ui->item_list_widget->currentItem() == NULL)
    {
        item = QString::fromStdString(this->item_list[0].name);
        price = QString::number(this->item_list[0].price);
    }
    else
    {
        item = ui->item_list_widget->currentItem()->text();
        price = QString::number(this->item_list[ui->item_list_widget->currentIndex().row()].price);
    }
    ui->add_sale_member_line_edit->setText(name);
    ui->add_sale_item_line_edit->setText(item);
    ui->add_sale_price_line_edit->setText(price);
}

void MainWindow::add_to_cart()
{
    stringstream ss;
    Item i = this->item_list[ui->item_list_widget->currentIndex().row()];
//    int quantity = ui->add_sale_quantity_spinbox->value();

//    for (int i = 1; i <= quantity; ++i)
        this->cart.add_item(i);

    double total = 0;
    for (int i = 0; i < this->cart.size(); ++i)
    {
        ss << left << setw(25) << this->cart[i].name << right << setw(25) << this->cart[i].price << endl;
        total += this->cart[i].price;
    }
    string dashes(50, '-');
    ss << dashes << endl;
    ss << left << setw(25) << "Total:" << right << setw(25) << total << endl;
    ui->output_box->setPlainText(QString::fromStdString(ss.str()));
}

void MainWindow::confirm_sale()
{
    for (int i = 0; i < this->cart.size(); ++i)
        this->member_list[ui->member_list_widget->currentIndex().row()].add_purchase(this->cart[i], this->current_date, 1);

    ui->output_box->setPlainText("Successfully added purchase to Member: " + ui->member_list_widget->currentItem()->text());
    this->cart.clear();
}

void MainWindow::view_member_purchases()
{
    // check that a member is selected
//    stringstream ss;
//    Member m = this->member_list[ui->member_list_widget->currentIndex().row()];
//    SaleContainer s = m.get_purchases();

//    ss << left << setw(30) << "Name:" << right << setw(30) << m.get_name() << endl;
//    ss << left << setw(30) << "ID:" << right << setw(30) << m.get_member_id() << endl;
//    ss << left << setw(30) << "Type:" << right << setw(30) << m.get_type() << endl << endl;
//    string dashes(60, '-');
//    ss << left << setw(30) << "Item" << right << setw(30) << "Price" << endl;
//    ss << dashes << endl;

//    for (int i = 0; i < s.size(); ++i)
//        ss << left << setw(30) << s[i].item.name << right << setw(30) << s[i].item.price << endl;
//    ss << dashes << endl;
//    ss << left << setw(30) << "Total:" << right << setw(30) << m.get_total_amount_spent() << endl;

    ui->output_box->setPlainText(QString::fromStdString(this->member_list.member_information(ui->member_list_widget->currentIndex().row())));
}

void MainWindow::view_sales_report()
{
    ui->output_box->setPlainText(QString::fromStdString(this->member_list.sales_report(this->current_date)));
}

void MainWindow::view_item_report()
{
    ;
}

void MainWindow::switch_to_add_member()
{
    ui->input_stacked_widget->setCurrentIndex(0);
}

void MainWindow::switch_to_remove_member()
{
    ui->input_stacked_widget->setCurrentIndex(1);
}

void MainWindow::switch_to_add_sale()
{
    ui->input_stacked_widget->setCurrentIndex(2);
}

MainWindow::~MainWindow()
{
    delete ui;
}
