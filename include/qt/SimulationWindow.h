#ifndef QT_SIMULATIONWINDOW_H
#define QT_SIMULATIONWINDOW_H

#include <QMainWindow>
#include <QMouseEvent>

#include "CellSpace.h"
#include "qt/SimulationToolBar.h"
#include "qt/SimulationScene.h"

class SimulationWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit SimulationWindow(QMainWindow *parent = 0);
    void passCellSpaceToScene(CellSpace *);

signals:

protected:
    void mousePressEvent(QMouseEvent*) override;

private slots:
    void startPauseButtonClicked(bool);
    void clearParticles();
private:
    SimulationToolBar *toolbar;
    SimulationScene *scene;
};

#endif // QT_SIMULATIONWINDOW_H
