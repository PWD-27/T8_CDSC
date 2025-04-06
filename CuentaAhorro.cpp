#include "CuentaAhorro.h"

CuentaAhorro::CuentaAhorro(double saldoInicial, int idCliente, double tasaInteres)
    : Cuenta(saldoInicial, idCliente), tasaInteres(tasaInteres) {}

void CuentaAhorro::aplicarInteresMensual() {
    saldo += saldo * (tasaInteres / 100.0);
}

bool CuentaAhorro::retirar(double cantidad) {
    if (cantidad <= saldo) {
        saldo -= cantidad;
        return true;
    }
    return false;
}

json CuentaAhorro::toJson() const {
    return {
            {"tipo", "ahorro"},
            {"numeroCuenta", numeroCuenta},
            {"saldo", saldo},
            {"idCliente", idCliente},
            {"tasaInteres", tasaInteres}
    };
}

CuentaAhorro CuentaAhorro::fromJson(const json& j) {
    CuentaAhorro cuenta;
    cuenta.numeroCuenta = j.at("numeroCuenta").get<int>();
    cuenta.saldo = j.at("saldo").get<double>();
    cuenta.idCliente = j.at("idCliente").get<int>();
    cuenta.tasaInteres = j.at("tasaInteres").get<double>();

    if (cuenta.numeroCuenta > Cuenta::ultimoNumeroCuenta) {
        Cuenta::setUltimoNumeroCuenta(cuenta.numeroCuenta);
    }

    return cuenta;
}

double CuentaAhorro::getTasaInteres() const {
    return tasaInteres;
}

void CuentaAhorro::setTasaInteres(double tasa) {
    tasaInteres = tasa;
}
