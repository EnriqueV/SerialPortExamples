/**
 * Con este ejemplo, podemos manipular el texto mostrado en 
 * la matris rgb. Tambien nos servirá para contrlar la tira
 * de led rgb.
 */


var serialport = require("serialport");
var Repl = require("./repl");
var SerialPort = serialport.SerialPort
var serialport = new SerialPort("/dev/tty.usbmodem1451",{
  baudrate: 14400,
  parser: serialport.parsers.readline("\n")
});

this.repl = new Repl({sp: serialport});

function sendCommnad(){;
  console.log("Enviando comando >>> ", (process.argv[2] || "???"));
  serialport.write( new Buffer( process.argv[2] || "???") );
}

serialport.on('open', function(){
  console.log('Serial Port Opened');  
  
  setTimeout( function(){ sendCommnad(); }, 2000);
});