import {Injectable} from '@angular/core';
import {BLE} from '@ionic-native/ble/ngx';

@Injectable({
    providedIn: 'root'
})
export class BluetoothService {
    serviceID = 'FFE0';
    characteristicID = 'FFE1';

    serviceIDFull = '0000FFE0-0000-1000-8000-00805F9B34FB';
    characteristicIDFull = '0000FFE1-0000-1000-8000-00805F9B34FB';

    constructor(private ble: BLE) {
    }

    public scan() {
        return this.ble.scan([], 5);
    }

    public connect(deviceId) {
        return this.ble.connect(deviceId);
    }

    public send(deviceId, data) {
        console.log(JSON.stringify(data));
        return this.ble.write(deviceId, this.serviceID, this.characteristicID, this.stringToBytes(JSON.stringify(data)));
    }

    public subscribeToNotifications(deviceID) {
        return this.ble.startNotification(deviceID, this.serviceID, this.characteristicID);
    }

    // ASCII only
    public stringToBytes(value) {
        const valueArray = new Uint8Array(value.length);
        for (let i = 0, l = value.length; i < l; i++) {
            valueArray[i] = value.charCodeAt(i);
        }
        return valueArray.buffer;
    }

    // ASCII only
    public bytesToString(buffer) {
        return String.fromCharCode.apply(null, new Uint8Array(buffer));
    }

    uint8arrayToStringMethod(myUint8Arr) {
        return String.fromCharCode.apply(null, myUint8Arr);
    }
}
