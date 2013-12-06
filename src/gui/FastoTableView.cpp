#include "gui/FastoTableView.h"

#include <QMenu>
#include <QHeaderView>

#include "common/macros.h"

namespace fastoredis
{
    FastoTableView::FastoTableView(QWidget *parent)
        :base_class(parent)
    {
        verticalHeader()->setDefaultAlignment(Qt::AlignLeft);
        horizontalHeader()->setDefaultAlignment(Qt::AlignLeft);
        setSelectionMode(QAbstractItemView::ExtendedSelection);
        setSelectionBehavior(QAbstractItemView::SelectItems);
        setContextMenuPolicy(Qt::CustomContextMenu);
        VERIFY(connect(this, SIGNAL(customContextMenuRequested(const QPoint&)), this, SLOT(showContextMenu(const QPoint&))));
    }

    void FastoTableView::showContextMenu(const QPoint &point)
    {
        QPoint menuPoint = mapToGlobal(point);
        menuPoint.setY(menuPoint.y() + horizontalHeader()->height());
        menuPoint.setX(menuPoint.x() + verticalHeader()->width());
        QMenu menu(this);
        menu.exec(menuPoint);
    }
}
