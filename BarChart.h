#pragma once
#include <QWidget>
#include <QMap>

class BarChartWidget : public QWidget {
    Q_OBJECT
public:
    explicit BarChartWidget(QWidget *parent = nullptr);
    
    void setData(const QMap<QString, int> &data);
    void setTitle(const QString &title);
    
protected:
    void paintEvent(QPaintEvent *event) override;
    
private:
    QMap<QString, int> m_data;
    QString m_title;
};

