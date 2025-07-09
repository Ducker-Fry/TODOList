#include "PieChart.h"
#include <QPainter>
#include <QPen>
#include <QBrush>
#include <QFont>

PieChartWidget::PieChartWidget(QWidget *parent) : QWidget(parent) {}

void PieChartWidget::setData(const QMap<QString, int> &data) {
    m_data = data;
    update();
}

void PieChartWidget::setTitle(const QString &title) {
    m_title = title;
    update();
}

void PieChartWidget::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);
    
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    
    // 绘制标题
    QFont titleFont = painter.font();
    titleFont.setPointSize(12);
    titleFont.setBold(true);
    painter.setFont(titleFont);
    painter.drawText(rect(), Qt::AlignHCenter | Qt::AlignTop, m_title);
    
    // 计算饼图区域
    int margin = 40;
    QRectF pieRect(margin, margin + 20, width() - 2 * margin, height() - 2 * margin - 20);
    
    // 计算总数值
    int total = 0;
    foreach (int value, m_data.values()) {
        total += value;
    }
    
    // 如果没有数据，绘制空图表
    if (total == 0) {
        painter.setPen(Qt::gray);
        painter.setBrush(Qt::lightGray);
        painter.drawEllipse(pieRect);
        painter.drawText(pieRect, Qt::AlignCenter, "No Data");
        return;
    }
    
    // 定义颜色列表
    QList<QColor> colors = {
        QColor(255, 100, 100),
        QColor(100, 255, 100),
        QColor(100, 100, 255),
        QColor(255, 255, 100),
        QColor(255, 100, 255),
        QColor(100, 255, 255)
    };
    
    // 绘制饼图
    int startAngle = 0;
    int i = 0;
    foreach (const QString &label, m_data.keys()) {
        int value = m_data[label];
        int angle = 360 * 16 * value / total;
        
        QColor color = colors[i % colors.size()];
        painter.setPen(color.darker());
        painter.setBrush(color);
        painter.drawPie(pieRect, startAngle, angle);
        
        // 绘制图例
        int legendY = margin + 20 + i * 20;
        painter.drawRect(width() - margin - 15, legendY, 15, 15);
        painter.drawText(width() - margin - 15 - 100, legendY, 100, 15, 
                         Qt::AlignRight | Qt::AlignVCenter, 
                         QString("%1 (%2%)").arg(label).arg(100.0 * value / total, 0, 'f', 1));
        
        startAngle += angle;
        i++;
    }
}
