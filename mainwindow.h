#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableView>

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget* parent = nullptr);

 private:
  void setupUi();

  QTableView* m_processesTableView;
};

#endif  // MAINWINDOW_H
