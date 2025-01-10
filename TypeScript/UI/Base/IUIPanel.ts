/*
 * @Author: linb
 * @Date: 2025-01-09 15:19:22
 * @Description:
 * @Copyright: Copyright HuanMos. All Rights Reserved.
 */

import { CommonEnum } from "../../Const/CommonEnum";
import { IUIBase } from "./IUIBase";

export interface IUIPanel extends IUIBase {
    /**
     * @description: 获取ZOrder
     * @return {*}
     */
    GetZOrder(): number;

    /**
     * @description: 获取窗口层级
     * @return {*}
     */
    GetPanelLayer(): CommonEnum.PanelLayer;

    /**
     * @description: 设置归属层级
     * @param {CommonEnum} panelLayer
     * @return {*}
     */
    SetPanelLayer(panelLayer: CommonEnum.PanelLayer): void;
}