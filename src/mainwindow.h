#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets>
#include <QtCore>

#include "audiofile.h"
#include "tageditorlayout.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {

    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    Ui::MainWindow* getUI();

private:
    Ui::MainWindow *ui;
    QList<AudioFile*> listOfFiles; //list of all opened files

    /*
     * List of all tag editor layouts. When the user clicks to open a file in the editor,
     *  a TagEditorLayout pointer is created and added to this list.
    */
    QList<TagEditorLayout*> listOfLayouts;

    TagEditorLayout* findLayout(AudioFile* file, bool create = true);
    void setIcons();
    void updateViews();
    void updateEditor();
    void reloadAllFiles();
    bool isFileOnList(QString path);
    bool unsavedChanges;
    AudioFile* openedFile; //the file that is viewed in the tag editor

public slots:
    void openFile();
    void openDirectory();
    void openInEditor(QTreeWidgetItem* file);
    void saveAll();
    void closeAll();
    void openCopyTagsDialog();
    void closeCurrentFile();
    void saveCurrentFile();
    void openMultipleTaggingDialog();
    void fileEdited();
    void openCreateAlbumDialog();
    void updateWindowTitle();

};

#endif // MAINWINDOW_H
