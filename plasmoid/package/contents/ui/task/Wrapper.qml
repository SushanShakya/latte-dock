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

import QtQuick 2.0

import org.kde.plasma.core 2.0 as PlasmaCore

import org.kde.latte.core 0.2 as LatteCore

Item{
    id: wrapper

    opacity: 0
    width: {
        if (!taskItem.visible)
            return 0;

        if (taskItem.isSeparator){
            if (!root.vertical)
                return 0;
            else
                return (taskItem.metrics.iconSize + root.widthMargins + root.screenEdgeMargin);
        }

        if (taskItem.isStartup && taskItem.animations.speedFactor.current !==0 ) {
            return root.vertical ? cleanScalingWidth + root.screenEdgeMargin : cleanScalingWidth;
        } else {
            return root.vertical ? showDelegateWidth + root.screenEdgeMargin : showDelegateWidth;
        }
    }

    height: {
        if (!taskItem.visible)
            return 0;

        if (taskItem.isSeparator){
            if (root.vertical)
                return 0;
            else
                return (taskItem.metrics.iconSize + root.heightMargins + root.screenEdgeMargin);
        }

        if (taskItem.isStartup && taskItem.animations.speedFactor.current !==0){
            return !root.vertical ? cleanScalingHeight + root.screenEdgeMargin : cleanScalingHeight;
        } else {
            return !root.vertical ? showDelegateHeight + root.screenEdgeMargin : showDelegateHeight;
        }
    }

    property int maxThickness: !root.vertical ? root.zoomFactor*(taskItem.metrics.iconSize+root.heightMargins)
                                              : root.zoomFactor*(taskItem.metrics.iconSize+root.widthMargins)

    property real showDelegateWidth: basicScalingWidth
    property real showDelegateHeight: basicScalingHeight

    //scales which are used mainly for activating InLauncher
    ////Scalers///////
    property bool inTempScaling: ((tempScaleWidth !== 1) || (tempScaleHeight !== 1) )

    property real mScale: 1
    property real tempScaleWidth: 1
    property real tempScaleHeight: 1

    property real scaleWidth: (inTempScaling == true) ? tempScaleWidth : mScale
    property real scaleHeight: (inTempScaling == true) ? tempScaleHeight : mScale

    property real cleanScalingWidth: (taskItem.metrics.iconSize + root.widthMargins) * mScale
    property real cleanScalingHeight: (taskItem.metrics.iconSize + root.heightMargins) * mScale

    property real basicScalingWidth : (inTempScaling == true) ? ((taskItem.metrics.iconSize + root.widthMargins) * scaleWidth) : cleanScalingWidth
    property real basicScalingHeight : (inTempScaling == true) ? ((taskItem.metrics.iconSize + root.heightMargins) * scaleHeight) : cleanScalingHeight

    property real regulatorWidth: taskItem.isSeparator ? width : basicScalingWidth;
    property real regulatorHeight: taskItem.isSeparator ? height : basicScalingHeight;

    property real visualScaledWidth: (taskItem.metrics.iconSize + root.internalWidthMargins) * mScale
    property real visualScaledHeight: (taskItem.metrics.iconSize + root.internalHeightMargins) * mScale
    /// end of Scalers///////

    //property int curIndex: icList.hoveredIndex
    //  property int index: taskItem.Positioner.index
    //property real center: (width + hiddenSpacerLeft.separatorSpace + hiddenSpacerRight.separatorSpace) / 2
    property real center: !root.vertical ?
                             (width + hiddenSpacerLeft.separatorSpace + hiddenSpacerRight.separatorSpace) / 2 :
                             (height + hiddenSpacerLeft.separatorSpace + hiddenSpacerRight.separatorSpace) / 2

    property color backgroundColor: taskIconItem.backgroundColor
    property color glowColor: taskIconItem.glowColor

    property bool progressVisible: taskIconItem.progressVisible
    property real progress: taskIconItem.progress

    property Item visualIconItem: taskIconItem.visualIconItem
    property Item titleTooltipVisualParent: taskIconItem.titleTooltipVisualParent
    property Item previewsTooltipVisualParent: taskIconItem.previewsTootipVisualParent

    signal runLauncherAnimation();

    readonly property string bothAxisZoomEvent: wrapper + "_zoom"
     /* Rectangle{
            anchors.fill: parent
            border.width: 1
            border.color: "green"
            color: "transparent"
        }*/

    Behavior on mScale {
        enabled: !root.globalDirectRender || inMimicParabolicAnimation
        NumberAnimation{
            duration: 3 * taskItem.animationTime
            easing.type: Easing.OutCubic
        }
    }

    Behavior on mScale {
        enabled: root.globalDirectRender && !inMimicParabolicAnimation && !restoreAnimation.running
        NumberAnimation { duration: root.directRenderAnimationTime }
    }

    IconItem{
        id: taskIconItem
        anchors.bottom: (root.location === PlasmaCore.Types.BottomEdge) ? parent.bottom : undefined
        anchors.top: (root.location === PlasmaCore.Types.TopEdge) ? parent.top : undefined
        anchors.left: (root.location === PlasmaCore.Types.LeftEdge) ? parent.left : undefined
        anchors.right: (root.location === PlasmaCore.Types.RightEdge) ? parent.right : undefined

        anchors.horizontalCenter: !root.vertical ? parent.horizontalCenter : undefined
        anchors.verticalCenter: root.vertical ? parent.verticalCenter : undefined

        anchors.bottomMargin: (root.location === PlasmaCore.Types.BottomEdge) ? root.screenEdgeMargin : 0
        anchors.topMargin: (root.location === PlasmaCore.Types.TopEdge) ? root.screenEdgeMargin : 0
        anchors.leftMargin: (root.location === PlasmaCore.Types.LeftEdge) ? root.screenEdgeMargin : 0
        anchors.rightMargin: (root.location === PlasmaCore.Types.RightEdge) ? root.screenEdgeMargin : 0

        anchors.horizontalCenterOffset: taskItem.iconOffsetX
        anchors.verticalCenterOffset: taskItem.iconOffsetY

        width: wrapper.regulatorWidth
        height: wrapper.regulatorHeight
    }

    function calculateScales( currentMousePosition ){
        if (root.zoomFactor===1) {
            return;
        }

        var distanceFromHovered = Math.abs(index - icList.hoveredIndex);

        // A new algorithm trying to make the zoom calculation only once
        // and at the same time fixing glitches
        if ((distanceFromHovered === 0) &&
                //! IMPORTANT: IS FIXING A BUG THAT NEGATIVE VALUES ARE SENT onEntered EVENT OF MOUSEAREA
                // (currentMousePosition>=0) &&
                (root.dragSource === null) ){

            //use the new parabolicManager in order to handle all parabolic effect messages
            var scales = parabolicManager.applyParabolicEffect(index, currentMousePosition, center);

            //Left hiddenSpacer for first task
            if(((index === parabolicManager.firstRealTaskIndex )&&(root.tasksCount>0)) && !root.disableLeftSpacer
                    && !inMimicParabolicAnimation && !inFastRestoreAnimation && !inAttentionAnimation){
                hiddenSpacerLeft.nScale = scales.leftScale - 1;
            }

            //Right hiddenSpacer for last task
            if(((index === parabolicManager.lastRealTaskIndex )&&(root.tasksCount>0)) && !root.disableRightSpacer
                    && !inMimicParabolicAnimation && !inFastRestoreAnimation && !inAttentionAnimation){
                hiddenSpacerRight.nScale =  scales.rightScale - 1;
            }

            if (!taskItem.inAttentionAnimation) {
                mScale = root.zoomFactor;
            } else {
                var subSpacerScale = (root.zoomFactor-1)/2;

                hiddenSpacerLeft.nScale = subSpacerScale;
                hiddenSpacerRight.nScale = subSpacerScale;
            }

            taskItem.scalesUpdatedOnce = false;
        }

    } //nScale

    function signalUpdateScale(nIndex, nScale, step){
        if (!taskItem.containsMouse && (index === nIndex)
                && (taskItem.hoverEnabled || inMimicParabolicAnimation)&&(tasksExtendedManager.waitingLaunchersLength()===0)){
            if (taskItem.inAttentionAnimation) {
                var subSpacerScale = (nScale-1)/2;

                hiddenSpacerLeft.nScale = subSpacerScale;
                hiddenSpacerRight.nScale = subSpacerScale;
            } else if (!inBlockingAnimation || taskItem.inMimicParabolicAnimation) {
                var newScale = 1;

                if(nScale >= 0) {
                    newScale = nScale + step;
                } else {
                    newScale = mScale + step;
                }

                if (inMimicParabolicAnimation && mimicParabolicScale === -1) {
                    mimicParabolicScale = newScale;
                }

                mScale = newScale;
            }
        }
    }

    function sendEndOfNeedBothAxisAnimation(){
        if (taskItem.isZoomed) {
            taskItem.isZoomed = false;
            taskItem.animations.needBothAxis.removeEvent(bothAxisZoomEvent);
        }
    }

    onMScaleChanged: {
        if ((mScale === root.zoomFactor) && !root.directRenderTimerIsRunning && !root.globalDirectRender) {
            root.setGlobalDirectRender(true);
        }

        if (inMimicParabolicAnimation){
            if (mScale >= mimicParabolicScale) {
                inMimicParabolicAnimation = false;
                inAnimation = false;
                inBlockingAnimation = false;
                mimicParabolicScale = -1;
            } else {
                var tempScale = (root.zoomFactor - mScale) / 2;

                hiddenSpacerLeft.nScale = tempScale;
                hiddenSpacerRight.nScale = tempScale;
            }
        }

        if ((mScale > 1) && !taskItem.isZoomed) {
            taskItem.isZoomed = true;
            taskItem.animations.needBothAxis.addEvent(bothAxisZoomEvent);
        } else if ((mScale == 1) && taskItem.isZoomed) {
            sendEndOfNeedBothAxisAnimation();
        }
    }

    Component.onCompleted: {
        if (!LatteCore.WindowSystem.compositingActive) {
            opacity = 1;
        }

        root.updateScale.connect(signalUpdateScale);
    }

    Component.onDestruction: {
        root.updateScale.disconnect(signalUpdateScale);
    }
}// Main task area // id:wrapper
