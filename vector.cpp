#include <iostream>
#include <initializer_list>


template <typename T>
class Vector
{
public:
    Vector();
    Vector(const Vector<T>&);
    Vector(Vector<T>&&);
    Vector(size_t,T);
    Vector(T);
    Vector(std::initializer_list<T>);
    ~Vector();
    Vector& operator=(const Vector<T>&);
    Vector& operator=(Vector<T>&&);
    void insert(int index,T value);
    void push_back(T value);
    void erase(int value);
    void shrink_to_fit();
    void new_capacity();
    size_t capacity();
    void pop_back();
    T at(T index);
    size_t size();
    void print();
    void clear();
    T empty();
private:
    size_t m_capacity;
    size_t m_size;
    T* m_item;
};

int main()
{
   //Vector<int> v;// default
   //Vector<int> r = v;
   //r = v;//copy
   //v = std::move(r);
   //Vector<int> d(std::move(v)); //move
   //Vector<int> e = {5,8,9,9};//list
   //e.insert(1,7);//insert()
   //Vector<int> m = (9);//count
   //Vector<std::string> e = {4,"hello"};// cap  value
   //e.clear();//clear()
   //e.push_back(99);//push_back(x)
   //std::cout << e.at(5) << std::endl; // at()
   //e.shrink_to_fit();//shrink to fit
   //int i = 0;
   //e.erase(i); //erase(x)
   //e.erase(2);
   //e.pop_back();//pop_back()
   //e.clear();//clear()
   //e.print();//print()
   //std::cout << std::endl;
   //std::cout << e.empty() << " empty " << std::endl;//empty()
   //std::cout << std::endl;
   //std::cout << e.capacity() << " capacity " << std::endl; // capacity
   //std::cout << e.size() <<" size " <<  std::endl;// sieze()
}

template <typename T>
void Vector<T>::shrink_to_fit()
{
    if(m_size != m_capacity) {
        m_capacity = m_size;
    T* new_item = new T[m_capacity];
    for(int i = 0; i < m_size; ++i) {
    new_item[i] = m_item[i];
    }
    delete[] m_item;
    m_item = new_item;
    new_item = nullptr;
    }
   }
template <typename T>
T Vector<T>::at(T index)
{
    if(index > m_size) {
        return - 1;
    }
    for(int i = 0; i < m_size; ++i) {
        if(i == index) {
            return m_item[i];
        }
    }
    return - 1;
}

template <typename T>
void Vector<T>::erase(int value)
{
    if(value > m_size) {
    return;
    }
    if(m_size == 0) {
    m_capacity = 0;
    return;
    }
    T* new_item = new T[m_capacity];
    int j = 0;
    for(int i = 0; i < m_size; ++i) {
    if(i == value) {
    ++i;
    }
    new_item[j] = m_item[i];
    ++j;
    }
    if(m_size <= 1 ) {
    m_capacity = 0;
    }
    --m_size;
    delete[] m_item;
    m_item = new_item;
    new_item = nullptr;
}
template <typename T>
void Vector<T>::new_capacity()
{
    if(m_size == m_capacity){
    m_capacity += m_capacity;
    T* new_item = new T[m_capacity];
    for(int i = 0; i < m_size; ++i) {
    new_item[i] = m_item[i];
    }
    delete[] m_item;
    m_item = new_item;
    new_item = nullptr;
    }
}
template <typename T>
void Vector<T>::insert(int index,T value)
{
    if(m_size == m_capacity){
    new_capacity();
    }
    T* new_cap = new T[m_capacity];
    int j = 0;
    for(int i = 0;i < m_size;++i) {
    j = i;
    if(j == index) {
    new_cap[j] = value;
    ++m_size;
    ++j;
    }
    new_cap[j] = m_item[i];
    }
    delete[] m_item;
    m_item = new_cap;
    new_cap = nullptr;
}
template<typename T>
T Vector<T>::empty()
{
    return !m_size;
}

template<typename T>
void Vector<T>::pop_back()
{
    --m_size;
}

template<typename T>
void Vector<T>::push_back(T value)
{
    if(m_size == m_capacity) {
    new_capacity();
    }
    m_item[m_size++] = value;
}

template<typename T>
void Vector<T>::clear()
{
    delete[] m_item;
    m_capacity = 0;
    m_size = 0;
    m_item = new T[m_capacity];
}

template<typename T>
void Vector<T>::print()
{
    for(int i = 0; i < m_size; ++i) {
    std::cout << m_item[i] << " " ;
    }
}

template<typename T>
size_t Vector<T>::size()
{
    return m_size;
}

template<typename T>
size_t Vector<T>::capacity() {
    return m_capacity;
}

template <typename T>
Vector<T>::Vector() :
    m_capacity{1},
    m_size{},
    m_item{}
{}

template <typename T>
Vector<T>::Vector(const Vector<T>& cmp) :
    m_capacity(cmp.m_capacity),
    m_size(cmp.m_size),
    m_item{}
{
    m_item = new T[m_capacity];
    for(int i = 0; i < m_size; ++i) {
        m_item[i] = cmp.m_item[i];
    }
}

template <typename T>
Vector<T>::Vector(Vector<T>&& tmp) :
    m_capacity(tmp.m_capacity),
    m_size(tmp.m_size),
    m_item(tmp.m_item)
{
    tmp.m_capacity = 0;
    tmp.m_size = 0;
    tmp.m_item = nullptr;
}
template <typename T>
Vector<T>::Vector(size_t cap,T value) :
    m_capacity(cap),
    m_size(cap),
    m_item(new T[m_capacity])
{
    for(int i = 0; i < m_size; ++i) {
    m_item[i] = value;
    }
}

template <typename T>
Vector<T>::Vector(T count) :
    m_capacity(count),
    m_size(count),
    m_item(new T[m_capacity])
{}
template <typename T>
Vector<T>::Vector(std::initializer_list<T> init) :
    m_capacity(init.size()),
    m_size(m_capacity),
    m_item(new T[m_capacity])
{
    int i = 0;
    for(auto itr = init.begin(); itr != init.end(); ++itr) {
        m_item[i++] = *itr;
    }
}

template <typename T>
Vector<T>::~Vector()
{
    if(m_item) {
        delete[] m_item;
    }
}

template <typename T>
Vector<T>& Vector<T>::operator=(const Vector<T>& cmp)
{
    if(this == &cmp) {
        return *this;
    }
    if(this->m_item) {
        delete[] m_item;
    }
    m_capacity = cmp.m_capacity;
    m_size = cmp.m_size;
    m_item = new T[m_capacity];
    for(int i = 0; i < m_size; ++i) {
        m_item[i] = cmp.m_item[i];
    }
    return *this;
}
template <typename T>
Vector<T>& Vector<T>::operator=(Vector<T>&& mov)
{
    std::swap(m_capacity, mov.m_capacity);
    std::swap(m_size, mov.m_size);
    std::swap(m_item, mov.m_item);
    return *this;
}
