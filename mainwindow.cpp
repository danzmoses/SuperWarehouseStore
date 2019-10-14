#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    // INITIALIZATION
    ui->setupUi(this);
    this->load();
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
    connect(ui->member_information_button, SIGNAL(clicked(bool)), this, SLOT(view_single_member_purchases()));

    // add member function
    connect(ui->add_member_confirm_button, SIGNAL(clicked(bool)), this, SLOT(add_member()));

    // add sale function
    connect(ui->member_list_widget, SIGNAL(itemSelectionChanged()), this, SLOT(add_sale_information()));
    connect(ui->item_list_widget, SIGNAL(itemSelectionChanged()), this, SLOT(add_sale_information()));
    connect(ui->add_sale_confirm_button, SIGNAL(clicked(bool)), this, SLOT(add_to_cart()));
    connect(ui->confirm_sale_button, SIGNAL(clicked(bool)), this, SLOT(confirm_sale()));

    // remove member function
    connect(ui->member_list_widget, SIGNAL(itemSelectionChanged()), this, SLOT(remove_member_information()));
    connect(ui->remove_member_confirm_button, SIGNAL(clicked(bool)), this, SLOT(remove_member()));

    // sales report function
    connect(ui->sales_report_button, SIGNAL(clicked(bool)), this, SLOT(view_sales_report()));

    // total purchases function
    connect(ui->total_purchases_button, SIGNAL(clicked(bool)), this, SLOT(view_total_member_purchases()));

    // item report button
    connect(ui->item_report_button, SIGNAL(clicked(bool)), this, SLOT(view_item_report()));

    // annual dues button
    connect(ui->annual_dues_button, SIGNAL(clicked(bool)), this, SLOT(view_annual_dues()));

    // membership expirations
    connect(ui->membership_expiration_button, SIGNAL(clicked(bool)), this, SLOT(view_membership_expirations()));

    // member rebates
    connect(ui->member_rebate_button, SIGNAL(clicked(bool)), this, SLOT(view_member_rebates()));
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
    if (!this->member_list.empty())
    {
        QListWidgetItem* item = ui->member_list_widget->currentItem();
        QString name = ui->member_list_widget->currentItem()->text();
        this->member_list.remove_member(ui->member_list_widget->currentIndex().row());
        delete ui->member_list_widget->takeItem(ui->member_list_widget->row(item));
        ui->output_box->setPlainText("Successfully removed (" + name + ") from member list");
    }
    else
        ui->output_box->setPlainText("ERROR: member list is empty");
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

    Item item;
    if (ui->item_list_widget->currentItem() == NULL)
        item = this->item_list[0];
    else
        item = this->item_list[ui->item_list_widget->currentIndex().row()];

    for (int i = 1; i <= ui->add_sale_quantity_spinbox->value(); ++i)
        this->cart.add_item(item);

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
    ui->add_sale_quantity_spinbox->setValue(1);
}

void MainWindow::confirm_sale()
{
    for (int i = 0; i < this->cart.size(); ++i)
        this->member_list[ui->member_list_widget->currentIndex().row()].add_purchase(this->cart[i], this->current_date, 1);

    ui->output_box->setPlainText("Successfully added purchase to Member: " + ui->member_list_widget->currentItem()->text());
    this->cart.clear();
}

void MainWindow::view_single_member_purchases()
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

    if (ui->member_list_widget->currentItem() != NULL)
        ui->output_box->setPlainText(QString::fromStdString(this->member_list.member_information(ui->member_list_widget->currentIndex().row())));
    else
        ui->output_box->setPlainText("ERROR: select a member to view their information");
}

void MainWindow::view_sales_report()
{
    ui->output_box->setPlainText(QString::fromStdString(this->member_list.sales_report(this->current_date)));
}

void MainWindow::view_item_report()
{
    stringstream ss;
    string dashes(90, '-');
    ss << left << setw(30) << "Item" << left << setw(30) << "Price" << left << setw(30) << "Quantity Sold" << endl;
    ss << dashes << endl;
    for (unsigned int i = 0; i < this->item_list.size(); ++i)
    {
        int quantity = 0;
        for (unsigned int j = 0; j < this->member_list.size(); ++j)
        {
            SaleContainer s = this->member_list[j].get_purchases();
            for (unsigned int k = 0; k < s.size(); ++k)
                if (s[k].item.name == item_list[i].name)
                    quantity += s[k].quantity;
        }
        ss << left << setw(30) << item_list[i].name << left << setw(30) << item_list[i].price << left << setw(30) << quantity << endl;
    }
    ui->output_box->setPlainText(QString::fromStdString(ss.str()));
}

void MainWindow::view_total_member_purchases()
{
    stringstream ss;

    string dashes(90, '-');
    ss << left << setw(30) << "Member ID" << left << setw(30) << "Member Name" << left << setw(30) << "Total Amount in Purchases" << endl;
    ss << dashes << endl;

    double total = 0;
    for (unsigned int i = 0; i < this->member_list.size(); ++i)
    {
        double subtotal = 0;
        SaleContainer s = this->member_list[i].get_purchases();
        for (unsigned int j = 0; j < s.size(); ++j)
            subtotal += s[j].item.price;
        total += subtotal;
        ss << left << setw(30) << this->member_list[i].get_member_id();
        ss << left << setw(30) << this->member_list[i].get_name();
        ss << left << setw(30) << subtotal << endl;
    }
    ss << dashes << endl;
    ss << left << setw(60) << "Total" << left << setw(30) << total << endl;

    ui->output_box->setPlainText(QString::fromStdString(ss.str()));
}

void MainWindow::view_annual_dues()
{
    stringstream temp;
    stringstream preferred;
    stringstream basic;
    string dashes(90, '-');
    temp << left << setw(30) << "Member Name" << left << setw(30) << "Member Type" << left << setw(30) << "Annual Dues" << endl;
    temp << dashes << endl;
    for (unsigned int i = 0; i < this->member_list.size(); ++i)
    {
        string name = this->member_list[i].get_name();
        string type = this->member_list[i].get_type();
        double annual_dues = this->member_list[i].get_annual_dues();
        if (type == "Basic")
            basic << left << setw(30) << name << left << setw(30) << type << left << setw(30) << annual_dues << endl;
        else if (type == "Preferred")
            preferred << left << setw(30) << name << left << setw(30) << type << left << setw(30) << annual_dues << endl;
    }
    temp << basic.str() << preferred.str() << endl;
    ui->output_box->setPlainText(QString::fromStdString(temp.str()));
}

void MainWindow::view_membership_expirations()
{
    stringstream ss;
    string dashes(90, '-');

    ss << left << setw(30) << "Member ID" << left << setw(30) << "Name" << left << setw(30) << "Expiration Date" << endl;
    ss << dashes << endl;
    for (unsigned int i = 0; i < this->member_list.size(); ++i)
    {
        ss << left << setw(30) << this->member_list[i].get_member_id();
        ss << left << setw(30) << this->member_list[i].get_name();
        ss << left << setw(30) << this->member_list[i].get_expiration_date().returnNumeric() << endl;
    }
    ui->output_box->setPlainText(QString::fromStdString(ss.str()));
}

void MainWindow::view_member_rebates()
{
    stringstream ss;
    string dashes(90, '-');
    ss << left << setw(30) << "Member ID" << left << setw(30) << "Name" << left << setw(30) << "Rebate" << endl;
    ss << dashes << endl;
    for (unsigned int i = 0; i < this->member_list.size(); ++i)
        if (this->member_list[i].get_type() == "Preferred")
        {
            ss << left << setw(30) << this->member_list[i].get_member_id();
            ss << left << setw(30) << this->member_list[i].get_name();
            ss << fixed << setprecision(2) << left << setw(30) << this->member_list[i].calculate_rebate() << endl;
        }
    ui->output_box->setPlainText(QString::fromStdString(ss.str()));
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

void MainWindow::remove_member_information()
{
    QString name;
    if (ui->member_list_widget->currentItem() == NULL)
        name = QString::fromStdString(this->member_list[0].get_name());
    else
        name = ui->member_list_widget->currentItem()->text();

    ui->remove_member_line_edit->setText(name);
}

void MainWindow::save()
{
    ofstream file;
    string itemsMain = "D:\\Qt\\CS8\\SuperWarehouseStore\\itemsMain.txt";
    string shopperMain = "D:\\Qt\\CS8\\SuperWarehouseStore\\warehouseShoppersMain.txt";
    file.open(itemsMain);

    if (!file)
    {
        cout << "ERROR: file not opened" << endl;
        exit(1);
    }

    for(int i = 0; i < item_list.size(); i++)
    {
        file << item_list[i].name << endl;
        file << item_list[i].price << endl;
    }

    file.close();
    file.open(shopperMain);

    if (!file)
    {
        cout << "ERROR: file not opened" << endl;
        exit(1);
    }

    for(int i = 0; i < member_list.size(); i++)
    {
        file << member_list[i].get_name() << endl;
        file << member_list[i].get_member_id() << endl;
        file << member_list[i].get_type() << endl;
        file << member_list[i].get_expiration_date().returnNumeric() << endl;
    }
}

void MainWindow::load()
{
    ifstream inFile;
    string itemsMain = "D:\\Qt\\CS8\\SuperWarehouseStore\\itemsMain.txt";
    string items = "D:\\Qt\\CS8\\SuperWarehouseStore\\items.txt";
    string shoppersMain = "D:\\Qt\\CS8\\SuperWarehouseStore\\warehouseShoppersMain.txt";
    string shoppers = "D:\\Qt\\CS8\\SuperWarehouseStore\\warehouseShoppers.txt";
    inFile.open(itemsMain);

    if(!inFile)
    {
        cout << "Error: Can't Open File.\n";
        inFile.close();
        item_list.load(items);
    }
    else
    {
        inFile.close();
        item_list.load(itemsMain);
    }

    inFile.open(shoppersMain);

    if(!inFile)
    {
        cout << "Error: Can't Open File.\n";
        inFile.close();
        member_list.load(shoppers);
    }
    else
    {
        inFile.close();
        member_list.load(shoppersMain);
    }
}

MainWindow::~MainWindow()
{
    this->save();
    delete ui;
}
