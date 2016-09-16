bool statusRele = false;
uint8_t tabelaLampERele = 0;

bool ligaLampada(){
  bool ligou = false;
  if(!digitalRead(statusLampada)){
    statusRele = !statusRele;
    digitalWrite(lampada, statusRele);
    alteraTabela();
    ligou = true;
  }
  return ligou;
}

bool desligaLampada(){
  bool desligou = false;
  if(digitalRead(statusLampada)){
    statusRele = !statusRele;
    digitalWrite(lampada,statusRele);
    alteraTabela();
    desligou = true;
  }
  return desligou;
}

bool verificaLampada(){// verifica toda tabela verdade
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
  return alteracaoUsuario;
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

