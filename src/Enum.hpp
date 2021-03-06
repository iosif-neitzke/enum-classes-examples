#ifndef ENUM_HPP_INCLUDED
#define ENUM_HPP_INCLUDED

#include <functional>
#include <set>
#include <algorithm>

template <class T>
class Enum {
  // Predicate for finding the corresponding instance
  struct Enum_Predicate_Corresponds :
    public std::unary_function<const Enum<T>*, bool> {
    
    Enum_Predicate_Corresponds( int Value ): m_value(Value) {}

    bool operator()( const Enum<T>* E ) const {
      return E->Get_Value() == m_value;
    }
    
  private:
    const int m_value;
  };
  
  // Comparison functor for the set of instances
  struct Enum_Ptr_Less :
    public std::binary_function<const Enum<T>*, const Enum<T>*, bool> {
      
    bool operator()( const Enum<T>* E_1 , const Enum<T>* E_2 ) const {
      return E_1->Get_Value() < E_2->Get_Value();
    }
  };
  
public:
  // Compiler-generated copy constructor and operator= are OK.
  // Access to int value
  int Get_Value() const { return m_value; }

  typedef std::set<const Enum<T>*, Enum_Ptr_Less> instances_list;
  typedef typename instances_list::const_iterator const_iterator;

  static int Min() { return ( *s_instances.begin() )->m_value; }
  static int Max() { return ( *s_instances.rbegin() )->m_value; }

  static const Enum<T>* Corresponding_Enum( int Value ) {
    const_iterator it = std::find_if( s_instances.begin() , s_instances.end() ,
				      Enum_Predicate_Corresponds( Value ) );
    return ( it != s_instances.end() ) ? *it : 0;
  }
  
  static bool Is_Valid_Value( int Value ) {
    return Corresponding_Enum( Value ) != 0;
  }

  // Number of elements
  static typename instances_list::size_type size() {return s_instances.size();}

  // Iteration
  static const_iterator begin() { return s_instances.begin(); }
  static const_iterator end() { return s_instances.end(); }
  
protected:
  explicit Enum( int Value ) : m_value(Value) { s_instances.insert(this); }

private:
  int m_value;
  static instances_list s_instances;
};

template <class T>
typename Enum<T>::instances_list Enum<T>::s_instances;

#endif
