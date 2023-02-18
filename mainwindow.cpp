#include "mainwindow.h"

#include "menuwidget.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
  resize(800, 600);

  setupUi();
}

void MainWindow::setupUi() {
  MenuWidget *menu = new MenuWidget();

  menu->addItem("Test1", QIcon::fromTheme("nm-device-wireless"),
                new QLabel("test1"));
  menu->addItem("Test2", QIcon::fromTheme("user-info"), new QLabel("test2"));
  MenuItem *parent = menu->addItem(
      "Test3", QIcon::fromTheme("dialog-information"), new QLabel("test3"));
  MenuItem *parent2 = menu->addItem("Test4", QIcon::fromTheme("important"),
                                    new QLabel("test4"), parent);
  menu->addItem("Test5", QIcon::fromTheme("important"), new QLabel("test5"),
                parent2);

  menu->addStretch();

  menu->addItem("Test1", QIcon::fromTheme("nm-device-wireless"), new QLabel("test1"));
  menu->addItem("Test2", QIcon::fromTheme("user-info"), new QLabel("test2"));
  MenuItem* parent = menu->addItem("Test3", QIcon::fromTheme("dialog-information"), new QLabel("test3"));
  MenuItem* parent2 = menu->addItem("Test4", QIcon::fromTheme("important"), new QLabel("test4"), parent);
  menu->addItem("Test5", QIcon::fromTheme("important"), new QLabel("test5"), parent2);

  menu->addStretch();

  setCentralWidget(menu);
}
