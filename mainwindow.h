#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
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
    void nodeAdded(MindmapNode* parent);
    void edgeAdded(MindmapNode* from, MindmapNode* to);

private slots:
    void on_actionAdd_Node_triggered();
    void on_action_Exit_triggered();

    void on_action_Save_triggered();

    void on_action_New_Mindmap_triggered();

private:
    Ui::MainWindow *ui;
    MindmapScene *_mindmapScene;

    MindmapNode* _root;
};

#endif // MAINWINDOW_H
