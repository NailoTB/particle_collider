#ifndef QT_SIMULATIONSCENE_H
#define QT_SIMULATIONSCENE_H

#include "CellSpace.h"

#include <QTimer>
#include <QGraphicsScene>
#include <QGraphicsEllipseItem>
#include <QGraphicsView>

class SimulationScene : public QGraphicsScene
{
    Q_OBJECT

public:
    explicit SimulationScene(QGraphicsScene *parent = 0);
    void loadCellSpace(CellSpace *);
    void createParticlesOnPoint(const int& xPos, const int& yPos, const int& velocity);
    void setTimerRunState(bool);
    void clearParticles();

signals:
private slots:

    void clearParticleItems();
    void updateParticlePositions();
    void flushView();
    void redraw();

private:
    CellSpace *simulationCellSpace;
    QList<QGraphicsEllipseItem *> particleItems;
    QGraphicsView *simulationView;
    QTimer *timer;
};

#endif // SIMULATIONSCENE_H
