#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "mindmapscene.hpp"
#include "about.hpp"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void passNodeDoubleClick(MindmapNodeGraphicsItem* item, NodeRawPtr node);

private slots:
    void on_actionAdd_Node_triggered();
    void on_action_Exit_triggered();
    void on_action_Save_triggered();
    void on_action_New_Mindmap_triggered();
    void on_action_About_triggered();
    void on_action_Open_file_triggered();
    void on_actionRemove_node_triggered();
    void on_actionExport_triggered();
    void onMindmapChange(bool wasSaved);

    void on_action_Save_as_triggered();

signals:
    void notifyMindmapChanged(bool wasSaved);

private:
    Ui::MainWindow *ui;
    MindmapScene *_mindmapScene;

    About* _about;

    bool _fileHasChanged = false;
    bool _fileExists = false;
    QString _currentFilePath;
    QString _currentFileName;

    bool _shouldSave();
    void _overwriteFile(const QString& filePath);
};

#endif // MAINWINDOW_H
