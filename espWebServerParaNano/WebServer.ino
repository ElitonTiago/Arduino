//Inicializacao so servidor http na porta 80
WiFiServer server(80);

void iniciaServidor(){
  server.begin();
}

void conexaoServidor(){
   //Aguarda uma nova conexao
  WiFiClient client = server.available();
  if (!client) {
    novaHora();
    return;
  }

  int loopBreak = 0;
  while(!client.available()){
    delay(1);
    loopBreak++;
    if(loopBreak > 10){
      client.flush();
      client.stop();
       return;
    }    
  }

  //Le a string enviada pelo cliente
  String req = client.readStringUntil('\r');
  //Limpa dados/buffer
  client.flush();   
  //Trata a string do cliente em busca de comandos
  if (req.indexOf("rele_on") != -1){    
    SaveValues("ligou pela Web");    
  } else if (req.indexOf("rele_off") != -1) {    
    SaveValues("desligou pela Web");
  }
  else {
    Serial.println("Requisicao invalida");
    getValues();
  }  
  delay(20);
  //Prepara a resposta para o cliente
  String buf = "";
  buf += "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<!DOCTYPE HTML>\r\n";
  buf += "<html lang=\"en\"><head><meta name=\"viewport\" content=\" width=device-width, initial-scale=1, user-scalable=no\"/>\r\n";
  buf += "<title>CordlessHome</title>";
  buf += "<style>.c{text-align: center;} div,input{padding:5px;font-size:1em;} input{width:80%;} body{text-align: center;font-family:verdana;} button{border:0;border-radius:0.3rem;background-color:#1fa3ec;color:#fff;line-height:2.4rem;font-size:1.2rem;width:100%;} .q{float: right;width: 64px;text-align: right;}</style>";
  buf += "</head>";
  buf += "<h3>CordlessHome</h3>";

  //De acordo com o status da GPIO envia o comando
  if(statusLumi)
    buf += "<div><h4>Lampada</h4><a href=\"?function=rele_off\"><button>Desligar</button></a></div>";
  else
    buf += "<div><h4>Lampada</h4><a href=\"?function=rele_on\"><button>Ligar</button></a></div>";

  buf += "<h4>Controle Neural da ilumina&ccedil;&atilde;o</h4><h5>Agora s&atilde;o ";
  buf += hora; 
  buf += " horas</h5><h4> Os Valores de controle para esta hora s&atilde;o : ";  
  buf += "</h4><p>Wb = ";
  buf += Wb;
  buf += "</p><p>Wl = ";
  buf += Wl;
  buf += "</p><p>Wm = ";
  buf += Wm;
  buf += "</p><p>Luz Desejada = ";
  buf += valorLuzDesejada*100;
  buf += "&#37;</p><p>Tempo para desligar = ";
  buf += tempoDesliga;
  buf += " segundos</p><h4> Os valores dos sensores s&atilde;o :</h4><p> Agora ";
  if(!movimento){
    buf += "n&atilde;o ";
  }
  buf += "est&aacute; ocorrendo movimento</p><p> A luminosidade agora &eacute; ";
  buf += luminosidade*100;
  buf += "&#37;</p></html>\n";

  //Envia a resposta para o cliente
  client.print(buf);
  client.flush();
  client.stop();  
}
