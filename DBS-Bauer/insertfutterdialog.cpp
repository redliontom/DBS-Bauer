#include "insertfutterdialog.h"
#include "ui_insertfutterdialog.h"
#include <QtSql/QSqlDatabase>
#include <QDebug>
#include <QSqlError>
#include <QSqlQuery>
#include "errordialog.h"

InsertFutterDialog::InsertFutterDialog(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::InsertFutterDialog)
{
	ui->setupUi(this);
	SetupLager();
}

InsertFutterDialog::~InsertFutterDialog()
{
	delete ui;
}

void InsertFutterDialog::on_buttonBox_accepted()
{

	QSqlQuery q;
	q.prepare("SELECT PK_Lager FROM LAGER WHERE Lagerart = ?");
	q.bindValue(0,ui->Lager->currentText());
	q.exec();
	q.first();
	int pk = q.value(0).toInt();
	q.clear();
	QString insertQuery =
			QString("SELECT usp_FutterEinfuegen('%1',%2,%3,%4)")
			.arg(
				ui->Name->text(),
				QString::number(ui->Preis->value()),
				QString::number(ui->Bestand->value()),
				QString::number(pk)
			);
	if(!q.exec(insertQuery)) {
		ErrorDialog() << q.lastError();
	}
}

void InsertFutterDialog::SetupLager()
{
	QSqlQuery q;

	ui->Lager->clear();

	if(!q.exec("SELECT * FROM \"v_Lagername\"")) {
		ErrorDialog() << q.lastError();
	}

	while(q.next()) {
		ui->Lager->addItem(q.value(0).toString());
	}
	ui->Lager->setCurrentIndex(0);
	ui->Lager->update();
	ui->Lager->show();
}
