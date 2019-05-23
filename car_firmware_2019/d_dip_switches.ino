/**
 * DIPSwitches Class
 * 
 * This class serves to be the interface to the DIP switches on the controller board.  
 */

class DIPSwitches {
  private:



  public: 
    // Default constructor ... does nothing.  This allows us to delay setting the pins until we want to (via the init method).  
    DIPSwitches() {  
    }

    /*
     * init - initialize the dip switches
     * 
     * TODO ... get the dip switch pins.  Also, make the dips do something!!!
     */
    void init() {
    }

  
    String getStatus() {
      String ret = String("[DIPs] Not supported yet!");
      return ret;
    }

  
};
