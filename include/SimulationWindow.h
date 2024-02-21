#ifndef SIMULATIONWINDOW_H
#define SIMULATIONWINDOW_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <QTimer>
#include <QSlider>
#include <QPushButton>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsEllipseItem>
#include <QTimer>
#include <QBrush>
#include <QElapsedTimer>
#include <QVBoxLayout>
#include <QSlider>
#include <QPushButton>
#include <QToolBar>
#include <QCloseEvent>
#include <iostream>
#include "CellSpace.h"
class SimulationWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit SimulationWindow(QMainWindow *parent = 0);
    void loadCellSpace(CellSpace*);

signals:

protected:

private slots:
    void startPauseButtonClicked();
    void updateSimulation();

private:
    CellSpace* simulationCellSpace; //TODO: replace with dynamic cell space with user adding particles
    QList<QGraphicsEllipseItem *> particleItems;

    QTimer *timer;
    QPushButton *pauseButton;
    QGraphicsView *simulationView;
    QGraphicsScene *scene;
    bool simulationRunning;

};

#endif // SIMULATIONWINDOW_H
