/*
*  Copyright 2016  Smith AR <audoban@openmailbox.org>
*                  Michail Vourlakos <mvourlakos@gmail.com>
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

#ifndef VIEW_H
#define VIEW_H

// local
#include <coretypes.h>
#include "containmentinterface.h"
#include "effects.h"
#include "positioner.h"
#include "visibilitymanager.h"
#include "indicator/indicator.h"
#include "settings/primaryconfigview.h"
#include "windowstracker/windowstracker.h"
#include "../shortcuts/globalshortcuts.h"
#include "../layout/genericlayout.h"
#include "../plasma/quick/containmentview.h"
#include "../plasma/quick/configview.h"

// C++
#include <array>

// Qt
#include <QQuickView>
#include <QMenu>
#include <QMetaObject>
#include <QMimeData>
#include <QScreen>
#include <QPointer>
#include <QTimer>


namespace Plasma {
class Types;
class Corona;
class Containment;
}

namespace PlasmaQuick {
class AppletQuickItem;
}


namespace KWayland {
namespace Client {
class PlasmaShellSurface;
}
}

namespace Latte {
class Corona;
class GenericLayout;

namespace ViewPart {
class ContextMenu;
}
}

namespace Latte {

class View : public PlasmaQuick::ContainmentView
{
    Q_OBJECT

    Q_PROPERTY(Latte::Types::ViewType type READ type WRITE setType NOTIFY typeChanged)

    Q_PROPERTY(bool alternativesIsShown READ alternativesIsShown NOTIFY alternativesIsShownChanged)
    Q_PROPERTY(bool behaveAsPlasmaPanel READ behaveAsPlasmaPanel WRITE setBehaveAsPlasmaPanel NOTIFY behaveAsPlasmaPanelChanged)
    Q_PROPERTY(bool byPassWM READ byPassWM WRITE setByPassWM NOTIFY byPassWMChanged)
    Q_PROPERTY(bool containsDrag READ containsDrag NOTIFY containsDragChanged)
    Q_PROPERTY(bool contextMenuIsShown READ contextMenuIsShown NOTIFY contextMenuIsShownChanged)
    Q_PROPERTY(bool inSettingsAdvancedMode READ inSettingsAdvancedMode NOTIFY inSettingsAdvancedModeChanged)

    //! Because Latte uses animations, changing to edit mode it may be different than
    //! when the isUserConfiguring changes value
    Q_PROPERTY(bool inEditMode READ inEditMode WRITE setInEditMode NOTIFY inEditModeChanged)
    Q_PROPERTY(bool isPreferredForShortcuts READ isPreferredForShortcuts WRITE setIsPreferredForShortcuts NOTIFY isPreferredForShortcutsChanged)
    Q_PROPERTY(bool latteTasksArePresent READ latteTasksArePresent WRITE setLatteTasksArePresent NOTIFY latteTasksArePresentChanged)
    Q_PROPERTY(bool onPrimary READ onPrimary WRITE setOnPrimary NOTIFY onPrimaryChanged)
    Q_PROPERTY(bool screenEdgeMarginEnabled READ screenEdgeMarginEnabled WRITE setScreenEdgeMarginEnabled NOTIFY screenEdgeMarginEnabledChanged)

    //! values to be used from Smart surrounding Views
    Q_PROPERTY(bool isTouchingBottomViewAndIsBusy READ isTouchingBottomViewAndIsBusy WRITE setIsTouchingBottomViewAndIsBusy NOTIFY isTouchingBottomViewAndIsBusyChanged)
    Q_PROPERTY(bool isTouchingTopViewAndIsBusy READ isTouchingTopViewAndIsBusy WRITE setIsTouchingTopViewAndIsBusy NOTIFY isTouchingTopViewAndIsBusyChanged)

    Q_PROPERTY(int alignment READ alignment WRITE setAlignment NOTIFY alignmentChanged)
    Q_PROPERTY(int fontPixelSize READ fontPixelSize WRITE setFontPixelSize NOTIFY fontPixelSizeChanged)
    Q_PROPERTY(int x READ x NOTIFY xChanged)
    Q_PROPERTY(int y READ y NOTIFY yChanged)
    Q_PROPERTY(int width READ width NOTIFY widthChanged)
    Q_PROPERTY(int height READ height NOTIFY heightChanged)
    Q_PROPERTY(int editThickness READ editThickness WRITE setEditThickness NOTIFY editThicknessChanged)
    Q_PROPERTY(int maxThickness READ maxThickness WRITE setMaxThickness NOTIFY maxThicknessChanged)
    Q_PROPERTY(int normalThickness READ normalThickness WRITE setNormalThickness NOTIFY normalThicknessChanged)
    Q_PROPERTY(int screenEdgeMargin READ screenEdgeMargin WRITE setScreenEdgeMargin NOTIFY screenEdgeMarginChanged)

    Q_PROPERTY(float maxLength READ maxLength WRITE setMaxLength NOTIFY maxLengthChanged)
    Q_PROPERTY(float offset READ offset WRITE setOffset NOTIFY offsetChanged)

    Q_PROPERTY(Latte::Layout::GenericLayout *layout READ layout WRITE setLayout NOTIFY layoutChanged)
    Q_PROPERTY(Latte::ViewPart::Effects *effects READ effects NOTIFY effectsChanged)
    Q_PROPERTY(Latte::ViewPart::ContainmentInterface *extendedInterface READ extendedInterface NOTIFY extendedInterfaceChanged)
    Q_PROPERTY(Latte::ViewPart::Indicator *indicator READ indicator NOTIFY indicatorChanged)
    Q_PROPERTY(Latte::ViewPart::Positioner *positioner READ positioner NOTIFY positionerChanged)
    Q_PROPERTY(Latte::ViewPart::VisibilityManager *visibility READ visibility NOTIFY visibilityChanged)
    Q_PROPERTY(Latte::ViewPart::WindowsTracker *windowsTracker READ windowsTracker NOTIFY windowsTrackerChanged)

    Q_PROPERTY(QRect absoluteGeometry READ absoluteGeometry NOTIFY absoluteGeometryChanged)
    Q_PROPERTY(QRect localGeometry READ localGeometry WRITE setLocalGeometry NOTIFY localGeometryChanged)
    Q_PROPERTY(QRect screenGeometry READ screenGeometry NOTIFY screenGeometryChanged)

public:
    View(Plasma::Corona *corona, QScreen *targetScreen = nullptr, bool byPassWM = false);
    virtual ~View();

    void init();

    Types::ViewType type() const;
    void setType(Types::ViewType type);

    bool alternativesIsShown() const;
    void setAlternativesIsShown(bool show);

    bool inDelete() const;

    bool onPrimary() const;
    void setOnPrimary(bool flag);

    int currentThickness() const;

    bool behaveAsPlasmaPanel() const;
    void setBehaveAsPlasmaPanel(bool behavior);

    bool containsDrag() const;
    bool containsMouse() const;

    bool contextMenuIsShown() const;

    bool byPassWM() const;
    void setByPassWM(bool bypass);

    bool inEditMode() const;
    void setInEditMode(bool edit);

    bool isFloatingWindow() const;

    bool isPreferredForShortcuts() const;
    void setIsPreferredForShortcuts(bool preferred);

    bool latteTasksArePresent() const;
    void setLatteTasksArePresent(bool present);

    bool inSettingsAdvancedMode() const;

    bool isTouchingBottomViewAndIsBusy() const;
    void setIsTouchingBottomViewAndIsBusy(bool touchAndBusy);

    bool isTouchingTopViewAndIsBusy() const;
    void setIsTouchingTopViewAndIsBusy(bool touchAndBusy);

    bool screenEdgeMarginEnabled() const;
    void setScreenEdgeMarginEnabled(bool enabled); 

    int fontPixelSize() const;
    void setFontPixelSize(int size);

    int editThickness() const;
    void setEditThickness(int thickness);

    int maxThickness() const;
    void setMaxThickness(int thickness);

    int normalThickness() const;
    void setNormalThickness(int thickness);

    int screenEdgeMargin() const;
    void setScreenEdgeMargin(int margin);

    int alignment() const;
    void setAlignment(int alignment);

    float maxLength() const;
    void setMaxLength(float length);

    float offset() const;
    void setOffset(float offset);

    QRect absoluteGeometry() const;
    QRect screenGeometry() const;

    QRect localGeometry() const;
    void setLocalGeometry(const QRect &geometry);

    QString validTitle() const;

    bool isOnActivity(const QString &activity) const;
    bool isOnAllActivities() const;

    QStringList activities() const;
    void setActivities(const QStringList &ids);


    bool settingsWindowIsShown();
    void showSettingsWindow();

    PlasmaQuick::ConfigView *configView();

    ViewPart::Effects *effects() const;   
    ViewPart::ContainmentInterface *extendedInterface() const;
    ViewPart::Indicator *indicator() const;
    ViewPart::Positioner *positioner() const;
    ViewPart::VisibilityManager *visibility() const;
    ViewPart::WindowsTracker *windowsTracker() const;

    Layout::GenericLayout *layout() const;
    void setLayout(Layout::GenericLayout *layout);

    KWayland::Client::PlasmaShellSurface *surface();

    //! release grab and restore mouse state
    void unblockMouse(int x, int y);

    void reconsiderScreen();

    //! these are signals that create crashes, such a example is the availableScreenRectChanged from corona
    //! when its containment is destroyed
    void disconnectSensitiveSignals();

public slots:
    Q_INVOKABLE void copyView();
    Q_INVOKABLE void removeView();

    Q_INVOKABLE QVariantList containmentActions();

    Q_INVOKABLE void moveToLayout(QString layoutName);
    Q_INVOKABLE void removeTasksPlasmoid();

    Q_INVOKABLE bool mimeContainsPlasmoid(QMimeData *mimeData, QString name);
    Q_INVOKABLE bool tasksPresent();

    void updateAbsoluteGeometry(bool bypassChecks = false);

    Q_INVOKABLE bool isHighestPriorityView();

protected slots:
    void showConfigurationInterface(Plasma::Applet *applet) override;

protected:
    bool event(QEvent *ev) override;
    void mousePressEvent(QMouseEvent *event) override;

signals:
    void eventTriggered(QEvent *ev);
    void mousePressed(const QPoint pos, const int button);
    void mouseReleased(const QPoint pos, const int button);
    void wheelScrolled(const QPoint pos, const QPoint angleDelta, const int buttons);

    void activitiesChanged();
    void alternativesIsShownChanged();
    void alignmentChanged();
    void behaveAsPlasmaPanelChanged();
    void byPassWMChanged();
    void configWindowGeometryChanged(); // is called from config windows
    void containsDragChanged();
    void contextMenuIsShownChanged();
    void dockLocationChanged();
    void editThicknessChanged();
    void effectsChanged();
    void extendedInterfaceChanged();
    void fontPixelSizeChanged();
    void forcedShown(); //[workaround] forced shown to avoid a KWin issue that hides windows when closing activities
    void widthChanged();
    void heightChanged();
    void inEditModeChanged();
    void indicatorChanged();
    void inSettingsAdvancedModeChanged();
    void isPreferredForShortcutsChanged();
    void isTouchingBottomViewAndIsBusyChanged();
    void isTouchingTopViewAndIsBusyChanged();
    void latteTasksArePresentChanged();
    void layoutChanged();
    void localGeometryChanged();
    void maxLengthChanged();
    void maxThicknessChanged();
    void normalThicknessChanged();
    void offsetChanged();
    void onPrimaryChanged();
    void positionerChanged();
    void screenEdgeMarginChanged();
    void screenEdgeMarginEnabledChanged();
    void screenGeometryChanged();
    void typeChanged();
    void visibilityChanged();
    void windowsTrackerChanged();
    void xChanged();
    void yChanged();

    void absoluteGeometryChanged(const QRect &geometry);

    void indicatorPluginChanged(const QString &indicatorId);
    void indicatorPluginRemoved(const QString &indicatorId);

    //! are used to trigger the Corona relevant signals and in that
    //! way we can disable any such signaling all together, e.g. through disconnectSensitiveSignals()
    void availableScreenRectChangedFrom(Latte::View *origin);
    void availableScreenRegionChangedFrom(Latte::View *origin);

private slots:
    void applyActivitiesToWindows();
    void availableScreenRectChangedFromSlot(View *origin);
    void configViewCreatedFor(Latte::View *view);
    void hideWindowsForSlidingOut();
    void preferredViewForShortcutsChangedSlot(Latte::View *view);
    void releaseGrab();
    void reloadSource();
    void updateTransientWindowsTracking();
    void statusChanged(Plasma::Types::ItemStatus);

    void addTransientWindow(QWindow *window);
    void removeTransientWindow(const bool &visible);

    void restoreConfig();
    void saveConfig();

private:
    void initSignalingForLocationChangeSliding();
    void setupWaylandIntegration();
    void updateAppletContainsMethod();

    void setContainsDrag(bool contains);

private:
    Plasma::Containment *containmentById(uint id);

    bool m_alternativesIsShown{false};
    bool m_behaveAsPlasmaPanel{false};
    bool m_byPassWM{true};
    bool m_containsDrag{false};
    bool m_containsMouse{false};
    bool m_inDelete{false};
    bool m_inEditMode{false};
    bool m_isPreferredForShortcuts{false};
    bool m_latteTasksArePresent{false};
    bool m_onPrimary{true};
    bool m_screenEdgeMarginEnabled{false};

    bool m_isTouchingBottomViewAndIsBusy{false};
    bool m_isTouchingTopViewAndIsBusy{false};

    int m_fontPixelSize{ -1};
    int m_editThickness{24};
    int m_maxThickness{24};
    int m_normalThickness{24};
    int m_screenEdgeMargin{-1};
    float m_maxLength{1};
    float m_offset{0};

    Types::Alignment m_alignment{Types::Center};
    Types::ViewType m_type{Types::DockView};

    QRect m_localGeometry;
    QRect m_absoluteGeometry;

    QStringList m_activities;

    //! HACK: In order to avoid crashes when the View is added and removed
    //! immediately during startup
    QTimer m_initLayoutTimer;

    //! HACK: Timers in order to handle KWin faulty
    //! behavior that hides Views when closing Activities
    //! with no actual reason
    QTimer m_visibleHackTimer1;
    QTimer m_visibleHackTimer2;

    QTimer m_releaseGrabTimer;
    int m_releaseGrab_x;
    int m_releaseGrab_y;

    Layout::GenericLayout *m_layout{nullptr};
    QPointer<PlasmaQuick::ConfigView> m_configView;

    QPointer<ViewPart::ContextMenu> m_contextMenu;
    QPointer<ViewPart::Effects> m_effects;
    QPointer<ViewPart::Indicator> m_indicator;
    QPointer<ViewPart::ContainmentInterface> m_interface;
    QPointer<ViewPart::Positioner> m_positioner;
    QPointer<ViewPart::VisibilityManager> m_visibility;
    QPointer<ViewPart::WindowsTracker> m_windowsTracker;

    //! Connections to release and bound for the assigned layout
    QList<QMetaObject::Connection> connectionsLayout;

    //! track transientWindows
    QList<QWindow *> m_transientWindows;

    QPointer<Latte::Corona> m_corona;

    KWayland::Client::PlasmaShellSurface *m_shellSurface{nullptr};
};

}

#endif
