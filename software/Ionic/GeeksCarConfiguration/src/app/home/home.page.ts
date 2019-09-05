import { Component, NgZone } from '@angular/core';
import {BluetoothService} from '../services/bluetooth.service';
import {Router} from '@angular/router';

@Component({
  selector: 'app-home',
  templateUrl: 'home.page.html',
  styleUrls: ['home.page.scss'],
})
export class HomePage {
  devices: any[] = [];

  constructor(private bluetoothService: BluetoothService,
              private ngZone: NgZone,
              private router: Router) {
  }

  startScan() {
    this.devices = [];

    console.log('Geeks for Kids: Start Scan');
    this.bluetoothService.scan().subscribe(
        device => this.onDeviceDiscovered(device),
        error => this.scanError(error)
    );
  }

  onDeviceDiscovered(device) {
    console.log('Geeks for Kids: onDeviceDiscovered');
    if (device.name) {
      console.log('Geeks for Kids: Device added: ' + device.name + ' ' + device.id);
      this.ngZone.run(() => {
        this.devices.push(device);
      });
    } else {
      console.log('Geeks for Kids: Device ignore - no name: ' + device.id);
    }
  }

  scanError(error) {
    console.log('Geeks for Kids: Scan Error');
    console.log(error);
  }

  connect(device) {
    console.log('Geeks for Kids: Connect to: ' + device.name + ' ' + device.id);
    this.bluetoothService.connect(device.id).subscribe(
        success => {
          console.log('Geeks for Kids: Connected!');
          console.log('Geeks for Kids: before navigation');
          this.router.navigate(['/detail', { id: device.id }]);
          console.log('Geeks for Kids: after navigate');
        },
        error => {
          console.log('Geeks for Kids: Connect Error');
        }
    );
  }
}
