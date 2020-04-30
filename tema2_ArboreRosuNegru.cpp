#include <iostream>
#include <string.h>

enum Culoare {Rosu, Negru, Dublu};

class Nod {

    int m_info;
    Nod *m_stanga, *m_dreapta, *m_parinte;
    Culoare m_culoare;

public:
    Nod(int info = 0, Nod *st = nullptr, Nod *dr = nullptr, Nod *p = nullptr, Culoare culoare = Rosu)
        : m_info{ info }, m_stanga{ st }, m_dreapta{ dr }, m_parinte{ p }, m_culoare{ culoare }
    {

    }

    Nod* getParinte() { return m_parinte; }
    Nod* getSt() { return m_stanga; }
    Nod* getDr() { return m_dreapta; }
    int getInfo() { return m_info; }

    void setParinte(Nod* p) {this->m_parinte = p;}
    void setSt(Nod* st) {this->m_stanga = st;}
    void setDr(Nod* dr) {this->m_dreapta = dr;}
    void setInfo(int info) {this->m_info = info;}

    friend Culoare getCuloare(Nod *x);
    friend void setCuloare(Nod *x, Culoare culoare);
};

Culoare getCuloare(Nod *x) {

    if (x == nullptr)
        return Negru;

    return x->m_culoare;
}

void setCuloare(Nod *x, Culoare culoare) {

    if (x == nullptr)
        return;

    x->m_culoare = culoare;
}


Nod* minValueNode(Nod *&nod) {

    Nod *ptr = nod;

    while (ptr->getSt() != nullptr)
        ptr = ptr->getSt();

    return ptr;
}

Nod* maxValueNode(Nod *&nod) {

    Nod *ptr = nod;

    while (ptr->getDr() != nullptr)
        ptr = ptr->getDr();

    return ptr;
}

Nod* deleteBST(Nod *&root, int data) {

    if (root == nullptr)
        return root;

    Nod *dr = root->getDr();
    Nod *st = root->getSt();

    if(data < root->getInfo()) {
        return deleteBST(st, data);
    }

    if (data > root->getInfo()) {
        return deleteBST(dr, data);
    }

    if (st == nullptr || dr == nullptr) {
        return root;
    }

    Nod *aux = minValueNode(dr);
    root->setInfo(aux->getInfo());

    return deleteBST(dr, aux->getInfo());
}


void rotateLeft(Nod *&radacina, Nod *&x) {

    Nod *right_child = x->getDr();
    x->setDr(right_child->getSt());

    if (x->getDr() != nullptr)
        x->getDr()->setParinte(x);

    right_child->setParinte(x->getParinte());

    if (x->getParinte() == nullptr)
        radacina = right_child;
    else if (x == x->getParinte()->getSt())
        x->getParinte()->setSt(right_child);
    else
        x->getParinte()->setDr(right_child);

    right_child->setSt(x);
    x->setParinte(right_child);
}

void rotateRight(Nod *&radacina, Nod *&x) {

    Nod *left_child = x->getSt();
    x->setSt(left_child->getDr());

    if (x->getSt() != nullptr)
        x->getSt()->setParinte(x);

    left_child->setParinte(x->getParinte());

    if (x->getParinte() == nullptr)
        radacina = left_child;
    else if (x == x->getParinte()->getSt())
        x->getParinte()->setSt(left_child);
    else
        x->getParinte()->setDr(left_child);

    left_child->setDr(x);
    x->setParinte(left_child);
}

void swapColor(Nod *a, Nod *b) {

    Culoare aux = getCuloare(a);
    setCuloare(a, getCuloare(b));
    setCuloare(b, aux);
}

void fix(Nod *&radacina, Nod *&x) {
    Nod *parinte = nullptr;
    Nod *bunic = nullptr;

    while (x != radacina && getCuloare(x) == Rosu && getCuloare(x->getParinte()) == Rosu) {
        parinte = x->getParinte();
        bunic = parinte->getParinte();

        if (parinte == bunic->getSt()) {
            Nod *unchi = bunic->getDr();

            if(unchi != nullptr && getCuloare(unchi) == Rosu) {
                setCuloare(unchi, Negru);
                setCuloare(parinte, Negru);
                setCuloare(bunic, Rosu);
                x = bunic;
            }
            else {
                if (x == parinte->getDr()) {
                    rotateLeft(radacina, parinte);
                    x = parinte;
                    parinte = x->getParinte();
                }

                rotateRight(radacina, bunic);
                swapColor(parinte, bunic);
                x = parinte;
            }
        }
        else {

            Nod *unchi = bunic->getSt();

            if(unchi != nullptr && getCuloare(unchi) == Rosu) {
                setCuloare(unchi, Negru);
                setCuloare(parinte, Negru);
                setCuloare(bunic, Rosu);
                x = bunic;
            }
            else {
                if (x == parinte->getSt()) {
                    rotateRight(radacina, parinte);
                    x = parinte;
                    parinte = x->getParinte();
                }

                rotateLeft(radacina, bunic);
                swapColor(parinte, bunic);
                x = parinte;
            }
        }
    }

    setCuloare(radacina, Negru);
}


Nod* inserareABC(Nod *&rad, Nod *&x) {

    if ((rad == nullptr) || (rad->getInfo() == 0))
        return x;

    Nod *st = rad->getSt();
    Nod *dr = rad->getDr();

    if (x->getInfo() <= rad->getInfo()) {
        rad->setSt(inserareABC(st, x));
        rad->getSt()->setParinte(rad);
    }
    else if (x->getInfo() > rad->getInfo()) {
        rad->setDr(inserareABC(dr, x));
        rad->getDr()->setParinte(rad);
    }

    return rad;
}

void insertRBT(Nod *&radacina, int info) {

    Nod *x = new Nod(info);

    radacina = inserareABC(radacina, x);

    fix(radacina, x);
}


void fixDelete(Nod *&radacina, Nod *&nod) {

    if (nod == nullptr)
        return;

    if (nod == radacina) {
        radacina = nullptr;
        return;
    }

    if (getCuloare(nod) == Rosu || getCuloare(nod->getSt()) == Rosu || getCuloare(nod->getDr()) == Rosu) {
        Nod *copil = nod->getSt() != nullptr ? nod->getSt() : nod->getDr();

        if (nod == nod->getParinte()->getSt()) {
            nod->getParinte()->setSt(copil);

            if (copil != nullptr)
                copil->setParinte(nod->getParinte());

            setCuloare(copil, Negru);
            delete (nod);
        }
        else {
            nod->getParinte()->setDr(copil);

            if (copil != nullptr)
                copil->setParinte(nod->getParinte());


            setCuloare(copil, Negru);
            delete (nod);
        }
    }
    else {
        Nod *frate = nullptr;
        Nod *parinte = nullptr;
        Nod *ptr = nod;

        setCuloare(ptr, Dublu);

        while (ptr != radacina && getCuloare(ptr) == Dublu) {
            parinte = ptr->getParinte();

            if (ptr == parinte->getSt()) {
                frate = parinte->getDr();

                if (getCuloare(frate) == Rosu) {
                    setCuloare(frate, Negru);
                    setCuloare(parinte, Rosu);
                    rotateLeft(radacina, parinte);
                }
                else {
                    if (getCuloare(frate->getSt()) == Negru && getCuloare(frate->getDr()) == Negru) {
                        setCuloare(frate, Rosu);

                        if(getCuloare(parinte) == Rosu)
                            setCuloare(parinte, Negru);
                        else
                            setCuloare(parinte, Dublu);

                        ptr = parinte;
                    }
                    else {
                        if (getCuloare(frate->getDr()) == Negru) {
                            setCuloare(frate->getSt(), Negru);
                            setCuloare(frate, Rosu);
                            rotateRight(radacina, frate);
                            frate = parinte->getDr();
                        }

                        setCuloare(frate, getCuloare(parinte));
                        setCuloare(parinte, Negru);
                        setCuloare(frate->getDr(), Negru);
                        rotateLeft(radacina, parinte);

                        break;
                    }
                }
            }
            else {
                frate = parinte->getSt();

                if (getCuloare(frate) == Rosu) {
                    setCuloare(frate, Negru);
                    setCuloare(parinte, Rosu);
                    rotateRight(radacina, parinte);
                }
                else {

                    if (getCuloare(frate->getSt()) == Negru && getCuloare(frate->getDr()) == Negru) {
                        setCuloare(frate, Rosu);

                        if (getCuloare(parinte) == Rosu)
                            setCuloare(parinte, Negru);
                        else
                            setCuloare(parinte, Dublu);

                        ptr = parinte;
                    }
                    else {

                        if (getCuloare(frate->getSt()) == Negru) {
                            setCuloare(frate->getDr(), Negru);
                            setCuloare(frate, Rosu);
                            rotateLeft(radacina, frate);
                            frate = parinte->getSt();
                        }

                        setCuloare(frate, getCuloare(parinte));
                        setCuloare(parinte, Negru);
                        setCuloare(frate->getSt(), Negru);
                        rotateRight(radacina, parinte);

                        break;
                    }
                }
            }
        }

        if (nod == nod->getParinte()->getSt())
            nod->getParinte()->setSt(nullptr);
        else
            nod->getParinte()->setDr(nullptr);

        delete(nod);
        setCuloare(radacina, Negru);
    }


}

void nrAparitii(Nod *rad, int val, int &contor) {
    if(rad == nullptr)
        return;
    else {
        nrAparitii(rad->getSt(), val, contor);

        if(val == rad->getInfo())
            contor++;

        nrAparitii(rad->getDr(), val, contor);
    }
}


void deleteRBT(Nod *&radacina, int info) {

    int cntr = 0;
    nrAparitii(radacina, info, cntr);

    std::cout << std::endl << cntr;

    while(cntr > 0) {
        Nod *x = deleteBST(radacina, info);
        fixDelete(radacina, x);
        cntr--;
    }
}

void cautare(Nod *rad, int x) {

    int cntr = 0;
    nrAparitii(rad, x, cntr);

    if (cntr >= 1)
        std::cout << '1';
    else
        std::cout << '0';
}

Nod* gasesteNod(Nod* rad, int val) {
    if (rad == nullptr || rad->getInfo() == val)
        return rad;

    if (rad->getInfo() < val)
        return gasesteNod(rad->getDr(), val);

    return gasesteNod(rad->getSt(), val);
}

Nod* succesor(Nod* rad, int val) {

    Nod *nod = gasesteNod(rad, val);

    if (nod->getDr() != nullptr) {
        Nod *dr = nod->getDr();
        return minValueNode(dr);
    }

    Nod *parinte = nod->getParinte();

    while (parinte != nullptr && nod == parinte->getDr()) {
        nod = parinte;
        parinte = parinte->getParinte();
    }

    return parinte;
}

void afisaresuccesor(Nod *rad, int x) {

    Nod *succ = succesor(rad, x);

    if (succ == nullptr)
        std::cout << -1;
    else
        std::cout << succ->getInfo();
}

Nod* predecesor(Nod* rad, int val) {

    Nod *nod = gasesteNod(rad, val);

    if (nod->getSt() != nullptr) {
        Nod *st = nod->getSt();
        return maxValueNode(st);
    }

    Nod *parinte = nod->getParinte();

    while (parinte != nullptr && nod == parinte->getSt()) {
        nod = parinte;
        parinte = parinte->getParinte();
    }

    return parinte;
}

void afisarepredecesor(Nod *rad, int x) {

    Nod *pred = predecesor(rad, x);

    if (pred == nullptr)
        std::cout << -1;
    else
        std::cout << pred->getInfo();
}

void afisareInterval(Nod* rad, int x, int y) {
    //std::cout << std::endl;//rad->getInfo();

    if (rad == nullptr)
        return;

    if (x < rad->getInfo())
        afisareInterval(rad->getSt(), x, y);

    if (x < rad->getInfo() && rad->getInfo() < y)
        std::cout << rad->getInfo() << " ";

    if (y > rad->getInfo())
        afisareInterval(rad->getDr(), x, y);

}

void afisare(Nod* nod) {

    if(nod == nullptr)
        return;
    else {
        afisare(nod->getSt());
        std::cout << nod->getInfo() << " " << getCuloare(nod) << std::endl;
        afisare(nod->getDr());
    }
}

int main() {

    Nod *rad;

    /*
    insertRBT(rad, 13);
    insertRBT(rad, 8);
    insertRBT(rad, 17);
    //insertRBT(rad, 13);
    insertRBT(rad, 1);
    insertRBT(rad, 11);
    insertRBT(rad, 15);
    insertRBT(rad, 25);
    //insertRBT(rad, 13);
    insertRBT(rad, 6);
    insertRBT(rad, 22);
    insertRBT(rad, 27);
    //insertRBT(rad, 13);
    //insertRBT(rad, 13);


    //insertRBT(rad, 13);
    //insertRBT(rad, 13);
    //deleteRBT(rad, 13);

    //afisare(rad->getDr()->getDr());
    //std::cout << std::endl;
    //int x = 6;
    //int y = 25;
    afisareInterval(rad, 1, 27);
    */
    int nrOp, a;
    char operatie[10], codOp;



    std::cout << "Introduceti operatie sau '$' pentru Stop: ";

    for (nrOp = 0; std::cin.getline(operatie, 10) && operatie[0] != '$';)
    {
        if (operatie[1] != ' ')
            std::cout << "Date introduse gresit";
        else {

            codOp = operatie[0];
            a = 2;

            while (operatie[a] != ' ' && a < strlen(operatie)) {
                a++;
            }

            int x = std::stoi(std::string(operatie + 2, a - 2));
            int y = 0;

            if (codOp == '6') {

                int b;
                b = a + 1;

                while (operatie[a] != ' ' && a < strlen(operatie)) {
                    a++;
                }

                y = std::stoi(std::string(operatie + a + 1, b - 2));
            }

            switch (codOp) {
                case '1':
                    insertRBT(rad, x);
                    break;

                case '2':
                    deleteRBT(rad, x);
                    break;

                case '3':
                    cautare(rad, x);
                    break;

                case '4':
                    afisaresuccesor(rad, x);
                    break;

                case '5':
                    afisarepredecesor(rad, x);
                    break;

                case '6':
                    afisareInterval(rad, x, y);
                    break;

                default:
                    std::cout << "Numarul nu conrespunde niciunei operatii";
            }
        }
        std::cout << std::endl;
        std::cout << "Introduceti operatie sau '$' pentru Stop: ";
    }


    return 0;
}
