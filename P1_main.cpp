#include <iostream>

#define MAX_ARRAY   5

using namespace std;

//classe abstrata actuator  
class Actuator {
    protected:
        int id;
    public:
        Actuator(int newID);
        void setID(int newID);
        int getID();
        virtual void activate() = 0;
        virtual void printStatus() {};
};

Actuator::Actuator(int newID) {
    setID(newID);
}

void Actuator::setID(int newID) {
    id = newID;
}

int Actuator::getID() {
    return id;
}

//classe concreta motor
class motor: public Actuator {
    private:
        int velocidade;
    public:
        motor(int newVelocidade);
        int getVelocidade();
        void setVelocidade(int newVelocidade);
        void printStatus();
        void activate();
};

motor::motor (int newVelocidade) {
    velocidade = newVelocidade;
}

void motor::activate() {
    velocidade += 10;
}

int motor::getVelocidade() {
    return velocidade;
}

void motor::setVelocidade(int newVelocidade) {
    velocidade = newVelocidade;
}

void motor::printStatus() {
    cout << 'Tipo: motor\nid: ' << id;
}

//classe concreta led
class led: public Actuator {
    private:
        bool intensidade;
    public:
        led(bool newIntensidade);
        bool getIntensidade();
        void setIntensidade(bool newIntensidade);
        void printStatus();
        void activate();
};

led::led(bool newIntensidade) {
    intensidade = newIntensidade;
}

void led::activate(){
    intensidade = !intensidade;
}

bool led::getIntensidade() {
    return intensidade;
}

void led::setIntensidade(bool newIntensidade) {
    intensidade = newIntensidade;
}

void led::printStatus() {
    cout << 'Tipo: led\nid: ' << id;
}

//criacao da classe controller
class Controller {
    private:
        Actuator *atuadores[5];
        int actuatorIndex = 0;
        bool tooManyActuatorsException = false;
    public:
        Controller();
        void addActuator(Actuator*);
        void showAll();
        void activateAll();
        void activateOne(int index);
        Actuator** getAtuadores();
};

Controller::Controller() {
}

Actuator** getAtuadores() {
    return atuadores;
}

void Controller::addActuator(Actuator* atuador) {
    //disparar excecao caso +5 atuadores
    if (actuatorIndex >= 5) throw tooManyActuatorsException;

    atuadores[actuatorIndex] = atuador;
    actuatorIndex++;
}

void Controller::activateOne(int index) {
    atuadores[index]->activate();
}

void Controller::showAll() {
    for (int i = 0; i<actuatorIndex; i++) {
        atuadores[i]->printStatus();
    }
}

void Controller::activateAll() {
    for (int i = 0; i<actuatorIndex; i++) {
        atuadores[i]->activate();
    }
}

//funcao template maxValue
template <typename T>
    T maxValue(T actuatorArray[MAX_ARRAY]) {
        T aux = 0;
        for (int i=0; i<MAX_ARRAY; i++) {
            if (actuatorArray[i] > aux) aux = actuatorArray[i];
        }

        return aux;
    }

void main() {
    //criacao do controlador
    Controller controlador;

    //inclusao dos atuadores
    motor motor1(10);
    controlador.addActuator(&motor1);

    motor motor2(14);
    controlador.addActuator(&motor2);

    led led1(true);
    controlador.addActuator(&led1);

    motor motor3(9);
    controlador.addActuator(&motor3);

    led led2(false);
    controlador.addActuator(&led2);

    //varias ativacoes
    controlador.activateAll();
    controlador.activateAll();
    controlador.activateOne(2);
    controlador.activateOne(4);
    controlador.activateOne(0);
    controlador.activateOne(2);
    controlador.activateAll();

    //maxValue

}