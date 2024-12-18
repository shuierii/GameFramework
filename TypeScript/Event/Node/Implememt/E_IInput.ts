/*
 * @Author: linb
 * @Date: 2024-11-25 18:34:37
 * @Description:
 * @Copyright: Copyright HuanMos. All Rights Reserved.
 */
import { E_INode } from "./E_INode";

export interface E_IInput extends E_INode {

    GetField(): string;

    /**
     * @description: 执行
     * @return {*}
     */
    Execute(): any;
}