#include <iostream>
#include <limits>
#include "Banco.h"

#include "/Users/usuario/CLionProjects/BancoJaveriano/json.hpp"

using namespace std;

void limpiarBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int main() {
    Banco banco("Banco Javeriano");

    banco.cargarDatos("BancoJaveriano.json");

    double tasa;
    cout << "Ingrese la tasa de interes para las cuentas de ahorro (%): ";
    while (!(cin >> tasa) || tasa < 0) {
        cout << "Valor invalido. Ingrese una tasa positiva: ";
        limpiarBuffer();
    }
    banco.setTasaInteres(tasa);
    limpiarBuffer();

    int opcionGeneral, opcionCliente, opcionCuenta, opcionEstadisticas, opcionOperaciones;

    do {
        cout << "\nMENU BANCO JAVERIANO\n";
        cout << "1. Clientes\n";
        cout << "2. Cuentas\n";
        cout << "3. Estadisticas\n";
        cout << "4. Operaciones Financieras\n";
        cout << "5. Salir y Guardar Datos\n";
        cout << "Seleccione una opcion: ";
        cin >> opcionGeneral;
        limpiarBuffer();

        switch (opcionGeneral) {
            case 1:
                cout << "\nCLIENTES\n";
                cout << "1. Agregar Cliente\n";
                cout << "2. Listar Clientes\n";
                cout << "Seleccione una opcion: ";
                cin >> opcionCliente;
                limpiarBuffer();

                if (opcionCliente == 1) {
                    string nombre, direccion;
                    cout << "Nombre del cliente: ";
                    getline(cin, nombre);
                    cout << "Direccion del cliente: ";
                    getline(cin, direccion);
                    banco.agregarCliente(nombre, direccion);
                } else if (opcionCliente == 2) {
                    banco.listarClientes();
                } else {
                    cout << "Opcion invalida.\n";
                }
                break;

            case 2:
                cout << "\nCUENTAS\n";
                cout << "1. Agregar Cuenta\n";
                cout << "2. Listar Cuentas\n";
                cout << "Seleccione una opcion: ";
                cin >> opcionCuenta;
                limpiarBuffer();

                if (opcionCuenta == 1) {
                    int idCliente;
                    double saldo;
                    cout << "ID del cliente: ";
                    cin >> idCliente;
                    limpiarBuffer();
                    cout << "Saldo inicial: ";
                    cin >> saldo;
                    limpiarBuffer();

                    int tipo;
                    cout << "Tipo de cuenta (1: Ahorro | 2: Corriente): ";
                    cin >> tipo;
                    limpiarBuffer();

                    if (tipo == 1) {
                        banco.agregarCuentaAhorro(idCliente, saldo);
                    } else if (tipo == 2) {
                        double limite;
                        cout << "Limite de sobregiro: ";
                        cin >> limite;
                        limpiarBuffer();
                        banco.agregarCuentaCorriente(idCliente, saldo, limite);
                    } else {
                        cout << "Tipo de cuenta invalido.\n";
                    }
                } else if (opcionCuenta == 2) {
                    banco.listarCuentas();
                } else {
                    cout << "Opcion invalida.\n";
                }
                break;

            case 3:
                cout << "\nESTADISTICAS\n";
                banco.mostrarEstadisticas();
                break;

            case 4:
                cout << "\nOPERACIONES FINANCIERAS\n";
                cout << "1. Aplicar Interes a Cuentas de Ahorro\n";
                cout << "2. Consignar Dinero en una Cuenta\n";
                cout << "3. Retirar Dinero de una Cuenta\n";
                cout << "Seleccione una opcion: ";
                cin >> opcionOperaciones;
                limpiarBuffer();

                if (opcionOperaciones == 1) {
                    banco.aplicarInteres();
                } else if (opcionOperaciones == 2) {
                    int numeroCuenta;
                    double monto;
                    cout << "Numero de cuenta: ";
                    cin >> numeroCuenta;
                    cout << "Monto a consignar: ";
                    cin >> monto;
                    if (banco.consignar(numeroCuenta, monto)) {
                        cout << "Consignacion exitosa.\n";
                    } else {
                        cout << "Cuenta no encontrada.\n";
                    }
                } else if (opcionOperaciones == 3) {
                    int numeroCuenta;
                    double monto;
                    cout << "Numero de cuenta: ";
                    cin >> numeroCuenta;
                    cout << "Monto a retirar: ";
                    cin >> monto;
                    if (banco.retirar(numeroCuenta, monto)) {
                        cout << "Retiro exitoso.\n";
                    } else {
                        cout << "Fondos insuficientes o cuenta no encontrada.\n";
                    }
                } else {
                    cout << "Opcion invalida.\n";
                }
                break;

            case 5:
                banco.guardarDatos("BancoJaveriano.json");
                cout << "Gracias por usar el sistema del Banco Javeriano. ¡Hasta pronto!\n";
                break;

            default:
                cout << "Opcion invalida. Intente de nuevo.\n";
                break;
        }

    } while (opcionGeneral != 5);

    return 0;
}
