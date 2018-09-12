#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGraphicsScene>
#include <QPixmap>
#include<QFile>
#include <QFileDialog>
#include <QSize>
#include <QDesktopWidget>
#include <QBrush>
#include <QPen>
#include <QGraphicsRectItem>
#include "rectobject.h"
#include <QDebug>
#include <QGraphicsItem>
#include "pixmapobject.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    scale_height=768;
    scale_width=1024;
    rects_num=6;
    default_rect_color=QColor(0, 100, 0, 100);
    uv_band=new QGraphicsScene();
    norm_band=new QGraphicsScene();
    main_scene=new QGraphicsScene();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_load_img_btn_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this,"Choose a picture","/home/");
    if(!filename.isEmpty())
    {
        img=new QPixmap(filename);

        scaled_img=img->scaled(scale_width-5,scale_height-100);
        ui->cutting_area->setScene(main_scene);
        main_scene->addPixmap(scaled_img);
        ui->cutting_area->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        ui->cutting_area->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        int margin=10;

        int area_height=scaled_img.height()-margin;
        int area_width=scaled_img.width()-margin;

        for(int i=0;i<rects_num;i++)
        {
            QRect r(margin,
                    (i)*area_height/rects_num+margin,
                    area_width-margin,
                    area_height/rects_num-margin);
            QPen pen;
            pen.setStyle(Qt::DashDotLine);
            pen.setWidth(1);
            pen.setColor(Qt::red);
            RectObject *r_o=new RectObject(r,QString("%1").arg(i+1),default_rect_color,pen);
            objects.push_back(r_o);
            main_scene->addItem(r_o);

        }
    }






}

void MainWindow::on_draw_bands_btn_clicked()
{
    ui->normal_band->setScene(norm_band);
    ui->uv_band->setScene(uv_band);
    int offset=0;
    QList<RectObject*>::iterator it;
    for(it=objects.begin();it!=objects.end();++it){
            RectObject *o=(*it);
            QRectF r=o->rect();
            PixmapObject *po=new PixmapObject(scaled_img.copy(r.x(),r.y(),r.width(),r.height()),QPointF(offset,0));
            PixmapObject *po_u=new PixmapObject(scaled_uv_img.copy(r.x(),r.y(),r.width(),r.height()),QPointF(offset,0));
            qDebug()<<po_u;
            norm_band->addItem(po);
            uv_band->addItem(po_u);
            offset+=r.width();
        }



}

void MainWindow::on_load_uv_img_btn_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this,"Choose a picture","/home/");
    if(!filename.isEmpty())
    {
        uv_img=new QPixmap(filename);
        scaled_uv_img=uv_img->scaled(scale_width-5,scale_height-100);
    }

}
