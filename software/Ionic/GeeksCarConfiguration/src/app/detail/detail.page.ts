import {Component, NgZone, OnInit} from '@angular/core';
import {ActivatedRoute} from '@angular/router';
import {BluetoothService} from '../services/bluetooth.service';
import {CarConfiguration} from '../model/car-configuration';
import {AlertController, ToastController} from '@ionic/angular';

@Component({
    selector: 'app-detail',
    templateUrl: './detail.page.html',
    styleUrls: ['./detail.page.scss'],
})
export class DetailPage implements OnInit {
    private id;
    private isConnected = false;
    private response;
    private isReceivingResponse = false;
    private configuration: CarConfiguration;

    constructor(private route: ActivatedRoute,
                private bluetoothService: BluetoothService,
                private alertCtrl: AlertController,
                private toastController: ToastController,
                private ngZone: NgZone) {
    }

    ngOnInit() {
        this.id = this.route.snapshot.paramMap.get('id');
        this.connect(this.id);
    }

    connect(id) {
        console.log('Geeks for Kids: Connect to: ' + id);
        this.bluetoothService.connect(id).subscribe(
            success => {
                console.log('Geeks for Kids: Connected!');
                this.ngZone.run(() => {
                    this.isConnected = true;
                });
            },
            error => {
                console.log('Geeks for Kids: Connect Error');
            }
        );
    }

    getConfiguration() {
        const command = {
            Command: 'Get'
        };
        this.bluetoothService.send(this.id, command);
    }

    resetConfiguration() {
        const command = {
            Command: 'Reset'
        };
        this.bluetoothService.send(this.id, command);
    }

    subscribe() {
        this.bluetoothService.subscribeToNotifications(this.id).subscribe(
            data => {
                console.log('Geeks for Kids: Notification Data Received');
                console.log(this.bluetoothService.bytesToString(data));
                this.processResponse(this.bluetoothService.bytesToString(data));
            },
            error => {
                console.log('Geeks for Kids: Notification Error');
                console.log(error);
            });
    }

    processResponse(response: string) {
        if (this.isReceivingResponse) {
            console.log('Partial data received');
            this.response += response;
        } else if (response.startsWith('{')) {
            console.log('Beginning of Json Response');
            this.isReceivingResponse = true;
            this.response = response;
        } else {
            // invalid data received, a response must begin with a {
            console.log('Invalid response data received: ' + response);
            return;
        }

        if (this.response.indexOf('}') > 0) {
            // we found the end of the response
            this.isReceivingResponse = false;
            const jsonResponse = JSON.parse(this.response);
            console.log('Complete repsonse found');
            console.log(jsonResponse);
            this.ngZone.run(() => {
                this.processCompletedResponse(jsonResponse);
            });
        }
    }

    processCompletedResponse(completedResponse) {
        if (completedResponse.Succss !== undefined) {
            if (completedResponse.Succss) {
                this.presentToast('Success');
            } else {
                this.presentToast('Request Failed');
            }
        } else if (completedResponse.version !== undefined) {
            this.configuration = completedResponse;
        }
    }

    onSubmit() {
        console.log(this.configuration);
        console.log('Saving Configuration');
        const dataPart1 = {
            Command: 'Set',
            maxSpeed: this.configuration.maxSpeed,
            actuatorCenter: this.configuration.actuatorCenter,
            actuatorMin: this.configuration.actuatorMin,
            actuatorMax: this.configuration.actuatorMax
        };

        const dataPart2 = {
            Command: 'Set',
            useJoystick: this.configuration.useJoystick,
            invertJoystickX: this.configuration.invertJoystickX,
            invertJoystickY: this.configuration.invertJoystickY
        };

        const dataPart3 = {
            Command: 'Set',
            useRc: this.configuration.useRc,
            usePotGo: this.configuration.usePotGo
        };

        const dataPart4 = {
            Command: 'Set',
            steeringPotCenter: this.configuration.steeringPotCenter,
            steeringPotMin: this.configuration.steeringPotMin,
            steeringPotMax: this.configuration.steeringPotMax
        };

        this.bluetoothService.send(this.id, dataPart1).then(
            success => {
                this.bluetoothService.send(this.id, dataPart2).then(
                    success2 => {
                        this.bluetoothService.send(this.id, dataPart3).then(
                            success3 => {
                                this.bluetoothService.send(this.id, dataPart4).then(
                                    success4 => {
                                        this.presentToast('Configuration Saved');
                                    },
                                    error4 => {
                                        this.presentToast('Save Failure 4');
                                    }
                                );
                            },
                            error3 => {
                                this.presentToast('Save Failure 3');
                            }
                        );
                    },
                    error2 => {
                        this.presentToast('Save Failure 2');
                    }
                );
            },
            error => {
                this.presentToast('Save Failure');
            }
        );
    }

    async presentToast(toastMessage) {
        const toast = await this.toastController.create({
            message: toastMessage,
            duration: 3000
        });
        toast.present();
    }
}
