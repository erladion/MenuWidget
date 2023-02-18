#include <QLabel>
#include <QVBoxLayout>

class QStackedWidget;
class QHBoxLayout;
class QString;
class QSize;
class QPixmap;

class TreeExpander : public QLabel {
  Q_OBJECT
 public:
  TreeExpander(QPixmap expanded, QPixmap collapsed) : m_expandedPixmap(expanded), m_collapsedPixmap(collapsed) { setPixmap(collapsed); }

  void setExpanded(bool expanded) {
    m_expanded = expanded;
    setPixmap(m_expanded ? m_expandedPixmap : m_collapsedPixmap);
  }

 signals:
  void mouseEnter();
  void mouseLeave();

 protected:
  void enterEvent(QEnterEvent* event) override { emit mouseEnter(); }
  void leaveEvent(QEvent* event) override { emit mouseLeave(); }

 private:
  QPixmap m_expandedPixmap;
  QPixmap m_collapsedPixmap;
  bool m_expanded = false;
};

class MenuItem : public QWidget {
  Q_OBJECT
 public:
  MenuItem(const QString& text, const QIcon& icon, MenuItem* parentItem = nullptr, QWidget* parent = nullptr);

  void addChild(MenuItem* child) {
    m_children.append(child);
    if (!m_expanded) {
      child->hide();
    }
    m_pTreeExpander->show();
  }

  QSize sizeHint() const override { return QSize(100, 25); }

 signals:
  void itemClicked();

 protected:
  void mousePressEvent(QMouseEvent* event) override;
  void leaveEvent(QEvent* event) override;
  void enterEvent(QEnterEvent* event) override;

 private:
  void expand();
  void collapse();

  QLabel* m_pIcon;
  QLabel* m_pTextLabel;
  TreeExpander* m_pTreeExpander;

  MenuItem* m_pParent;
  QList<MenuItem*> m_children;

  bool m_expanded;
  bool m_mouseOverExpander;
};

class MenuWidget : public QWidget {
  Q_OBJECT

 public:
  explicit MenuWidget(QWidget* parent = nullptr);

  MenuItem* addItem(const QString& text, const QIcon& icon = QIcon(), QWidget* widget = nullptr, MenuItem* parent = nullptr);

  void addStretch() { m_pButtonLayout->addStretch(); }

 private:
  QStackedWidget* m_pContents;
  QHBoxLayout* m_pMainLayout;
  QVBoxLayout* m_pButtonLayout;
  QMap<MenuItem*, QWidget*> m_menuWidgets;
};
