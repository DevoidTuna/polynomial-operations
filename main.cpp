// Integrante: Patrick Brining

#include <iostream>
#include <sstream>
#include <string>
#include <cmath>
#include <cctype>
#include <cstdlib>
#include <algorithm>
using namespace std;

struct Monomio {
    double coef;
    char letra;
    int exp;
};

struct Polinomio {
    Monomio *termos;
    int n;
};

string lerLinha(string mensagem) {
    string linha;
    cout << mensagem;
    if (!getline(cin, linha))
        exit(0);
    return linha;
}

double lerNumero(string mensagem) {
    while (true) {
        string linha = lerLinha(mensagem);
        replace(linha.begin(), linha.end(), ',', '.');
        stringstream ss(linha);
        double valor;
        char sobra;
        if (ss >> valor && !(ss >> sobra))
            return valor;
        cout << "  Valor invalido, digite um numero.\n";
    }
}

int lerInteiro(string mensagem) {
    while (true) {
        double valor = lerNumero(mensagem);
        if (valor == (int)valor)
            return valor;
        cout << "  Digite um numero inteiro.\n";
    }
}

Polinomio criar(int n) {
    Polinomio p;
    p.n = n;
    p.termos = new Monomio[n];
    return p;
}

void liberar(Polinomio p) {
    delete[] p.termos;
}

bool maiorExpoente(Monomio a, Monomio b) {
    return a.exp > b.exp;
}

void simplificar(Polinomio &p) {
    int k = 0;
    for (int i = 0; i < p.n; i++) {
        int j = 0;
        while (j < k && p.termos[j].exp != p.termos[i].exp)
            j++;
        if (j < k)
            p.termos[j].coef += p.termos[i].coef;
        else
            p.termos[k++] = p.termos[i];
    }

    p.n = 0;
    for (int i = 0; i < k; i++)
        if (p.termos[i].coef != 0)
            p.termos[p.n++] = p.termos[i];

    sort(p.termos, p.termos + p.n, maiorExpoente);
}

void mostrarMonomio(Monomio m, bool primeiro) {
    if (m.coef < 0)
        cout << (primeiro ? "-" : " - ");
    else if (!primeiro)
        cout << " + ";

    double c = fabs(m.coef);
    if (c != 1 || m.exp == 0)
        cout << c;
    if (m.exp != 0)
        cout << m.letra;
    if (m.exp != 0 && m.exp != 1)
        cout << "^" << m.exp;
}

void mostrar(Polinomio p) {
    if (p.n == 0)
        cout << "0";
    for (int i = 0; i < p.n; i++)
        mostrarMonomio(p.termos[i], i == 0);
    cout << endl;
}

Polinomio ler(string nome, char letra) {
    cout << "\n--- Polinomio " << nome << " ---\n";
    int n;
    do {
        n = lerInteiro("Quantidade de termos: ");
    } while (n < 1);

    Polinomio p = criar(n);
    for (int i = 0; i < n; i++) {
        cout << "Termo " << i + 1 << ":\n";
        p.termos[i].coef = lerNumero("  coeficiente: ");
        p.termos[i].exp = lerInteiro("  expoente: ");
        p.termos[i].letra = letra;
    }
    simplificar(p);

    cout << nome << "(" << letra << ") = ";
    mostrar(p);
    return p;
}

double valor(Polinomio p, double x) {
    double soma = 0;
    for (int i = 0; i < p.n; i++)
        soma += p.termos[i].coef * pow(x, p.termos[i].exp);
    return soma;
}

Polinomio somar(Polinomio a, Polinomio b) {
    Polinomio r = criar(a.n + b.n);
    for (int i = 0; i < a.n; i++)
        r.termos[i] = a.termos[i];
    for (int i = 0; i < b.n; i++)
        r.termos[a.n + i] = b.termos[i];
    simplificar(r);
    return r;
}

Polinomio multiplicarMonomio(Polinomio p, Monomio m) {
    Polinomio r = criar(p.n);
    for (int i = 0; i < p.n; i++) {
        r.termos[i] = p.termos[i];
        r.termos[i].coef *= m.coef;
        r.termos[i].exp += m.exp;
    }
    simplificar(r);
    return r;
}

Polinomio multiplicarEscalar(Polinomio p, double k) {
    return multiplicarMonomio(p, {k, ' ', 0});
}

Polinomio subtrair(Polinomio a, Polinomio b) {
    Polinomio negativoB = multiplicarEscalar(b, -1);
    Polinomio r = somar(a, negativoB);
    liberar(negativoB);
    return r;
}

Polinomio multiplicar(Polinomio a, Polinomio b) {
    Polinomio r = criar(a.n * b.n);
    int k = 0;
    for (int i = 0; i < a.n; i++)
        for (int j = 0; j < b.n; j++) {
            r.termos[k] = a.termos[i];
            r.termos[k].coef *= b.termos[j].coef;
            r.termos[k].exp += b.termos[j].exp;
            k++;
        }
    simplificar(r);
    return r;
}

int main() {
    cout << "===== CALCULADORA DE POLINOMIOS =====\n\n";

    string linha;
    do {
        linha = lerLinha("Letra da incognita (ex: x): ");
    } while (linha.size() != 1 || !isalpha(linha[0]));
    char letra = linha[0];

    Polinomio p = ler("P", letra);
    Polinomio q = ler("Q", letra);

    int op;
    do {
        cout << "\n========================================\n";
        cout << "  P(" << letra << ") = ";
        mostrar(p);
        cout << "  Q(" << letra << ") = ";
        mostrar(q);
        cout << "========================================\n"
             << "  1 - Valor numerico de P e Q\n"
             << "  2 - Somar (P + Q)\n"
             << "  3 - Subtrair (P - Q)\n"
             << "  4 - Multiplicar P por uma constante\n"
             << "  5 - Multiplicar P por um monomio\n"
             << "  6 - Multiplicar (P * Q)\n"
             << "  7 - Digitar novos polinomios\n"
             << "  0 - Sair\n"
             << "----------------------------------------\n";
        op = lerInteiro("Opcao: ");
        cout << endl;

        Polinomio r = {nullptr, 0};
        switch (op) {
        case 0:
            break;
        case 1: {
            double x = lerNumero(string("Valor de ") + letra + ": ");
            cout << "P(" << x << ") = " << valor(p, x) << endl;
            cout << "Q(" << x << ") = " << valor(q, x) << endl;
            break;
        }
        case 2:
            r = somar(p, q);
            cout << "P + Q = ";
            break;
        case 3:
            r = subtrair(p, q);
            cout << "P - Q = ";
            break;
        case 4: {
            double k = lerNumero("Constante: ");
            r = multiplicarEscalar(p, k);
            cout << "P * (" << k << ") = ";
            break;
        }
        case 5: {
            Monomio m;
            m.letra = letra;
            m.coef = lerNumero("Coeficiente do monomio: ");
            m.exp = lerInteiro("Expoente do monomio: ");
            r = multiplicarMonomio(p, m);
            cout << "P * (";
            mostrarMonomio(m, true);
            cout << ") = ";
            break;
        }
        case 6:
            r = multiplicar(p, q);
            cout << "P * Q = ";
            break;
        case 7:
            liberar(p);
            liberar(q);
            p = ler("P", letra);
            q = ler("Q", letra);
            break;
        default:
            cout << "Opcao invalida.\n";
        }

        if (r.termos != nullptr) {
            mostrar(r);
            liberar(r);
        }
        if (op != 0 && op != 7)
            lerLinha("\nPressione ENTER para voltar ao menu...");
    } while (op != 0);

    liberar(p);
    liberar(q);
    return 0;
}
