import { IRecycable } from "../Interface/IRecycable";
import { LogUtility } from "../Utility/LogUtility";

/*
 * @Author: linb
 * @Date: 2024-04-15 15:58:38
 * @Description:
 * @Copyright: Copyright HuanMos. All Rights Reserved.
 */
export class ObjectPool {

    // <对象类型，对象class>
    private mObjMap: Map<string, Set<IRecycable>> = new Map();

    /**
     * @description: 创建对象
     * @param {string} objType
     * @param {new} objClass
     * @return {*}
     */
    Spawn<TObject extends IRecycable>(objType: string, objClass: new (...args: any[]) => IRecycable): TObject {
        // 有缓存对象可用
        if (this.mObjMap.has(objType) && this.mObjMap.get(objType).size > 0) {
            let obj = [...this.mObjMap.get(objType)][0];

            // 移除对象
            this.mObjMap.get(objType).delete(obj);

            obj.Reset();

            return obj as TObject;
        }

        // 没有对象，创建新对象
        let obj = new objClass();

        return obj as TObject;
    }

    /**
     * @description: 回收对象
     * @param {string} objType
     * @param {IRecycable} recycleObj
     * @return {*}
     */
    Recycle(objType: string, recycleObj: IRecycable): boolean {
        // 1.池子里没有这个类型，新建类型放入要回收的对象
        if (!this.mObjMap.has(objType)) {
            recycleObj.Reset();

            let set: Set<IRecycable> = new Set();
            set.add(recycleObj);

            this.mObjMap.set(objType, set);

            return true;
        }

        // 2.池子里有这个对象
        if (this.mObjMap.get(objType).has(recycleObj)) {
            return false;
        }

        // 3.池子里没有这个对象，加入池子
        recycleObj.Reset();

        let objSet = this.mObjMap.get(objType);
        if (objSet.size >= 100000) {
            LogUtility.Warn(`the objType(${objType}) pool num(${objSet.size}) very large.`)
        }

        objSet.add(recycleObj);

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