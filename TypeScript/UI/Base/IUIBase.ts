/*
 * @Author: linb
 * @Date: 2025-01-09 15:19:14
 * @Description:
 * @Copyright: Copyright HuanMos. All Rights Reserved.
 */
import * as UE from "ue";

export interface IUIBase {
    /**
     * @description: 初始化
     * @return {*}
     */
    Init(): void;

    /**
     * @description: 启用
     * @return {*}
     */
    Enable(): void;

    /**
     * @description: 禁用
     * @return {*}
     */
    Disable(): void;

    /**
     * @description: 销毁
     * @return {*}
     */
    Destroy(): void;

    /**
     * @description: 获取控件
     * @return {*}
     */
    GetUIWidget(): UE.UserWidget;

    /**
     * @description: 设置可见性
     * @param {UE} inVisibility
     * @return {*}
     */
    SetVisibility(inVisibility: UE.ESlateVisibility): void;

    /**
     * @description: 获取窗口别名
     * @return {*}
     */
    GetCookieName(): string;

    /**
     * @description: 设置窗口别名
     * @param {string} cookieName
     * @return {*}
     */
    SetCookieName(cookieName: string): void;
}