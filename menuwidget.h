#include <QtWidgets>

class TreeExpander : public QWidget {
  Q_OBJECT
public:
  void setExpanded(bool expanded) {
    m_expanded = expanded;
    repaint();
  }

signals:
  void mouseEnter();
  void mouseLeave();

protected:
  void paintEvent(QPaintEvent *event) override {
    QStyleOption opt;
    opt.initFrom(this);

    QPainter painter(this);
    drawTreeExpander(&painter, &opt);
  }

  void enterEvent(QEnterEvent *event) override { emit mouseEnter(); }
  void leaveEvent(QEvent *event) override { emit mouseLeave(); }

private:
  void drawTreeExpander(QPainter *painter, const QStyleOption *option) {
    painter->setPen(QPen(option->palette.color(QPalette::ButtonText), 1,
                         Qt::SolidLine, Qt::RoundCap, Qt::MiterJoin));
    painter->setRenderHint(QPainter::Antialiasing, true);

    int padding = option->rect.width() / 4;
    int wHalf = option->rect.width() / 2;
    int hHalf = option->rect.height() / 2;
    int wPadded = option->rect.width() - padding;
    int hPadded = option->rect.height() - padding;

    QPoint p1, p2, p3;
    if (!m_expanded) {
      p1 = QPoint(wHalf, padding);
      p2 = QPoint(wPadded, hHalf);
      p3 = QPoint(wHalf, hPadded);
    } else {
      p1 = QPoint(padding, hHalf);
      p2 = QPoint(wHalf, hPadded);
      p3 = QPoint(wPadded, hHalf);
    }
    painter->drawLine(p1, p2);
    painter->drawLine(p2, p3);
  }

  bool m_expanded = false;
};

class MenuItem : public QWidget {
  Q_OBJECT
public:
  MenuItem(const QString &text, const QIcon &icon,
           MenuItem *parentItem = nullptr, QWidget *parent = nullptr);

  void addChild(MenuItem *child) {
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
  void mousePressEvent(QMouseEvent *event) override;
  void leaveEvent(QEvent *event) override;
  void enterEvent(QEnterEvent *event) override;

private:
  void expand();
  void collapse();

  QLabel *m_pLeftIcon;
  QLabel *m_pTextLabel;
  TreeExpander *m_pTreeExpander;

  MenuItem *m_pParent;
  QList<MenuItem *> m_children;

  bool m_expanded;
  bool m_mouseOverExpander;
};

class MenuWidget : public QWidget {
  Q_OBJECT

public:
  explicit MenuWidget(QWidget *parent = nullptr);

  MenuItem *addItem(const QString &text, const QIcon &icon = QIcon(),
                    QWidget *widget = nullptr, MenuItem *parent = nullptr);

  void addStretch() { m_pButtonLayout->addStretch(); }

private:
  QStackedWidget *m_pContents;
  QHBoxLayout *m_pMainLayout;
  QVBoxLayout *m_pButtonLayout;
  QMap<MenuItem *, int> m_menuIndices;
};
