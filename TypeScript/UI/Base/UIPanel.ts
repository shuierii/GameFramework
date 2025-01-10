/*
 * @Author: linb
 * @Date: 2025-01-09 15:18:49
 * @Description:
 * @Copyright: Copyright HuanMos. All Rights Reserved.
 */
import * as UE from "ue";
import { CommonEnum } from "../../Const/CommonEnum";
import { SystemID } from "../../Const/SystemID";
import { IUISystem } from "../../System/UI/IUISystem";
import { IUIPanel } from "./IUIPanel";
import { UIBase } from "./UIBase";

export abstract class UIPanel extends UIBase implements IUIPanel {

    private mPanelLayer: CommonEnum.PanelLayer;

    /**
     * @description: 关闭窗口
     * @return {*}
     */
    Close(): void {
        this.GetSystem<IUISystem>(SystemID.UI_SYSTEM).ClosePanel(this.GetCookieName());
    }

    /**
     * @description: 获取ZOrder
     * @return {*}
     */
    GetZOrder(): number {
        if (this.GetUIWidget().Slot == null)
            return -1;

        let slot = this.GetUIWidget().Slot as UE.CanvasPanelSlot;
        if (slot == null)
            return -1;

        return slot.ZOrder;
    }

    /**
     * @description: 获取窗口层级
     * @return {*}
     */
    GetPanelLayer(): CommonEnum.PanelLayer {
        return this.mPanelLayer;
    }

    /**
     * @description: 设置归属层级
     * @param {CommonEnum} panelLayer
     * @return {*}
     */
    SetPanelLayer(panelLayer: CommonEnum.PanelLayer): void {
        this.mPanelLayer = panelLayer;
    }
}