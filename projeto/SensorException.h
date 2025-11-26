#ifndef SENS_EXCEP_H
#define SENS_EXCEP_H

#include <exception>

class LuminosidadeException : public std::exception {
private:
    float valor;
public:
    explicit LuminosidadeException(float v) : valor(v) {}

    const char* what() const noexcept override {
        return "Luminosidade acima do limite permitido.";
    }

    float getValor() const noexcept {
        return valor;
    }
};

class TemperaturaException : public std::exception {
private:
    float valor;
public:
    explicit TemperaturaException(float v) : valor(v) {}

    const char* what() const noexcept override {
        return "Temperatura excedeu o limite de segurança.";
    }

    float getValor() const noexcept {
        return valor;
    }
};

class UmidadeException : public std::exception {
private:
    float valor;
public:
    explicit UmidadeException(float v) : valor(v) {}

    const char* what() const noexcept override {
        return "Umidade excedeu o limite de segurança.";
    }

    float getValor() const noexcept {
        return valor;
    }
};

#endif
