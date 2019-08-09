#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "graph.hpp"

class QGraphicsScene;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionAdd_Node_triggered();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *mindmapScene;

    Graph _graph;

    void _drawMindmap();
};

#endif // MAINWINDOW_H
