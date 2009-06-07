#include "window.h"

Window::Window(pann::Net* _net)
{
    this->resize(700, 500);
    QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(this->sizePolicy().hasHeightForWidth());
    this->setSizePolicy(sizePolicy);
    this->setMinimumSize(QSize(700, 500));
    this->setFocusPolicy(Qt::StrongFocus);
    this->setAutoFillBackground(false);

    label = new QLabel(tr("test"), this);
    QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Preferred);
    sizePolicy1.setHorizontalStretch(0);
    sizePolicy1.setVerticalStretch(0);
    sizePolicy1.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
    label->setSizePolicy(sizePolicy1);
    label->setMinimumSize(QSize(150, 0));
    label->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    label->setWordWrap(true);

    glWidget = new GLWidget(_net, label);
    glWidget->setMinimumSize(QSize(0, 0));
    glWidget->setFocusPolicy(Qt::StrongFocus);

    QHBoxLayout* horizontalLayout = new QHBoxLayout(this);
    horizontalLayout->addWidget(glWidget);
    horizontalLayout->addWidget(label);

    setLayout(horizontalLayout );

    setWindowTitle(tr("pann viewer"));
}

void Window::mouseDoubleClickEvent(QMouseEvent* event)
{
    pann::moo();
}

