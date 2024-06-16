#include "GUI.h"
#include <map>
#include <qpalette.h>
#include <QPainter>

MyGUI::MyGUI(Service& s, QWidget* parent) : QMainWindow(parent), service{ s } {
    ui.setupUi(this);
    setWindowTitle("Tenants Manager");
    initUI();
    addEventListeners();
}

void MyGUI::initUI() {
    NotifUi = nullptr;
    //l = new QListWidget;
    help = new QAction("&How to use the app...", this);
    undoB = new QPushButton("          &Undo         ",this);
    add = new QPushButton(" &Add Tenant  ");
    modif = new QPushButton("  &Modify Tenant  ");
    del = new QPushButton("&Delete Tenant");
    find = new QPushButton("&Find apartament");
    filter1 = new QPushButton("Filter by &type");
    filter2 = new QPushButton(" Filter by &surface ");
    sort1 = new QPushButton("Sort by name (desc)");
    sort2 = new QPushButton("Sort by area (desc)");
    sort3 = new QPushButton("Sort by type and area (desc)");
    sort4 = new QPushButton(" Sort by name (asc) ");
    sort5 = new QPushButton(" Sort by area (asc) ");
    sort6 = new QPushButton(" Sort by type and area (asc) ");
    report = new QPushButton(" Type &Report ");
    notif = new QPushButton("   &Notification List   ");
    notifRdOnly = new QPushButton("Notification &List Draw");
    name = new QLineEdit();
    apartament = new QLineEdit();
    type = new QLineEdit();
    area = new QLineEdit();
    NotifEditLine = new QLineEdit();

    AddToNotif = new QPushButton("Add to Not&ification List");
    AddRandToNotif = new QPushButton("Add Random to Notificati&on List");
    ClearNotif = new QPushButton("&Clear Notification List");

    QFont font("Palatino Linotype");
    add->setFont(font);
    modif->setFont(font);
    del->setFont(font);
    find->setFont(font);
    filter1->setFont(font);
    filter2->setFont(font);
    undoB->setFont(font);
    report->setFont(font);
    notif->setFont(font);
    notifRdOnly->setFont(font);
    sort1->setFont(font);
    sort2->setFont(font);
    sort3->setFont(font);
    sort4->setFont(font);
    sort5->setFont(font);
    sort6->setFont(font);

    QWidget* main = new QWidget(this);
    QWidget* inputs = new QWidget();
    QHBoxLayout* hLay = new QHBoxLayout();
    QHBoxLayout* hLayButtons = new QHBoxLayout();
    QHBoxLayout* hLayButtons2 = new QHBoxLayout();
    QHBoxLayout* hLayButtons3 = new QHBoxLayout();
    QHBoxLayout* hLayButtons4 = new QHBoxLayout(); 
    QHBoxLayout* hLayButtons5 = new QHBoxLayout();
    QVBoxLayout* vLayInputs = new QVBoxLayout();
    QHBoxLayout* hLayName = new QHBoxLayout();
    QHBoxLayout* hLayApart = new QHBoxLayout();
    QHBoxLayout* hLayType = new QHBoxLayout();
    QHBoxLayout* hLayArea = new QHBoxLayout();
    QHBoxLayout* hLayNotif = new QHBoxLayout(); 
    QHBoxLayout* hLayNotif2 = new QHBoxLayout();
    QVBoxLayout* vLay = new QVBoxLayout();
    QVBoxLayout* vLayList = new QVBoxLayout();
    QLabel* nameL = new QLabel("          Owner's Name:  ");
    QLabel* apartamentL = new QLabel("Apartament Number:  ");
    QLabel* typeL = new QLabel("      Apartament Type:  ");
    QLabel* areaL = new QLabel("      Apartament Area:  ");
    QLabel* listL = new QLabel("        Tenants List\n");
    QLabel* fieldsL = new QLabel("                          Tenant Details\n");

    vector<Tenant> v = service.get_all_from_repo();
    mainList = new QListView;
    mainList->setMinimumSize(250, 100);
    mainListModel = new MyListModel(v);
    mainList->setModel(mainListModel);

    //initWidgetList(l);

    hLayName->addWidget(nameL);
    hLayName->addWidget(name);
    hLayApart->addWidget(apartamentL);
    hLayApart->addWidget(apartament);
    hLayType->addWidget(typeL);
    hLayType->addWidget(type);
    hLayArea->addWidget(areaL);
    hLayArea->addWidget(area);

    vLayInputs->addStretch();
    vLayInputs->addWidget(fieldsL);
    vLayInputs->addLayout(hLayName);
    vLayInputs->addLayout(hLayApart);
    vLayInputs->addLayout(hLayType);
    vLayInputs->addLayout(hLayArea);
    vLayInputs->addSpacing(10);

    hLayButtons->addWidget(add);
    hLayButtons->addStretch();
    hLayButtons->addWidget(modif);
    hLayButtons->addStretch();
    hLayButtons->addWidget(del);
    hLayButtons->addStretch();
    hLayButtons->addWidget(find);
    hLayButtons2->addWidget(filter1);
    hLayButtons2->addStretch();
    hLayButtons2->addWidget(filter2);
    hLayButtons2->addStretch();
    hLayButtons2->addWidget(report);
    hLayButtons2->addStretch(); 
    hLayButtons2->addWidget(undoB);
    
    hLayButtons3->addWidget(sort1);
    hLayButtons3->addStretch();
    hLayButtons3->addWidget(sort2);
    hLayButtons3->addStretch();
    hLayButtons3->addWidget(sort3);

    hLayButtons4->addWidget(sort4);
    hLayButtons4->addStretch();
    hLayButtons4->addWidget(sort5);
    hLayButtons4->addStretch();
    hLayButtons4->addWidget(sort6);

    hLayButtons5->addWidget(notif); 
    hLayButtons5->addStretch();
    hLayButtons5->addWidget(notifRdOnly);

    hLayNotif->addWidget(AddToNotif);
    hLayNotif->addStretch();
    hLayNotif->addWidget(AddRandToNotif);
    hLayNotif->addStretch();
    hLayNotif->addWidget(ClearNotif);

    hLayNotif2->addWidget(new QLabel("Insert apartament number or amount of apartaments:"));
    hLayNotif2->addWidget(NotifEditLine);

    vLay->addStretch();
    vLay->addLayout(vLayInputs);
    vLay->addLayout(hLayButtons);
    vLay->addLayout(hLayButtons2); 
    vLay->addLayout(hLayButtons5); 
    vLay->addSpacing(15);
    vLay->addWidget(new QLabel("Notification list management:"));
    vLay->addLayout(hLayNotif2);
    vLay->addLayout(hLayNotif); 

    vLayList->addWidget(listL);
    vLayList->addWidget(mainList);
    vLayList->addSpacing(20);
    vLayList->addLayout(hLayButtons3);
    vLayList->addLayout(hLayButtons4);

    hLay->addSpacing(10); 
    //hLay->addWidget(mainList); 
    hLay->addSpacing(20);
    hLay->addLayout(vLayList);
    hLay->addSpacing(20);
    hLay->addLayout(vLay);
    hLay->addSpacing(10); 
   
    
    butoaneaux = new QVBoxLayout();
    butoaneaux->addLayout(hLay);
    butoaneaux2 = new QHBoxLayout();

    //generam butoane dinamic
    generateButtons();
    butoaneaux->addSpacing(20);
    butoaneaux->addLayout(butoaneaux2);

    main->setLayout(butoaneaux);
    helpMenu = menuBar()->addMenu("&Help");
    helpMenu->setFont(font);
    helpMenu->addAction(help);
    
    this->setCentralWidget(main);
}

void MyGUI::addEventListeners() {
    QObject::connect(help, &QAction::triggered, this, [&]() { helpWindow(); });
    QObject::connect(undoB, &QPushButton::clicked, this, [&]() { undo(); });
    QObject::connect(report, &QPushButton::clicked, this, [&]() { typeReportWindow(); });
    QObject::connect(notif, &QPushButton::clicked, this, [&]() { notificationListWindow(); });
    QObject::connect(notifRdOnly, &QPushButton::clicked, this, [&]() { notificationListRdOnlWindow(); });
    QObject::connect(add, &QPushButton::clicked, this, [&]() { addTenant(); }); 
    QObject::connect(modif, &QPushButton::clicked, this, [&]() { editTenant(); });
    QObject::connect(del, &QPushButton::clicked, this, [&]() { deleteTenant(); });
    QObject::connect(find, &QPushButton::clicked, this, [&]() { findApartament(); });
    QObject::connect(filter1, &QPushButton::clicked, this, [&]() { filterByType(); });
    QObject::connect(filter2, &QPushButton::clicked, this, [&]() { filterByArea(); });
    QObject::connect(sort1, &QPushButton::clicked, this, [&]() { sort(1); });
    QObject::connect(sort2, &QPushButton::clicked, this, [&]() { sort(3); });
    QObject::connect(sort3, &QPushButton::clicked, this, [&]() { sort(5); });
    QObject::connect(sort4, &QPushButton::clicked, this, [&]() { sort(2); });
    QObject::connect(sort5, &QPushButton::clicked, this, [&]() { sort(4); });
    QObject::connect(sort6, &QPushButton::clicked, this, [&]() { sort(6); });
    QObject::connect(AddToNotif, &QPushButton::clicked, this, [&]() { addToNotifFunc(); clearInputLines(); });
    QObject::connect(AddRandToNotif, &QPushButton::clicked, this, [&]() { addRandToNotifFunc(); clearInputLines(); });
    QObject::connect(ClearNotif, &QPushButton::clicked, this, [&]() { service.clear_notification_list(); });
    /*QObject::connect(l, &QListWidget::itemSelectionChanged, this, [this]() {
        for (QListWidgetItem* item : l->selectedItems()) dumpDataFromListItem(item);
    });*/
    QObject::connect(mainList->selectionModel(), &QItemSelectionModel::selectionChanged, [&]() {
        if (mainList->selectionModel()->selectedIndexes().isEmpty()) {
            //nu este nimic selectat (golesc detaliile)
            return;
        }
        QModelIndex selIndex = mainList->selectionModel()->selectedIndexes().at(0);
        //putem lua date din lista
        QString text = selIndex.data(Qt::DisplayRole).toString();
        QVector<QString> tenant = text.split("-");
        name->setText(tenant[0]);
        apartament->setText(tenant[1]);
        type->setText(tenant[2]);
        area->setText(tenant[3]);
        NotifEditLine->setText(tenant[1]);
    });
}

void MyGUI::notificationListWindow() { 
    NotifUi = new NotificationListUI(service); 
    service.addObserver(NotifUi);
    NotifUi->show();
} 

void MyGUI::notificationListRdOnlWindow() { 
    DrawUi = new NotificationListDrawingUI(service); 
    service.addObserver(DrawUi);
    DrawUi->show();
}

void MyGUI::typeReportWindow() {
    QWidget* window = new QWidget;
    window->setWindowTitle("Types Report");
    QPushButton* exit_window = new QPushButton("&Exit");
    QObject::connect(exit_window, &QPushButton::clicked, window, &QWidget::close);
    QLabel* textL = new QLabel("        Types Report\n");
    QLabel* spaceL = new QLabel("   ");
    QListView* report = new QListView;
    QVBoxLayout* vLay = new QVBoxLayout();
    QHBoxLayout* hLay = new QHBoxLayout();
    QFont font("Palatino Linotype");
    exit_window->setFont(font);
    exit_window->setStyleSheet("background-color:lightgrey;");

    std::map<string, vector<Tenant>> rep;
    service.create_report(rep); 

    /*for (const auto& pair : rep) {
        QString t = t.fromStdString(pair.first);
        new QListWidgetItem("      Apartaments with type \""+t+"\":", report);
        for (const auto& tenant : pair.second) {
            QString name = name.fromStdString(tenant.get_name()); 
            QString type = type.fromStdString(tenant.get_type());  
            QString apart = apart.number(tenant.get_apartament());  
            QString area = area.number(tenant.get_area()); 
            new QListWidgetItem("Owner: "+name + ";   Ap. number: " + apart + ";   Ap. type: " + type + ";   Area: " + area + " sq meters", report);
        }
        new QListWidgetItem(" ", report);
    }*/
    vector<Tenant> aps;
    for (const auto& pair : rep) {
        string s = "\n  Tenants with apartament of type \"" +pair.first+ "\":\n";
        Tenant t(s, -1, "", -1);
        aps.push_back(t);
        for (const auto& tenant : pair.second)
            aps.push_back(tenant);
    }

    MyListModel* model = new MyListModel(aps);
    report->setModel(model);
    report->setMinimumWidth(350);

    vLay->addWidget(textL);
    vLay->addWidget(report);
    vLay->addWidget(spaceL);
    hLay->addStretch();
    hLay->addWidget(exit_window);
    hLay->addStretch();
    vLay->addLayout(hLay);
    window->setLayout(vLay);
    window->show();
}

void MyGUI::initWidgetList(QListWidget* l) {
    for (const Tenant& t : service.get_all_from_repo()) {
        QString tenant, name, type, apart, area;
        name = name.fromStdString(t.get_name());
        type = type.fromStdString(t.get_type()); 
        apart = apart.number(t.get_apartament()); 
        area = area.number(t.get_area());
        tenant = name + "-" + apart + "-" + type + "-" + area;
        new QListWidgetItem(tenant, l);
    }
}

void MyGUI::helpWindow() {
    QWidget* window = new QWidget();
    window->setWindowTitle("Help Window");
    QPushButton* exit_window = new QPushButton("&Got it!");
    QObject::connect(exit_window, &QPushButton::clicked, window, &QWidget::close);
    QVBoxLayout* vLay = new QVBoxLayout();
    QHBoxLayout* hLayAux = new QHBoxLayout();
    QHBoxLayout* hLay = new QHBoxLayout();
    QFont font("Palatino Linotype");
    exit_window->setFont(font);
    exit_window->setStyleSheet("background-color:lightgrey;");

    QLabel* text = new QLabel("\n                 App instructions/explanations:\n\n\
    - Add operation: add new tenant by inserting a valid name, ap. number, type and area   \n\
    - Delete operation: delete a tenant that has a certain name (provided by the user)   \n\
    - Edit operation: modify a tenant's apartament details like area or type   \n\
    - Find operation: find an apartament by it's number   \n\
    - Filtering: filter all tenants in the app by a specified criteria   \n\
    - Sorting: sort all tenants in the app by specified criteria and order   \n\
    - Types Report: shows a window with the list of tenants organised by apartament types   \n\
    - Notification List Draw: generates a graphical depiction of the notifcation list   \n\
    - Notification List: create a notification list with apartaments stored in the app;   \n\
                                  manage and export it in a \".csv\" or \".html\" file, if needed   \n\n\
        Notes:\n\
 *A tenant is \"already existent\" if their name or apartament no. already appear in the app   \n\
 *Tenants can be easily seen and accessed by clicking them in the tenants list   \n\
 *The notification list can be managed using features below \"Notification List Management\"            \n\n\
    ");
    QFont font2("Sheriff");
    text->setFont(font2);

    hLay->addStretch();
    hLay->addWidget(text);
    hLay->addStretch();
    hLayAux->addStretch();
    hLayAux->addWidget(exit_window);
    hLayAux->addStretch();
    vLay->addStretch();
    vLay->addLayout(hLay);
    vLay->addLayout(hLayAux);
    vLay->addStretch();

    window->setLayout(vLay);
    window->show();
}

void MyGUI::addTenant() {
    if (name->text() != "" && apartament->text() != "" && type->text() != "" && area->text() != "") {
        qDebug() << name->text() + ", " + apartament->text() + ", " + type->text() + ", " + area->text();
        try {
            bool ok;
            string Sname = name->text().toStdString();
            string Stype = type->text().toStdString();
            int Iapart = apartament->text().toInt(&ok);
            if (!ok) throw(ServiceException("Invalid apartament number!"));
            int Iarea = area->text().toInt(&ok);
            if (!ok) throw(ServiceException("Invalid apartament area!"));
            service.add_tenant(Sname,Iapart,Stype,Iarea);
            QMessageBox::information(nullptr, "Addition Success", "The tenant " + name->text() + " has been added!", QMessageBox::Ok);
            //updateWidgetList(service.get_all_from_repo());
            mainListModel->setTenants(service.get_all_from_repo());

            generateButtons();
        }
        catch (ServiceException& se) {
            QString err = err.fromStdString(se.get_message());
            QMessageBox::critical(nullptr, "Addition Fail", err, QMessageBox::Close);
        }
        clearInputLines();
        
    }
    else QMessageBox::critical(nullptr, "Addition Fail", "Tenant details are incomplete!", QMessageBox::Close);
}

void MyGUI::editTenant() {
    if (name->text() != "" && type->text() != "" && area->text() != "") {
        qDebug() << name->text() + ", " + apartament->text() + ", " + type->text() + ", " + area->text();
        try {
            bool ok;
            string Sname = name->text().toStdString();
            string Stype = type->text().toStdString();
            int Iarea = area->text().toInt(&ok);
            if (!ok) throw(ServiceException("Invalid apartament area!"));
            service.edit_tenant(Sname, -1, Stype, Iarea);
            QMessageBox::information(nullptr, "Modification Success", "Tenant " + name->text() + "'s details have been modified!", QMessageBox::Ok);
            //updateWidgetList(service.get_all_from_repo());
            mainListModel->setTenants(service.get_all_from_repo());
            generateButtons();
        }
        catch (ServiceException& se) { 
            QString err = err.fromStdString(se.get_message()); 
            QMessageBox::critical(nullptr, "Modification Fail", err, QMessageBox::Close);
        }
        clearInputLines();
        
    }
    else QMessageBox::critical(nullptr, "Modification Fail", "Tenant details are incomplete!", QMessageBox::Close);
}

void MyGUI::deleteTenant() {
    if (name->text() != "") {
        qDebug() << name->text();
        try {
            string Sname = name->text().toStdString();
            service.delete_tenant(Sname);
            QMessageBox::information(nullptr, "Deletion Success", "The tenant " + name->text() + " has been deleted!", QMessageBox::Ok);
            //updateWidgetList(service.get_all_from_repo());
            mainListModel->setTenants(service.get_all_from_repo());
            generateButtons();
        }
        catch (ServiceException& se) { 
            QString err = err.fromStdString(se.get_message()); 
            QMessageBox::critical(nullptr, "Modification Fail", err, QMessageBox::Close); 
        } 
        clearInputLines(); 
        
    }
    else QMessageBox::critical(nullptr, "Deletion Fail", "Please enter a tenant's name!", QMessageBox::Close);
}

void MyGUI::findApartament() const {
    if (apartament->text() != "") {
        qDebug() << apartament->text();
        try {
            bool ok;
            int Iapart = apartament->text().toInt(&ok);
            if (!ok) throw(ServiceException("Invalid apartament number!"));
            Tenant found = service.find_apartament(Iapart);
            QString name = name.fromStdString(found.get_name());
            QString type = type.fromStdString(found.get_type());
            QString area = area.number(found.get_area());
            QMessageBox::information(nullptr, "Found Match", "The apartament no. " + apartament->text() + " has been found!\nDetails:\n   -Owner: " + name + "\n   -Type: " + type + "\n   -Area: " + area + " sq meters\n", QMessageBox::Ok); 
        }
        catch (ServiceException& se) { 
            QString err = err.fromStdString(se.get_message()); 
            QMessageBox::critical(nullptr, "Modification Fail", err, QMessageBox::Close); 
        }
        clearInputLines(); 
    }
    else QMessageBox::critical(nullptr, "Find Fail", "Please enter an apartament's number!", QMessageBox::Close);
}

void MyGUI::filterByType() {
    if (type->text() != "") {
        qDebug() << type->text();
        try {
            vector<Tenant> filtered = service.filter_by_type(type->text().toStdString());
            QMessageBox::information(nullptr, "Filter Success", "Saved tenants have been successfully filtered by type \"" + type->text() + "\"!", QMessageBox::Ok);
            //updateWidgetList(filtered);
            mainListModel->setTenants(filtered);
        }
        catch (ServiceException& se) { 
            QString err = err.fromStdString(se.get_message()); 
            QMessageBox::critical(nullptr, "Filter Fail", err, QMessageBox::Close); 
        }
        clearInputLines();
    }
    else QMessageBox::critical(nullptr, "Filter Fail", "Please enter an apartament's type!", QMessageBox::Close);
}

void MyGUI::filterByArea() {
    if (area->text() != "") {
        qDebug() << area->text();
        try {
            vector<Tenant> filtered = service.filter_by_area(area->text().toInt());
            QMessageBox::information(nullptr, "Filter Success", "Saved tenants have been successfully filtered by area " + area->text() + "!", QMessageBox::Ok); 
            //updateWidgetList(filtered);
            mainListModel->setTenants(filtered);
        }
        catch (ServiceException& se) {
            QString err = err.fromStdString(se.get_message());  
            QMessageBox::critical(nullptr, "Filter Fail", err, QMessageBox::Close);  
        }  
        clearInputLines(); 
    }
    else QMessageBox::critical(nullptr, "Filter Fail", "Please enter an apartament's area!", QMessageBox::Close); 
}

void MyGUI::sort(const int& sortType) {
    qDebug() << sortType;
    vector<Tenant> sorted = service.sort_manager(sortType); 
    //updateWidgetList(sorted); 
    mainListModel->setTenants(sorted);
}

void MyGUI::addToNotifFunc() {
    try {
        bool ok; 
        int nrAp = NotifEditLine->text().toInt(&ok); 
        if (!ok) throw(ServiceException("Invalid apartament number!")); 
        service.add_apartament_to_notification_list(nrAp); 
    }
    catch (ServiceException& se) { 
        QString err = err.fromStdString(se.get_message()); 
        QMessageBox::critical(nullptr, "Addition Fail", err, QMessageBox::Close); 
    }
}

void MyGUI::addRandToNotifFunc() {
    try {
        bool ok;
        int amount = NotifEditLine->text().toInt(&ok);
        if (!ok) throw(ServiceException("Invalid amount of apartaments!"));
        service.add_apartaments_randomly(amount); 
    }
    catch (ServiceException& se) { 
        QString err = err.fromStdString(se.get_message()); 
        QMessageBox::critical(nullptr, "Addition Fail", err, QMessageBox::Close); 
    }
}

void MyGUI::clearInputLines() const noexcept {
    name->setText("");
    apartament->setText("");
    type->setText("");
    area->setText("");
    NotifEditLine->setText("");
}

void MyGUI::undo() {
    qDebug() << "undo";
    try { 
        service.undo(); 
        //updateWidgetList(service.get_all_from_repo());
        mainListModel->setTenants(service.get_all_from_repo());
        generateButtons();
    }
    catch (ServiceException& se) {
        QString err = err.fromStdString(se.get_message()); 
        QMessageBox::critical(nullptr, "Undo Fail", err, QMessageBox::Close); 
    }
}

//void MyGUI::updateWidgetList(const vector<Tenant>& vect) {
//    last = nullptr;
//    //l->clear();
//    for (const Tenant& t : vect) { 
//        QString tenant, name, type, apart, area; 
//        name = name.fromStdString(t.get_name()); 
//        type = type.fromStdString(t.get_type()); 
//        apart = apart.number(t.get_apartament()); 
//        area = area.number(t.get_area()); 
//        tenant = name + "-" + apart + "-" + type + "-" + area; 
//        new QListWidgetItem(tenant, l); 
//    }  
//}

void MyGUI::dumpDataFromListItem(QListWidgetItem* elem) const {
    QString str = elem->text();
    QStringList dataList = str.split("-");
    QVector<QString> data = dataList.toVector();
    name->setText(data[0]);
    apartament->setText(data[1]);
    type->setText(data[2]);
    area->setText(data[3]);
    NotifEditLine->setText(data[1]);
}

void MyGUI::generateButtons() {
    std::map<string, vector<Tenant>> rep;
    service.create_report(rep);

    for (auto b : butoane) delete b;
    butoane.clear();

    for (const auto& pair : rep) {
        QString t = t.fromStdString(pair.first);
        QPushButton* nou = new QPushButton(t);
        QFont font("Palatino Linotype");
        nou->setFont(font);
        nou->setStyleSheet("background-color:lightgrey;");
        butoaneaux2->addWidget(nou);
        butoane.push_back(nou);
        int nr = 0;
        for (const auto& tenant : pair.second) nr++;
        QString n = n.number(nr);
        QObject::connect(nou, &QPushButton::clicked, this, [t, n]() { QMessageBox::information(nullptr, t + " type", "There are " + n + " apartaments of this type!", QMessageBox::Ok); });
    }
}

void NotificationListUI::init() {
    this->setWindowTitle("Notification List");
    reader = new QLineEdit;
    context = new QLabel;
    enter = new QPushButton("Enter");
    cancel = new QPushButton("Done");
    exit = new QPushButton("Exit");
    exprt = new QPushButton("Export");
    add = new QPushButton("Add Apartament");
    clear = new QPushButton("Empty List");
    random = new QPushButton("Random Add Apartaments");
    textL = new QLabel("        Notification List\n");
    spaceL = new QLabel("   ");
    notif = new QListView;
    vector<Tenant> aps = serv.get_notif_list();
    notifModel = new MyListModel(aps);
    notif->setModel(notifModel);

    QVBoxLayout* vLayList = new QVBoxLayout();
    QVBoxLayout* vLayButtons = new QVBoxLayout();
    QVBoxLayout* vLay = new QVBoxLayout();
    QHBoxLayout* hLayContext = new QHBoxLayout();
    QHBoxLayout* hLayButtons = new QHBoxLayout();
    QHBoxLayout* hLay = new QHBoxLayout();
    QHBoxLayout* hLayExit = new QHBoxLayout();
    QFont font("Palatino Linotype");
    enter->setFont(font);
    cancel->setFont(font);
    exit->setFont(font);
    exprt->setFont(font);
    add->setFont(font);
    clear->setFont(font);
    random->setFont(font);
    exit->setStyleSheet("background-color:lightgrey;");

    vLayList->addWidget(textL);
    vLayList->addWidget(notif);
    hLay->addLayout(vLayList);
    vLay->addStretch();
    vLay->addWidget(context);
    hLayContext->addStretch();
    hLayContext->addWidget(reader);
    hLayContext->addWidget(enter);
    hLayContext->addWidget(cancel);
    hLayContext->addStretch();
    vLay->addLayout(hLayContext);
    reader->hide();
    enter->hide();
    cancel->hide();
    vLayButtons->addWidget(add); 
    vLayButtons->addWidget(random); 
    vLayButtons->addWidget(clear); 
    vLayButtons->addWidget(exprt); 
    hLayButtons->addStretch();
    hLayButtons->addLayout(vLayButtons);
    hLayButtons->addStretch();
    vLay->addLayout(hLayButtons);
    vLay->addStretch();
    hLayExit->addStretch();
    hLayExit->addWidget(exit);
    hLayExit->addStretch();
    vLay->addLayout(hLayExit);
    vLay->addStretch();
    hLay->addWidget(spaceL);
    hLay->addLayout(vLay);
    this->setLayout(hLay);
}

void NotificationListUI::addEventListeners() {
    QObject::connect(add, &QPushButton::clicked, this, [this]() { addTenant(); });
    QObject::connect(random, &QPushButton::clicked, this, [this]() { addSomeTenants(); });
    QObject::connect(clear, &QPushButton::clicked, this, [this]() { clearNotificationList(); });
    QObject::connect(exprt, &QPushButton::clicked, this, [this]() { exportNotificationList(); });
    QObject::connect(cancel, &QPushButton::clicked, this, [this]() { cancelUtil(); });
    QObject::connect(exit, &QPushButton::clicked, this, &QWidget::close);
}

void NotificationListUI::addTenant() {
    context->setText("Enter apartament number:");
    actionUtil();
    QObject::disconnect(enter, &QPushButton::clicked, this, nullptr);
    QObject::connect(enter, &QPushButton::clicked, this, [this]() { text = reader->text(); reader->setText(""); if (text != "") qDebug() << text; doAddTenant(); });
}

void NotificationListUI::addSomeTenants() {
    context->setText("Enter amount of apartaments to be added:");
    actionUtil();
    QObject::disconnect(enter, &QPushButton::clicked, this, nullptr);
    QObject::connect(enter, &QPushButton::clicked, this, [this]() { text = reader->text(); reader->setText(""); if (text != "") qDebug() << text; doAddSomeTenants();  });
}

void NotificationListUI::exportNotificationList() {
    context->setText("Enter a file name (\"[name].[csv/html]\"):");
    actionUtil();
    QObject::disconnect(enter, &QPushButton::clicked, this, nullptr);
    QObject::connect(enter, &QPushButton::clicked, this, [this]() { text = reader->text(); reader->setText(""); if (text != "") qDebug() << text; doExport(); });
}

void NotificationListUI::cancelUtil() {
    reader->setText("");
    context->hide();
    reader->hide();
    enter->hide();
    cancel->hide();
    add->show();
    random->show();
    clear->show();
    exprt->show();
}

void NotificationListUI::actionUtil() {
    add->hide();
    random->hide();
    clear->hide();
    exprt->hide();
    context->show();
    reader->show();
    enter->show();
    cancel->show();
}

void NotificationListUI::clearNotificationList() {
    serv.clear_notification_list();
    //updateWidgetList();
    notifModel->setTenants(serv.get_notif_list());
    qDebug() << "clear";
}

void NotificationListUI::doAddTenant() { 
    try {
        bool ok;  
        int nrAp = text.toInt(&ok);   
        if (!ok) throw(ServiceException("Invalid apartament number!"));  
        serv.add_apartament_to_notification_list(nrAp);
        //updateWidgetList();
        notifModel->setTenants(serv.get_notif_list());
        qDebug() << "add";
    }
    catch (ServiceException& se) { 
        QString err = err.fromStdString(se.get_message()); 
        QMessageBox::critical(nullptr, "Addition Fail", err, QMessageBox::Close); 
    }
}

void NotificationListUI::doAddSomeTenants() { 
    try {
        bool ok; 
        int amount = text.toInt(&ok); 
        if (!ok) throw(ServiceException("Invalid amount of apartaments!")); 
        serv.add_apartaments_randomly(amount); 
        //updateWidgetList(); 
        notifModel->setTenants(serv.get_notif_list());
        qDebug() << "add_more"; 
    }
    catch (ServiceException& se) { 
        QString err = err.fromStdString(se.get_message()); 
        QMessageBox::critical(nullptr, "Addition Fail", err, QMessageBox::Close); 
    }
}

void NotificationListUI::doExport() { 
    string file = text.toStdString();
    if (file.size() > 4 && file[file.size() - 4] == '.' && file[file.size() - 3] == 'c' && file[file.size() - 2] == 's' && file[file.size() - 1] == 'v') {
        serv.export_to_file(file);
        QMessageBox::information(nullptr, "Export Success", "The notification list has been exported to file: "+text, QMessageBox::Ok);
        return; 
    }
    if (file.size() > 5 && file[file.size() - 5] == '.' && file[file.size() - 4] == 'h' && file[file.size() - 3] == 't' && file[file.size() - 2] == 'm' && file[file.size() - 1] == 'l') {
        serv.export_to_file(file);
        QMessageBox::information(nullptr, "Export Success", "The notification list has been exported to file: " + text, QMessageBox::Ok); 
        return;
    }
    QMessageBox::critical(nullptr, "Export Fail", "Invalid file name!", QMessageBox::Close);
    qDebug() << "export";
}

//void NotificationListUI::updateWidgetList() { 
//    notif->clear();  
//    vector<Tenant> vect = serv.get_notif_list();
//    for (const Tenant& t : vect) {  
//        QString tenant, name, type, apart, area;   
//        name = name.fromStdString(t.get_name());  
//        type = type.fromStdString(t.get_type());  
//        apart = apart.number(t.get_apartament());  
//        area = area.number(t.get_area()); 
//        tenant = name + "-" + apart + "-" + type + "-" + area; 
//        new QListWidgetItem(tenant, notif);  
//    }
//}

void NotificationListUI::update() { /*updateWidgetList();*/notifModel->setTenants(serv.get_notif_list());}

void NotificationListDrawingUI::paintEvent(QPaintEvent* ev) {
    QPainter p{ this };
    vector<Tenant> list = serv.get_notif_list();
    srand(Seed);
    int x, y;
    for (const Tenant& t : list) {
        y = rand() % (this->height() - 70);
        x = rand() % (this->width() - 50); 
        p.drawImage(x,y,QImage("apartament.png"));
    }
}

void NotificationListDrawingUI::update() { paintEvent(nullptr); }
