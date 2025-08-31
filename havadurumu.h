#ifndef HAVADURUMU_H
#define HAVADURUMU_H

#include <QMainWindow>
#include <QNetworkAccessManager>
#include <QNetworkReply>

QT_BEGIN_NAMESPACE
namespace Ui {
class havadurumu;
}
QT_END_NAMESPACE

class havadurumu : public QMainWindow
{
    Q_OBJECT

public:
    // Constructor (Uygulama açıldığında çalışır)
    havadurumu(QWidget *parent = nullptr);

    // Destructor (Uygulama kapanırken çalışır, belleği temizler)
    ~havadurumu();

private slots:
    void onResult(QNetworkReply *reply);// API'den veri geldiğinde çalışacak fonksiyon

private slots:
    void on_CelciusButton_clicked(); //C butonu

    void on_FahreneitButton_clicked(); //F butonu

    void on_havadurumu_iconSizeChanged(const QSize &iconSize);

private slots:
    void on_fetchButton_clicked(); //Receive butonu

    void on_exitButton_clicked(); //Exit butonu

    void onCellClicked(const QString &linkData); //Saatlere tıklansın

    void on_suggestionButton_clicked(); //Öneri butonu

private:
    Ui::havadurumu *ui; // Arayüzü bileşenlerini temsil eder

    QNetworkAccessManager *manager; // API isteklerini yöneten nesne

    QString currentUnit; // Anlık kullanılan sıcaklık birimi

    void fetchWeather(QString unit); // Hava durumu verilerini almak için fonksiyon

    void displayError(const QString &message);

    bool errorDialogVisible = false;

    QString lastWeatherCondition;

};

#endif // HAVADURUMU_H
