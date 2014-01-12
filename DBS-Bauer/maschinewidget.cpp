#include "maschinewidget.h"
#include "ui_maschinewidget.h"
#include <QtSql/QSqlDatabase>
#include <QDebug>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlQueryModel>

MaschineWidget::MaschineWidget(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::MaschineWidget)
{
	ui->setupUi(this);
	chronik = new QSqlQueryModel(ui->tableVerwendung);
	maschinen = new QSqlTableModel(ui->tableMaschine);
	maschinen->setTable("maschine");

	if(!maschinen->select()) {
		qDebug() << maschinen->lastError();
	}
	ui->tableMaschine->setModel(maschinen);
	ui->tableMaschine->setSelectionBehavior(QAbstractItemView::SelectRows);
	ui->tableMaschine->setSelectionMode(QAbstractItemView::SingleSelection);
	ui->tableMaschine->setEditTriggers(QAbstractItemView::NoEditTriggers);

	// PK verstecken
	ui->tableMaschine->hideColumn(0);
	ui->tableMaschine->hideColumn(1);
}

MaschineWidget::~MaschineWidget()
{
	delete chronik;
	delete maschinen;
	delete ui;
}

void MaschineWidget::on_tableMaschine_clicked(const QModelIndex &index)
{
	bool ok = false;
	int currentPk = (maschinen->index(index.row(), 0)).data().toInt(&ok);

	if (currentPk <= 0 || !ok) {
		qDebug() << maschinen->lastError();
	} else {
		QSqlQuery q;
		if (!q.exec(QString("SELECT * FROM usp_MaschineChronik(%1)").arg(currentPk))) {
			qDebug() << q.lastError();
		}
		chronik->setQuery(q);
		ui->tableVerwendung->setModel(chronik);
		ui->tableVerwendung->hideColumn(0);
	}
}
