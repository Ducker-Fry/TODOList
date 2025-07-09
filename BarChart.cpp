#include "BarChart.h"
#include <QPainter>
#include <QPen>
#include <QBrush>
#include <QFont>

BarChartWidget::BarChartWidget(QWidget *parent) : QWidget(parent) {}

void BarChartWidget::setData(const QMap<QString, int> &data) {
    m_data = data;
    update();
}

void BarChartWidget::setTitle(const QString &title) {
    m_title = title;
    update();
}

void BarChartWidget::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);
    
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    
    // 绘制标题
    QFont titleFont = painter.font();
    titleFont.setPointSize(12);
    titleFont.setBold(true);
    painter.setFont(titleFont);
    painter.drawText(rect(), Qt::AlignHCenter | Qt::AlignTop, m_title);
    
    // 计算图表区域
    int margin = 40;
    int bottomMargin = 60;
    QRectF chartRect(margin, margin + 20, width() - 2 * margin, height() - margin - bottomMargin - 20);
    
    // 如果没有数据，绘制空图表
    if (m_data.isEmpty()) {
        painter.setPen(Qt::gray);
        painter.setBrush(Qt::lightGray);
        painter.drawRect(chartRect);
        painter.drawText(chartRect, Qt::AlignCenter, "No Data");
        return;
    }
    
    // 找到最大值
    int maxValue = 0;
    foreach (int value, m_data.values()) {
        if (value > maxValue) {
            maxValue = value;
        }
    }
    
    if (maxValue == 0) maxValue = 1; // 避免除以零
    
    // 绘制坐标轴
    painter.setPen(Qt::black);
    painter.drawLine(chartRect.bottomLeft(), chartRect.topLeft());
    painter.drawLine(chartRect.bottomLeft(), chartRect.bottomRight());
    
    // 绘制刻度
    int numTicks = 5;
    for (int i = 0; i <= numTicks; i++) {
        int y = chartRect.bottom() - i * chartRect.height() / numTicks;
        painter.drawLine(chartRect.left() - 5, y, chartRect.left(), y);
        painter.drawText(chartRect.left() - 40, y - 5, 35, 15, 
                         Qt::AlignRight | Qt::AlignVCenter, 
                         QString::number(maxValue * i / numTicks));
    }
    
    // 绘制柱状图
    int barWidth = chartRect.width() / (m_data.size() * 1.5);
    int i = 0;
    foreach (const QString &label, m_data.keys()) {
        int value = m_data[label];
        int barHeight = value * chartRect.height() / maxValue;
        int x = chartRect.left() + i * barWidth * 1.5 + barWidth * 0.25;
        int y = chartRect.bottom() - barHeight;
        
        painter.setPen(QColor(50, 100, 200));
        painter.setBrush(QColor(100, 150, 255));
        painter.drawRect(x, y, barWidth, barHeight);
        
        // 绘制标签
        painter.save();
        painter.rotate(-45);
        painter.drawText(y - 5, chartRect.bottom() + 30, label);
        painter.restore();
        
        i++;
    }
}
