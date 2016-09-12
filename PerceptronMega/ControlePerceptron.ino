//variaveis perceptron
bool bias = 1;
float Wb = -0.2;
float Wm = 0.7;
float Wl = -0.4;
float aprendizagem = 0.01;
float valorLuzDesejada = 0.68;
bool p1 = false; //valor do perceptron para ligar a lampada
bool p2 = false; //valor do perceptron para controle da luminosidade

bool realizaPerceptron = false;
long tempoPerceptron = 10000000;//tempo em que é realizado o perceptron
int contDesliga = 0; 
int tempoDesliga = 60;//valor em que o contador tem que chegar para assim desligar a lampada, multiplicado pelo tempoPercetron ocorre o tempo que fica ligado

void pCallback(){
    realizaPerceptron = true;
}

void criaTimerParaPerceptron(){
  Timer1.initialize(tempoPerceptron);
  Timer1.attachInterrupt(pCallback);
}

void chamaPerceptron(){
  if(realizaPerceptron){
    realizaPerceptron = false;
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
    p1 = perceptron(luminosidade, movimento);//perceptron automatizado
    p2 = perceptron(luminosidade, digitalRead(statusLampada));//o mesmo perceptron so considerando o ato do usuario em vez do sensor de movimento
    if(p2 != digitalRead(statusLampada)){//verifica se a lampada possui o mesmo status do perceptron se nao deve ser corrigido o erro
      if(p1 == p2){// se os dois perceptrons forem verdadeiros sao corrigidos os valores de controle do perceptron
        verificaErro(p1, luminosidade, movimento);
      }else{// se forem diferentes eh alterado o valor da iluminacao desejada
        int erroLuz = ((int) p2) - ((int) digitalRead(statusLampada));
        perceptronLuzDesejada(luminosidade,erroLuz);
      }
    }
    if(!digitalRead(statusLampada)){//se o usuario desligou a lampada
      if(contDesliga < tempoDesliga){//considera que deveria ter desligado e diminui o tempoDesliga
        float corTempo = 100/contDesliga;//quanto mais rapido o usuario desligar mais vai influenciar no novo numero
        tempoDesliga = tempoDesliga + (1*aprendizagem*corTempo);
      }
    }else{// se o usuario ligou a lampada
      if(contDesliga > tempoDesliga && contDesliga < (2*tempoDesliga)){//considera que desligou rapido demais e aumenta o tempoDesliga
        float corTempo = 1000/contDesliga;//quanto mais rapido o usuario religar mais vai influenciar no novo numero
        tempoDesliga = tempoDesliga + (1*aprendizagem*corTempo);//usuado a mesma conta de ajuste de valor do perceptron (erro*aprendizagem*valorlido)
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

bool perceptronLuzDesejada(float mediaLuminosidade, int erroLuz){
  valorLuzDesejada = valorLuzDesejada + (erroLuz * aprendizagem * mediaLuminosidade);//utilizado a mesma regra de aprendizagem 
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
