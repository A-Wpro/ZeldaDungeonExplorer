#ifndef GAMEVIEW_H
#define GAMEVIEW_H
#include <QGraphicsView>
#include <QFrame>
#include <QObject>
#include <QWidget>


QT_BEGIN_NAMESPACE
class QLabel;
class QSlider;
class QToolButton;
QT_END_NAMESPACE

class GraphicsView;
class View;


class GraphicsView: public QGraphicsView
{
public:
    GraphicsView(View *v) : QGraphicsView(), view(v) { }

protected:
    void wheelEvent(QWheelEvent *) override;
    void mouseMoveEvent(QMouseEvent *e) override;

private:
    View *view;
};

class View : public QFrame
{
public:
    explicit View(const QString &name, QWidget *parent = nullptr);
    QGraphicsView *view() const;

public slots:
    void zoomIn(int level = 1);
    void zoomOut(int level = 1);
    void xValueChanged(int value);
    void yValueChanged(int value);


private slots:
    void resetView();
    void setResetButtonEnabled();
    void setupMatrix();
    void togglePointerMode();
    void toggleOpenGL();
    void toggleAntialiasing();
    void print();
    void rotateLeft();
    void rotateRight();


private:
    GraphicsView *graphicsView;
    QLabel *label;
    QLabel *label2;
    QToolButton *selectModeButton;
    QToolButton *dragModeButton;
    QToolButton *resetButton;
    QSlider *zoomSlider;
    QSlider *rotateSlider;
    QPoint player;
};


#endif // GAMEVIEW_H
