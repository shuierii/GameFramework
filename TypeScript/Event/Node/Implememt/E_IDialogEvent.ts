/*
 * @Author: linb
 * @Date: 2024-11-26 16:13:35
 * @Description:
 * @Copyright: Copyright HuanMos. All Rights Reserved.
 */

import { E_IRoot } from "./E_IRoot";
import { E_IScript } from "./E_IScript";

export interface E_IDialogEvent extends E_IRoot {
    /**
     * @description: 设置剧情脚本列表
     * @param {Array} triggerList
     * @return {*}
     */
    SetScriptList(scriptList: Array<E_IScript>): void;
}