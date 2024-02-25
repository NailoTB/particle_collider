#ifndef QT_SIMULATIONSCENE_H
#define QT_SIMULATIONSCENE_H

#include <QTimer>
#include <QGraphicsScene>
#include <QGraphicsEllipseItem>
#include <QGraphicsView>
#include <QGraphicsSceneMouseEvent>
#include "CellSpace.h"

class SimulationScene : public QGraphicsScene
{
    Q_OBJECT

public:
    explicit SimulationScene(QGraphicsScene *parent = 0);
    void loadCellSpace(CellSpace *);
    void createParticlesOnPoint(const int& xPos, const int& yPos, const std::vector<double>& velocity);
    void setTimerRunState(bool);
    void clearParticles();
    void generateInitialState();
signals:
    void particleCount(int);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent*) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent*) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent*) override;
private slots:
    void updateParticleCount();
    void clearPreviousParticleGraphics();
    void updateParticlePositions();
    void flushView();
    void redraw();

private:
    CellSpace *simulationCellSpace;
    QList<QGraphicsEllipseItem *> previousTimestepParticleGraphics;
    QGraphicsView *simulationView;
    QTimer *simulationTimer;
    QTimer *particleCountTimer;
    QPointF mouseDragStartPoint;
    QGraphicsLineItem *mouseDragArrow;
};

#endif // SIMULATIONSCENE_H
