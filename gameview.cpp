#include "gameview.h"
#include "gamescene.h"
#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <QDebug>
#include <QWheelEvent>
#include <QGraphicsView>
#include <QStyle>
#include <QWidget>
#include <QToolButton>
#include <QSlider>
#include <QVBoxLayout>
#include <QButtonGroup>
#include <QLabel>
#include <QtMath>
#include <QAbstractSlider>
#include "player.h"

void GraphicsView::wheelEvent(QWheelEvent *e)
{
    if (e->angleDelta().y() > 0)
        view->zoomIn(6);
    else
        view->zoomOut(6);

    QList<QGraphicsItem*> items = scene()->items();

    for (int i = 0; i<items.size(); i++)
    {
        if(typeid (*(items[i]))==typeid(Player))
        {
            centerOn(items[i]->pos());
        }
    }
}

void GraphicsView::mouseMoveEvent(QMouseEvent *e)
{
    QList<QGraphicsItem*> items = scene()->items();
    for (int i = 0; i<items.size(); i++)
    {
        if(typeid (*(items[i]))==typeid(Player))
        {
            centerOn(items[i]->pos());
        }
    }
}

View::View(const QString &name, QWidget *parent) : QFrame(parent)
{
    setFrameStyle(Sunken | StyledPanel);
    graphicsView = new GraphicsView(this);
    graphicsView->setRenderHint(QPainter::Antialiasing, false);
    graphicsView->setDragMode(QGraphicsView::ScrollHandDrag);
    graphicsView->setOptimizationFlags(QGraphicsView::DontSavePainterState);
    graphicsView->setViewportUpdateMode(QGraphicsView::SmartViewportUpdate);
    graphicsView->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    int size = style()->pixelMetric(QStyle::PM_ToolBarIconSize);
    QSize iconSize(size, size);

    zoomSlider = new QSlider;
    zoomSlider->setMinimum(0);
    zoomSlider->setMaximum(500);
    zoomSlider->setValue(250);
    zoomSlider->setTickPosition(QSlider::TicksRight);
    zoomSlider->hide();

    // Zoom slider layout
    QVBoxLayout *zoomSliderLayout = new QVBoxLayout;

    zoomSliderLayout->addWidget(zoomSlider);

    QToolButton *rotateLeftIcon = new QToolButton;
    rotateLeftIcon->setIcon(QPixmap(":/rotateleft.png"));
    rotateLeftIcon->setIconSize(iconSize);

    QToolButton *rotateRightIcon = new QToolButton;
    rotateRightIcon->setIcon(QPixmap(":/rotateright.png"));
    rotateRightIcon->setIconSize(iconSize);
    rotateSlider = new QSlider;
    rotateSlider->setOrientation(Qt::Horizontal);
    rotateSlider->setMinimum(-360);
    rotateSlider->setMaximum(360);
    rotateSlider->setValue(0);
    rotateSlider->setTickPosition(QSlider::TicksBelow);
    rotateSlider->hide();

    resetButton = new QToolButton;
    resetButton->setText(tr("0"));
    resetButton->setEnabled(false);
    resetButton->hide();

    QGridLayout *topLayout = new QGridLayout;

    topLayout->addWidget(graphicsView, 1, 0);
    topLayout->addLayout(zoomSliderLayout, 1, 1);

    topLayout->addWidget(resetButton, 2, 1);
    setLayout(topLayout);

    connect(resetButton, &QAbstractButton::clicked, this, &View::resetView);
    connect(zoomSlider, &QAbstractSlider::valueChanged, this, &View::setupMatrix);

    setupMatrix();
}

QGraphicsView *View::view() const
{
    return static_cast<QGraphicsView *>(graphicsView);
}

void View::resetView()
{
    zoomSlider->setValue(250);
    setupMatrix();
    graphicsView->ensureVisible(QRectF(0, 0, 0, 0));

    resetButton->setEnabled(false);
}

void View::setResetButtonEnabled()
{
    resetButton->setEnabled(true);
}

void View::setupMatrix()
{
    qreal scale = qPow(qreal(2), (zoomSlider->value() - 250) / qreal(50));

    QTransform matrix;
    matrix.scale(scale, scale);

    graphicsView->setTransform(matrix);
    setResetButtonEnabled();
}

void View::togglePointerMode()
{
    graphicsView->setDragMode(selectModeButton->isChecked()
                              ? QGraphicsView::RubberBandDrag
                              : QGraphicsView::ScrollHandDrag);
    graphicsView->setInteractive(selectModeButton->isChecked());
}

void View::zoomIn(int level)
{
    if ((zoomSlider->value() + level)<=280)
    {
        zoomSlider->setValue(zoomSlider->value() + level);
    }
}

void View::zoomOut(int level)
{
    if((zoomSlider->value() - level)>=200)
    {
        zoomSlider->setValue(zoomSlider->value() - level);
    }
}



