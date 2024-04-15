import { IRecycable } from "../Interface/IRecycable";

/*
 * @Author: linb
 * @Date: 2024-04-15 15:58:38
 * @Description:
 * @Copyright: Copyright HuanMos. All Rights Reserved.
 */
export class ObjectPool {

    // <对象类型，对象class>
    private mObjMap: Map<string, IRecycable> = new Map();

    /**
     * @description: 创建对象
     * @param {string} objType
     * @param {new} objClass
     * @return {*}
     */
    Spawn<TObject extends IRecycable>(objType: string, objClass: new (...args: any[]) => IRecycable): TObject {
        // 有缓存对象可用
        if (this.mObjMap.has(objType)) {
            let obj = this.mObjMap.get(objType);

            obj.Reset();

            return obj as TObject;
        }

        // 创建新对象
        let obj = new objClass();

        return obj as TObject;
    }

    /**
     * @description: 回收
     * @param {string} objType
     * @return {*}
     */
    Recycle(objType: string): boolean {
        if (!this.mObjMap.has(objType)) {
            return false;
        }

        let obj = this.mObjMap.get(objType);

        // 重置对象
        obj.Reset();

        return true;
    }

    /**
     * @description: 清理
     * @return {*}
     */
    Clear(): void {
        this.mObjMap.clear();
    }
}