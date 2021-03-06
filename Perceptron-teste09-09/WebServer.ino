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
    chamaPerceptron();
    return;
  }

  Serial.println("Nova conexao requisitada...");
  int loopBreak = 0;
  while(!client.available()){
    delay(1);
    loopBreak++;
    if(loopBreak > 50){
      Serial.println("Ops, Cliente não foi encontrado");
       return;
    }    
  }
  Serial.printf("O loopBreak eh %d",loopBreak);
  if(loopBreak > 50){
    Serial.println("Erro, nao era para estar aqui");
  }
  Serial.println("Nova conexao OK...");

  //Le a string enviada pelo cliente
  String req = client.readStringUntil('\r');
  //Mostra a string enviada
  Serial.println(req);
  //Limpa dados/buffer
  client.flush();

  //Trata a string do cliente em busca de comandos
  if (req.indexOf("rele_on") != -1){    
    alteracaoUsuario = ligaLampada();
  } else if (req.indexOf("rele_off") != -1) {    
    alteracaoUsuario = desligaLampada();
  }
  else {
    Serial.println("Requisicao invalida");
  }
  delay(50);
  //Prepara a resposta para o cliente
  String buf = "";
  buf += "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<!DOCTYPE HTML>\r\n";
  buf += "<html lang=\"en\"><head><meta name=\"viewport\" content=\" width=device-width, initial-scale=1, user-scalable=no\"/>\r\n";
  buf += "<title>CordlessHome</title>";
  buf += "<style>.c{text-align: center;} div,input{padding:5px;font-size:1em;} input{width:80%;} body{text-align: center;font-family:verdana;} button{border:0;border-radius:0.3rem;background-color:#1fa3ec;color:#fff;line-height:2.4rem;font-size:1.2rem;width:100%;} .q{float: right;width: 64px;text-align: right;}</style>";
  buf += "</head>";
  buf += "<h3>CordlessHome</h3>";

  //De acordo com o status da GPIO envia o comando
  if(digitalRead(statusLampada))
    buf += "<div><h4>Lampada</h4><a href=\"?function=rele_off\"><button>Desligar</button></a></div>";
  else
    buf += "<div><h4>Lampada</h4><a href=\"?function=rele_on\"><button>Ligar</button></a></div>";

  buf += "<h4>Controle Neural da ilumina&ccedil;&atilde;o</h4>";
  buf += "<p>hora = ";
  buf += hora;  
  buf += "</p><p>Wb = <input type=\"text\" name=\"Wb\" value=\" ";
  buf += Wb;
  buf += "\"></p><p>Wl = ";
  buf += Wl;
  buf += "</p><p>Wm = ";
  buf += Wm;
  buf += "</p><p>Luz Desejada = ";
  buf += valorLuzDesejada;
  buf += "</p><p>Luminosidade agora = ";
  buf += luminosidade;
  buf += "</p><p>Movimento = ";
  buf += movimento;
  buf += "</p><p>Desliga em = ";
  buf += tempoDesliga;
  buf += "</p>";
  buf += "<script type=\"text/javascript\"> $(document).ready(function(){";
  buf += "var timeoutId = 0;";
  buf += "$(\".sendValues\").click(function(){";
  buf += "clearTimeout(timeoutId);";
  buf += "timeoutId = setTimeout(function(){";
  buf += "$.get(\"http://192.168.5.200:80/?function=Wb="
  buf += "</script></html>\n";

  //Envia a resposta para o cliente
  client.print(buf);
  client.flush();
  client.stop();

  Serial.println("Cliente desconectado!");
}

