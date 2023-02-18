#include <QHBoxLayout>
#include <QIcon>
#include <QLabel>
#include <QMap>
#include <QPushButton>
#include <QStackedWidget>
#include <QVBoxLayout>

#include "menuwidget.h"

static const int ICON_SIZE = 16;

MenuItem::MenuItem(const QString &text, const QIcon &icon, MenuItem *parentItem,
                   QWidget *parent)
    : QWidget(parent), m_pTextLabel(new QLabel(text)), m_pParent(parentItem),
      m_expanded(false), m_mouseOverExpander(false) {

  QHBoxLayout *l = new QHBoxLayout();
  l->setSpacing(5);
  l->setContentsMargins(0, 0, 0, 0);
  l->setAlignment(Qt::AlignLeft);

  m_pLeftIcon = new QLabel();
  m_pLeftIcon->setPixmap(icon.pixmap(ICON_SIZE, ICON_SIZE));

  m_pTreeExpander = new TreeExpander();
  m_pTreeExpander->setMinimumSize(QSize(ICON_SIZE, ICON_SIZE));
  m_pTreeExpander->setMaximumSize(QSize(ICON_SIZE, ICON_SIZE));
  m_pTreeExpander->hide();

  connect(m_pTreeExpander, &TreeExpander::mouseEnter, this,
          [this]() { m_mouseOverExpander = true; });

  connect(m_pTreeExpander, &TreeExpander::mouseLeave, this,
          [this]() { m_mouseOverExpander = false; });

  l->addWidget(m_pLeftIcon);
  l->addWidget(m_pTextLabel);
  l->addSpacerItem(
      new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Preferred));
  l->addWidget(m_pTreeExpander);

  setMinimumWidth(100);

  setLayout(l);
}

void MenuItem::mousePressEvent(QMouseEvent *event) {
  if (event->button() == Qt::LeftButton) {
    if (m_mouseOverExpander && m_expanded) {
      collapse();
      emit itemClicked();

      return;
    }

    expand();
    m_pTreeExpander->setExpanded(true);
    emit itemClicked();
  }
}

void MenuItem::expand() {
  if (m_expanded) {
    return;
  }

  for (MenuItem *child : m_children) {
    child->show();
  }
  m_expanded = true;
}
void MenuItem::collapse() {
  if (!m_expanded) {
    return;
  }

  for (MenuItem *child : m_children) {
    child->collapse();
    child->hide();
  }

  m_pTreeExpander->setExpanded(false);
  m_expanded = false;
}

void MenuItem::enterEvent(QEnterEvent *event) {
  QWidget::enterEvent(event);

  qWarning() << "Entering: " << m_pTextLabel->text();

  QPalette palette = this->palette();
  palette.setColor(QPalette::Window, QColor(173, 216, 230));
  setPalette(palette);
  repaint();
}

void MenuItem::leaveEvent(QEvent *event) {
  QWidget::leaveEvent(event);

  qWarning() << "Leaving: " << m_pTextLabel->text();

  QPalette palette = this->palette();
  palette.setColor(QPalette::Window, Qt::white);
  setPalette(palette);
  repaint();
}

MenuWidget::MenuWidget(QWidget *parent)
    : QWidget(parent), m_pContents(new QStackedWidget(this)),
      m_pMainLayout(new QHBoxLayout(this)), m_pButtonLayout(new QVBoxLayout) {
  QFrame *f = new QFrame(this);
  f->setFrameShape(QFrame::Box);
  f->setLayout(m_pButtonLayout);
  f->setMaximumWidth(200);
  m_pButtonLayout->setContentsMargins(0, 0, 0, 0);

  m_pMainLayout->addWidget(f);
  m_pMainLayout->addWidget(m_pContents);

  setLayout(m_pMainLayout);
}

MenuItem *MenuWidget::addItem(const QString &text, const QIcon &icon,
                              QWidget *widget, MenuItem *parent) {
  MenuItem *menu;
  if (parent) {
    menu = new MenuItem(text, icon, parent);
    menu->setContentsMargins(parent->contentsMargins().left() + ICON_SIZE, 0, 0,
                             0);

    parent->addChild(menu);
  } else {
    menu = new MenuItem(text, icon);
  }
  connect(menu, &MenuItem::itemClicked, this, [this, menu]() {
    m_pContents->setCurrentIndex(m_menuIndices.value(menu));
  });

  m_pButtonLayout->addWidget(menu);
  int index = m_pContents->addWidget(widget);
  m_menuIndices.insert(menu, index);

  return menu;
}
