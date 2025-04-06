#include "CuentaCorriente.h"

CuentaCorriente::CuentaCorriente(double saldoInicial, int idCliente, double limiteSobregiro)
    : Cuenta(saldoInicial, idCliente), limiteSobregiro(limiteSobregiro) {}

bool CuentaCorriente::retirar(double cantidad) {
    if (cantidad <= saldo + limiteSobregiro) {
        saldo -= cantidad;
        return true;
    }
    return false;
}

json CuentaCorriente::toJson() const {
    return {
            {"tipo", "corriente"},
            {"numeroCuenta", numeroCuenta},
            {"saldo", saldo},
            {"idCliente", idCliente},
            {"limiteSobregiro", limiteSobregiro}
    };
}

CuentaCorriente CuentaCorriente::fromJson(const json& j) {
    CuentaCorriente cuenta;
    cuenta.numeroCuenta = j.at("numeroCuenta").get<int>();
    cuenta.saldo = j.at("saldo").get<double>();
    cuenta.idCliente = j.at("idCliente").get<int>();
    cuenta.limiteSobregiro = j.at("limiteSobregiro").get<double>();

    if (cuenta.numeroCuenta > Cuenta::ultimoNumeroCuenta) {
        Cuenta::setUltimoNumeroCuenta(cuenta.numeroCuenta);
    }

    return cuenta;
}

double CuentaCorriente::getLimiteSobregiro() const {
    return limiteSobregiro;
}

void CuentaCorriente::setLimiteSobregiro(double limite) {
    limiteSobregiro = limite;
}
