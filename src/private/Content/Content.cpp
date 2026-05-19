#include "Content/Content.h"
#include <QVBoxLayout>
#include <QLabel>
#include "Database/Database.h";

Content::Content(QWidget* parent)
{
	SetupMainLayout();
}

void Content::UpdateContent(Database* db) {
	QVector<Szamla> invoices = db->getAllInvoices();
	contentLayout = new QVBoxLayout(contentWidget);
	for(const Szamla& invoce : invoices){
		QLabel* label = new QLabel(QString("ID: %1, Név: %2, Összeg: %3, Dátum: %4")
			.arg(invoce.id)
			.arg(invoce.nev)
			.arg(invoce.osszeg)
			.arg(invoce.datum), this);

		label->setStyleSheet("color: black; border: 1px solid black; border-radius: 10px; font-size: 24pt;");

		contentLayout->addWidget(label);
	}
}

void Content::SetupMainLayout()
{
	QLabel* label = new QLabel("content test", this);
	label->setAlignment(Qt::AlignCenter);
	contentWidget = new QWidget(this);

	m_layout = new QVBoxLayout(this);
	m_layout->setContentsMargins(0, 0, 0, 0);
	m_layout->setSpacing(0);

	m_layout->addWidget(label);
	m_layout->addWidget(contentWidget);

	m_layout->stretch(0);
	label->setStyleSheet(R"(
	font-size: 24px;
	color: black;
	)");
}
