/**
 * DIPSwitches Class
 * 
 * This class serves to be the interface to the DIP switches on the controller board.  
 */

class DIPSwitches {
  private:

    int dipPin1;
    int dipPin2;
    int dipPin3;
    int dipPin4;
    int dipPin5;
    int dipPin6;
    


  public: 
    // Default constructor ... does nothing.  This allows us to delay setting the pins until we want to (via the init method).  
    DIPSwitches() {  
    }

    /*
     * init - initialize the dip switch pins
     */
    void init(int d1, int d2, int d3, int d4, int d5, int d6) {
      dipPin1 = d1;
      dipPin2 = d2;
      dipPin3 = d3;
      dipPin4 = d4;
      dipPin5 = d5;
      dipPin6 = d6;
      pinMode(dipPin1,INPUT_PULLUP);
      pinMode(dipPin2,INPUT_PULLUP);
      pinMode(dipPin3,INPUT_PULLUP);
      pinMode(dipPin4,INPUT_PULLUP);
      pinMode(dipPin5,INPUT_PULLUP);
      pinMode(dipPin6,INPUT_PULLUP);
    }

    /*
     * getters ... just doing digital reads
     */
    boolean getPin1() {return digitalRead(dipPin1);}
    boolean getPin2() {return digitalRead(dipPin2);}
    boolean getPin3() {return digitalRead(dipPin3);}
    boolean getPin4() {return digitalRead(dipPin4);}
    boolean getPin5() {return digitalRead(dipPin5);}
    boolean getPin6() {return digitalRead(dipPin6);}
  
    String getStatus() {
      String ret = String("[DIPs] ");
      ret.concat(String("1:"));ret.concat(getPin1());
      ret.concat(String(" 2:"));ret.concat(getPin2());
      ret.concat(String(" 3:"));ret.concat(getPin3());
      ret.concat(String(" 4:"));ret.concat(getPin4());
      ret.concat(String(" 5:"));ret.concat(getPin5());
      ret.concat(String(" 6:"));ret.concat(getPin6());

      return ret;
    }

  
};
