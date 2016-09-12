bool statusRele = false;
uint8_t tabelaLampERele = 0;

void ligaLampada(){
  Serial.println("liga lampada");
  if(!digitalRead(statusLampada)){
    Serial.println("liga mesmo");
    statusRele = !statusRele;
    digitalWrite(lampada, statusRele);
    alteraTabela();
  }
}

void desligaLampada(){
  Serial.println("desliga lampada");
  if(digitalRead(statusLampada)){
    Serial.println("desliga mesmo");
    statusRele = !statusRele;
    digitalWrite(lampada,statusRele);
    alteraTabela();
  }
}

void verificaLampada(){// verifica toda tabela verdade
  if(!statusRele && !digitalRead(statusLampada)){// quando os dois em zero
    if(tabelaLampERele != 0){//se não fechar corretamente eh realizado o perceptron de alteracao de usuario
      alteracaoUsuario = true;
      alteraTabela();
    }
  }else if(statusRele && !digitalRead(statusLampada)){//quando a lampada desligada e rele ligado
    if(tabelaLampERele != 1){
      alteracaoUsuario = true;
      alteraTabela();
    }
  }else if(!statusRele && digitalRead(statusLampada)){//quando a lampada ligada e rele desligado
    if(tabelaLampERele != 2){
      alteracaoUsuario = true;
      alteraTabela();
    }
  }else if(statusRele && digitalRead(statusLampada)){//quando os dois ligados
    if(tabelaLampERele != 3){
      alteracaoUsuario = true;
      alteraTabela();
    }
  }
}

void alteraTabela(){// tabela verdade da relação entre o rele e o status da lampada
  if(!statusRele && !digitalRead(statusLampada)){// quando os dois em zero
    tabelaLampERele = 0;
  }else if(statusRele && !digitalRead(statusLampada)){//quando a lampada desligada e rele ligado
    tabelaLampERele = 1;
  }else if(!statusRele && digitalRead(statusLampada)){//quando a lampada ligada e rele desligado
    tabelaLampERele = 2;
  }else if(statusRele && digitalRead(statusLampada)){//quando os dois ligados
    tabelaLampERele = 3;
  }
}

