#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets>
#include <QtCore>

#include "audiofile.h"
#include "tageditorlayout.h"
#include "filelist.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {

    Q_OBJECT

public:
    explicit MainWindow(QStringList files);
    ~MainWindow();
    Ui::MainWindow* getUI();

private:
    Ui::MainWindow *ui;
    FileList listOfFiles;

    /*
     * List of all tag editor layouts. When the user clicks to open a file in the editor,
     * a TagEditorLayout pointer is created and added to this list.
    */
    QList<TagEditorLayout*> listOfLayouts;

    TagEditorLayout* findLayout(AudioFile* file, bool create = true);
    void setIcons();
    void openFilesFromArguments(QStringList files);
    void updateViews();
    void updateEditor();
    void closeEditor();
    void openFile(QString path, bool update = true);
    void closeFile(QString path);
    void closeFile(int i);
    bool unsavedChanges();
    void saveSession();
    void openLastSession();
    AudioFile* openedFile; //the file that is viewed in the tag editor

public slots:
    void openFileDialog();
    void openDirectory();
    void openInEditor(QTreeWidgetItem* file);
    void saveAll();
    void closeAll();
    void openCopyTagsDialog();
    void closeCurrentFile();
    void saveCurrentFile();
    void openMultipleTaggingDialog();
    void openCreateAlbumDialog();
    void updateWindowTitle();
    void openSettingsDialog();

};

#endif // MAINWINDOW_H
