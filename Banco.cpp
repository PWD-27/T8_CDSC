#include "Banco.h"
#include <iostream>
#include <iomanip>

Banco::Banco(const string& nombre) : nombre(nombre) {}

Banco::~Banco() {
    for (auto cuenta : cuentas) {
        delete cuenta;
    }
}

void Banco::setTasaInteres(double tasa) {
    tasaInteresAhorro = tasa;
}

void Banco::agregarCliente(const string& nombre, const string& direccion) {
    clientes.emplace_back(nombre, direccion);
    cout << "Cliente agregado con ID: " << clientes.back().getId() << endl;
}

void Banco::agregarCuentaAhorro(int idCliente, double saldoInicial) {
    cuentas.push_back(new CuentaAhorro(saldoInicial, idCliente, tasaInteresAhorro));
    cout << "Cuenta de ahorro creada con numero: " << cuentas.back()->getNumeroCuenta() << endl;
}

void Banco::agregarCuentaCorriente(int idCliente, double saldoInicial, double limiteSobregiro) {
    cuentas.push_back(new CuentaCorriente(saldoInicial, idCliente, limiteSobregiro));
    cout << "Cuenta corriente creada con numero: " << cuentas.back()->getNumeroCuenta() << endl;
}

void Banco::listarClientes() const {
    cout << "\nLista de Clientes\n";
    for (const auto& c : clientes) {
        cout << "ID: " << c.getId() << " | Nombre: " << c.getNombre() << " | Direccion: " << c.getDireccion() << endl;
    }
}

void Banco::listarCuentas() const {
    cout << "\nLista de Cuentas\n";
    for (const auto& c : cuentas) {
        cout << "Numero: " << c->getNumeroCuenta()
             << " | Cliente ID: " << c->getIdCliente()
             << " | Saldo: " << fixed << setprecision(2) << c->getSaldo() << endl;
    }
}

void Banco::aplicarInteres() {
    for (auto& c : cuentas) {
        auto* ahorro = dynamic_cast<CuentaAhorro*>(c);
        if (ahorro) {
            ahorro->aplicarInteresMensual();
        }
    }
    cout << "Interes aplicado a las cuentas de ahorro.\n";
}

bool Banco::consignar(int numeroCuenta, double monto) {
    for (auto& c : cuentas) {
        if (c->getNumeroCuenta() == numeroCuenta) {
            c->consignar(monto);
            return true;
        }
    }
    return false;
}

bool Banco::retirar(int numeroCuenta, double monto) {
    for (auto& c : cuentas) {
        if (c->getNumeroCuenta() == numeroCuenta) {
            return c->retirar(monto);
        }
    }
    return false;
}

void Banco::mostrarEstadisticas() const {
    int totalClientes = clientes.size();
    int totalCuentas = cuentas.size();
    double totalSaldo = 0.0;
    int cuentaAhorro = 0, cuentaCorriente = 0;

    for (const auto& c : cuentas) {
        totalSaldo += c->getSaldo();
        if (dynamic_cast<CuentaAhorro*>(c)) cuentaAhorro++;
        else if (dynamic_cast<CuentaCorriente*>(c)) cuentaCorriente++;
    }

    double promedioSaldo = totalCuentas > 0 ? totalSaldo / totalCuentas : 0.0;

    cout << "\nEstadisticas del Banco\n";
    cout << "Total Clientes: " << totalClientes << endl;
    cout << "Total Cuentas: " << totalCuentas << endl;
    cout << "Promedio de Saldo: " << fixed << setprecision(2) << promedioSaldo << endl;
    cout << "Tasa de Interes Ahorros: " << tasaInteresAhorro << "%" << endl;
    cout << "N Cuentas Ahorro: " << cuentaAhorro << endl;
    cout << "N Cuentas Corriente: " << cuentaCorriente << endl;

    cout << "\nClientes Registrados\n";
    for (const auto& c : clientes) {
        cout << "ID: " << c.getId() << " | Nombre: " << c.getNombre() << endl;
    }

    cout << "\nCuentas Registradas\n";
    for (const auto& c : cuentas) {
        string tipo = dynamic_cast<CuentaAhorro*>(c) ? "Ahorro" : "Corriente";
        cout << "Cliente ID: " << c->getIdCliente()
             << " | Cuenta N: " << c->getNumeroCuenta()
             << " | Tipo: " << tipo << endl;
    }
}

void Banco::guardarDatos(const string& rutaArchivo) const {
    json j;
    j["clientes"] = json::array();
    j["cuentas"] = json::array();

    for (const auto& c : clientes) {
        j["clientes"].push_back(c.toJson());
    }

    for (const auto& c : cuentas) {
        j["cuentas"].push_back(c->toJson());
    }

    ofstream archivo(rutaArchivo);
    if (archivo.is_open()) {
        archivo << setw(4) << j << endl;
        archivo.close();
        cout << "Datos guardados exitosamente en " << rutaArchivo << endl;
    } else {
        cerr << "Error al guardar datos.\n";
    }
}

void Banco::cargarDatos(const string& rutaArchivo) {
    ifstream archivo(rutaArchivo);
    if (!archivo.is_open()) {
        cerr << "Archivo no encontrado, iniciando nuevo banco.\n";
        return;
    }

    json j;
    archivo >> j;
    archivo.close();

    clientes.clear();
    for (const auto& item : j["clientes"]) {
        clientes.push_back(Cliente::fromJson(item));
    }

    for (auto cuenta : cuentas) {
        delete cuenta;
    }
    cuentas.clear();

    for (const auto& item : j["cuentas"]) {
        string tipo = item.at("tipo").get<string>();
        if (tipo == "ahorro") {
            cuentas.push_back(new CuentaAhorro(CuentaAhorro::fromJson(item)));
        } else if (tipo == "corriente") {
            cuentas.push_back(new CuentaCorriente(CuentaCorriente::fromJson(item)));
        }
    }

    cout << "Datos cargados desde " << rutaArchivo << endl;
}
