/*
*  Copyright 2019  Michail Vourlakos <mvourlakos@gmail.com>
*
*  This file is part of Latte-Dock
*
*  Latte-Dock is free software; you can redistribute it and/or
*  modify it under the terms of the GNU General Public License as
*  published by the Free Software Foundation; either version 2 of
*  the License, or (at your option) any later version.
*
*  Latte-Dock is distributed in the hope that it will be useful,
*  but WITHOUT ANY WARRANTY; without even the implied warranty of
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*  GNU General Public License for more details.
*
*  You should have received a copy of the GNU General Public License
*  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef VIEWCONTAINMENTINTERFACE_H
#define VIEWCONTAINMENTINTERFACE_H

// local
#include "tasksmodel.h"

// Qt
#include <QMetaMethod>
#include <QObject>
#include <QPointer>
#include <QQuickItem>
#include <QTimer>

namespace PlasmaQuick {
class AppletQuickItem;
}

namespace Latte {
class Corona;
class View;
}


namespace Latte {
namespace ViewPart {

class ContainmentInterface: public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool hasExpandedApplet READ hasExpandedApplet NOTIFY hasExpandedAppletChanged)

    Q_PROPERTY(QAbstractListModel *tasksModel READ tasksModel() NOTIFY tasksModelChanged)

public:
    ContainmentInterface(Latte::View *parent);
    virtual ~ContainmentInterface();

    bool hasExpandedApplet() const;

    bool applicationLauncherInPopup() const;
    bool applicationLauncherHasGlobalShortcut() const;
    bool containsApplicationLauncher() const;
    bool isCapableToShowShortcutBadges();

    bool activateEntry(const int index);
    bool newInstanceForEntry(const int index);

    bool activatePlasmaTask(const int index);
    bool newInstanceForPlasmaTask(const int index);

    bool hideShortcutBadges();
    bool showOnlyMeta();
    bool showShortcutBadges(const bool showLatteShortcuts, const bool showMeta);

    //! this is updated from external apps e.g. a thunderbird plugin
    bool updateBadgeForLatteTask(const QString identifier, const QString value);

    int applicationLauncherId() const;
    int appletIdForIndex(const int index);

    QAbstractListModel *tasksModel() const;

public slots:
    Q_INVOKABLE void deactivateApplets();
    Q_INVOKABLE void toggleAppletExpanded(const int id);

    Q_INVOKABLE bool appletIsExpandable(const int id);
    Q_INVOKABLE bool appletIsExpanded(const int id);

signals:
    void hasExpandedAppletChanged();
    void expandedAppletStateChanged();
    void tasksModelChanged();

private slots:
    void identifyMainItem();
    void identifyMethods();

    void updateAppletsTracking();
    void on_appletExpandedChanged();

private:
    void addExpandedApplet(const int &id);
    void removeExpandedApplet(const int &id);

    bool appletIsExpandable(PlasmaQuick::AppletQuickItem *appletQuickItem);

private:
    QMetaMethod m_activateEntryMethod;
    QMetaMethod m_appletIdForIndexMethod;
    QMetaMethod m_newInstanceMethod;
    QMetaMethod m_showShortcutsMethod;

    QPointer<Latte::Corona> m_corona;
    QPointer<Latte::View> m_view;
    QPointer<QQuickItem> m_mainItem;

    //! startup timer to initialize
    //! applets tracking
    QTimer m_appletsExpandedConnectionsTimer;

    TasksModel *m_tasksModel;

    QHash<PlasmaQuick::AppletQuickItem *, QMetaObject::Connection> m_appletsExpandedConnections;
    QList<int> m_expandedAppletIds;
};

}
}

#endif
