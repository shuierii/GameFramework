/*
 * @Author: linb
 * @Date: 2025-01-09 15:13:31
 * @Description:
 * @Copyright: Copyright HuanMos. All Rights Reserved.
 */
import * as UE from "ue";
import { SystemBase } from "../../Abstract/SystemBase";
import { CommonEnum } from "../../Const/CommonEnum";
import { SystemID } from "../../Const/SystemID";
import { MainGame } from "../../MainGame";
import { IUIPanel } from "../../UI/Base/IUIPanel";
import { LogUtility } from "../../Utility/LogUtility";
import { IUISystem } from "./IUISystem";

//       Root
//   对话  提示  底层

export class UISystem extends SystemBase implements IUISystem {

    // 根UI控件，所有的界面控件都要根放入UI下作为子UI
    private mRootWidgeht: UE.Game.UI.UserWidgets.WBP_Root.WBP_Root_C;

    // 页面记录
    private mNameToPanelMap: Map<string, IUIPanel> = new Map();

    // 窗口层级下子窗口的映射
    private mPanelLayerToPanelNameMap: Map<CommonEnum.PanelLayer, Set<string>> = new Map();

    // 窗口层级对应的RootUI映射
    private mLayerRootMap: Map<CommonEnum.PanelLayer, UE.Game.UI.UserWidgets.WBP_Root.WBP_Root_C> = new Map();

    protected GetSystemID(): number {
        return SystemID.UI_SYSTEM;
    }

    protected OnInit(): void {

    }

    protected OnRelease(): void {
        if (this.mRootWidgeht) {
            this.mRootWidgeht.RemoveFromParent();
        }

        for (let panel of this.mNameToPanelMap.values()) {
            panel.Disable();
            panel.Destroy();
        }

        this.mNameToPanelMap.clear();
        this.mPanelLayerToPanelNameMap.clear();
        this.mLayerRootMap.clear();
        this.mRootWidgeht = null;
    }

    /**
     * @description: 显示窗口
     * @param {new} panelClass  窗口类
     * @param {string} panelName    窗口名
     * @param {CommonEnum} panelLayer   窗口层级
     * @return {*}
     */
    ShowPanel<TPanel extends IUIPanel>(panelClass: new (...args: any[]) => IUIPanel, panelName: string, panelLayer: CommonEnum.PanelLayer = CommonEnum.PanelLayer.DIALOG): TPanel {
        if (this.mRootWidgeht == null)
            this.InitRootUI();

        if (panelClass == null)
            return null;

        let panel: IUIPanel = this.GetPanel(panelName);
        // 没有创建过此窗口的记录
        if (panel == null) {
            // 创建窗口
            panel = new panelClass();
            if (panel == null) {
                LogUtility.Error(`the panel(${panelName}) new failed`);

                return null;
            }

            // 记录
            this.mNameToPanelMap.set(panelName, panel);

            // 设置窗口cookieName
            panel.SetCookieName(panelName);

            // 显示窗口
            panel.SetVisibility(UE.ESlateVisibility.SelfHitTestInvisible);

            // 设置层级
            this.AddPanelToLayer(panelName, panel, panelLayer);

            // 窗口初始化
            panel.Init();

            // 窗口启用
            panel.Enable();
        }

        // 有此窗口的创建记录
        else {
            // 显示窗口
            panel.SetVisibility(UE.ESlateVisibility.SelfHitTestInvisible);

            // 设置层级
            if (!this.mPanelLayerToPanelNameMap.get(panelLayer).has(panelName)) {
                this.AddPanelToLayer(panelName, panel, panelLayer);
            }

            // 窗口启用
            panel.Enable();
        }

        return panel as TPanel;
    }

    /**
     * @description: 关闭窗口
     * @param {string} panelName
     * @return {*}
     */
    ClosePanel(panelName: string): void {
        let panel = this.GetPanel(panelName);
        if (panel == null)
            return;

        // 窗口隐藏
        panel.SetVisibility(UE.ESlateVisibility.Collapsed);

        // 窗口禁用
        panel.Disable();

        // 从当前层级中移除
        let panelLayer = panel.GetPanelLayer();
        let uiSet = this.mPanelLayerToPanelNameMap.get(panelLayer);
        uiSet.delete(panelName);

        // 从父节点移除
        panel.GetUIWidget().RemoveFromParent();

        // 窗口销毁
        panel.Destroy();

        // 移除记录
        this.mNameToPanelMap.delete(panelName);
    }

    /**
     * @description: 创建UI控件
     * @param {string} widgetName
     * @return {*}
     */
    CreateUIWidget<TWidget extends UE.UserWidget>(widgetName: string): TWidget {
        let widgetRef = `/Game/UI/UserWidgets/` + `${widgetName}.${widgetName}_C`;

        // 加载widget class
        let widgetClass = UE.Class.Load(widgetRef);
        if (widgetClass == null) {
            LogUtility.Error(`the widget(${widgetName}) load class failed`)

            return null;
        }

        let widget = UE.WidgetExtensionMethods.CreateWidget(MainGame.UEInstance.GetWorld(), widgetClass);
        if (widget == null) {
            LogUtility.Error(`the widget(${widgetName}) create failed`);

            return null;
        }

        return widget as TWidget;
    }

    /**
     * @description: 获取窗口
     * @param {string} panelName
     * @return {*}
     */
    GetPanel(panelName: string): IUIPanel {
        if (!this.mNameToPanelMap.has(panelName))
            return null;

        return this.mNameToPanelMap.get(panelName);
    }

    /**
     * @description: 初始化RootUI
     * @return {*}
     */
    private InitRootUI(): void {
        if (this.mRootWidgeht != null)
            return;

        // 创建根UI
        this.mRootWidgeht = this.CreateUIWidget<UE.Game.UI.UserWidgets.WBP_Root.WBP_Root_C>("WBP_Root");
        if (this.mRootWidgeht == null) {
            LogUtility.Error(`the root(WBP_Root) create failed`);

            return null;
        }

        // 添加到视口
        this.mRootWidgeht.AddToViewport(0);

        this.mRootWidgeht.SetVisibility(UE.ESlateVisibility.SelfHitTestInvisible);

        // 遍历UI层级，添加到 RootWidget 下
        for (let key in CommonEnum.PanelLayer) {
            let panelLayer = parseInt(CommonEnum.PanelLayer[key]);
            if (isNaN(panelLayer))
                continue;

            let uiWidget = this.CreateUIWidget<UE.Game.UI.UserWidgets.WBP_Root.WBP_Root_C>("WBP_Root");
            let slot = this.mRootWidgeht.RootCanvas.AddChildToCanvas(uiWidget);
            if (slot == null)
                continue;

            // 设置锚点
            slot.SetAnchors(new UE.Anchors(new UE.Vector2D(0, 0), new UE.Vector2D(1, 1)));
            slot.SetAlignment(new UE.Vector2D(0, 0));
            slot.SetOffsets(new UE.Margin(0, 0, 0, 0));
            slot.SetZOrder(panelLayer);

            this.mLayerRootMap.set(panelLayer, uiWidget);

            this.mPanelLayerToPanelNameMap.set(panelLayer, new Set());
        }
    }

    /**
     * @description: 添加页面到指定层级下
     * @return {*}
     */
    private AddPanelToLayer(panelName: string, panel: IUIPanel, panelLayer: CommonEnum.PanelLayer): void {
        if (panel == null)
            return;

        // 获取对应的层级RootUI
        if (!this.mLayerRootMap.has(panelLayer)) {
            LogUtility.Error(`panelLayer(${panelLayer}) not exist`);

            return;
        }

        let uiWidget = this.mLayerRootMap.get(panelLayer);
        let slot = uiWidget.RootCanvas.AddChildToCanvas(panel.GetUIWidget());
        if (slot == null)
            return;

        // 获取当前层级下的最大ZOrder值
        let uiNameSet = this.mPanelLayerToPanelNameMap.get(panelLayer);
        let maxZOrder = -1;
        for (let uiName of uiNameSet) {
            let panel = this.mNameToPanelMap.get(uiName);
            let ZOrder = panel.GetZOrder();
            if (ZOrder > maxZOrder)
                maxZOrder = ZOrder;
        }

        slot.SetAnchors(new UE.Anchors(new UE.Vector2D(0, 0), new UE.Vector2D(1, 1)));
        slot.SetAlignment(new UE.Vector2D(0, 0));
        slot.SetOffsets(new UE.Margin(0, 0, 0, 0));
        slot.SetZOrder(maxZOrder + 1);

        // 放入层级映射
        this.mPanelLayerToPanelNameMap.get(panelLayer).add(panelName);
        panel.SetPanelLayer(panelLayer);
    }
}