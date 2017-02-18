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

import QtQuick 2.1
import QtQuick.Window 2.2

import org.kde.plasma.core 2.0 as PlasmaCore

import org.kde.latte 0.1 as Latte

Window{
    width: mainGrid.width + 10
    height: Math.min(mainGrid.height+10, Screen.height-root.realSize)
    visible: true

    property string space:" :   "

    Grid{
        id:mainGrid
        columns: 2

        Text{
            text: "Window Width"+space
        }

        Text{
            text: dock.width
        }

        Text{
            text: "Window Height"+space
        }

        Text{
            text: dock.height
        }

        Text{
            text: "Contents Width"+space
        }

        Text{
            text: layoutsContainer.contentsWidth
        }

        Text{
            text: "Contents Height"+space
        }

        Text{
            text: layoutsContainer.contentsHeight
        }

        Text{
            text: "Max Length (user)"+space
        }

        Text{
            text: plasmoid.configuration.maxLength +"%"
        }

        Text{
            text: "Max Length (pixels)"+space
        }

        Text{
            text: root.maxLength
        }

        Text{
            text: "Mask"+space
        }

        Text{
            text: dock.maskArea.x +", "+ dock.maskArea.y+"  "+dock.maskArea.width+"x"+dock.maskArea.height
        }

        Text{
            text: "Local Geometry"+space
        }

        Text{
            text: visibilityManager.localGeometry.x + ", " + visibilityManager.localGeometry.y + "  " +
                  visibilityManager.localGeometry.width + "x" + visibilityManager.localGeometry.height
        }

        Text{
            text: "Is Hidden (flag)"+space
        }

        Text{
            text: {
                if (dock.visibility.isHidden)
                    return "Yes";
                else
                    return "No";
            }
        }

        Text{
            text: "Contains Mouse (flag)"+space
        }

        Text{
            text: {
                if (dock.visibility.containsMouse)
                    return "Yes";
                else
                    return "No";
            }
        }

        Text{
            text: "Edit Mode"+space
        }

        Text{
            text: {
                if (root.editMode)
                    return "Yes";
                else
                    return "No";
            }
        }

        Text{
            text: "   -----------   "
        }

        Text{
            text: " -----------   "
        }

        Text{
            text: "Location"+space
        }

        Text{
            text: {
                switch(plasmoid.location){
                case PlasmaCore.Types.LeftEdge:
                    return "Left Edge";
                    break;
                case PlasmaCore.Types.RightEdge:
                    return "Right Edge";
                    break;
                case PlasmaCore.Types.TopEdge:
                    return "Top Edge";
                    break;
                case PlasmaCore.Types.BottomEdge:
                    return "Bottom Edge";
                    break;
                }

                return " <unknown> : " + plasmoid.location;
            }
        }

        Text{
            text: "Alignment"+space
        }

        Text{
            text: {
                switch(plasmoid.configuration.panelPosition){
                case Latte.Dock.Left:
                    return "Left";
                    break;
                case Latte.Dock.Right:
                    return "Right";
                    break;
                case Latte.Dock.Center:
                    return "Center";
                    break;
                case Latte.Dock.Top:
                    return "Top";
                    break;
                case Latte.Dock.Bottom:
                    return "Bottom";
                    break;
                case Latte.Dock.Justify:
                    return "Justify";
                    break;
                }

                return "<unknown> : " + plasmoid.configuration.panelPosition;
            }
        }

        Text{
            text: "Visibility"+space
        }

        Text{
            text: {
                switch(dock.visibility.mode){
                case Latte.Dock.AlwaysVisible:
                    return "Always Visible";
                    break;
                case Latte.Dock.AutoHide:
                    return "Auto Hide";
                    break;
                case Latte.Dock.DodgeActive:
                    return "Dodge Active";
                    break;
                case Latte.Dock.DodgeMaximized:
                    return "Dodge Maximized";
                    break;
                case Latte.Dock.DodgeAllWindows:
                    return "Dodge All Windows";
                    break;
                case Latte.Dock.None:
                    return "None";
                    break;
                }

                return "<unknown> : " + dock.visibility.mode;
            }
        }

        Text{
            text: "Zoom Factor"+space
        }

        Text{
            text: root.zoomFactor
        }

        Text{
            text: "   -----------   "
        }

        Text{
            text: " -----------   "
        }

        Text{
            text: "Icon Size (user)"+space
        }

        Text{
            text: plasmoid.configuration.iconSize
        }

        Text{
            text: "Icon Size (automatic)"+space
        }

        Text{
            text: root.automaticIconSizeBasedSize
        }

        Text{
            text: "Icon Size (current)"+space
        }

        Text{
            text: root.iconSize
        }

        Text{
            text: "   -----------   "
        }

        Text{
            text: " -----------   "
        }

        Text{
            text: "Show Panel Background (user)"+space
        }

        Text{
            text: {
                if (plasmoid.configuration.useThemePanel)
                    return "Yes";
                else
                    return "No";
            }
        }

        Text{
            text: "Panel Background Length"+space
        }

        Text{
            text: root.realPanelLength
        }

        Text{
            text: "Panel Background Thickness(user)"+space
        }

        Text{
            text: plasmoid.configuration.panelSize
        }

        Text{
            text: "Panel Background Thickness(automatic)"+space
        }

        Text{
            text: root.realPanelSize
        }

        Text{
            text: "Panel Background Shadow"+space
        }

        Text{
            text: root.panelShadow
        }

        Text{
            text: "Panel Background Margin"+space
        }

        Text{
            text: root.panelMargin
        }

        Text{
            text: "   -----------   "
        }

        Text{
            text: " -----------   "
        }

        Text{
            text: "Mask - Normal Thickness"+space
        }

        Text{
            text: visibilityManager.thicknessNormal
        }

        Text{
            text: "Thickness Uses Panel Size"+space
        }

        Text{
            text: visibilityManager.panelIsBiggerFromIconSize
        }

        Text{
            text: "Draw Shadows (external)"+space
        }

        Text{
            text: {
                if (root.drawShadowsExternal)
                    return "Yes";
                else
                    return "No";
            }
        }

        Text{
            text: "   -----------   "
        }

        Text{
            text: " -----------   "
        }

        Text{
            text: "Applet Hovered"+space
        }

        Text{
            text: layoutsContainer.hoveredIndex
        }

        Text{
            text: "Task Hovered"+space
        }

        Text{
            text: root.latteAppletHoveredIndex
        }

        Text{
            text: "In Normal State"+space
        }

        Text{
            text: visibilityManager.normalState
        }

        Text{
            text: "Animations Both Axis"+space
        }

        Text{
            text: root.animationsNeedBothAxis
        }

        Text{
            text: "Animations Only Length"+space
        }

        Text{
            text: root.animationsNeedLength
        }

        Text{
            text: "Animations Need Thickness"+space
        }

        Text{
            text: root.animationsNeedThickness
        }

    }
}
