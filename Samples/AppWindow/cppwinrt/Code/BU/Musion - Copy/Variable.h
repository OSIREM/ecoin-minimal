/*

Variable - osirem.com
Copyright OSIREM LTD (C) 2016
www.bitolyl.com/osirem bitcoin-office.com ecn.world

This source is proprietary, and cannot be used, in part or in full without
the express permission of the original author. The original author retain the
rights to use, modify, and/or relicense this code without notice.

*/

#ifndef VARIABLE_H
#define VARIABLE_H

#include <vector>
#include <math.h>

#include "MuType.h"

#include <vector>
#include <unordered_map>
#include <functional>
#include <iostream>

#include <boost/any.hpp>

#define ECOIN_TARGET_CURRENT_SPECIFIC_VARTYPES_FLOAT 0
#define ECOIN_TARGET_CURRENT_SPECIFIC_VARTYPES_INT 1
#define ECOIN_TARGET_CURRENT_SPECIFIC_VARTYPES_STRING 2

#if 0
namespace andyg{
template<class...>
struct type_list{};
  
template<class... TYPES>
struct visitor_base
{
    using types = andyg::type_list<TYPES...>;
};
        
struct heterogeneous_container
{
    public:
    heterogeneous_container() = default;
    heterogeneous_container(const heterogeneous_container& _other)
    {
        *this = _other;
    }
    
    heterogeneous_container& operator=(const heterogeneous_container& _other)
    {
        clear();
        clear_functions = _other.clear_functions;
        copy_functions = _other.copy_functions;
        size_functions = _other.size_functions;
        for (auto&& copy_function : copy_functions)
        {
            copy_function(_other, *this);
        }
        return *this;
    }
    
    template<class T>
    void push_back(const T& _t)
    {
        // don't have it yet, so create functions for printing, copying, moving, and destroying
        if (items<T>.find(this) == std::end(items<T>))
        {   
            clear_functions.emplace_back([](heterogeneous_container& _c){items<T>.erase(&_c);});
            
            // if someone copies me, they need to call each copy_function and pass themself
            copy_functions.emplace_back([](const heterogeneous_container& _from, heterogeneous_container& _to)
                                        {
                                            items<T>[&_to] = items<T>[&_from];
                                        });
            size_functions.emplace_back([](const heterogeneous_container& _c){return items<T>[&_c].size();});
        }
        items<T>[this].push_back(_t);
    }
    
    void clear()
    {
        for (auto&& clear_func : clear_functions)
        {
            clear_func(*this);
        }
    }
    
    template<class T>
    size_t number_of() const
    {
        auto iter = items<T>.find(this);
        if (iter != items<T>.cend())
            return items<T>[this].size();
        return 0;
    }
    
    size_t size() const
    {
        size_t sum = 0;
        for (auto&& size_func : size_functions)
        {
            sum += size_func(*this);
        }
        // gotta be careful about this overflowing
        return sum;
    }
    
    ~heterogeneous_container()
    {
        clear();
    }   
    
    template<class T>
    void visit(T&& visitor)
    {
        visit_impl(visitor, typename std::decay_t<T>::types{});
    }
    
    private:
    template<class T>
    static std::unordered_map<const heterogeneous_container*, std::vector<T>> items;
    
    template<class T, class U>
    using visit_function = decltype(std::declval<T>().operator()(std::declval<U&>()));
    template<class T, class U>
    static constexpr bool has_visit_v = std::experimental::is_detected<visit_function, T, U>::value;
      
    template<class T, template<class...> class TLIST, class... TYPES>
    void visit_impl(T&& visitor, TLIST<TYPES...>)
    {
        //(..., visit_impl_help<std::decay_t<T>, TYPES>(visitor));
    }
    
    template<class T, class U>
    void visit_impl_help(T& visitor)
    {
        static_assert(has_visit_v<T, U>, "Visitors must provide a visit function accepting a reference for each type");
        for (auto&& element : items<U>[this])
        {
            visitor(element);
        }
    }
    
    std::vector<std::function<void(heterogeneous_container&)>> clear_functions;
    std::vector<std::function<void(const heterogeneous_container&, heterogeneous_container&)>> copy_functions;
    std::vector<std::function<size_t(const heterogeneous_container&)>> size_functions;
};

template<class T>
std::unordered_map<const heterogeneous_container*, std::vector<T>> heterogeneous_container::items;
}

struct print_visitor : andyg::visitor_base<int, double, char, std::string>
{
    template<class T>
    void operator()(T& _in)
    {
        std::cout << _in << " ";
    }
};
struct my_visitor : andyg::visitor_base<int, double>
{
    template<class T>
    void operator()(T& _in) 
    {
        _in +=_in;
    }
};

int main()
{
    auto print_container = [](andyg::heterogeneous_container& _in){_in.visit(print_visitor{}); std::cout << std::endl;};
    andyg::heterogeneous_container c;
    c.push_back('a');
    c.push_back(1);
    c.push_back(2.0);
    c.push_back(3);
    c.push_back(std::string{"foo"});
    std::cout << "c: ";
    print_container(c);
    andyg::heterogeneous_container c2 = c;
    std::cout << "c2: ";
    print_container(c2);
    c.clear();
    std::cout << "c after clearing c: ";
    c.visit(print_visitor{});
    std::cout << std::endl;
    std::cout << "c2 after clearing c: ";
    print_container(c2);
    c = c2;
    std::cout << "c after assignment to c2: ";
    print_container(c);
    my_visitor v;
    
    std::cout << "Visiting c (should double ints and doubles)\n";
    c.visit(v);
    std::cout << "c: ";
    print_container(c);
    
    struct string_visitor : andyg::visitor_base<std::string>
    {
        void operator()(std::string& _s) 
        {
            // append bar to all strings
            _s += "bar";
        }
    };
    std::cout << "Visiting c again (should append \"bar\" to all strings)\n";
    c.visit(string_visitor{});
    std::cout << "c: ";
    print_container(c);
    std::cout << "Size of c: " << c.size() << std::endl;
    std::cout << "Number of integers in c: " << c.number_of<int>() << std::endl;
}

#include <iostream>
#include <string>
#include <vector>
#include <cassert>

// TypeEraser.h

template <std::size_t Tsize, std::size_t Talign>
struct TypeEraser {
public:
    template <class T>
    TypeEraser(T *typeTag);                                             // (1)

    TypeEraser(TypeEraser &&other);

    ~TypeEraser();

    TypeEraser(TypeEraser const &) = delete;
    TypeEraser &operator = (TypeEraser const &) = delete;

    template <class T>
    T &get();

private:
    void (*_deleter)(char *s);                                          // (2)
    void (*_mover)(TypeEraser &self, TypeEraser &&other);               //
    alignas(Talign) char _storage[Tsize];                               //
};

template <class Tarchetype>
using TypeEraserFor = TypeEraser<                                       // (3)
    sizeof(Tarchetype),                                                 //
    alignof(Tarchetype)                                                 //
>;

template <std::size_t Tsize, std::size_t Talign>
template <class T>
TypeEraser<Tsize, Talign>::TypeEraser(T*)
: _deleter([](char *s) {
    reinterpret_cast<T*>(s)->~T();                                      // (4)
})
, _mover([](TypeEraser &self, TypeEraser &&other) {
    new (self._storage) T(std::move(other.get<T>()));
}) {
    static_assert(sizeof(T) == Tsize, "Wrong object size !");           // (3)
    static_assert(alignof(T) == Talign, "Wrong object alignment !");    //
    new (_storage) T;
}

template <std::size_t Tsize, std::size_t Talign>
template <class T>
T &TypeEraser<Tsize, Talign>::get() {
    #pragma GCC diagnostic ignored "-Wstrict-aliasing"
    return *reinterpret_cast<T*>(_storage);                             // (4)
    #pragma GCC diagnostic pop
}

template <std::size_t Tsize, std::size_t Talign>
TypeEraser<Tsize, Talign>::TypeEraser(TypeEraser &&other)
: _deleter(other._deleter)
, _mover(other._mover) {
    _mover(*this, std::move(other));
}


template <std::size_t Tsize, std::size_t Talign>
TypeEraser<Tsize, Talign>::~TypeEraser() {
    _deleter(_storage);
}

// MultiVector.h

struct MultiVector {
    template <class T>
    std::vector<T> &all();

    template <class T, class... Args>
    T &emplace(Args &&... args);

    template <class T>
    T &add(T &&orig);

private:
    static std::size_t _tIdCounter;

    template <class T>
    static std::size_t typeId();

    std::vector<TypeEraserFor<std::vector<char>>> subVectors;
};

template <class T>
std::size_t MultiVector::typeId() {                                     // (5)
    static std::size_t id = _tIdCounter++;
    return id;
}

template <class T>
std::vector<T> &MultiVector::all() {
    std::size_t tId = typeId<T>();
    assert(tId <= subVectors.size());
    if(tId == subVectors.size()) {
        subVectors.emplace_back(static_cast<std::vector<T>*>(nullptr)); // (1)
    }
    return subVectors[tId].get<std::vector<T>>();
}

template <class T, class... Args>
T &MultiVector::emplace(Args &&... args) {
    auto &allT = all<T>();
    allT.emplace_back(std::forward<Args>(args)...);
    return allT.back();
}

template <class T>
T &MultiVector::add(T &&orig) {
    auto &allT = all<std::remove_reference_t<T>>();
    allT.push_back(std::forward<T>(orig));
    return allT.back();
}

// MultiVector.cpp

std::size_t MultiVector::_tIdCounter = 0u;

int mainy()
{    
    MultiVector mv;

    for(int i = 0; i < 10; ++i)
        mv.add(i);

    mv.emplace<std::string>("Hello");
    mv.emplace<std::string>("World");
    mv.emplace<std::string>("!");

    for(auto &i : mv.all<int>())
        std::cout << i << ' ';
    std::cout << '\n';
    for(auto &s : mv.all<std::string>())
        std::cout << s << ' ';
    std::cout << '\n';

    assert(mv.all<float>().empty());

    return 0;
}
#endif

namespace ecoin
{
    class Class;

	enum Variable_Precision
		{
		MuVar_Start,
		MuVar_Float,
		MuVar_Float2,
		MuVar_Float3,
		MuVar_Float4,
		MuVar_uInt,
		MuVar_Int,
		MuVar_Int2,
		MuVar_Int3,
		MuVar_Int4,
		MuVar_Bool,
		MuVar_Char,
		MuVar_String,
		MuVar_Full,
		MuVar_Total
		};

	enum Variable_Action
		{
		MuAct_Start,
		MuAct_Random,
		MuAct_RandInt,
		MuAct_Reset,
		MuAct_Inc,
		MuAct_Dec,
		MuAct_Double,
        MuAct_Finish,
		MuAct_Total
		};

    typedef struct
    {
        float m_X;
        float m_Y;
        float m_Z;
    }float3;

    typedef struct
    {
        float m_X;
        float m_Y;
        float m_Z;
        float m_W;
    }float4;

	class VartemplateInterface
		{
		virtual bool someFunction() { return true; }
		};

	class Variable : MuType
		{
		public:
            Variable()
                {
                acClear();
                };
			Variable(std::string f_Stg, uint f_CodeType);
            Variable(uint f_PrecType) : MuType(MuTYPE_Variable), m_MxName("IdentVar"), m_CodeType(0), m_PrecType(f_PrecType)
                {
                m_Action = MuAct_Start;
                };
            Variable(std::string f_Stg, uint f_CodeType, uint f_PrecType) : MuType(MuTYPE_Variable), m_MxName(f_Stg), m_CodeType(f_CodeType), m_PrecType(f_PrecType)
				{
                m_Action = MuAct_Start;
				};
            ~Variable()
                {
                acClear();
                
                m_Action = MuAct_Finish;
                };

            void acClear(void)
                {
                m_Action = MuAct_Start;
                m_MxName.clear();
                m_PrecType = 0;
                m_CodeType = 0;
                m_Variable = 0;
                }

			boost::any m_Var;

            std::shared_ptr<ecoin::Class> m_LinkClass;

            boost::any get_Value(void);
			void set_Value(boost::any f_Value);

            std::shared_ptr<Variable> CloneVar(std::shared_ptr<Variable> v1);

            /*Variable* getPtr(void)
				{
				return this;
				}*/

            /*Variable* operator=(const Variable* v)
				{
				m_Var = v->m_Var;
				}

            std::shared_ptr<Variable> operator=(const std::shared_ptr<Variable> v)
				{
				m_Var = v->m_Var;
				}

            void operator=(const Variable &v)
				{
				m_Var = v.m_Var;
				}*/

			uint m_PrecType;
			uint m_CodeType;

			uint m_Variable;

			std::string m_MxName;
            std::vector<std::string> m_vec_NameCall;

			unsigned char m_Action;
		};

	extern int agFind_VarType(std::string f_String);

    extern int agFind_CurrentSpec_VarType(std::string f_String);

	extern std::shared_ptr<Variable> av_Identity(uint f_PrecType);

    std::shared_ptr<Variable> operator+ (const std::shared_ptr<Variable>& v1, const std::shared_ptr<Variable>& v2);
    std::shared_ptr<Variable> operator- (const std::shared_ptr<Variable>& v1, const std::shared_ptr<Variable>& v2);
    std::shared_ptr<Variable> operator* (const std::shared_ptr<Variable>& v1, const std::shared_ptr<Variable>& v2);
    std::shared_ptr<Variable> operator/ (const std::shared_ptr<Variable>& v1, const std::shared_ptr<Variable>& v2);
    std::shared_ptr<Variable> operator<< (const std::shared_ptr<Variable>& v1, const std::shared_ptr<Variable>& v2);
    std::shared_ptr<Variable> operator>> (const std::shared_ptr<Variable>& v1, const std::shared_ptr<Variable>& v2);
    std::shared_ptr<Variable> operator% (const std::shared_ptr<Variable>& v1, const std::shared_ptr<Variable>& v2);
    bool operator==(const std::shared_ptr<Variable>& v1, const std::shared_ptr<Variable>& v2);
    bool operator!=(const std::shared_ptr<Variable>& v1, const std::shared_ptr<Variable>& v2);
}


#endif