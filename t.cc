template <class T>
class A
{
public:
  A<T>();

  T& get();
private:
  T m_elem;
};

class B
{
public:
  B();

  B& operator =(const B&);
};
   

template <class T>
A<T>::A()
{
};

template <class T>
T&
A<T>::get()
{
  return m_elem;
}

B::B()
{
}

B&
B::operator = (const B&a)
{
  return *this;
}

main()
{
  A<int> a;

  int a1 = a.get();
  
  A<B> b;
  B b_b;

  b_b = b.get();
  
}
