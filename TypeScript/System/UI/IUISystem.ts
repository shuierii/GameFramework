/*
 * @Author: linb
 * @Date: 2025-01-09 15:13:42
 * @Description:
 * @Copyright: Copyright HuanMos. All Rights Reserved.
 */
import * as UE from "ue";
import { CommonEnum } from "../../Const/CommonEnum";
import { ISystem } from "../../Interface/ISystem";
import { IUIPanel } from "../../UI/Base/IUIPanel";

export interface IUISystem extends ISystem {

    /**
     * @description: 显示窗口
     * @param {new} panelClass  窗口类
     * @param {string} panelName    窗口名
     * @param {CommonEnum} panelLayer   窗口层级
     * @return {*}
     */
    ShowPanel<TPanel extends IUIPanel>(panelClass: new (...args: any[]) => IUIPanel, panelName: string, panelLayer?: CommonEnum.PanelLayer): TPanel;

    /**
     * @description: 关闭窗口
     * @param {string} panelName
     * @return {*}
     */
    ClosePanel(panelName: string): void;

    /**
     * @description: 创建UI控件
     * @param {string} widgetName
     * @return {*}
     */
    CreateUIWidget<TWidget extends UE.UserWidget>(widgetName: string): TWidget;
}