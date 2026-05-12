/**
 * Configuration Class
 * 
 * This class serves to interpret the eeprom settings to define the configuration for this car
 */

class M5DialConfiguration {
  private:
    Configuration *configuration;
    Steering *steering;
    Joystick *joystick;
    
  public: 
    // Default constructor ... does nothing.  This allows us to delay setting the pins until we want to (via the init method).  
    M5DialConfiguration() {  
    }

    /*
     * init - initialize the dip switch pins
     */
    void init(Configuration *c, Joystick *j, Steering *s) {
      configuration = c;
      joystick = j;
      steering = s;
    }

    void m5DialConfigureCar() {
      configuration->sendConfigurationsToM5Dial();
      steering->setSteeringDeltaScaled(2);

      // Read the config value from the M5Dial
      // Check to see if the value has changed and if so, save it to EEPROM
      while (1) {
        M5DialCurrentConfiguration config = configuration->readCurrentM5DialConfiguration();

        if (config.success) {
          // If the M5Dial isn't in config mode, then just continue
          // This should never happen
          if (!config.configMode) {
            Serial.println("M5Dial not in config mode");
            delay(100);
            continue;
          }

          // Can't set Version which is the first register
          if (config.validRegister) {
            configuration->saveM5DialConfiguration(config);
          } else {
            Serial.println("Invalid register");
          }
        } else {
          Serial.println("Erroring reading M5Dial Configuration");
        }

        if (config.reg >= EEPROM_ACTUATOR_MIN && config.reg <= EEPROM_ACTUATOR_MAX) {
          int target;
          if (config.reg == EEPROM_ACTUATOR_MIN) {
            steering->setSteeringMinScaled(configuration->getSteeringMin());
            target = -100;
          } else if (config.reg == EEPROM_ACTUATOR_CENTER) {
            steering->setSteeringCenterScaled(configuration->getSteeringCenter());
            target = 0;
          } else if (config.reg == EEPROM_ACTUATOR_MAX) {
            steering->setSteeringMaxScaled(configuration->getSteeringMax());
            target = 100;
          }

          Serial.print("Set Linear Actuator Target: ");
          Serial.println(target);
          // give the linear actuator some time to move before we ask for the next configuration value
          for (int i = 0; i < 10; i++) {
            // The Joystick calls are needed for an obscure reason...
            joystick->getXAxisScaled();
            joystick->getYAxisScaled();
            steering->setSteeringPosition(target);
            delay(5);
          }
        } else {
          steering->forceStop();
          delay(50);
        }
      }
    }
};
