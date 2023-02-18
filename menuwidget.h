#include <QtWidgets>

class MenuItem : public QWidget {
  Q_OBJECT
 public:
  MenuItem(const QString& text, const QIcon& icon, MenuItem* parentItem = nullptr, QWidget* parent = nullptr);

 private:
  QPushButton* m_pTextLabel;
  QPushButton* m_pRightIcon;

  MenuItem* m_pParent;
};

class MenuWidget : public QWidget {
  Q_OBJECT

 public:
  explicit MenuWidget(QWidget* parent = nullptr);

  QPushButton* addItem(const QString& text, const QIcon& icon = QIcon(), QWidget* widget = nullptr, QPushButton* parent = nullptr);

  void showWidget(QWidget* widget);
  void showWidget(int index);

 private:
  QPushButton* createButton(const QString& text, const QIcon& icon = QIcon());
  void showSubItems(QPushButton* button);
  void hideSubItems(QPushButton* button);
  void updateCurrentWidget();
  void showParent(QPushButton* parent);

  QStackedWidget* contents_;
  QVBoxLayout* mainLayout_;
  QHBoxLayout* buttonLayout_;
  QList<QPushButton*> items_;
  QList<QWidget*> widgets_;
  QMap<QPushButton*, QList<QPushButton*>> subItems_;
  QMap<QPushButton*, QWidget*> subWidgets_;
};
