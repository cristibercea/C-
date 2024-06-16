//#include "vector.h"

//void vector::resize(){
//    cap *= 2;
//    Tenant* new_elems = new Tenant[cap];
//    for (int i = 0; i < lg; i++)
//        new_elems[i] = elems[i];
//    delete[] elems;
//    elems = new_elems;
//}
//
//void vector::push_back(const Tenant& tr) {
//    if (lg == cap) { resize(); }
//    elems[lg] = tr;
//    lg++;
//}
//
//std::vector<Tenant> vector::toSTDVector() const {
//    std::vector<Tenant> rez;
//    for (int i = 0; i < lg; i++)
//        rez.push_back(elems[i]);
//    return rez;
//}
//
//void vector::erase(const int poz){
//    lg--;
//    for (int i = poz; i < lg; i++)
//        elems[i] = elems[i+1];
//}

//bool vector::operator==(const vector& ot) const {
//    for (int i = 0; i < lg; i++)
//        if (!(this->elems[i] == ot.elems[i]))
//            return false;
//    return true;
//}
//
//vector& vector::operator=(const vector& ot) {
//    Tenant* nelems = new Tenant[cap];///verificam daca putem aloca memorie(daca nu se poate, se arunca o exceptie, dar macar elems nu s-a sters inca)
//    delete[] elems;
//    cap = ot.cap;
//    lg = ot.lg;
//    elems = nelems;
//    for (int i = 0; i < lg; i++)
//        elems[i] = ot.elems[i];
//    return *this;
//}
//
//MyIterator vector::begin() { return MyIterator(*this, 0);}
//
//MyIterator vector::end() { return MyIterator(*this); }



///iterator
//bool MyIterator::operator!=(const MyIterator& ot) {
//    return poz != ot.poz;
//}
//
//Tenant& MyIterator::operator*() {
//    return v[poz];
//}
//
//MyIterator MyIterator::operator++() {
//    poz++;
//    return *this;
//}
//
//MyIterator MyIterator::operator+(int i) {
//    poz+=i;
//    return *this;
//}
//
//MyIterator MyIterator::operator-(int i) {
//    poz -= i;
//    return *this;
//}
