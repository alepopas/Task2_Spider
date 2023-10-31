#include "widget.h"

#include <QPainter>
#include <QTimer>

Widget::Widget(QWidget *parent) : QWidget(parent) {
  this->setStyleSheet("background-color: #8cde8d;");

  windowCenter_ = QPoint(rect().width()/2,rect().height()/2);
  spider_ = new Spider(windowCenter_);
  timer_ = new QTimer(this);
  timer_->start(100);
  timer_->setInterval(100);

  connect(timer_, &QTimer::timeout, [this](){ spider_->MoveSpider(); repaint(); });
}

Widget::~Widget() {}

void Widget::paintEvent(QPaintEvent* event) {
  Q_UNUSED(event);

  QPainter painter(this);
  QPen pen(Qt::white, 3, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
  painter.setPen(pen);
  painter.setRenderHint(QPainter::Antialiasing);
  spider_->DrawWeb(&painter);
  spider_->DrawSpider(&painter);
}

void Widget::keyPressEvent(QKeyEvent* event) {
  int deltaTimerInterval = 50;

  if (event->key() == Qt::Key_Up) {
    AddToTimerInterval(-deltaTimerInterval);
  } else if (event->key() == Qt::Key_Down) {
    AddToTimerInterval(deltaTimerInterval);
  }
}

void Widget::AddToTimerInterval(int milliseconds) {
  int minInterval = 100;
  int maxInterval = 1000;
  int newInterval = timer_->interval() + milliseconds;

  newInterval = qBound(minInterval, newInterval, maxInterval);
  timer_->setInterval(newInterval);
}
