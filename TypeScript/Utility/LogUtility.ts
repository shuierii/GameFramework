
export class LogUtility {
    static Log(...data: any[]): void {
        console.log(data);
    }

    static Warn(...data: any[]): void {
        console.warn(data);
    }

    static Error(...data: any[]): void {
        console.error(data);
    }
}