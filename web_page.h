const char webpage[] PROGMEM = R"=====(

  <!DOCTYPE html>
  <html lang="en" class="js-focus-visible">
  <style>
    .btn0 {
        background-color: #444444;
        border: none;
        color: white;
        padding: 10px 20px;
        text-align: center;
        text-decoration: none;
        display: inline-block;
        font-size: 40px;
        margin: 4px 2px;
        cursor: pointer;
        width: 40%;
        left: 5%;
        user-select: none;
      }
      
    .btn1 {
        background-color: #444444;
        border: none;
        color: white;
        padding: 10px 20px;
        text-align: center;
        text-decoration: none;
        display: inline-block;
        font-size: 40px;
        margin: 4px 2px;
        cursor: pointer;
        width: 40%;
        right: 5%;
        user-select: none;
  
      }
      .progress {
    position: relative;
    width: 85%;
    height: 60px;
    background: #7cc3b5;
    border-radius: 5px;
    overflow: hidden;
  }
  
  .progress__fill {
    width: 0%;
    height: 100%;
    background: #025445;
    transition: all 0.2s;
  }
  
  .progress__text {
    position: absolute;
    top: 50%;
    right: 5px;
    transform: translateY(-50%);
    font: bold 14px "Quicksand", sans-serif;
    color: #ffffff;
  }
  
  </style>
  <body onload="process()">
    
  <div class="progress">
  <div class="progress__fill" id ="fill" ></div>
  <span class="progress__text" id="value">20</span>
    
    </div>
    <br>
    <div>
  <button type="button" class="btn0" id="left" onmousedown="start_stepper('left')" ontouchstart="start_stepper('left')" 
  onmouseup="start_stepper('stop')" ontouchend="start_stepper('stop')">fine</button>
  <button type="button" class="btn1" id="left" onmousedown="start_stepper('right')" ontouchstart="start_stepper('right')" 
  onmouseup="start_stepper('stop')" ontouchend="start_stepper('stop')">coarse</button>
  <br>
  <br>
  <buttom type="button" class="btn0" id="home" onclick="home()">home</buttom>
  <br>
  
  </div>
  </body>
  
    <script type = "text/javascript">
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
  function home(){
    var xhttp = new XMLHttpRequest();
    xhttp.open("PUT","home",false)
        xhttp.send(); 
  }
  
      
      function start_stepper(dir){
  
         var xhttp = new XMLHttpRequest(); 
         
        
       xhttp.open("PUT","/"+dir,false)
        xhttp.send();
      
       
        }
        
        
     function process(){
       
       if(xmlHttp.readyState==0 ||xmlHttp.readyState==4) {
          xmlHttp.open("PUT","json",true);
       
          xmlHttp.onreadystatechange=response;
          
          xmlHttp.send(null);
          
        }       
          // you may have to play with this value, big pages need more porcessing time, and hence
          // a longer timeout
          setTimeout("process()",200);
      }
  
      function response(){
        var jsonobj;
       
        
        jsonobj= JSON.parse (xmlHttp.responseText);
       document.querySelector(".progress__fill").style.width=`${jsonobj.position}%`;
       document.querySelector(".progress__text").textContent=`${jsonobj.position}`;
      
      
    }
      
    </script>
    </html>
  
)=====";
