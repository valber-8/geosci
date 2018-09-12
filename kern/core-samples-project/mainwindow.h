#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QPixmap>
#include <QVector>
#include <QRect>
#include <QColor>
#include "rectobject.h"
#include <QList>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

    void on_load_img_btn_clicked();

    void on_draw_bands_btn_clicked();

    void on_load_uv_img_btn_clicked();

private:
    Ui::MainWindow *ui;

    QPixmap *img;
    QPixmap scaled_img;

    QList<RectObject*> objects;

    QPixmap *uv_img;
    QPixmap scaled_uv_img;

    int scale_height;
    int scale_width;

    int rects_num;
    QColor default_rect_color;
    QColor selection_color;

    QGraphicsScene *main_scene;
    QGraphicsScene *norm_band;
    QGraphicsScene *uv_band;


};

#endif // MAINWINDOW_H
