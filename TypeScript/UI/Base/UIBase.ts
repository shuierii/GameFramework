/*
 * @Author: linb
 * @Date: 2025-01-09 15:18:40
 * @Description:
 * @Copyright: Copyright HuanMos. All Rights Reserved.
 */
import * as UE from "ue";
import { ElementBase } from "../../Abstract/ElementBase";
import { SystemID } from "../../Const/SystemID";
import { IUISystem } from "../../System/UI/IUISystem";
import { GameUtility } from "../../Utility/GameUtility";
import { LogUtility } from "../../Utility/LogUtility";
import { IUIBase } from "./IUIBase";

export abstract class UIBase extends ElementBase implements IUIBase {
    // 子节点列表
    private mChildUIList: Array<IUIBase> = [];
    private mCookieName: string = "";

    protected mUIWidget: UE.UserWidget;

    protected abstract OnInit(): void;
    protected abstract OnEnable(): void;
    protected abstract OnDisable(): void;
    protected abstract OnDestroy(): void;

    constructor() {
        super();

        this.mCookieName = GameUtility.CreateCookie("UIBase");
    }

    //#region ------------------UI生命周期函数Start--------------------

    /**
     * @description: 初始化
     * @return {*}
     */
    Init(): void {
        this.OnInit();
    }

    /**
     * @description: 启用
     * @return {*}
     */
    Enable(): void {
        this.OnEnable();

        for (let childUI of this.mChildUIList) {
            if (childUI == null)
                continue;

            childUI.Enable();
        }
    }

    /**
     * @description: 禁用
     * @return {*}
     */
    Disable(): void {
        for (let childUI of this.mChildUIList) {
            if (childUI == null)
                continue;

            childUI.Disable();
        }

        this.OnDisable();
    }

    /**
     * @description: 销毁
     * @return {*}
     */
    Destroy(): void {
        for (let childUI of this.mChildUIList) {
            if (childUI == null)
                continue;

            childUI.Destroy();
        }

        this.mChildUIList = [];

        this.OnDestroy();
    }

    //#endregion ------------------UI生命周期函数End--------------------

    /**
     * @description: 初始化UIWidget
     * @param {string} widgetName
     * @return {*}
     */
    InitWidget(widgetName: string): void {
        let UISys = this.GetSystem<IUISystem>(SystemID.UI_SYSTEM);

        this.mUIWidget = UISys.CreateUIWidget(widgetName);
        if (this.mUIWidget == null) {
            LogUtility.Error(`the widget(${widgetName}) create widget failed`);

            return;
        }
    }

    /**
     * @description: 获取控件
     * @return {*}
     */
    GetUIWidget(): UE.UserWidget {
        return this.mUIWidget;
    }

    /**
     * @description: 添加子节点
     * @param {TUIBase} UI
     * @return {*}
     */
    AddChildUI<TUIBase extends IUIBase>(UI: TUIBase): TUIBase {
        this.mChildUIList.push(UI);

        UI.Init();
        UI.Enable();

        return UI as TUIBase;
    }

    /**
     * @description: 移除子节点
     * @param {IUIBase} UI
     * @return {*}
     */
    RemoveChildUI(UI: IUIBase): void {
        if (!this.mChildUIList.includes(UI))
            return;

        this.mChildUIList.splice(this.mChildUIList.indexOf(UI), 1);

        UI.Disable();
        UI.Destroy();
    }

    /**
     * @description: 设置可见性
     * @param {UE} inVisibility
     * @return {*}
     */
    SetVisibility(inVisibility: UE.ESlateVisibility): void {
        if (this.mUIWidget == null)
            return;

        this.mUIWidget.SetVisibility(inVisibility);
    }

    /**
     * @description: 获取窗口别名
     * @return {*}
     */
    GetCookieName(): string {
        return this.mCookieName;
    }

    /**
     * @description: 设置窗口别名
     * @param {string} cookieName
     * @return {*}
     */
    SetCookieName(cookieName: string): void {
        this.mCookieName = cookieName;
    }
}