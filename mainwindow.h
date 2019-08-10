#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "graph.hpp"
#include "mindmapscene.hpp"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:
    void nodeAdded(size_t nodeId, Node* node);
    void edgeAdded(Node* from, Node* to);

private slots:
    void on_actionAdd_Node_triggered();
    void on_action_Exit_triggered();

private:
    Ui::MainWindow *ui;
    MindmapScene *mindmapScene;

    Graph _graph;
    size_t _root;

    void _drawMindmap();
};

#endif // MAINWINDOW_H
