bool statusRele = false;
uint8_t tabelaLampERele = 0;
int lampada = 7;

void beginLumiControl(){
  pinMode(2,INPUT);
  pinMode(lampada, OUTPUT);
  digitalWrite(lampada, 0); 
  delay(70);
  alteraTabela();
}

bool leLampada(){
  return digitalRead(2);
}

bool ligaLampada(){
  bool ligou = false;
  if(!leLampada()){
    statusRele = !statusRele;
    digitalWrite(lampada, statusRele);
    delay(70);
    alteraTabela();
    ligou = true;
  }
  return ligou;
}

bool desligaLampada(){
  bool desligou = false;
  if(leLampada()){
    statusRele = !statusRele;
    digitalWrite(lampada,statusRele);
    delay(70);
    alteraTabela();
    desligou = true;
  }
  return desligou;
}

bool verificaLampada(){// verifica toda tabela verdade
  alteracaoUsuario = false;
  if(!statusRele && !leLampada()){// quando os dois em zero
    if(tabelaLampERele != 0){//se não fechar corretamente eh realizado o perceptron de alteracao de usuario
      Serial.println(1);
      alteracaoUsuario = true;
      alteraTabela();
    }
  }else if(statusRele && !leLampada()){//quando a lampada desligada e rele ligado
    if(tabelaLampERele != 1){
      Serial.println(2);
      alteracaoUsuario = true;
      alteraTabela();
    }
  }else if(!statusRele && leLampada()){//quando a lampada ligada e rele desligado
    if(tabelaLampERele != 2){
      Serial.println(3);
      alteracaoUsuario = true;
      alteraTabela();
    }
  }else if(statusRele && leLampada()){//quando os dois ligados
    if(tabelaLampERele != 3){
      Serial.println(4);
      alteracaoUsuario = true;
      alteraTabela();
    }
  }
  return alteracaoUsuario;
}

void alteraTabela(){// tabela verdade da relação entre o rele e o status da lampada
  if(!statusRele && !leLampada()){// quando os dois em zero
    tabelaLampERele = 0;
  }else if(statusRele && !leLampada()){//quando a lampada desligada e rele ligado
    tabelaLampERele = 1;
  }else if(!statusRele && leLampada()){//quando a lampada ligada e rele desligado
    tabelaLampERele = 2;
  }else if(statusRele && leLampada()){//quando os dois ligados
    tabelaLampERele = 3;
  }
}

