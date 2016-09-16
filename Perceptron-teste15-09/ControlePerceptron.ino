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
    if(verificaLampada()){
      Serial.println("nao iniciou");
      SaveValues("Usuario alterou estado da lampada pelo interruptor");
      return; //ter certeza que nao foi alterado o estado da lampada antes do perceptron
    }
    millisPerceptron = millis();
    tempoPerceptron = TIME_EXEC;//sempre que executado o perceptron volta a executar a cada 2 segundos
    luminosidade = getLuminosidade();
    movimento = getMovimento();
    p1 = perceptron(luminosidade, movimento);
    int saida = verificaErro(p1, luminosidade, movimento);
    if(saida != -1){
      if(saida == 1){
        contDesliga = 0; //Sempre que a saida for ligar zera o contador
        ligaLampada();
        SaveValues("Perceptron liga lampada");
      }else{
        if(contDesliga <= (2*tempoDesliga)){
          contDesliga++;// somente quando contador chegar ao valor do tempo eh que a saida ira desligar
        }
        if(contDesliga >= tempoDesliga){          
          desligaLampada();
          SaveValues("Perceptron desliga lampada");
        }
      }
    }
  }
  if(alteracaoUsuario){//caso o usuario altere antes do perceptron eh realizado verificacao e correcao dos valores
    alteracaoUsuario = false;    
    millisPerceptron = millis();//resetar o tempo do perceptron
    bool lampadaLigada = leLampada();
    if(lampadaLigada)
      tempoPerceptron = TIME_DELAY - (TIME_EXEC*tempoDesliga);
    else
      tempoPerceptron = TIME_DELAY;
    luminosidade = getLuminosidade();
    movimento = getMovimento();
    p1 = perceptron(luminosidade, lampadaLigada);
    //verifica se a lampada possui o mesmo status do perceptron se nao deve ser corrigido o erro
    if(p1 != lampadaLigada){
      int erroLuz = ((int) p1) - ((int) lampadaLigada);
      perceptronLuzDesejada(luminosidade,erroLuz);
      SaveValues("atualizou Luz Desejada");
      GravaNovosValores();      
    }
    if(lampadaLigada){//se o usuario desligou a lampada
      if(contDesliga < tempoDesliga && tempoDesliga >= 5){//considera que deveria ter desligado e diminui o tempoDesliga
        int corTempo = tempoDesliga - contDesliga;//quanto mais rapido o usuario desligar mais vai influenciar no novo numero
        tempoDesliga = tempoDesliga + (-1*(aprendizagem*100)*corTempo)/100;
        SaveValues("reduziu Tempo Desliga");
        GravaNovosValores();
      }else if(tempoDesliga < 5){
        tempoDesliga = 5;
      }
    }else{// se o usuario ligou a lampada
      if(contDesliga > tempoDesliga && contDesliga < (2*tempoDesliga) && tempoDesliga < 100){//considera que desligou rapido demais e aumenta o tempoDesliga
        int corTempo = contDesliga - tempoDesliga;//quanto mais rapido o usuario religar mais vai influenciar no novo numero
        tempoDesliga = tempoDesliga + (1*(aprendizagem*100)*corTempo)/100;//usuado a mesma conta de ajuste de valor do perceptron (erro*aprendizagem*valorlido)
        SaveValues("Aumentou Tempo Desliga");
        GravaNovosValores();
      }else if(tempoDesliga >= 100){
        tempoDesliga = 100;
      }
    }
  }
}

//função principal do sistema, onde é realizado o perceptron
bool perceptron(float mediaLuminosidade, bool valorSensorMov){
  float somatoria = (bias * Wb) + (mediaLuminosidade * Wl) + (valorSensorMov * Wm);
  if(somatoria > 0){
    return 1;
  }else{
    return 0;
  }
}

//função para ajustes das variaveis nas horas que a lampada não é atuada
void ajusteHoraParada(){
  //ajuste para mais proximo do que foi lido na ultima hora
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

//Altera o valor de luz desejada utilizando a mesma formula de correção de erro do perceptron
bool perceptronLuzDesejada(float mediaLuminosidade, int erroLuz){
  valorLuzDesejada = valorLuzDesejada + (erroLuz * (aprendizagem*100) * mediaLuminosidade)/100;
}

//função de correção de erro do perceptron
void correcaoErro(int erro, float mediaLuminosidade, bool valorSensorMov){
  Wb = Wb + (erro * aprendizagem * bias);
  Wl = Wl + (erro * aprendizagem * mediaLuminosidade);
  Wm = Wm + (erro * aprendizagem * valorSensorMov);
  SaveValues("Perceptron realizou correcao de erro");
  GravaNovosValores();
}

//função de verificação de erro do perceptron
int verificaErro(bool saida, float mediaLuminosidade, bool valorSensorMov){
  // condicional que define o que o perceptron deve fazer
  if(mediaLuminosidade < valorLuzDesejada && valorSensorMov == 1){
    //Aqui eu espero que tenha 1 se não tiver, então 1 - 0 = 1
    if(!saida){
      correcaoErro(1, mediaLuminosidade, valorSensorMov);
      return -1;
    }else{
      return 1;
    }
  }else{
    //Aqui eu espero que tenha 0 se não tiver, então 0 - 1 = -1
    if(saida){
      correcaoErro(-1, mediaLuminosidade, valorSensorMov);
      return -1;
    }else{
      return 0;
    }
  }
}
