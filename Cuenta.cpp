#include "Cuenta.h"

int Cuenta::ultimoNumeroCuenta = 99;

Cuenta::Cuenta() {}

Cuenta::Cuenta(double saldoInicial, int idCliente)
    : saldo(saldoInicial), idCliente(idCliente) {
    numeroCuenta = ++ultimoNumeroCuenta;
}

int Cuenta::getNumeroCuenta() const {
    return numeroCuenta;
}

double Cuenta::getSaldo() const {
    return saldo;
}

int Cuenta::getIdCliente() const {
    return idCliente;
}

void Cuenta::consignar(double cantidad) {
    saldo += cantidad;
}

void Cuenta::setUltimoNumeroCuenta(int numero) {
    ultimoNumeroCuenta = numero;
}
