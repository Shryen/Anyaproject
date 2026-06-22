#include <QHBoxLayout>
#include <QMessageBox>
#include "MainWindow.h"
#include "Buttons/AddButton.h"
#include "Database/Database.h"
#include "Content/Content.h"
#include "Sidebar/Sidebar.h"


MainWindow::MainWindow(QWidget* parent) : QWidget(parent) {
	// Start Database
	database = new Database();

	// Setup Window
	setWindowTitle("Számlák");
	setFixedSize(QSize{ 1280,720 });
	setStyleSheet(R"(
		background-color: #fff5ee;
	)");

	// Setup Layout and widgets
	QHBoxLayout* MainLayout = new QHBoxLayout(this);
	MainLayout->setContentsMargins(0, 0, 0, 0);
	MainLayout->setSpacing(0);

	sideBar = new Sidebar(this);
	contentWidget = new Content(this);

	MainLayout->addWidget(sideBar);
	MainLayout->addWidget(contentWidget);

	contentWidget->UpdateContent(database);
	QString profitSum = database->GetSumOfInvoices();
	contentWidget->SetProfitSum(profitSum);

	connect(contentWidget, &Content::AddToDatabaseRequested, this,&MainWindow::onDataReceived);
	connect(contentWidget, &Content::DeleteFromDatabaseRequested, this, &MainWindow::onDeleteRequested);
	connect(contentWidget, &Content::EditFromDatabaseRequested, this, &MainWindow::onEditRequested);
	connect(contentWidget, &Content::OnListChanged, this, [this]() {
		contentWidget->UpdateContent(database);
		QString profitSum = database->GetSumOfInvoices();
		contentWidget->SetProfitSum(profitSum);
	});
	connect(contentWidget, &Content::InvoiceSelected, this, &MainWindow::onInvoiceSelected);
}

void MainWindow::onDeleteRequested()
{
	QString message = "<h1>Biztosan szeretnéd törölni a kiválasztott számlát?</h1>";
	QString selectedInvoiceInfo = database->getInvoiceInfo(selectedInvoiceId);
	QMessageBox* confirmDialog = new QMessageBox(this);
	confirmDialog->setText(message);
	confirmDialog->setInformativeText(selectedInvoiceInfo);
	QPushButton* YesButton = confirmDialog->addButton(tr("Igen"), QMessageBox::ActionRole);
	QPushButton* NoButton = confirmDialog->addButton(tr("Nem"), QMessageBox::ActionRole);

	confirmDialog->setStyleSheet(R"(
    QMessageBox {
        background-color: #fff5ee;
    }
    QLabel {
        color: black;
        text-align: center;
        qproperty-alignment: AlignCenter;
    }
    QPushButton {
        background-color: #5fa8d3;
        color: #f0ead6;
        font-weight: bold;
        font-size: 13pt;
        border-radius: 6px;
        border: 2px solid #4f98c3;
        padding: 6px 20px;
        min-width: 80px;
    }
    QPushButton:hover {
        background-color: #4f98c3;
    }
    QPushButton:pressed {
        background-color: #3f88b3;
    }
)");
	confirmDialog->exec();

	if (confirmDialog->clickedButton() == YesButton) {
		if (selectedInvoiceId != -1) {
			database->deleteData(selectedInvoiceId);
			contentWidget->UpdateContent(database);
			contentWidget->OnListChanged();
		}
	}
	else if (confirmDialog->clickedButton() == NoButton) {
		
	}
	
}

void MainWindow::onEditRequested(const Invoice& Data)
{
	database->updateData(Data);
	contentWidget->UpdateContent(database);
	contentWidget->OnListChanged();
}

void MainWindow::onInvoiceSelected(int id)
{
	selectedInvoiceId = id;
}


void MainWindow::onDataReceived(const Invoice& Data) {
	database->insertData(Data);
	contentWidget->UpdateContent(database);
	contentWidget->OnListChanged();
}
