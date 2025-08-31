#include "havadurumu.h"
#include "./ui_havadurumu.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QUrlQuery>
#include <QDebug>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QJsonArray>
#include <QMessageBox>
#include <QRandomGenerator>

//Constructor
havadurumu::havadurumu(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::havadurumu)
{
    ui->setupUi(this);//Arayüz ögelerini ayarlar

    ui->cityLineEdit->setPlaceholderText("ENTER A CITY NAME:"); //cityLineEdit'te şehir ismi girmeden önce yazar

    manager = new QNetworkAccessManager(this); //Ağ (internet) üzerinden veri almak için gereken nesne oluşturulur

    connect(manager, &QNetworkAccessManager::finished,this, &havadurumu::onResult); //Veri geldiğinde onResult fonksiyonunu çağır

    connect(ui->cityLineEdit, &QLineEdit::returnPressed,this, &havadurumu::on_CelciusButton_clicked); //Kullanıcı enter'a bastığında veriyi celcius cinsinden getir

    connect(ui->CelciusButton, &QPushButton::clicked,this, &havadurumu::on_CelciusButton_clicked); //C butonuna basıldığında sıcaklık birimini C cinsinden getir

    connect(ui->FahreneitButton, &QPushButton::clicked,this, &havadurumu::on_FahreneitButton_clicked);//F butonuna basıldığında sıcaklık birimini F cinsinden getir

    connect(ui->fetchButton, &QPushButton::clicked,this, &havadurumu::on_fetchButton_clicked); // Receive butonuna basıldığında veriyi otomatik olarak C cinsinden getir

    connect(ui->exitButton, &QPushButton::clicked, qApp, &QApplication::quit); //Exit butonu ile arayüzü kapat

    connect(ui->resultLabel, &QLabel::linkActivated, this, &havadurumu::onCellClicked); // Herhangi bir saate tıklandığında link gibi algılayarak tıklama sağlasın


    //Hava durumu değerlerinin kaydırmalı gösterilmesini sağlar.
    QLabel *label = ui->resultScrollArea->widget()->findChild<QLabel*>("scrollLabel");
    if (label) {
        label->setWordWrap(true);
        label->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::MinimumExpanding);
        label->setMaximumWidth(700);
    }
}


//Destructor (Uygulama kapanırken oluşur)
havadurumu::~havadurumu()
{
    delete ui;
}

// Hava durumu verilerini çeken fonksiyon (metric: °C, imperial: °F)
void havadurumu::fetchWeather(QString unit) {
    QString city = ui->cityLineEdit->text().trimmed();

    // Eğer kullanıcı şehir ismini girmemişse ve hata kutusu zaten açık değilse
    if (city.isEmpty() && !errorDialogVisible) {
        errorDialogVisible = true; // Artık uyarı kutusu açık, ikinci kez açılmasını engelle

        // Yeni bir hata mesaj kutusu oluştur
        QMessageBox *msgBox = new QMessageBox(this);
        msgBox->setIcon(QMessageBox::Critical);
        msgBox->setWindowTitle("ERROR");
        msgBox->setText("<b style='color:#aa0000;'>PLEASE ENTER A CITY NAME.");
        msgBox->setStandardButtons(QMessageBox::Ok);

        // Arka plan sade stil
        msgBox->setStyleSheet("");

        connect(msgBox, &QMessageBox::finished, this, [this](int){
            errorDialogVisible = false; // Kapatıldığında hata kutusu tekrar gösterilebilir hale gelir
        });

        msgBox->show();
        return;
    }

    currentUnit = unit;  // Sıcaklık birimini °C veya °F cinsinden sakla

    // API anahtarı ve URL oluşturuluyor
    QString apiKey = "MY_API_KEY";
    QString url = QString("http://api.openweathermap.org/data/2.5/forecast?q=%1&appid=%2&units=%3&lang=tr")
                      .arg(city, apiKey, unit);

    // Ağa istek gönder
    QUrl qurl(url);
    QNetworkRequest request(qurl);
    manager->get(request);

}

// Receive butonuna tıklandığında çalışır
void havadurumu::on_fetchButton_clicked() {
    // Kullanıcı enter'a basmadıysa, bu butonla manuel çalıştırma
    fetchWeather(currentUnit.isEmpty() ? "metric" : currentUnit);
}

// Celcius butonuna basıldığında sıcaklık °C cinsinden gösterilir
void havadurumu::on_CelciusButton_clicked() {
    fetchWeather("metric");
}

// Fahrenheit butonuna basıldığında sıcaklık °F cinsinden gösterilir
void havadurumu::on_FahreneitButton_clicked() {
    fetchWeather("imperial");
}
    // API'den gelen cevap burada işlenir
void havadurumu::onResult(QNetworkReply *reply) {

    if (reply->error()) { //Eğer alınan cevap hata koduna gidiyorsa

        // Hata kodu 404 ise (şehir bulunamadı) ve uyarı zaten açık değilse
        if (reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt() == 404 && !errorDialogVisible) {

            errorDialogVisible = true; //true yaparak tekrar uyarı gösterilmesini engelliyorum

            QMessageBox *msgBox = new QMessageBox(this); // Hata mesaj kutusu (hata mesaj kutusu nesnesi) oluşturuluyor
            msgBox->setIcon(QMessageBox::Critical); // Kırmızı çarpı işareti
            msgBox->setWindowTitle("ERROR"); // Pencere (pop-up) başlığı
            msgBox->setText("<b style='color:#aa0000;'>INVALID CITY NAME! PLEASE ENTER A VALID CITY NAME.</b>");
            msgBox->setStandardButtons(QMessageBox::Ok);  // "OK" butonu

            msgBox->setStyleSheet("");  // Stil temizlenir, varsayılan pencere gibi görünür

            connect(msgBox, &QMessageBox::finished, this, [this](int){
                errorDialogVisible = false; // Uyarı (error pop-up) tekrar gösterilebilir hale getiriliyor
            });

            msgBox->show(); // exec() yerine show() kullanılır ki pencere donmasın ve çift açılmasın
        }

        // Bellek sızıntısını önlemek için bağlantı temizleniyor
        reply->deleteLater();
        return;
    }

    // JSON (anahtar-kilit) verisi okunur
    QByteArray responseData = reply->readAll();
    QJsonDocument doc = QJsonDocument::fromJson(responseData);
    QJsonObject obj = doc.object();

    if (!obj.contains("list")) {
        reply->deleteLater();
        return;
    }

    QString cityName = ui->cityLineEdit->text().trimmed().toUpper();

    QString result = QString("<h2 style='color:#2c3e50;'>🌍<b>%1</b></h2>")
                         .arg(cityName); //tablonun en başındaki şehir ismi başlığı

    QJsonArray listArray = obj["list"].toArray();  // Saatlik tahminleri içeren liste alınır

    QString currentDay;

    // Tahminler işlenir
    for (const QJsonValue &value : listArray) {
        QJsonObject entry = value.toObject();
        QString dt_txt = entry["dt_txt"].toString(); // Tarih ve saat
        QString date = dt_txt.left(10); // Sadece tarih alınır (YYYY-MM-DD)

         // Yeni güne geçildiyse, yeni tablo başlatılır
        if (date != currentDay) {
            if (!currentDay.isEmpty()) result += "</table></div>"; // Önceki tabloyu kapat
            currentDay = date;

            // Gün ve tablo sütunları başlıkları oluşturulur
            result += QString("<div style='width:100%%; margin-bottom:20px;'>"
                              "<p style='font-weight:bold; font-size:14px;'>📅 Date(Year/Month/Day):  %1</p>"
                              "<table style='width:100%%; border-collapse:collapse; font-family:Arial; font-size:13px;'>"
                              "<tr style='background-color:#f2f2f2;'>"
                              "<th align='left'>⏰ <b>Hour </b></th>"
                              "<th align='left'>🌤 <b>Condition </b></th>"
                              "<th align='left'>🌡 <b>Temperature </b></th>"
                              "<th align='left'>💧 <b>Humidity </b></th>"
                              "<th align='left'>🌬 <b>Wind Speed </b></th>"
                              "</tr>")
                          .arg(currentDay);
        }

        //Veriler tek tek çekilir
        QString time = dt_txt.mid(11, 5); //Zaman verisi

        double temp = entry["main"].toObject()["temp"].toDouble(); //Sıcaklık verisi

        int humidity = entry["main"].toObject()["humidity"].toInt(); //Nem verisi

        double wind = entry["wind"].toObject()["speed"].toDouble(); //Rüzgar hızı oranı verisi

        QString desc = entry["weather"].toArray()[0].toObject()["main"].toString(); //Hava durumu verisi (condition)

        QString tempUnit = (currentUnit == "imperial") ? "°F" : "°C"; // Sıcaklığın birimi

        //Çekilen veriler satır satır eklenir
        result += QString("<tr>"
                          "<td><a href='%1|%2|%3|%4'>%1</a></td>"
                          "<td>%2</td><td>%3%4</td><td>%5%</td><td>%6 m/s</td>"
                          "</tr>")
                      .arg(time, desc, QString::number(temp), tempUnit,
                           QString::number(humidity), QString::number(wind));

    }

    result += "</table></div>";  // Son tabloyu da kapat

    // Sonuç metni arayüzdeki label'a aktarılır
    QLabel *label = ui->resultScrollArea->widget()->findChild<QLabel*>("resultLabel");
    if (label) {
        label->setText(result);
    }

    reply->deleteLater(); // Belleği temizle

}

void havadurumu::on_havadurumu_iconSizeChanged(const QSize &iconSize)
{

}

// EXİT butonuna basılınca uygulama kapatılsın
void havadurumu::on_exitButton_clicked()
{
    QApplication::quit();
}

// Saat bağlantısına tıklandığında detaylı bilgi göster
void havadurumu::onCellClicked(const QString &linkData) {
    QStringList parts = linkData.split("|");
    if (parts.size() != 4)
        return;

    // Linkten gelen bilgileri ayrıştır
    QString hour = parts[0];

    QString condition = parts[1];
    lastWeatherCondition=condition;

    QString temperature = parts[2];

    QString unit = parts[3];

    QString cityName = ui->cityLineEdit->text().trimmed().toUpper();

    QString comment; //hava durumu hakkında yorum

    QString imagePath; //hava durumunu gösteren fotoğrafın yolu

    if (condition == "Clear") { //hava güneşliyse verilecek mesaj ve resim
        comment = "The weather is sunny and warm.";
        imagePath = "C:\\Users\\PC\\Desktop\\gunes.png";

    }else if (condition == "Rain") { //hava yağmurluysa verilecek mesaj ve resim
        comment = "It's raining, don't forget to take an umbrella.";
        imagePath = "C:\\Users\\PC\\Desktop\\yağmur.png";
    }
    else if (condition == "Clouds") { //hava bulutluysa verilecek mesaj ve resim
        comment = "The weather is cloudy and stuffy.";
        imagePath = "C:\\Users\\PC\\Desktop\\bulut.png";
    }
    else if (condition == "Snow") { //hava karlıysa verilecek mesaj ve resim
        comment = "It's snowing, dress warmly!";
        imagePath = "C:\\Users\\PC\\Desktop\\kar.png";
    }
    else if (condition == "Thunderstorm") { //hava şimşekliyse verilecek mesaj ve resim
        comment = "There is a thunderstorm, be careful.";
        imagePath = "C:\\Users\\PC\\Desktop\\simsek.png";
    }
    else { //hava durumu bilinmediğinde verilecek mesaj
        comment = "The weather is unknown.";
    }

    // Resmi weatherImageLabel(QLabel)'a aktar
    QPixmap pix(imagePath);
    ui->weatherImageLabel->setPixmap(pix.scaled(285, 285, Qt::KeepAspectRatio, Qt::SmoothTransformation));

    // Resmin altına gerekli bilgileri yaz (comment, city name, hour, temperature, temp unit,)
    QString html = QString("<h2 style='color:#2c3e50;'>%1</h2>"
                           "<p><b></b> %2<br>"
                           "<b></b> %3%4<br>"
                           "<b></b> %5</p>")
                       .arg(cityName)
                       .arg(hour)
                       .arg(temperature)
                       .arg(unit)
                       .arg(comment);

    ui->weatherInfoLabel->setText(html);
    ui->suggestionLabel->clear(); //yeni bir saate tıklandığında öneri kutucuğunu temizle
}

//Suggest butonuna basıldığında hava durumu ile ilgili aktivite önerisi versin
void havadurumu::on_suggestionButton_clicked()
{
    QString suggestion = "Please receive weather data first."; //hiçbir seçim yapılmadan önceki uyarı

    if (lastWeatherCondition.isEmpty()) { //eğer hiç veri yoksa öneri yapma
        ui->suggestionLabel->setText(suggestion);
        return;
    }

    QString lowered = lastWeatherCondition.toLower(); // en son alınan hava durumunu küçük harf yap

    // Her hava durumu için birden fazla öneriler
    QStringList clearSuggestions = { //hava güneşli, açıksa verilecek öneriler
        "☀ Go for a walk or jog in the park.",
        "🌳 Great weather for a picnic under the trees.",
        "🚴‍ Perfect time for biking around the neighborhood.",
        "📸 Try outdoor photography with natural sunlight.",
        "🌞 Do some sunbathing or light yoga outside."
    };

    QStringList cloudSuggestions = { //hava bulutluysa verilecek öneriler
        "⛅ A cozy coffee shop visit sounds great.",
        "📷 Overcast skies? Ideal for soft-light photography.",
        "🎭 Maybe attend an indoor art show or theater event.",
        "🏞 Go for a calm, meditative walk under the clouds."
    };

    QStringList rainSuggestions = { //hava yağmurluysa verilecek öneriler
        "🌧 Time for a movie marathon indoors.",
        "📚 Read your favorite book by the window.",
        "☕ Warm drinks and board games are perfect now.",
        "🛁 Take a relaxing hot bath. "
    };

    QStringList snowSuggestions = { //hava karlıysa verilecek öneriler
        "❄ Build a snowman or have a snowball fight!",
        "☕ Enjoy hot chocolate and watch the snow fall.",
        "🧤 Take winter photos or go for a short snowy walk.",
        "🎿 Try skiing or sledding if you're near a hill!"
    };

    QStringList thunderstormSuggestions = { //hava şimşekliyse verilecek öneriler
        "⚡ Stay indoors and unplug electronics.",
        "🎮 Play indoor games or listen to calming music.",
        "📓 Write, draw, or work on a hobby while it storms.",
        "🎧 Catch up on a podcast or audiobook safely inside."
    };

    //duruma göre öneri yap
    if (lowered.contains("clear")) { //eğer hava açıksa

        int index = QRandomGenerator::global()->bounded(clearSuggestions.size()); // clearSuggestions listesinin rastgele bir indeks seçer

        suggestion = clearSuggestions.at(index); // Seçilen indeksteki öneriyi alır ve 'suggestion' değişkenine atar

    } else if (lowered.contains("cloud")) { // eğer hava bulutluysa
        int index = QRandomGenerator::global()->bounded(cloudSuggestions.size());
        suggestion = cloudSuggestions.at(index);

    } else if (lowered.contains("rain")) { // eğer hava yağmurluysa
        int index = QRandomGenerator::global()->bounded(rainSuggestions.size());
        suggestion = rainSuggestions.at(index);

    } else if (lowered.contains("snow")) { // eğer hava karlıysa
        int index = QRandomGenerator::global()->bounded(snowSuggestions.size());
        suggestion = snowSuggestions.at(index);

    } else if (lowered.contains("thunderstorm")) { // eğer hava şimşekliyse
        int index = QRandomGenerator::global()->bounded(thunderstormSuggestions.size());
        suggestion = thunderstormSuggestions.at(index);

    } else {
       suggestion = "The weather is unknown, no suggestion."; // hava durumu bilinmiyorsa
    }

    ui->suggestionLabel->setText(suggestion); // öneriyi suggestionLabel'a aktar
}

