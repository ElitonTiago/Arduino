//variaveis perceptron
bool bias = 1;
float aprendizagem = 0.01;
bool p1 = false; //valor do perceptron para ligar a lampada
int contDesliga = 0; 
unsigned long millisPerceptron = 0;


void chamaPerceptron(){
  unsigned long millisAtual = (millis()) - millisPerceptron;
  if(millisAtual < 0) millisPerceptron = 0;
  if(millisAtual >= tempoPerceptron && !alteracaoUsuario){
    if(verificaLampada) return; //ter certeza que nao foi alterado o estado da lampada antes do perceptron
    millisPerceptron = millis();
    tempoPerceptron = 5000;//sempre que executado o perceptron volta a executar a cada 5 segundos
    luminosidade = getLuminosidade();
    movimento = getMovimento();
    Serial.print("Perceptron Movimento : ");
    Serial.println(movimento);
    Serial.print("Perceptron Luminosidade : ");
    Serial.println(luminosidade);
    p1 = perceptron(luminosidade, movimento);
    int saida = verificaErro(p1, luminosidade, movimento);
    if(saida != -1){
      if(saida == 1){
        contDesliga = 0; //Sempre que a saida for ligar zera o contador
        ligaLampada();
      }else{
        if(contDesliga <= (2*tempoDesliga)){
          contDesliga++;// somente quando contador chegar ao valor do tempo eh que a saida ira desligar
        }
        if(contDesliga >= tempoDesliga){          
          desligaLampada();
        }
      }
    }
  }
  if(alteracaoUsuario){//caso o usuario altere antes do perceptron eh realizado verificacao e correcao dos valores
    alteracaoUsuario = false;
    tempoPerceptron = 300000;//após interração pelo usuário o perceptron fica 5 minutos sem executar
    millisPerceptron = millis();
    luminosidade = getLuminosidade();
    movimento = getMovimento();
    Serial.print("Usuario Movimento : ");
    Serial.println(movimento);
    Serial.print("Usuario Luminosidade : ");
    Serial.println(luminosidade);
    p1 = perceptron(luminosidade, digitalRead(statusLampada));
    //verifica se a lampada possui o mesmo status do perceptron se nao deve ser corrigido o erro
    if(p1 != digitalRead(statusLampada)){
      Serial.println("a Lampada tem um estado diferente do perceptron ");
      int erroLuz = ((int) p1) - ((int) digitalRead(statusLampada));
      perceptronLuzDesejada(luminosidade,erroLuz);
      GravaNovosValores();      
    }
    if(!digitalRead(statusLampada)){//se o usuario desligou a lampada
      Serial.println("o usuario desligou a lampada");
      if(contDesliga < tempoDesliga && tempoDesliga > 5){//considera que deveria ter desligado e diminui o tempoDesliga
        Serial.println("Diminui tempo desliga");
        int corTempo = tempoDesliga - contDesliga;//quanto mais rapido o usuario desligar mais vai influenciar no novo numero
        tempoDesliga = tempoDesliga + (-1*(aprendizagem*100)*corTempo)/100;
        GravaNovosValores();
      }
    }else{// se o usuario ligou a lampada
      Serial.println("o usuario ligou a lampada");
      if(contDesliga > tempoDesliga && contDesliga < (2*tempoDesliga) && tempoDesliga < 100){//considera que desligou rapido demais e aumenta o tempoDesliga
        Serial.println("aumenta tempo desliga");
        int corTempo = contDesliga - tempoDesliga;//quanto mais rapido o usuario religar mais vai influenciar no novo numero
        tempoDesliga = tempoDesliga + (1*(aprendizagem*100)*corTempo)/100;//usuado a mesma conta de ajuste de valor do perceptron (erro*aprendizagem*valorlido)
        GravaNovosValores();
      }
    }
  }
}

bool perceptron(float mediaLuminosidade, bool valorSensorMov){
  float somatoria = (bias * Wb) + (mediaLuminosidade * Wl) + (valorSensorMov * Wm);
  Serial.print("somatoria : ");
  Serial.println(somatoria);
  if(somatoria > 0){
    return 1;
  }else{
    return 0;
  }
}

void ajusteHoraParada(){
  //ajuste para mais proximo da que foi lida na ultima hora
  if(valorLuzDesejada > luminosidade && valorLuzDesejada < 0,9){
    perceptronLuzDesejada(valorLuzDesejada-luminosidade, -1);
  }else if(valorLuzDesejada < luminosidade && valorLuzDesejada > 0,05){
    perceptronLuzDesejada(luminosidade-valorLuzDesejada, 1);
  }
  //ajuste de reducao do tempo ligado, pois nao foi ligado nesta hora
  if(tempoDesliga > 5){
    tempoDesliga = tempoDesliga + (-1*(aprendizagem*100)*tempoDesliga)/100;
  }
}

bool perceptronLuzDesejada(float mediaLuminosidade, int erroLuz){
  valorLuzDesejada = valorLuzDesejada + (erroLuz * (aprendizagem*100) * mediaLuminosidade)/100;//utilizado a mesma regra de aprendizagem 
}

void correcaoErro(int erro, float mediaLuminosidade, bool valorSensorMov){
  Serial.print("Wb velho : ");
  Serial.println(Wb);
  Wb = Wb + (erro * aprendizagem * bias);
  Serial.print("Wb novo : ");
  Serial.println(Wb);
  Serial.print("Wl velho : ");
  Serial.println(Wl);
  Wl = Wl + (erro * aprendizagem * mediaLuminosidade);
  Serial.print("Wl novo : ");
  Serial.println(Wl);
  Serial.print("Wm velho : ");
  Serial.println(Wm);
  Wm = Wm + (erro * aprendizagem * valorSensorMov);
  Serial.print("Wm novo : ");
  Serial.println(Wm);
  GravaNovosValores();
}

int verificaErro(bool saida, float mediaLuminosidade, bool valorSensorMov){
  if(mediaLuminosidade < valorLuzDesejada && valorSensorMov == 1){
    Serial.print("Ligado ? : ");
    Serial.println(saida);
    //Aqui eu espero que tenha 1 se não tiver, então 1 - 0 = 1
    if(!saida){
      correcaoErro(1, mediaLuminosidade, valorSensorMov);
      return -1;
    }else{
      return 1;
    }
  }else{
    Serial.print("Desligado ? : ");
    Serial.println(saida);
    //Aqui eu espero que tenha 0 se não tiver, então 0 - 1 = -1
    if(saida){
      correcaoErro(-1, mediaLuminosidade, valorSensorMov);
      return -1;
    }else{
      return 0;
    }
  }
}
