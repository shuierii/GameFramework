/*
 * @Author: linb
 * @Date: 2024-11-25 18:35:15
 * @Description:
 * @Copyright: Copyright HuanMos. All Rights Reserved.
 */
import { E_INode } from "./E_INode";

export interface E_IOutput extends E_INode {
    GetField(): string;

    /**
     * @description: 执行
     * @return {*}
     */
    Execute(): boolean;
}