const char PAGE_MAIN[] PROGMEM = R"=====( 

<!DOCTYPE html>
<html lang="en" class="js-focus-visible">

<title>Web Page Update Demo</title>

  <style>
    table {
      position: relative;
      width:100%;
      border-spacing: 0px;
    }
    tr {
      border: 1px solid white;
      font-family: "Verdana", "Arial", sans-serif;
      font-size: 20px;
    }
    th {
      height: 20px;
      padding: 3px 15px;
      background-color: #343a40;
      color: #FFFFFF !important;
      }
    td {
      height: 20px;
       padding: 3px 15px;
    }
    .tabledata {
      font-size: 24px;
      position: relative;
      padding-left: 5px;
      padding-top: 5px;
      height:   25px;
      border-radius: 5px;
      color: #FFFFFF;
      line-height: 20px;
      transition: all 200ms ease-in-out;
      background-color: #176B87;
    }
    .fanrpmslider {
      width: 30%;
      height: 55px;
      outline: none;
      height: 25px;
    }
    .bodytext {
      font-family: "Verdana", "Arial", sans-serif;
      font-size: 24px;
      text-align: left;
      font-weight: light;
      border-radius: 5px;
      display:inline;
    }
    .navbar {
      width: 100%;
      height: 50px;
      margin: 0;
      padding: 10px 0px;
      background-color: #FFF;
      color: #000000;
      border-bottom: 5px solid #293578;
    }
    .fixed-top {
      position: fixed;
      top: 0;
      right: 0;
      left: 0;
      z-index: 1030;
    }
    .navtitle {
      float: left;
      height: 50px;
      font-family: "Verdana", "Arial", sans-serif;
      font-size: 50px;
      font-weight: bold;
      line-height: 50px;
      padding-left: 20px;
    }
   .navheading {
     position: fixed;
     left: 60%;
     height: 50px;
     font-family: "Verdana", "Arial", sans-serif;
     font-size: 20px;
     font-weight: bold;
     line-height: 20px;
     padding-right: 20px;
   }
   .navdata {
      justify-content: flex-end;
      position: fixed;
      left: 70%;
      height: 50px;
      font-family: "Verdana", "Arial", sans-serif;
      font-size: 20px;
      font-weight: bold;
      line-height: 20px;
      padding-right: 20px;
   }
    .category {
      font-family: "Verdana", "Arial", sans-serif;
      font-weight: bold;
      font-size: 32px;
      line-height: 50px;
      padding: 20px 10px 0px 10px;
      color: #000000;
    }
    .heading {
      font-family: "Verdana", "Arial", sans-serif;
      font-weight: normal;
      font-size: 28px;
      text-align: left;
    }

    .btn {
      background-color: #444444;
      border: none;
      color: white;
      padding: 10px 20px;
      text-align: center;
      text-decoration: none;
      display: inline-block;
      font-size: 16px;
      margin: 4px 2px;
      cursor: pointer;
    }
    .foot {
      font-family: "Verdana", "Arial", sans-serif;
      font-size: 20px;
      position: relative;
      height:   30px;
      text-align: center;   
      color: #AAAAAA;
      line-height: 20px;
    }
    .container {
      max-width: 1800px;
      margin: 0 auto;
    }
    table tr:first-child th:first-child {
      border-top-left-radius: 5px;
    }
    table tr:first-child th:last-child {
      border-top-right-radius: 5px;
    }
    table tr:last-child td:first-child {
      border-bottom-left-radius: 5px;
    }
    table tr:last-child td:last-child {
      border-bottom-right-radius: 5px;
    }

  </style>

  <body style="background-color: #efefef" onload="process()">

    <header>
      <div class="navbar fixed-top">
          <div class="container">
            <div class="navtitle">Street Light Monitor</div>
            <div class="navdata" id = "date">mm/dd/yyyy</div>
            <div class="navheading">DATE</div><br>
            <div class="navdata" id = "time">00:00:00</div>
            <div class="navheading">TIME</div>

          </div>
      </div>
    </header>

    <main class="container" style="margin-top:70px">
      <div class="category">LEDs STATUS</div>
      <div style="border-radius: 10px !important;">
      <table style="width:50%">
      <colgroup>
        <col span="1" style="background-color:rgb(230,230,230); width: 20%; color:#000000 ;">
        <col span="1" style="background-color:rgb(200,200,200); width: 15%; color:#000000 ;">
        <col span="1" style="background-color:rgb(180,180,180); width: 15%; color:#000000 ;">
      </colgroup>
      <col span="2"style="background-color:rgb(0,0,0); color:#FFFFFF">
      <col span="2"style="background-color:rgb(0,0,0); color:#FFFFFF">
      <col span="2"style="background-color:rgb(0,0,0); color:#FFFFFF">
      <tr>
        <th colspan="1"><div class="heading">Pin</div></th>
        <th colspan="1"><div class="heading">State</div></th> 
        <th colspan="1"><div class="heading">LDR Values</div></th>
      </tr>
      <tr>
        <td><div class="bodytext">LED1</div></td>  
        <td><div class="tabledata" id = "b0" style="background-color:#176B87;"></div></td>
        <td><div class="tabledata" id = "v0"></div></td>
      </tr>
      <tr>
        <td><div class="bodytext">LED2</div></td>  
        <td><div class="tabledata" id = "b1"></div></td>
        <td><div class="tabledata" id = "v1"></div></td>
      </tr>
      <tr>
        <td><div class="bodytext">LED3</div></td>  
        <td><div class="tabledata" id = "b2"></div></td>
        <td><div class="tabledata" id = "v2"></div></td>
      </tr>
      <tr>
        <td><div class="bodytext">LED4</div></td>  
        <td><div class="tabledata" id = "b3"></div></td>
        <td><div class="tabledata" id = "v3"></div></td>
      </tr>
      <tr>
        <td><div class="bodytext">LED5</div></td>  
        <td><div class="tabledata" id = "b4"></div></td>
        <td><div class="tabledata" id = "v4"></div></td>
      </tr>
      <tr>
        <td><div class="bodytext">LED6</div></td>  
        <td><div class="tabledata" id = "b5"></div></td>
        <td><div class="tabledata" id = "v5"></div></td>
      </tr>
      <tr>
        <td><div class="bodytext">LED7</div></td>  
        <td><div class="tabledata" id = "b6"></div></td>
        <td><div class="tabledata" id = "v6"></div></td>
      </tr>
      <tr>
        <td><div class="bodytext">LED8</div></td>  
        <td><div class="tabledata" id = "b7"></div></td>
        <td><div class="tabledata" id = "v7"></div></td>
      </tr>
      <!-- <tr>
        <td><div class="bodytext">Current Sensor</div></td> 
        <td><div class="tabledata" id = "b8"></div></td>
        <td><div class="tabledata" id = "v8"></div></td>
      </tr> -->
        <!-- <tr>
        <td><div class="bodytext">Digital switch</div></td>
        <td><div class="tabledata" id = "switch"></div></td>
      </tr> -->
      </table>

      <h2 class="category" style="text-align: left; margin-top: 0px; margin-bottom: 0px;">Current Monitoring</h2>
      <table style="width:100%; margin-bottom: 0px; margin-top: 0px; border-radius: 10px !important; ">
          <colgroup>
              <col span="1" style="background-color:rgb(230,230,230); width: 16%; color:#000000 ;">
              <col span="1" style="background-color:rgb(200,200,200); width: 23%; color:#000000 ;">
              <col span="1" style="background-color:rgb(180,180,180); width: 23%; color:#000000 ;">
              <col span="1" style="background-color:rgb(180,180,180); width: 23%; color:#000000 ;">
          </colgroup>
          <col span="2" style="background-color:rgb(0,0,0); color:#FFFFFF">
          <col span="2" style="background-color:rgb(0,0,0); color:#FFFFFF">
          <col span="2" style="background-color:rgb(0,0,0); color:#FFFFFF">
          <tr>
              <th colspan="1">
                  <div class="heading">Sensors </div>
              </th>
              <th colspan="1">
                  <div class="heading">Values in ampere</div>
              </th>
              <th colspan="1">
                  <div class="heading">Values in volt</div>
              </th>
          </tr>
          <tr>
              <td>
                  <div class="bodytext">Current Sensor</div>
              </td>
              <td>
                  <div class="tabledata" id="b8"></div>
              </td>
              <td>
                  <div class="tabledata" id="v8"></div>
              </td>
          </tr>
      </table>

    </div>
    <br>
    <!-- <div class="category">Sensor Controls</div>
    <br>
    <div class="bodytext">LED </div>
    <button type="button" class = "btn" id = "btn0" onclick="ButtonPress0()">Toggle</button>
    </div>
    <br>
    <div class="bodytext">Switch</div>
    <button type="button" class = "btn" id = "btn1" onclick="ButtonPress1()">Toggle</button>
    </div>
    <br>
    <br>
    <div class="bodytext">Fan Speed Control (RPM: <span id="fanrpm"></span>)</div>
    <br>
    <input type="range" class="fanrpmslider" min="0" max="255" value = "0" width = "0%" oninput="UpdateSlider(this.value)"/>
    <br>
    <br> -->
  </main>

  <footer div class="foot" id = "temp" >Project by Savvy Innovators</div></footer>

  </body>


  <script type = "text/javascript">

    // global variable visible to all java functions
    var xmlHttp=createXmlHttpObject();

    // function to create XML object
    function createXmlHttpObject(){
      if(window.XMLHttpRequest){
        xmlHttp=new XMLHttpRequest();
      }
      else{
        xmlHttp=new ActiveXObject("Microsoft.XMLHTTP");
      }
      return xmlHttp;
    }

    // function to handle button press from HTML code above
    // and send a processing string back to server
    // this processing string is use in the .on method
    function ButtonPress0() {
      var xhttp = new XMLHttpRequest(); 
      var message;
      // if you want to handle an immediate reply (like status from the ESP
      // handling of the button press use this code
      // since this button status from the ESP is in the main XML code
      // we don't need this
      // remember that if you want immediate processing feedbac you must send it
      // in the ESP handling function and here
      /*
      xhttp.onreadystatechange = function() {
        if (this.readyState == 4 && this.status == 200) {
          message = this.responseText;
          // update some HTML data
        }
      }
      */

      xhttp.open("PUT", "BUTTON_0", false);
      xhttp.send();
    }


    // function to handle button press from HTML code above
    // and send a processing string back to server
    // this processing string is use in the .on method
    function ButtonPress1() {
      var xhttp = new XMLHttpRequest(); 
      /*
      xhttp.onreadystatechange = function() {
        if (this.readyState == 4 && this.status == 200) {
          document.getElementById("button1").innerHTML = this.responseText;
        }
      }
      */
      xhttp.open("PUT", "BUTTON_1", false);
      xhttp.send(); 
    }

    function UpdateSlider(value) {
      var xhttp = new XMLHttpRequest();
      // this time i want immediate feedback to the fan speed
      // yea yea yea i realize i'm computing fan speed but the point
      // is how to give immediate feedback
      xhttp.onreadystatechange = function() {
        if (this.readyState == 4 && this.status == 200) {
          // update the web based on reply from  ESP
          document.getElementById("fanrpm").innerHTML=this.responseText;
        }
      }
      // this syntax is really weird the ? is a delimiter
      // first arg UPDATE_SLIDER is use in the .on method
      // server.on("/UPDATE_SLIDER", UpdateSlider);
      // then the second arg VALUE is use in the processing function
      // String t_state = server.arg("VALUE");
      // then + the controls value property
      xhttp.open("PUT", "UPDATE_SLIDER?VALUE="+value, true);
      xhttp.send();
    }

    // function to handle the response from the ESP
    function response(){
      var message;
      var barwidth;
      var currentsensor;
      var xmlResponse;
      var xmldoc;
      var dt = new Date();
      var color = "#e8e8e8";

      // get the xml stream
      xmlResponse=xmlHttp.responseXML;

      // get host date and time
      document.getElementById("time").innerHTML = dt.toLocaleTimeString();
      document.getElementById("date").innerHTML = dt.toLocaleDateString();

      // A0
      xmldoc = xmlResponse.getElementsByTagName("B0"); //bits for A0
      message = xmldoc[0].firstChild.nodeValue;

      barwidth = message / 40.95;
      document.getElementById("b0").innerHTML=message;
      color = "#176B87";
      document.getElementById("b0").style.width=(barwidth+"%");
      // if you want to use global color set above in <style> section
      // other wise uncomment and let the value dictate the color
      //document.getElementById("b0").style.backgroundColor=color;
      //document.getElementById("b0").style.borderRadius="5px";

      xmldoc = xmlResponse.getElementsByTagName("V0"); //volts for A0
      message = xmldoc[0].firstChild.nodeValue;
      document.getElementById("v0").innerHTML=message;
      barwidth = message * 0.0976;
      color = " # 1B6B93";


      document.getElementById("v0").style.width=(barwidth+"%");
      // you can set color dynamically, maybe blue below a value, red above
      document.getElementById("v0").style.backgroundColor=color;
      //document.getElementById("v0").style.borderRadius="5px";


      xmldoc = xmlResponse.getElementsByTagName("B1"); //bits for A0
      message = xmldoc[0].firstChild.nodeValue;
      color = "#176B87";
      barwidth = message / 40.95;
      document.getElementById("b1").innerHTML=message;
      document.getElementById("b1").style.width=(barwidth+"%");
      // if you want to use global color set above in <style> section
      // other wise uncomment and let the value dictate the color
      //document.getElementById("b1").style.backgroundColor=color;
      //document.getElementById("b1").style.borderRadius="5px";

      xmldoc = xmlResponse.getElementsByTagName("V1"); //volts for A0
      message = xmldoc[0].firstChild.nodeValue;
      document.getElementById("v1").innerHTML=message;
      barwidth = message * 0.0976;
      color = " # 1B6B93";


      document.getElementById("v1").style.width=(barwidth+"%");
      // you can set color dynamically, maybe blue below a value, red above
      document.getElementById("v1").style.backgroundColor=color;
      //document.getElementById("v1").style.borderRadius="5px";


      xmldoc = xmlResponse.getElementsByTagName("B2"); //bits for A0
      message = xmldoc[0].firstChild.nodeValue;

      color = "#176B87";

      barwidth = message / 40.95;
      document.getElementById("b2").innerHTML=message;
      document.getElementById("b2").style.width=(barwidth+"%");
      // if you want to use global color set above in <style> section
      // other wise uncomment and let the value dictate the color
      //document.getElementById("b2").style.backgroundColor=color;
      //document.getElementById("b2").style.borderRadius="5px";

      xmldoc = xmlResponse.getElementsByTagName("V2"); //volts for A0
      message = xmldoc[0].firstChild.nodeValue;
      document.getElementById("v2").innerHTML=message;
      barwidth = message * 0.0976;
      color = " # 1B6B93";

      document.getElementById("v2").style.width=(barwidth+"%");
      // you can set color dynamically, maybe blue below a value, red above
      document.getElementById("v2").style.backgroundColor=color;
      //document.getElementById("v2").style.borderRadius="5px";

      xmldoc = xmlResponse.getElementsByTagName("B3"); //bits for A0
      message = xmldoc[0].firstChild.nodeValue;

      color = "#176B87";

      barwidth = message / 40.95;
      document.getElementById("b3").innerHTML=message;
      document.getElementById("b3").style.width=(barwidth+"%");
      // if you want to use global color set above in <style> section
      // other wise uncomment and let the value dictate the color
      //document.getElementById("b3").style.backgroundColor=color;
      //document.getElementById("b3").style.borderRadius="5px";

      xmldoc = xmlResponse.getElementsByTagName("V3"); //volts for A0
      message = xmldoc[0].firstChild.nodeValue;
      document.getElementById("v3").innerHTML=message;
      barwidth = message * 0.0976;
      color = " # 1B6B93";

      document.getElementById("v3").style.width=(barwidth+"%");
      // you can set color dynamically, maybe blue below a value, red above
      document.getElementById("v3").style.backgroundColor=color;
      //document.getElementById("v3").style.borderRadius="5px";

      xmldoc = xmlResponse.getElementsByTagName("B4"); //bits for A0
      message = xmldoc[0].firstChild.nodeValue;

      color = "#176B87";

      barwidth = message / 40.95;
      document.getElementById("b4").innerHTML=message;
      document.getElementById("b4").style.width=(barwidth+"%");
      // if you want to use global color set above in <style> section
      // other wise uncomment and let the value dictate the colo3
      //document.getElementById("b4").style.backgroundColor=color;
      //document.getElementById("b4").style.borderRadius="5px";

      xmldoc = xmlResponse.getElementsByTagName("V4"); //volts for A0
      message = xmldoc[0].firstChild.nodeValue;
      document.getElementById("v4").innerHTML=message;
      barwidth = message * 0.0976;
      color = " # 1B6B93";

      document.getElementById("v4").style.width=(barwidth+"%");
      // you can set color dynamically, maybe blue below a value, red above
      document.getElementById("v4").style.backgroundColor=color;
      //document.getElementById("v4").style.borderRadius="5px";

      xmldoc = xmlResponse.getElementsByTagName("B5"); //bits for A0
      message = xmldoc[0].firstChild.nodeValue;

      color = "#176B87";

      barwidth = message / 40.95;
      document.getElementById("b5").innerHTML=message;
      document.getElementById("b5").style.width=(barwidth+"%");
      // if you want to use global color set above in <style> section
      // other wise uncomment and let the value dictate the color
      // document.getElementById("b5").style.backgroundColor=color;
      //document.getElementById("b5").style.borderRadius="5px";

      xmldoc = xmlResponse.getElementsByTagName("V5"); //volts for A0
      message = xmldoc[0].firstChild.nodeValue;
      document.getElementById("v5").innerHTML=message;
      barwidth = message * 0.0976;
      color = " # 1B6B93";

      document.getElementById("v5").style.width=(barwidth+"%");
      // you can set color dynamically, maybe blue below a value, red above
      document.getElementById("v5").style.backgroundColor=color;
      //document.getElementById("v0").style.borderRadius="5px";

      xmldoc = xmlResponse.getElementsByTagName("B6"); //bits for A0
      message = xmldoc[0].firstChild.nodeValue;

      color = "#176B87";

      barwidth = message / 40.95;
      document.getElementById("b6").innerHTML=message;
      document.getElementById("b6").style.width=(barwidth+"%");
      // if you want to use global color set above in <style> section
      // other wise uncomment and let the value dictate the color
      //document.getElementById("b6").style.backgroundColor=color;
      //document.getElementById("b6").style.borderRadius="5px";

      xmldoc = xmlResponse.getElementsByTagName("V6"); //volts for A0
      message = xmldoc[0].firstChild.nodeValue;
      document.getElementById("v6").innerHTML=message;
      barwidth = message * 0.0976;
      color = " # 1B6B93";

      document.getElementById("v6").style.width=(barwidth+"%");
      // you can set color dynamically, maybe blue below a value, red above
      document.getElementById("v6").style.backgroundColor=color;
      //document.getElementById("v6").style.borderRadius="5px";

      xmldoc = xmlResponse.getElementsByTagName("B7"); //bits for A0
      message = xmldoc[0].firstChild.nodeValue;

      color = "#176B87";

      barwidth = message / 40.95;
      document.getElementById("b7").innerHTML=message;
      document.getElementById("b7").style.width=(barwidth+"%");
      // if you want to use global color set above in <style> section
      // other wise uncomment and let the value dictate the color
      //document.getElementById("b7").style.backgroundColor=color;
      //document.getElementById("b7").style.borderRadius="5px";

      xmldoc = xmlResponse.getElementsByTagName("V7"); //volts for A0
      message = xmldoc[0].firstChild.nodeValue;
      document.getElementById("v7").innerHTML=message;
      barwidth = message * 0.0976;
      color = " # 1B6B93";

      document.getElementById("v7").style.width=(barwidth+"%");
      // you can set color dynamically, maybe blue below a value, red above
      document.getElementById("v7").style.backgroundColor=color;
      //document.getElementById("v7").style.borderRadius="5px";

      // A1
      xmldoc = xmlResponse.getElementsByTagName("B8");
      message = xmldoc[0].firstChild.nodeValue;
      color = "#04364A";
      document.getElementById("b8").innerHTML=message;
      width = message * 2;
      document.getElementById("b8").style.width=(width+"%");
      document.getElementById("b8").style.backgroundColor=color;
      //document.getElementById("b8").style.borderRadius="5px";

      xmldoc = xmlResponse.getElementsByTagName("V8");
      message = xmldoc[0].firstChild.nodeValue;
      width = message * 10;
      document.getElementById("v8").innerHTML=message;
      document.getElementById("v8").style.width=(width+"%");
      document.getElementById("v8").style.backgroundColor=color;
      //document.getElementById("v8").style.borderRadius="5px";

    //   xmldoc = xmlResponse.getElementsByTagName("LED");
    //   message = xmldoc[0].firstChild.nodeValue;

    //   if (message == 0){
    //     document.getElementById("btn0").innerHTML="Turn ON";
    //   }
    //   else{
    //     document.getElementById("btn0").innerHTML="Turn OFF";
    //   }

    //   xmldoc = xmlResponse.getElementsByTagName("SWITCH");
    //   message = xmldoc[0].firstChild.nodeValue;
    //   document.getElementById("switch").style.backgroundColor="rgb(200,200,200)";
    //   // update the text in the table
    //   if (message == 0){
    //     document.getElementById("switch").innerHTML="Switch is OFF";
    //     document.getElementById("btn1").innerHTML="Turn ON";
    //     document.getElementById("switch").style.color="#0000AA"; 
    //   }
    //   else {
    //     document.getElementById("switch").innerHTML="Switch is ON";
    //     document.getElementById("btn1").innerHTML="Turn OFF";
    //     document.getElementById("switch").style.color="#00AA00";
    //   }
     }

    // general processing code for the web page to ask for an XML steam
    // this is actually why you need to keep sending data to the page to 
    // force this call with stuff like this
    // server.on("/xml", SendXML);
    // otherwise the page will not request XML from the ESP, and updates will not happen
    function process(){

     if(xmlHttp.readyState==0 || xmlHttp.readyState==4) {
        xmlHttp.open("PUT","xml",true);
        xmlHttp.onreadystatechange=response;
        xmlHttp.send(null);
      }       
        // you may have to play with this value, big pages need more porcessing time, and hence
        // a longer timeout
        setTimeout("process()",100);
    }


  </script>

</html>



)=====";