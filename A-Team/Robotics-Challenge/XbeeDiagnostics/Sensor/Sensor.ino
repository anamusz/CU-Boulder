/* ////////////////////////////////





Summary




//////////////////////////////////*/



// filterSamples should  be an odd number, no smaller than 3 (<<# sensitive, #<< insensitive)
#define filterSamples  7          
#define filterSamples2  17

// holds past RSSI values for filtering
int sensSmoothArray [filterSamples]; 
int sensSmoothArray2 [filterSamples2];

// variables for sensor data
int rawData, smoothData;  
int rawData2, smoothData2;  




void setup() {
  Serial.begin(57600); 
}


void loop() {
    int sens = analogRead(0);
    int x = millis()%100;
    
   // Serial.println(x);
    Serial.println(sens);
    
    smoothData = digitalSmooth(sens, sensSmoothArray);
   // Serial.println(x);
    Serial.println(smoothData);
    
    smoothData2 = digitalSmooth2(sens, sensSmoothArray2);
    //Serial.println(x);
    Serial.println(smoothData2);

    delay(100);
}








/////////////////////////////////////////////////////
////////////////Local Functions//////////////////////
/////////////////////////////////////////////////////





//Digital filter used to smooth the input data. 

int digitalSmooth2(int rawIn, int *sensSmoothArray2){     // "int *sensSmoothArray" passes an array to the function - the asterisk indicates the array name is a pointer
  int j, k, temp, top, bottom;
  long total;
  static int i;
 // static int raw[filterSamples];
  static int sorted[filterSamples2];
  boolean done;

  i = (i + 1) % filterSamples2;    // increment counter and roll over if necc. -  % (modulo operator) rolls over variable
  sensSmoothArray2[i] = rawIn;                 // input new data into the oldest slot

  // Serial.print("raw = ");

  for (j=0; j<filterSamples2; j++){     // transfer data array into anther array for sorting and averaging
    sorted[j] = sensSmoothArray2[j];
  }

  done = 0;                // flag to know when we're done sorting              
  while(done != 1){        // simple swap sort, sorts numbers from lowest to highest
    done = 1;
    for (j = 0; j < (filterSamples2 - 1); j++){
      if (sorted[j] > sorted[j + 1]){     // numbers are out of order - swap
        temp = sorted[j + 1];
        sorted [j+1] =  sorted[j] ;
        sorted [j] = temp;
        done = 0;
      }
    }
  }

  // throw out top and bottom 15% of samples - limit to throw out at least one from top and bottom
  bottom = max(((filterSamples2 * 15)  / 100), 1); 
  top = min((((filterSamples2 * 85) / 100) + 1  ), (filterSamples2 - 1));   // the + 1 is to make up for asymmetry caused by integer rounding
  k = 0;
  total = 0;
  for ( j = bottom; j< top; j++){
    total += sorted[j];  // total remaining indices
    k++; 

  }
  return total / k;    // divide by number of samples
}


          
          
//Digital filter used to smooth the input data. 

int digitalSmooth(int rawIn, int *sensSmoothArray){     // "int *sensSmoothArray" passes an array to the function - the asterisk indicates the array name is a pointer
  int j, k, temp, top, bottom;
  long total;
  static int i;
 // static int raw[filterSamples];
  static int sorted[filterSamples];
  boolean done;

  i = (i + 1) % filterSamples;    // increment counter and roll over if necc. -  % (modulo operator) rolls over variable
  sensSmoothArray[i] = rawIn;                 // input new data into the oldest slot

  // Serial.print("raw = ");

  for (j=0; j<filterSamples; j++){     // transfer data array into anther array for sorting and averaging
    sorted[j] = sensSmoothArray[j];
  }

  done = 0;                // flag to know when we're done sorting              
  while(done != 1){        // simple swap sort, sorts numbers from lowest to highest
    done = 1;
    for (j = 0; j < (filterSamples - 1); j++){
      if (sorted[j] > sorted[j + 1]){     // numbers are out of order - swap
        temp = sorted[j + 1];
        sorted [j+1] =  sorted[j] ;
        sorted [j] = temp;
        done = 0;
      }
    }
  }

  // throw out top and bottom 15% of samples - limit to throw out at least one from top and bottom
  bottom = max(((filterSamples * 15)  / 100), 1); 
  top = min((((filterSamples * 85) / 100) + 1  ), (filterSamples - 1));   // the + 1 is to make up for asymmetry caused by integer rounding
  k = 0;
  total = 0;
  for ( j = bottom; j< top; j++){
    total += sorted[j];  // total remaining indices
    k++; 

  }
  return total / k;    // divide by number of samples
}


