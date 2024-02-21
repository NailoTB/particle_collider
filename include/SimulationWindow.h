#ifndef SIMULATIONWINDOW_H
#define SIMULATIONWINDOW_H

#include <QApplication>
#include <QTimer>
#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QToolBar>
#include <QBrush>
#include <QGraphicsEllipseItem>
#include <QPushButton>

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
