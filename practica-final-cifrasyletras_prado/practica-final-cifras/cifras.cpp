#include <vector>
#include <iostream>
#include <random>
#include <algorithm>


using namespace std;

//generador para conseguir la lista de números aleatoria
random_device a;
mt19937 generador(a());

vector<string> soluciones;

vector<int> v_aleatorio(){

    //Números de los que se puede sacar para calcular el objetivo
    vector<int> C={1,2,3,4,5,6,7,8,9,10,25,50,75,100};


    uniform_int_distribution<> dist(0, C.size()-1);
    vector<int> final;
    for (int i = 0; i<6; i++) {
        int num = dist(a);
        final.push_back(C[num]);
    }

    return final;
}

bool calcular(vector<int> v, int objetivo) {

    // Buscamos si alguno de nuestros factores es divisor del número. Si lo es, podemos intentar buscar una solución
    // más rápida

    int i = 0;
    bool solucionado = false;
    while (!solucionado && i < v.size()){
        if (v[i] != 0 && v[i] != 1&& objetivo % v[i] == 0){
            int num=v[i];
            vector<int> copia = v;
            copia.erase(copia.begin()+i);
            int nuevo_obj=objetivo/num;
            int pos_antes = soluciones.size();
            solucionado = calcular(copia, nuevo_obj);
            if (solucionado) {
                string nueva = to_string(nuevo_obj) + "*" + to_string(v[i]) + "=" + to_string(objetivo);
                soluciones.insert(soluciones.begin() + pos_antes, nueva);
            }else i++;
        }
        else {
            i++;
        }
    }

    // Ahora, tras la comprobación anterior (posiblemente simplificando el problema), buscamos la combinación
    // a fuerza bruta


    // el siguiente bool se pone a false si ya no quedan números con los que operar o si la solución ha sido encontrada
    bool operando = true;
    i=0;
    while (operando) {
        int j =0;
        int tam =v.size();
        while (j<tam && !solucionado) {
            if (i == j) { j++; continue; }
            int actual = v[j];
            int num = v[i]+v[j];

            if (num==objetivo) {
                soluciones.push_back(to_string(actual) + "+" + to_string(v[i]) + "=" + to_string(num));
                return true;
            }

            vector<int> copia=v;
            copia.erase(copia.begin()+i);
            if (i < j) copia.erase(copia.begin() +j-1);
            else copia.erase(copia.begin()+j);
            copia.push_back(num);
            tam--;
            solucionado = calcular(copia, objetivo);
            if (solucionado) soluciones.push_back(to_string(actual) + "+" + to_string(v[i]) + "=" + to_string(num));
            ++j;
        }
        j=0;
        while (j<tam && !solucionado) {
            if (i == j) { j++; continue; }
            vector<int> copia = v;
            int actual = v[j];
            int num = v[i]-v[j];

            if (num > 0) {
                if (num==objetivo) {
                    soluciones.push_back(to_string(v[i]) + "-" + to_string(actual) + "=" + to_string(num));
                    return true;
                }

                vector<int> copia=v;
                copia.erase(copia.begin()+i);
                if (i < j) copia.erase(copia.begin() +j-1);
                else copia.erase(copia.begin()+j);
                copia.push_back(num);
                tam--;
                solucionado = calcular(copia, objetivo);
                if (solucionado) soluciones.push_back(to_string(v[i]) + "-" + to_string(actual) + "=" + to_string(num));
            }
            ++j;
        }
        j=0;
        while (j<tam && !solucionado) {
            if (i == j) { j++; continue; }
            vector<int> copia = v;
            int actual = v[j];
            if (v[i]%v[j]==0) {
                int num = v[i]/v[j];
                if (num==objetivo) {
                    soluciones.push_back(to_string(v[i]) + "/" + to_string(actual) + "=" + to_string(num));
                    return true;
                }
                copia.erase(copia.begin()+i);
                if (i < j) copia.erase(copia.begin() +j-1);
                else copia.erase(copia.begin()+j);
                copia.push_back(num);
                tam--;
                solucionado = calcular(copia, objetivo);
                if (solucionado) soluciones.push_back(to_string(v[i]) + "/" + to_string(actual) + "=" + to_string(num));
            }
            ++j;
        }
        j=0;
        while (j<tam && !solucionado) {
            if (i == j) { j++; continue; }
            vector<int> copia = v;
            int actual = v[j];
            int num = v[i]*v[j];

            if (num==objetivo) {
                soluciones.push_back(to_string(actual) + "*" + to_string(v[i]) + "=" + to_string(num));
                return true;
            }
            copia.erase(copia.begin()+i);
            if (i < j) copia.erase(copia.begin() +j-1);
            else copia.erase(copia.begin()+j);
            copia.push_back(num);
            tam--;
            solucionado = calcular(copia, objetivo);
            if (solucionado) soluciones.push_back(to_string(actual) + "*" + to_string(v[i]) + "=" + to_string(num));
            ++j;
        }
        ++i;
        if (i >= v.size() || solucionado) operando = false;
    }

    return solucionado;
}

int main() {

    vector<int> v = v_aleatorio();

    cout << "Numeros: [";
    for (int i = 0; i < v.size(); i++) {

        if (i == v.size() - 1) {
            cout << v[i];
        }
        else cout << v[i] << ",";
    }

    cout << "]" << endl;

    uniform_int_distribution<> dist(100, 999);
    int objetivo = dist(generador);

    cout << "Objetivo: " << objetivo << endl;

    if (calcular(v, objetivo)) {

        reverse(soluciones.begin(), soluciones.end());
        for (int i = 0; i < soluciones.size(); i++) {

            cout << i+1 << ". " << soluciones[i] << endl;
        }
    }
    else cout << "No hay soluciones";


    return 0;
}