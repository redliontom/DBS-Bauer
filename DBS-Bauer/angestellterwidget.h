#ifndef ANGESTELLTERWIDGET_H
#define ANGESTELLTERWIDGET_H

#include <QWidget>
#include <QSqlTableModel>

namespace Ui {
class AngestellterWidget;
}

class AngestellterWidget : public QWidget
{
	Q_OBJECT
	QSqlTableModel *angestellten;
	QSqlQueryModel *arbeiten;

public:
	explicit AngestellterWidget(QWidget *parent = 0);
	~AngestellterWidget();

private slots:
	void on_tableAngestellter_clicked(const QModelIndex &index);

	void on_AngestellterNeu_clicked();

	void on_AngestellterTot_clicked();

private:
	int currentPk;
	Ui::AngestellterWidget *ui;
};

#endif // ANGESTELLTERWIDGET_H
