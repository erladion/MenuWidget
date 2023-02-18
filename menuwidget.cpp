#include <QHBoxLayout>
#include <QIcon>
#include <QMap>
#include <QPushButton>
#include <QStackedWidget>
#include <QVBoxLayout>

#include "menuwidget.h"

MenuItem::MenuItem(const QString& text, const QIcon& icon, MenuItem* parentItem, QWidget* parent)
    : QWidget(parent), m_pTextLabel(new QPushButton(icon, text)), m_pParent(parentItem) {
  QHBoxLayout* l = new QHBoxLayout();

  m_pRightIcon = new QPushButton();

  l->addWidget(m_pTextLabel);
  l->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Preferred));
  l->addWidget(m_pRightIcon);

  setLayout(l);
}

MenuWidget::MenuWidget(QWidget* parent)
    : QWidget(parent), contents_(new QStackedWidget(this)), mainLayout_(new QVBoxLayout(this)), buttonLayout_(new QHBoxLayout) {
  mainLayout_->addLayout(buttonLayout_);
  mainLayout_->addWidget(contents_);

  setLayout(mainLayout_);
}
