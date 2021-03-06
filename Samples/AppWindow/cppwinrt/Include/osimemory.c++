/*

osimemory - osirem.com
Copyright OSIREM LTD (C) 2016
www.bitolyl.com/osirem bitcoin-office.com ecn.world

This source is proprietary, and cannot be used, in part or in full without
the express permission of the original author. The original author retain the
rights to use, modify, and/or relicense this code without notice.

*/

#pragma once
#ifndef _MEMORY_
#define _MEMORY_
#include <yvals_core.h>
#if _STL_COMPILER_PREPROCESSOR
#include <exception>
#include <iosfwd>
#include <type_traits>
#include <typeinfo>
#include <xmemory>

#if _HAS_CXX20
#include <atomic>
#endif

#pragma pack(push, _CRT_PACKING)
#pragma warning(push, _STL_WARNING_LEVEL)
#pragma warning(disable : _STL_DISABLED_WARNINGS)
_STL_DISABLE_CLANG_WARNINGS
#pragma push_macro("new")
#undef new

_STD_BEGIN
// FUNCTION TEMPLATE uninitialized_copy_n
#if _HAS_IF_CONSTEXPR
template <class _InIt, class _Diff, class _NoThrowFwdIt>
_NoThrowFwdIt uninitialized_copy_n(const _InIt _First, const _Diff _Count_raw, _NoThrowFwdIt _Dest) {
    // copy [_First, _First + _Count) to [_Dest, ...)
    _Algorithm_int_t<_Diff> _Count = _Count_raw;
    if (0 < _Count) {
        auto _UFirst = _Get_unwrapped_n(_First, _Count);
        auto _UDest  = _Get_unwrapped_n(_Dest, _Count);
        if constexpr (_Ptr_copy_cat<decltype(_UFirst), decltype(_UDest)>::_Really_trivial) {
            _UDest = _Copy_memmove(_UFirst, _UFirst + _Count, _UDest);
        } else {
            _Uninitialized_backout<decltype(_UDest)> _Backout{_UDest};
            for (; 0 < _Count; --_Count, (void) ++_UFirst) {
                _Backout._Emplace_back(*_UFirst);
            }

            _UDest = _Backout._Release();
        }

        _Seek_wrapped(_Dest, _UDest);
    }

    return _Dest;
}
#else // ^^^ _HAS_IF_CONSTEXPR / !_HAS_IF_CONSTEXPR vvv
template <class _InIt, class _Diff, class _NoThrowFwdIt>
_NoThrowFwdIt _Uninitialized_copy_n_unchecked2(_InIt _First, _Diff _Count, const _NoThrowFwdIt _Dest,
    false_type) { // copy [_First, _First + _Count) to [_Dest, ...), no special optimization
    _Uninitialized_backout<_NoThrowFwdIt> _Backout{_Dest};
    for (; 0 < _Count; --_Count, (void) ++_First) {
        _Backout._Emplace_back(*_First);
    }

    return _Backout._Release();
}

template <class _InIt, class _Diff, class _NoThrowFwdIt>
_NoThrowFwdIt _Uninitialized_copy_n_unchecked2(const _InIt _First, const _Diff _Count, const _NoThrowFwdIt _Dest,
    true_type) { // copy [_First, _First + _Count) to [_Dest, ...), memmove optimization
    return _Copy_memmove(_First, _First + _Count, _Dest);
}

template <class _InIt, class _Diff, class _NoThrowFwdIt>
_NoThrowFwdIt uninitialized_copy_n(const _InIt _First, const _Diff _Count_raw, _NoThrowFwdIt _Dest) {
    // copy [_First, _First + _Count) to [_Dest, ...)]
    _Algorithm_int_t<_Diff> _Count = _Count_raw;
    if (0 < _Count) {
        auto _UFirst = _Get_unwrapped_n(_First, _Count);
        auto _UDest  = _Get_unwrapped_n(_Dest, _Count);
        _Seek_wrapped(_Dest, _Uninitialized_copy_n_unchecked2(_UFirst, _Count, _UDest,
                                 bool_constant<_Ptr_copy_cat<decltype(_UFirst), decltype(_UDest)>::_Really_trivial>{}));
    }

    return _Dest;
}
#endif // _HAS_IF_CONSTEXPR

#if _HAS_CXX17
// FUNCTION TEMPLATE uninitialized_move
template <class _InIt, class _NoThrowFwdIt>
_NoThrowFwdIt uninitialized_move(const _InIt _First, const _InIt _Last, _NoThrowFwdIt _Dest) {
    // move [_First, _Last) to raw [_Dest, ...)
    _Adl_verify_range(_First, _Last);
    const auto _UFirst = _Get_unwrapped(_First);
    const auto _ULast  = _Get_unwrapped(_Last);
    const auto _UDest  = _Get_unwrapped_n(_Dest, _Idl_distance<_InIt>(_UFirst, _ULast));
    _Seek_wrapped(_Dest, _Uninitialized_move_unchecked(_UFirst, _ULast, _UDest));
    return _Dest;
}

// FUNCTION TEMPLATE uninitialized_move_n
template <class _InIt, class _Diff, class _NoThrowFwdIt>
pair<_InIt, _NoThrowFwdIt> uninitialized_move_n(_InIt _First, const _Diff _Count_raw, _NoThrowFwdIt _Dest) {
    // move [_First, _First + _Count) to [_Dest, ...)
    _Algorithm_int_t<_Diff> _Count = _Count_raw;
    if (0 < _Count) {
        auto _UFirst = _Get_unwrapped_n(_First, _Count);
        auto _UDest  = _Get_unwrapped_n(_Dest, _Count);
        if constexpr (_Ptr_move_cat<decltype(_UFirst), decltype(_UDest)>::_Really_trivial) {
            _UDest = _Copy_memmove(_UFirst, _UFirst + _Count, _UDest);
            _UFirst += _Count;
        } else {
            _Uninitialized_backout<decltype(_UDest)> _Backout{_UDest};
            for (; 0 < _Count; --_Count, (void) ++_UFirst) {
                _Backout._Emplace_back(_STD move(*_UFirst));
            }

            _UDest = _Backout._Release();
        }

        _Seek_wrapped(_Dest, _UDest);
        _Seek_wrapped(_First, _UFirst);
    }

    return {_First, _Dest};
}
#endif // _HAS_CXX17

// FUNCTION TEMPLATE uninitialized_fill_n
#if _HAS_IF_CONSTEXPR
template <class _NoThrowFwdIt, class _Diff, class _Tval>
_NoThrowFwdIt uninitialized_fill_n(_NoThrowFwdIt _First, const _Diff _Count_raw, const _Tval& _Val) {
    // copy _Count copies of _Val to raw _First
    _Algorithm_int_t<_Diff> _Count = _Count_raw;
    if (0 < _Count) {
        auto _UFirst = _Get_unwrapped_n(_First, _Count);
        if constexpr (_Fill_memset_is_safe<_Unwrapped_n_t<const _NoThrowFwdIt&>, _Tval>) {
            _CSTD memset(_UFirst, static_cast<unsigned char>(_Val), _Count);
            _UFirst += _Count;
        } else {
            _Uninitialized_backout<_Unwrapped_n_t<const _NoThrowFwdIt&>> _Backout{_UFirst};
            for (; 0 < _Count; --_Count) {
                _Backout._Emplace_back(_Val);
            }

            _UFirst = _Backout._Release();
        }

        _Seek_wrapped(_First, _UFirst);
    }

    return _First;
}
#else // ^^^ _HAS_IF_CONSTEXPR // !_HAS_IF_CONSTEXPR vvv
template <class _NoThrowFwdIt, class _Diff, class _Tval>
_NoThrowFwdIt _Uninitialized_fill_n_unchecked1(
    const _NoThrowFwdIt _First, _Diff _Count, const _Tval& _Val, false_type) {
    // copy _Count copies of _Val to raw _First, no special optimization
    _Uninitialized_backout<_NoThrowFwdIt> _Backout{_First};
    for (; 0 < _Count; --_Count) {
        _Backout._Emplace_back(_Val);
    }

    return _Backout._Release();
}

template <class _NoThrowFwdIt, class _Diff, class _Tval>
_NoThrowFwdIt _Uninitialized_fill_n_unchecked1(
    const _NoThrowFwdIt _First, const _Diff _Count, const _Tval& _Val, true_type) {
    // copy _Count copies of _Val to raw _First, memset optimization
    _CSTD memset(_First, static_cast<unsigned char>(_Val), _Count);
    return _First + _Count;
}

template <class _NoThrowFwdIt, class _Diff, class _Tval>
_NoThrowFwdIt uninitialized_fill_n(_NoThrowFwdIt _First, const _Diff _Count_raw, const _Tval& _Val) {
    // copy _Count copies of _Val to raw _First
    _Algorithm_int_t<_Diff> _Count = _Count_raw;
    if (0 < _Count) {
        auto _UFirst = _Get_unwrapped_n(_STD move(_First), _Count);
        _Seek_wrapped(_First, _Uninitialized_fill_n_unchecked1(_STD move(_UFirst), _Count, _Val,
                                  bool_constant<_Fill_memset_is_safe<_Unwrapped_t<_NoThrowFwdIt>, _Tval>>{}));
    }

    return _First;
}
#endif // _HAS_IF_CONSTEXPR

#if _HAS_CXX20
template <class _Ty, class... _Types>
auto construct_at(_Ty* const _Location, _Types&&... _Args) noexcept(noexcept(::new (const_cast<void*>(
    static_cast<const volatile void*>(_Location))) _Ty(_STD forward<_Types>(_Args)...))) // strengthened
    -> decltype(
        ::new (const_cast<void*>(static_cast<const volatile void*>(_Location))) _Ty(_STD forward<_Types>(_Args)...)) {
    return ::new (const_cast<void*>(static_cast<const volatile void*>(_Location))) _Ty(_STD forward<_Types>(_Args)...);
}

namespace ranges {
    using _STD construct_at;
} // namespace ranges
#endif // _HAS_CXX20

#if _HAS_CXX17
// FUNCTION TEMPLATE destroy_at
template <class _Ty>
void destroy_at(_Ty* const _Location) noexcept /* strengthened */ {
    _Location->~_Ty();
}

// FUNCTION TEMPLATE destroy
template <class _NoThrowFwdIt>
void destroy(const _NoThrowFwdIt _First, const _NoThrowFwdIt _Last) { // destroy all elements in [_First, _Last)
    _Adl_verify_range(_First, _Last);
    _Destroy_range(_Get_unwrapped(_First), _Get_unwrapped(_Last));
}

// FUNCTION TEMPLATE destroy_n
template <class _NoThrowFwdIt, class _Diff>
_NoThrowFwdIt destroy_n(_NoThrowFwdIt _First, const _Diff _Count_raw) {
    // destroy all elements in [_First, _First + _Count)
    _Algorithm_int_t<_Diff> _Count = _Count_raw;
    if (0 < _Count) {
        auto _UFirst = _Get_unwrapped_n(_First, _Count);
        if constexpr (is_trivially_destructible_v<_Iter_value_t<_NoThrowFwdIt>>) {
            _STD advance(_UFirst, _Count);
        } else {
            do {
                _Destroy_in_place(*_UFirst);
                ++_UFirst;
                --_Count;
            } while (0 < _Count);
        }

        _Seek_wrapped(_First, _UFirst);
    }

    return _First;
}

// FUNCTION TEMPLATE uninitialized_default_construct
template <class _NoThrowFwdIt>
void uninitialized_default_construct(const _NoThrowFwdIt _First, const _NoThrowFwdIt _Last) {
    // default-initialize all elements in [_First, _Last)
    using _Ty = _Iter_value_t<_NoThrowFwdIt>;
    _Adl_verify_range(_First, _Last);
    if constexpr (!is_trivially_default_constructible_v<_Ty>) {
        const auto _ULast = _Get_unwrapped(_Last);
        _Uninitialized_backout _Backout{_Get_unwrapped(_First)};
        for (; _Backout._Last != _ULast; ++_Backout._Last) {
            ::new (static_cast<void*>(_Unfancy(_Backout._Last))) _Ty;
        }

        _Backout._Release();
    }
}

// FUNCTION TEMPLATE uninitialized_default_construct_n
template <class _NoThrowFwdIt, class _Diff>
_NoThrowFwdIt uninitialized_default_construct_n(_NoThrowFwdIt _First, const _Diff _Count_raw) {
    // default-initialize all elements in [_First, _First + _Count_raw)
    using _Ty                      = _Iter_value_t<_NoThrowFwdIt>;
    _Algorithm_int_t<_Diff> _Count = _Count_raw;
    if (0 < _Count) {
        if constexpr (is_trivially_default_constructible_v<_Ty>) {
            _STD advance(_First, _Count);
        } else {
            _Uninitialized_backout _Backout{_Get_unwrapped_n(_First, _Count)};
            for (; 0 < _Count; ++_Backout._Last, (void) --_Count) {
                ::new (static_cast<void*>(_Unfancy(_Backout._Last))) _Ty;
            }

            _Seek_wrapped(_First, _Backout._Release());
        }
    }

    return _First;
}

// FUNCTION TEMPLATE uninitialized_value_construct
template <class _NoThrowFwdIt>
void uninitialized_value_construct(const _NoThrowFwdIt _First, const _NoThrowFwdIt _Last) {
    // value-initialize all elements in [_First, _Last)
    _Adl_verify_range(_First, _Last);
    const auto _UFirst = _Get_unwrapped(_First);
    const auto _ULast  = _Get_unwrapped(_Last);
    if constexpr (_Use_memset_value_construct_v<_Unwrapped_t<const _NoThrowFwdIt&>>) {
        _Zero_range(_UFirst, _ULast);
    } else {
        _Uninitialized_backout _Backout{_UFirst};
        while (_Backout._Last != _ULast) {
            _Backout._Emplace_back();
        }

        _Backout._Release();
    }
}

// FUNCTION TEMPLATE uninitialized_value_construct_n
template <class _NoThrowFwdIt, class _Diff>
_NoThrowFwdIt uninitialized_value_construct_n(_NoThrowFwdIt _First, const _Diff _Count_raw) {
    // value-initialize all elements in [_First, _First + _Count_raw)
    _Algorithm_int_t<_Diff> _Count = _Count_raw;
    if (0 < _Count) {
        _Seek_wrapped(_First, _Uninitialized_value_construct_n_unchecked1(_Get_unwrapped_n(_First, _Count), _Count));
    }

    return _First;
}

#endif // _HAS_CXX17


#if _HAS_DEPRECATED_RAW_STORAGE_ITERATOR
// CLASS TEMPLATE raw_storage_iterator
template <class _OutIt, class _Ty>
class _CXX17_DEPRECATE_RAW_STORAGE_ITERATOR raw_storage_iterator { // wrap stores to raw buffer as output iterator
public:
    using iterator_category = output_iterator_tag;
    using value_type        = void;
    using difference_type   = void;
    using pointer           = void;
    using reference         = void;

    explicit raw_storage_iterator(_OutIt _First) : _Next(_First) {}

    _NODISCARD raw_storage_iterator& operator*() { // pretend to return designated value
        return *this;
    }

    raw_storage_iterator& operator=(const _Ty& _Val) { // construct value designated by stored iterator
        _Construct_in_place(*_Next, _Val);
        return *this;
    }

    raw_storage_iterator& operator=(_Ty&& _Val) { // construct value designated by stored iterator
        _Construct_in_place(*_Next, _STD move(_Val));
        return *this;
    }

    raw_storage_iterator& operator++() {
        ++_Next;
        return *this;
    }

    raw_storage_iterator operator++(int) {
        raw_storage_iterator _Ans = *this;
        ++_Next;
        return _Ans;
    }

    _NODISCARD _OutIt base() const {
        return _Next;
    }

private:
    _OutIt _Next;
};
#endif // _HAS_DEPRECATED_RAW_STORAGE_ITERATOR


#if _HAS_AUTO_PTR_ETC
// CLASS TEMPLATE auto_ptr
template <class _Ty>
class auto_ptr;

template <class _Ty>
struct auto_ptr_ref { // proxy reference for auto_ptr copying
    explicit auto_ptr_ref(_Ty* _Right) : _Ref(_Right) {}

    _Ty* _Ref; // generic pointer to auto_ptr ptr
};

template <class _Ty>
class auto_ptr { // wrap an object pointer to ensure destruction
public:
    using element_type = _Ty;

    explicit auto_ptr(_Ty* _Ptr = nullptr) noexcept : _Myptr(_Ptr) {}

    auto_ptr(auto_ptr& _Right) noexcept : _Myptr(_Right.release()) {}

    auto_ptr(auto_ptr_ref<_Ty> _Right) noexcept {
        _Ty* _Ptr   = _Right._Ref;
        _Right._Ref = nullptr; // release old
        _Myptr      = _Ptr; // reset this
    }

    template <class _Other>
    operator auto_ptr<_Other>() noexcept { // convert to compatible auto_ptr
        return auto_ptr<_Other>(*this);
    }

    template <class _Other>
    operator auto_ptr_ref<_Other>() noexcept { // convert to compatible auto_ptr_ref
        _Other* _Cvtptr = _Myptr; // test implicit conversion
        auto_ptr_ref<_Other> _Ans(_Cvtptr);
        _Myptr = nullptr; // pass ownership to auto_ptr_ref
        return _Ans;
    }

    template <class _Other>
    auto_ptr& operator=(auto_ptr<_Other>& _Right) noexcept {
        reset(_Right.release());
        return *this;
    }

    template <class _Other>
    auto_ptr(auto_ptr<_Other>& _Right) noexcept : _Myptr(_Right.release()) {}

    auto_ptr& operator=(auto_ptr& _Right) noexcept {
        reset(_Right.release());
        return *this;
    }

    auto_ptr& operator=(auto_ptr_ref<_Ty> _Right) noexcept {
        _Ty* _Ptr   = _Right._Ref;
        _Right._Ref = 0; // release old
        reset(_Ptr); // set new
        return *this;
    }

    ~auto_ptr() noexcept {
        delete _Myptr;
    }

    _NODISCARD _Ty& operator*() const noexcept {
#if _ITERATOR_DEBUG_LEVEL == 2
        _STL_VERIFY(_Myptr, "auto_ptr not dereferenceable");
#endif // _ITERATOR_DEBUG_LEVEL == 2

        return *get();
    }

    _NODISCARD _Ty* operator->() const noexcept {
#if _ITERATOR_DEBUG_LEVEL == 2
        _STL_VERIFY(_Myptr, "auto_ptr not dereferenceable");
#endif // _ITERATOR_DEBUG_LEVEL == 2

        return get();
    }

    _NODISCARD _Ty* get() const noexcept {
        return _Myptr;
    }

    _Ty* release() noexcept {
        _Ty* _Tmp = _Myptr;
        _Myptr    = nullptr;
        return _Tmp;
    }

    void reset(_Ty* _Ptr = nullptr) noexcept { // destroy designated object and store new pointer
        if (_Ptr != _Myptr) {
            delete _Myptr;
        }

        _Myptr = _Ptr;
    }

private:
    _Ty* _Myptr; // the wrapped object pointer
};

template <>
class auto_ptr<void> {
public:
    using element_type = void;
};
#endif // _HAS_AUTO_PTR_ETC


// CLASS bad_weak_ptr
class bad_weak_ptr : public exception { // exception type for invalid use of expired weak_ptr object
public:
    bad_weak_ptr() noexcept {}

    _NODISCARD virtual const char* __CLR_OR_THIS_CALL what() const noexcept override {
        // return pointer to message string
        return "bad_weak_ptr";
    }
};

[[noreturn]] inline void _Throw_bad_weak_ptr() {
    _THROW(bad_weak_ptr{});
}

// CLASS _Ref_count_base
class __declspec(novtable) _Ref_count_base { // common code for reference counting
private:
#ifdef _M_CEE_PURE
    // permanent workaround to avoid mentioning _purecall in msvcurt.lib, ptrustu.lib, or other support libs
    virtual void _Destroy() noexcept {
        _STD terminate();
    }

    virtual void _Delete_this() noexcept {
        _STD terminate();
    }
#else // ^^^ _M_CEE_PURE / !_M_CEE_PURE vvv
    virtual void _Destroy() noexcept     = 0; // destroy managed resource
    virtual void _Delete_this() noexcept = 0; // destroy self
#endif // _M_CEE_PURE

    _Atomic_counter_t _Uses  = 1;
    _Atomic_counter_t _Weaks = 1;

protected:
    constexpr _Ref_count_base() noexcept = default; // non-atomic initializations

public:
    _Ref_count_base(const _Ref_count_base&) = delete;
    _Ref_count_base& operator=(const _Ref_count_base&) = delete;

    virtual ~_Ref_count_base() noexcept {} // TRANSITION, should be non-virtual

    bool _Incref_nz() noexcept { // increment use count if not zero, return true if successful
        auto& _Volatile_uses = reinterpret_cast<volatile long&>(_Uses);
        long _Count          = _ISO_VOLATILE_LOAD32(_Volatile_uses);

        while (_Count != 0) {
            const long _Old_value = _INTRIN_RELAXED(_InterlockedCompareExchange)(&_Volatile_uses, _Count + 1, _Count);
            if (_Old_value == _Count) {
                return true;
            }

            _Count = _Old_value;
        }

        return false;
    }

    void _Incref() noexcept { // increment use count
        _MT_INCR(_Uses);
    }

    void _Incwref() noexcept { // increment weak reference count
        _MT_INCR(_Weaks);
    }

    void _Decref() noexcept { // decrement use count
        if (_MT_DECR(_Uses) == 0) {
            _Destroy();
            _Decwref();
        }
    }

    void _Decwref() noexcept { // decrement weak reference count
        if (_MT_DECR(_Weaks) == 0) {
            _Delete_this();
        }
    }

    long _Use_count() const noexcept {
        return static_cast<long>(_Uses);
    }

    virtual void* _Get_deleter(const type_info&) const noexcept {
        return nullptr;
    }
};

// CLASS TEMPLATE _Ref_count
template <class _Ty>
class _Ref_count : public _Ref_count_base { // handle reference counting for pointer without deleter
public:
    explicit _Ref_count(_Ty* _Px) : _Ref_count_base(), _Ptr(_Px) {}

private:
    virtual void _Destroy() noexcept override { // destroy managed resource
        delete _Ptr;
    }

    virtual void _Delete_this() noexcept override { // destroy self
        delete this;
    }

    _Ty* _Ptr;
};

// CLASS TEMPLATE _Ref_count_resource
template <class _Resource, class _Dx>
class _Ref_count_resource : public _Ref_count_base { // handle reference counting for object with deleter
public:
    _Ref_count_resource(_Resource _Px, _Dx _Dt)
        : _Ref_count_base(), _Mypair(_One_then_variadic_args_t{}, _STD move(_Dt), _Px) {}

    virtual void* _Get_deleter(const type_info& _Typeid) const noexcept override {
#if _HAS_STATIC_RTTI
        if (_Typeid == typeid(_Dx)) {
            return const_cast<_Dx*>(_STD addressof(_Mypair._Get_first()));
        }
#else // _HAS_STATIC_RTTI
        (void) _Typeid;
#endif // _HAS_STATIC_RTTI

        return nullptr;
    }

private:
    virtual void _Destroy() noexcept override { // destroy managed resource
        _Mypair._Get_first()(_Mypair._Myval2);
    }

    virtual void _Delete_this() noexcept override { // destroy self
        delete this;
    }

    _Compressed_pair<_Dx, _Resource> _Mypair;
};

// CLASS TEMPLATE _Ref_count_resource_alloc
template <class _Resource, class _Dx, class _Alloc>
class _Ref_count_resource_alloc : public _Ref_count_base {
    // handle reference counting for object with deleter and allocator
public:
    _Ref_count_resource_alloc(_Resource _Px, _Dx _Dt, const _Alloc& _Ax)
        : _Ref_count_base(),
          _Mypair(_One_then_variadic_args_t{}, _STD move(_Dt), _One_then_variadic_args_t{}, _Ax, _Px) {}

    virtual void* _Get_deleter(const type_info& _Typeid) const noexcept override {
#if _HAS_STATIC_RTTI
        if (_Typeid == typeid(_Dx)) {
            return const_cast<_Dx*>(_STD addressof(_Mypair._Get_first()));
        }
#else // _HAS_STATIC_RTTI
        (void) _Typeid;
#endif // _HAS_STATIC_RTTI

        return nullptr;
    }

private:
    using _Myalty = _Rebind_alloc_t<_Alloc, _Ref_count_resource_alloc>;

    virtual void _Destroy() noexcept override { // destroy managed resource
        _Mypair._Get_first()(_Mypair._Myval2._Myval2);
    }

    virtual void _Delete_this() noexcept override { // destroy self
        _Myalty _Al = _Mypair._Myval2._Get_first();
        this->~_Ref_count_resource_alloc();
        _Deallocate_plain(_Al, this);
    }

    _Compressed_pair<_Dx, _Compressed_pair<_Myalty, _Resource>> _Mypair;
};

// DECLARATIONS
template <class _Ty>
struct default_delete;

template <class _Ty, class _Dx = default_delete<_Ty>>
class unique_ptr;

template <class _Ty>
class shared_ptr;

template <class _Ty>
class weak_ptr;

template <class _Yty, class = void>
struct _Can_enable_shared : false_type {}; // detect unambiguous and accessible inheritance from enable_shared_from_this

template <class _Yty>
struct _Can_enable_shared<_Yty, void_t<typename _Yty::_Esft_type>>
    : is_convertible<remove_cv_t<_Yty>*, typename _Yty::_Esft_type*>::type {
    // is_convertible is necessary to verify unambiguous inheritance
};

#if !_HAS_IF_CONSTEXPR
template <class _Other, class _Yty>
void _Enable_shared_from_this1(const shared_ptr<_Other>& _This, _Yty* _Ptr, true_type) noexcept {
    // enable shared_from_this
    if (_Ptr && _Ptr->_Wptr.expired()) {
        _Ptr->_Wptr = shared_ptr<remove_cv_t<_Yty>>(_This, const_cast<remove_cv_t<_Yty>*>(_Ptr));
    }
}

template <class _Other, class _Yty>
void _Enable_shared_from_this1(const shared_ptr<_Other>&, _Yty*, false_type) noexcept {
    // don't enable shared_from_this
}
#endif // !_HAS_IF_CONSTEXPR

// CLASS TEMPLATE _Ptr_base
struct _Exception_ptr_access;

template <class _Ty>
class _Ptr_base { // base class for shared_ptr and weak_ptr
public:
    using element_type = remove_extent_t<_Ty>;

    _NODISCARD long use_count() const noexcept {
        return _Rep ? _Rep->_Use_count() : 0;
    }

    template <class _Ty2>
    _NODISCARD bool owner_before(const _Ptr_base<_Ty2>& _Right) const noexcept { // compare addresses of manager objects
        return _Rep < _Right._Rep;
    }

    _Ptr_base(const _Ptr_base&) = delete;
    _Ptr_base& operator=(const _Ptr_base&) = delete;

protected:
    _NODISCARD element_type* get() const noexcept {
        return _Ptr;
    }

    constexpr _Ptr_base() noexcept = default;

    ~_Ptr_base() = default;

    template <class _Ty2>
    void _Move_construct_from(_Ptr_base<_Ty2>&& _Right) noexcept {
        // implement shared_ptr's (converting) move ctor and weak_ptr's move ctor
        _Ptr = _Right._Ptr;
        _Rep = _Right._Rep;

        _Right._Ptr = nullptr;
        _Right._Rep = nullptr;
    }

    template <class _Ty2>
    void _Copy_construct_from(const shared_ptr<_Ty2>& _Other) noexcept {
        // implement shared_ptr's (converting) copy ctor
        _Other._Incref();

        _Ptr = _Other._Ptr;
        _Rep = _Other._Rep;
    }

    template <class _Ty2>
    void _Alias_construct_from(const shared_ptr<_Ty2>& _Other, element_type* _Px) noexcept {
        // implement shared_ptr's aliasing ctor
        _Other._Incref();

        _Ptr = _Px;
        _Rep = _Other._Rep;
    }

    template <class _Ty2>
    void _Alias_move_construct_from(shared_ptr<_Ty2>&& _Other, element_type* _Px) noexcept {
        // implement shared_ptr's aliasing move ctor
        _Ptr = _Px;
        _Rep = _Other._Rep;

        _Other._Ptr = nullptr;
        _Other._Rep = nullptr;
    }

    template <class _Ty0>
    friend class weak_ptr; // specifically, weak_ptr::lock()

    template <class _Ty2>
    bool _Construct_from_weak(const weak_ptr<_Ty2>& _Other) noexcept {
        // implement shared_ptr's ctor from weak_ptr, and weak_ptr::lock()
        if (_Other._Rep && _Other._Rep->_Incref_nz()) {
            _Ptr = _Other._Ptr;
            _Rep = _Other._Rep;
            return true;
        }

        return false;
    }

    void _Incref() const noexcept {
        if (_Rep) {
            _Rep->_Incref();
        }
    }

    void _Decref() noexcept { // decrement reference count
        if (_Rep) {
            _Rep->_Decref();
        }
    }

    void _Swap(_Ptr_base& _Right) noexcept { // swap pointers
        _STD swap(_Ptr, _Right._Ptr);
        _STD swap(_Rep, _Right._Rep);
    }

    template <class _Ty2>
    void _Weakly_construct_from(const _Ptr_base<_Ty2>& _Other) noexcept { // implement weak_ptr's ctors
        if (_Other._Rep) {
            _Ptr = _Other._Ptr;
            _Rep = _Other._Rep;
            _Rep->_Incwref();
        } else {
            _STL_INTERNAL_CHECK(!_Ptr && !_Rep);
        }
    }

    void _Incwref() const noexcept {
        if (_Rep) {
            _Rep->_Incwref();
        }
    }

    void _Decwref() noexcept { // decrement weak reference count
        if (_Rep) {
            _Rep->_Decwref();
        }
    }

private:
    element_type* _Ptr{nullptr};
    _Ref_count_base* _Rep{nullptr};

    template <class _Ty0>
    friend class _Ptr_base;

    friend shared_ptr<_Ty>;

    template <class _Ty0>
    friend struct atomic;

    friend _Exception_ptr_access;

#if _HAS_STATIC_RTTI
    template <class _Dx, class _Ty0>
    friend _Dx* get_deleter(const shared_ptr<_Ty0>& _Sx) noexcept;
#endif // _HAS_STATIC_RTTI
};

// TYPE TRAIT _Can_scalar_delete
template <class _Yty, class = void>
struct _Can_scalar_delete : false_type {};
template <class _Yty>
struct _Can_scalar_delete<_Yty, void_t<decltype(delete _STD declval<_Yty*>())>> : true_type {};

// TYPE TRAIT _Can_array_delete
template <class _Yty, class = void>
struct _Can_array_delete : false_type {};
template <class _Yty>
struct _Can_array_delete<_Yty, void_t<decltype(delete[] _STD declval<_Yty*>())>> : true_type {};

// TYPE TRAIT _Can_call_function_object
template <class _Fx, class _Arg, class = void>
struct _Can_call_function_object : false_type {};
template <class _Fx, class _Arg>
struct _Can_call_function_object<_Fx, _Arg, void_t<decltype(_STD declval<_Fx>()(_STD declval<_Arg>()))>> : true_type {};

// TYPE TRAIT _SP_convertible
template <class _Yty, class _Ty>
struct _SP_convertible : is_convertible<_Yty*, _Ty*>::type {};
template <class _Yty, class _Uty>
struct _SP_convertible<_Yty, _Uty[]> : is_convertible<_Yty (*)[], _Uty (*)[]>::type {};
template <class _Yty, class _Uty, size_t _Ext>
struct _SP_convertible<_Yty, _Uty[_Ext]> : is_convertible<_Yty (*)[_Ext], _Uty (*)[_Ext]>::type {};

// TYPE TRAIT _SP_pointer_compatible
template <class _Yty, class _Ty>
struct _SP_pointer_compatible : is_convertible<_Yty*, _Ty*>::type {
    // N4659 [util.smartptr.shared]/5 "a pointer type Y* is said to be compatible
    // with a pointer type T* " "when either Y* is convertible to T* ..."
};
template <class _Uty, size_t _Ext>
struct _SP_pointer_compatible<_Uty[_Ext], _Uty[]> : true_type {
    // N4659 [util.smartptr.shared]/5 "... or Y is U[N] and T is cv U[]."
};
template <class _Uty, size_t _Ext>
struct _SP_pointer_compatible<_Uty[_Ext], const _Uty[]> : true_type {
    // N4659 [util.smartptr.shared]/5 "... or Y is U[N] and T is cv U[]."
};
template <class _Uty, size_t _Ext>
struct _SP_pointer_compatible<_Uty[_Ext], volatile _Uty[]> : true_type {
    // N4659 [util.smartptr.shared]/5 "... or Y is U[N] and T is cv U[]."
};
template <class _Uty, size_t _Ext>
struct _SP_pointer_compatible<_Uty[_Ext], const volatile _Uty[]> : true_type {
    // N4659 [util.smartptr.shared]/5 "... or Y is U[N] and T is cv U[]."
};

// CLASS TEMPLATE shared_ptr
template <class _Ux>
struct _Temporary_owner {
    _Ux* _Ptr;

    explicit _Temporary_owner(_Ux* const _Ptr_) noexcept : _Ptr(_Ptr_) {}
    _Temporary_owner(const _Temporary_owner&) = delete;
    _Temporary_owner& operator=(const _Temporary_owner&) = delete;
    ~_Temporary_owner() {
        delete _Ptr;
    }
};

template <class _UxptrOrNullptr, class _Dx>
struct _Temporary_owner_del {
    _UxptrOrNullptr _Ptr;
    _Dx& _Dt;
    bool _Call_deleter = true;

    explicit _Temporary_owner_del(const _UxptrOrNullptr _Ptr_, _Dx& _Dt_) noexcept : _Ptr(_Ptr_), _Dt(_Dt_) {}
    _Temporary_owner_del(const _Temporary_owner_del&) = delete;
    _Temporary_owner_del& operator=(const _Temporary_owner_del&) = delete;
    ~_Temporary_owner_del() {
        if (_Call_deleter) {
            _Dt(_Ptr);
        }
    }
};

template <class _Ty>
class shared_ptr : public _Ptr_base<_Ty> { // class for reference counted resource management
private:
    using _Mybase = _Ptr_base<_Ty>;

public:
    using typename _Mybase::element_type;

    int m_MID;
    std::string m_ObjectName;
    std::string m_TypeID;

#if _HAS_CXX17
    using weak_type = weak_ptr<_Ty>;
#endif // _HAS_CXX17

    constexpr shared_ptr() noexcept = default;

    constexpr shared_ptr(nullptr_t) noexcept {} // construct empty shared_ptr

    template <class _Ux,
        enable_if_t<conjunction_v<conditional_t<is_array_v<_Ty>, _Can_array_delete<_Ux>, _Can_scalar_delete<_Ux>>,
                        _SP_convertible<_Ux, _Ty>>,
            int> = 0>
    explicit shared_ptr(_Ux* _Px) { // construct shared_ptr object that owns _Px
#if _HAS_IF_CONSTEXPR
        if constexpr (is_array_v<_Ty>) {
            _Setpd(_Px, default_delete<_Ux[]>{});
        } else {
            _Temporary_owner<_Ux> _Owner(_Px);
            _Set_ptr_rep_and_enable_shared(_Owner._Ptr, new _Ref_count<_Ux>(_Owner._Ptr));
            _Owner._Ptr = nullptr;
        }
#else // ^^^ _HAS_IF_CONSTEXPR // !_HAS_IF_CONSTEXPR vvv
        _Setp(_Px, is_array<_Ty>{});
#endif // _HAS_IF_CONSTEXPR
    }

    template <class _Ux, class _Dx,
        enable_if_t<conjunction_v<is_move_constructible<_Dx>, _Can_call_function_object<_Dx&, _Ux*&>,
                        _SP_convertible<_Ux, _Ty>>,
            int> = 0>
    shared_ptr(_Ux* _Px, _Dx _Dt) { // construct with _Px, deleter
        _Setpd(_Px, _STD move(_Dt));
    }

    template <class _Ux, class _Dx, class _Alloc,
        enable_if_t<conjunction_v<is_move_constructible<_Dx>, _Can_call_function_object<_Dx&, _Ux*&>,
                        _SP_convertible<_Ux, _Ty>>,
            int> = 0>
    shared_ptr(_Ux* _Px, _Dx _Dt, _Alloc _Ax) { // construct with _Px, deleter, allocator
        _Setpda(_Px, _STD move(_Dt), _Ax);
    }

    template <class _Dx,
        enable_if_t<conjunction_v<is_move_constructible<_Dx>, _Can_call_function_object<_Dx&, nullptr_t&>>, int> = 0>
    shared_ptr(nullptr_t, _Dx _Dt) { // construct with nullptr, deleter
        _Setpd(nullptr, _STD move(_Dt));
    }

    template <class _Dx, class _Alloc,
        enable_if_t<conjunction_v<is_move_constructible<_Dx>, _Can_call_function_object<_Dx&, nullptr_t&>>, int> = 0>
    shared_ptr(nullptr_t, _Dx _Dt, _Alloc _Ax) { // construct with nullptr, deleter, allocator
        _Setpda(nullptr, _STD move(_Dt), _Ax);
    }

    template <class _Ty2>
    shared_ptr(const shared_ptr<_Ty2>& _Right, element_type* _Px) noexcept {
        // construct shared_ptr object that aliases _Right
        this->_Alias_construct_from(_Right, _Px);
    }

    template <class _Ty2>
    shared_ptr(shared_ptr<_Ty2>&& _Right, element_type* _Px) noexcept {
        // move construct shared_ptr object that aliases _Right
        this->_Alias_move_construct_from(_STD move(_Right), _Px);
    }

    shared_ptr(const shared_ptr& _Other) noexcept { // construct shared_ptr object that owns same resource as _Other
        this->_Copy_construct_from(_Other);
    }

    template <class _Ty2, enable_if_t<_SP_pointer_compatible<_Ty2, _Ty>::value, int> = 0>
    shared_ptr(const shared_ptr<_Ty2>& _Other) noexcept {
        // construct shared_ptr object that owns same resource as _Other
        this->_Copy_construct_from(_Other);
    }

    shared_ptr(shared_ptr&& _Right) noexcept { // construct shared_ptr object that takes resource from _Right
        this->_Move_construct_from(_STD move(_Right));
    }

    template <class _Ty2, enable_if_t<_SP_pointer_compatible<_Ty2, _Ty>::value, int> = 0>
    shared_ptr(shared_ptr<_Ty2>&& _Right) noexcept { // construct shared_ptr object that takes resource from _Right
        this->_Move_construct_from(_STD move(_Right));
    }

    template <class _Ty2, enable_if_t<_SP_pointer_compatible<_Ty2, _Ty>::value, int> = 0>
    explicit shared_ptr(const weak_ptr<_Ty2>& _Other) { // construct shared_ptr object that owns resource *_Other
        if (!this->_Construct_from_weak(_Other)) {
            _Throw_bad_weak_ptr();
        }
    }

#if _HAS_AUTO_PTR_ETC
    template <class _Ty2, enable_if_t<is_convertible_v<_Ty2*, _Ty*>, int> = 0>
    shared_ptr(auto_ptr<_Ty2>&& _Other) { // construct shared_ptr object that owns *_Other.get()
        _Ty2* _Px = _Other.get();
        _Set_ptr_rep_and_enable_shared(_Px, new _Ref_count<_Ty2>(_Px));
        _Other.release();
    }
#endif // _HAS_AUTO_PTR_ETC

    template <class _Ux, class _Dx,
        enable_if_t<conjunction_v<_SP_pointer_compatible<_Ux, _Ty>,
                        is_convertible<typename unique_ptr<_Ux, _Dx>::pointer, element_type*>>,
            int> = 0>
    shared_ptr(unique_ptr<_Ux, _Dx>&& _Other) {
        using _Fancy_t   = typename unique_ptr<_Ux, _Dx>::pointer;
        using _Raw_t     = typename unique_ptr<_Ux, _Dx>::element_type*;
        using _Deleter_t = conditional_t<is_reference_v<_Dx>, decltype(_STD ref(_Other.get_deleter())), _Dx>;

        const _Fancy_t _Fancy = _Other.get();

        if (_Fancy) {
            const _Raw_t _Raw = _Fancy;
            const auto _Rx    = new _Ref_count_resource<_Fancy_t, _Deleter_t>(_Fancy, _Other.get_deleter());
            _Set_ptr_rep_and_enable_shared(_Raw, _Rx);
            _Other.release();
        }
    }

    ~shared_ptr() noexcept { // release resource
        this->_Decref();
    }

    shared_ptr& operator=(const shared_ptr& _Right) noexcept {
        shared_ptr(_Right).swap(*this);
        return *this;
    }

    template <class _Ty2>
    shared_ptr& operator=(const shared_ptr<_Ty2>& _Right) noexcept {
        shared_ptr(_Right).swap(*this);
        return *this;
    }

    shared_ptr& operator=(shared_ptr&& _Right) noexcept { // take resource from _Right
        shared_ptr(_STD move(_Right)).swap(*this);
        return *this;
    }

    template <class _Ty2>
    shared_ptr& operator=(shared_ptr<_Ty2>&& _Right) noexcept { // take resource from _Right
        shared_ptr(_STD move(_Right)).swap(*this);
        return *this;
    }

#if _HAS_AUTO_PTR_ETC
    template <class _Ty2>
    shared_ptr& operator=(auto_ptr<_Ty2>&& _Right) {
        shared_ptr(_STD move(_Right)).swap(*this);
        return *this;
    }
#endif // _HAS_AUTO_PTR_ETC

    template <class _Ux, class _Dx>
    shared_ptr& operator=(unique_ptr<_Ux, _Dx>&& _Right) { // move from unique_ptr
        shared_ptr(_STD move(_Right)).swap(*this);
        return *this;
    }

    void swap(shared_ptr& _Other) noexcept {
        this->_Swap(_Other);
    }

    void reset() noexcept { // release resource and convert to empty shared_ptr object
        shared_ptr().swap(*this);
    }

    template <class _Ux>
    void reset(_Ux* _Px) { // release, take ownership of _Px
        shared_ptr(_Px).swap(*this);
    }

    template <class _Ux, class _Dx>
    void reset(_Ux* _Px, _Dx _Dt) { // release, take ownership of _Px, with deleter _Dt
        shared_ptr(_Px, _Dt).swap(*this);
    }

    template <class _Ux, class _Dx, class _Alloc>
    void reset(_Ux* _Px, _Dx _Dt, _Alloc _Ax) { // release, take ownership of _Px, with deleter _Dt, allocator _Ax
        shared_ptr(_Px, _Dt, _Ax).swap(*this);
    }

    using _Mybase::get;

    template <class _Ty2 = _Ty, enable_if_t<!disjunction_v<is_array<_Ty2>, is_void<_Ty2>>, int> = 0>
    _NODISCARD _Ty2& operator*() const noexcept {
        return *get();
    }

    template <class _Ty2 = _Ty, enable_if_t<!is_array_v<_Ty2>, int> = 0>
    _NODISCARD _Ty2* operator->() const noexcept {
        return get();
    }

    template <class _Ty2 = _Ty, class _Elem = element_type, enable_if_t<is_array_v<_Ty2>, int> = 0>
    _NODISCARD _Elem& operator[](ptrdiff_t _Idx) const noexcept /* strengthened */ {
        return get()[_Idx];
    }

#if _HAS_DEPRECATED_SHARED_PTR_UNIQUE
    _CXX17_DEPRECATE_SHARED_PTR_UNIQUE _NODISCARD bool unique() const noexcept {
        // return true if no other shared_ptr object owns this resource
        return this->use_count() == 1;
    }
#endif // _HAS_DEPRECATED_SHARED_PTR_UNIQUE

    explicit operator bool() const noexcept {
        return get() != nullptr;
    }

private:
#if !_HAS_IF_CONSTEXPR
    template <class _Ux>
    void _Setp(_Ux* _Px, true_type) { // take ownership of _Px
        _Setpd(_Px, default_delete<_Ux[]>{});
    }

    template <class _Ux>
    void _Setp(_Ux* const _Px, false_type) { // take ownership of _Px
        _Temporary_owner<_Ux> _Owner(_Px);
        _Set_ptr_rep_and_enable_shared(_Owner._Ptr, new _Ref_count<_Ux>(_Owner._Ptr));
        _Owner._Ptr = nullptr;
    }
#endif // !_HAS_IF_CONSTEXPR

    template <class _UxptrOrNullptr, class _Dx>
    void _Setpd(const _UxptrOrNullptr _Px, _Dx _Dt) { // take ownership of _Px, deleter _Dt
        _Temporary_owner_del<_UxptrOrNullptr, _Dx> _Owner(_Px, _Dt);
        _Set_ptr_rep_and_enable_shared(
            _Owner._Ptr, new _Ref_count_resource<_UxptrOrNullptr, _Dx>(_Owner._Ptr, _STD move(_Dt)));
        _Owner._Call_deleter = false;
    }

    template <class _UxptrOrNullptr, class _Dx, class _Alloc>
    void _Setpda(const _UxptrOrNullptr _Px, _Dx _Dt, _Alloc _Ax) { // take ownership of _Px, deleter _Dt, allocator _Ax
        using _Alref_alloc = _Rebind_alloc_t<_Alloc, _Ref_count_resource_alloc<_UxptrOrNullptr, _Dx, _Alloc>>;

        _Temporary_owner_del<_UxptrOrNullptr, _Dx> _Owner(_Px, _Dt);
        _Alref_alloc _Alref(_Ax);
        _Alloc_construct_ptr<_Alref_alloc> _Constructor(_Alref);
        _Constructor._Allocate();
        _Construct_in_place(*_Constructor._Ptr, _Owner._Ptr, _STD move(_Dt), _Ax);
        _Set_ptr_rep_and_enable_shared(_Owner._Ptr, _Unfancy(_Constructor._Ptr));
        _Constructor._Ptr    = nullptr;
        _Owner._Call_deleter = false;
    }

#if _HAS_CXX20
    template <class _Ty0, class... _Types>
    friend enable_if_t<!is_array_v<_Ty0>, shared_ptr<_Ty0>> make_shared(_Types&&... _Args);

    template <class _Ty0, class _Alloc, class... _Types>
    friend enable_if_t<!is_array_v<_Ty0>, shared_ptr<_Ty0>> allocate_shared(const _Alloc& _Al_arg, _Types&&... _Args);

    template <class _Ty0>
    friend enable_if_t<is_unbounded_array_v<_Ty0>, shared_ptr<_Ty0>> make_shared(size_t _Count);

    template <class _Ty0, class _Alloc>
    friend enable_if_t<is_unbounded_array_v<_Ty0>, shared_ptr<_Ty0>> allocate_shared(
        const _Alloc& _Al_arg, size_t _Count);

    template <class _Ty0>
    friend enable_if_t<is_bounded_array_v<_Ty0>, shared_ptr<_Ty0>> make_shared();

    template <class _Ty0, class _Alloc>
    friend enable_if_t<is_bounded_array_v<_Ty0>, shared_ptr<_Ty0>> allocate_shared(const _Alloc& _Al_arg);

    template <class _Ty0>
    friend enable_if_t<is_unbounded_array_v<_Ty0>, shared_ptr<_Ty0>> make_shared(
        size_t _Count, const remove_extent_t<_Ty0>& _Val);

    template <class _Ty0, class _Alloc>
    friend enable_if_t<is_unbounded_array_v<_Ty0>, shared_ptr<_Ty0>> allocate_shared(
        const _Alloc& _Al_arg, size_t _Count, const remove_extent_t<_Ty0>& _Val);

    template <class _Ty0>
    friend enable_if_t<is_bounded_array_v<_Ty0>, shared_ptr<_Ty0>> make_shared(const remove_extent_t<_Ty0>& _Val);

    template <class _Ty0, class _Alloc>
    friend enable_if_t<is_bounded_array_v<_Ty0>, shared_ptr<_Ty0>> allocate_shared(
        const _Alloc& _Al_arg, const remove_extent_t<_Ty0>& _Val);
#else // ^^^ _HAS_CXX20 / !_HAS_CXX20 vvv
    template <class _Ty0, class... _Types>
    friend shared_ptr<_Ty0> make_shared(_Types&&... _Args);

    template <class _Ty0, class _Alloc, class... _Types>
    friend shared_ptr<_Ty0> allocate_shared(const _Alloc& _Al_arg, _Types&&... _Args);
#endif // !_HAS_CXX20

    template <class _Ux>
    void _Set_ptr_rep_and_enable_shared(_Ux* const _Px, _Ref_count_base* const _Rx) noexcept { // take ownership of _Px
        this->_Ptr = _Px;
        this->_Rep = _Rx;
#if _HAS_IF_CONSTEXPR
        if constexpr (conjunction_v<negation<is_array<_Ty>>, negation<is_volatile<_Ux>>, _Can_enable_shared<_Ux>>) {
            if (_Px && _Px->_Wptr.expired()) {
                _Px->_Wptr = shared_ptr<remove_cv_t<_Ux>>(*this, const_cast<remove_cv_t<_Ux>*>(_Px));
            }
        }
#else // ^^^ _HAS_IF_CONSTEXPR // !_HAS_IF_CONSTEXPR vvv
        _Enable_shared_from_this1(*this, _Px,
            bool_constant<
                conjunction_v<negation<is_array<_Ty>>, negation<is_volatile<_Ux>>, _Can_enable_shared<_Ux>>>{});
#endif // _HAS_IF_CONSTEXPR
    }

    void _Set_ptr_rep_and_enable_shared(nullptr_t, _Ref_count_base* const _Rx) noexcept { // take ownership of nullptr
        this->_Ptr = nullptr;
        this->_Rep = _Rx;
    }
};

#if _HAS_CXX17
template <class _Ty>
shared_ptr(weak_ptr<_Ty>) -> shared_ptr<_Ty>;

template <class _Ty, class _Dx>
shared_ptr(unique_ptr<_Ty, _Dx>) -> shared_ptr<_Ty>;
#endif // _HAS_CXX17

template <class _Ty1, class _Ty2>
_NODISCARD bool operator==(const shared_ptr<_Ty1>& _Left, const shared_ptr<_Ty2>& _Right) noexcept {
    return _Left.get() == _Right.get();
}

template <class _Ty1, class _Ty2>
_NODISCARD bool operator!=(const shared_ptr<_Ty1>& _Left, const shared_ptr<_Ty2>& _Right) noexcept {
    return _Left.get() != _Right.get();
}

template <class _Ty1, class _Ty2>
_NODISCARD bool operator<(const shared_ptr<_Ty1>& _Left, const shared_ptr<_Ty2>& _Right) noexcept {
    return _Left.get() < _Right.get();
}

template <class _Ty1, class _Ty2>
_NODISCARD bool operator>=(const shared_ptr<_Ty1>& _Left, const shared_ptr<_Ty2>& _Right) noexcept {
    return _Left.get() >= _Right.get();
}

template <class _Ty1, class _Ty2>
_NODISCARD bool operator>(const shared_ptr<_Ty1>& _Left, const shared_ptr<_Ty2>& _Right) noexcept {
    return _Left.get() > _Right.get();
}

template <class _Ty1, class _Ty2>
_NODISCARD bool operator<=(const shared_ptr<_Ty1>& _Left, const shared_ptr<_Ty2>& _Right) noexcept {
    return _Left.get() <= _Right.get();
}

template <class _Ty>
_NODISCARD bool operator==(const shared_ptr<_Ty>& _Left, nullptr_t) noexcept {
    return _Left.get() == nullptr;
}

template <class _Ty>
_NODISCARD bool operator==(nullptr_t, const shared_ptr<_Ty>& _Right) noexcept {
    return nullptr == _Right.get();
}

template <class _Ty>
_NODISCARD bool operator!=(const shared_ptr<_Ty>& _Left, nullptr_t) noexcept {
    return _Left.get() != nullptr;
}

template <class _Ty>
_NODISCARD bool operator!=(nullptr_t, const shared_ptr<_Ty>& _Right) noexcept {
    return nullptr != _Right.get();
}

template <class _Ty>
_NODISCARD bool operator<(const shared_ptr<_Ty>& _Left, nullptr_t) noexcept {
    return _Left.get() < static_cast<typename shared_ptr<_Ty>::element_type*>(nullptr);
}

template <class _Ty>
_NODISCARD bool operator<(nullptr_t, const shared_ptr<_Ty>& _Right) noexcept {
    return static_cast<typename shared_ptr<_Ty>::element_type*>(nullptr) < _Right.get();
}

template <class _Ty>
_NODISCARD bool operator>=(const shared_ptr<_Ty>& _Left, nullptr_t) noexcept {
    return _Left.get() >= static_cast<typename shared_ptr<_Ty>::element_type*>(nullptr);
}

template <class _Ty>
_NODISCARD bool operator>=(nullptr_t, const shared_ptr<_Ty>& _Right) noexcept {
    return static_cast<typename shared_ptr<_Ty>::element_type*>(nullptr) >= _Right.get();
}

template <class _Ty>
_NODISCARD bool operator>(const shared_ptr<_Ty>& _Left, nullptr_t) noexcept {
    return _Left.get() > static_cast<typename shared_ptr<_Ty>::element_type*>(nullptr);
}

template <class _Ty>
_NODISCARD bool operator>(nullptr_t, const shared_ptr<_Ty>& _Right) noexcept {
    return static_cast<typename shared_ptr<_Ty>::element_type*>(nullptr) > _Right.get();
}

template <class _Ty>
_NODISCARD bool operator<=(const shared_ptr<_Ty>& _Left, nullptr_t) noexcept {
    return _Left.get() <= static_cast<typename shared_ptr<_Ty>::element_type*>(nullptr);
}

template <class _Ty>
_NODISCARD bool operator<=(nullptr_t, const shared_ptr<_Ty>& _Right) noexcept {
    return static_cast<typename shared_ptr<_Ty>::element_type*>(nullptr) <= _Right.get();
}

template <class _Elem, class _Traits, class _Ty>
basic_ostream<_Elem, _Traits>& operator<<(basic_ostream<_Elem, _Traits>& _Out, const shared_ptr<_Ty>& _Px) {
    // write contained pointer to stream
    return _Out << _Px.get();
}

template <class _Ty>
void swap(shared_ptr<_Ty>& _Left, shared_ptr<_Ty>& _Right) noexcept {
    _Left.swap(_Right);
}

template <class _Ty1, class _Ty2>
_NODISCARD shared_ptr<_Ty1> static_pointer_cast(const shared_ptr<_Ty2>& _Other) noexcept {
    // static_cast for shared_ptr that properly respects the reference count control block
    const auto _Ptr = static_cast<typename shared_ptr<_Ty1>::element_type*>(_Other.get());
    return shared_ptr<_Ty1>(_Other, _Ptr);
}

template <class _Ty1, class _Ty2>
_NODISCARD shared_ptr<_Ty1> static_pointer_cast(shared_ptr<_Ty2>&& _Other) noexcept {
    // static_cast for shared_ptr that properly respects the reference count control block
    const auto _Ptr = static_cast<typename shared_ptr<_Ty1>::element_type*>(_Other.get());
    return shared_ptr<_Ty1>(_STD move(_Other), _Ptr);
}

template <class _Ty1, class _Ty2>
_NODISCARD shared_ptr<_Ty1> const_pointer_cast(const shared_ptr<_Ty2>& _Other) noexcept {
    // const_cast for shared_ptr that properly respects the reference count control block
    const auto _Ptr = const_cast<typename shared_ptr<_Ty1>::element_type*>(_Other.get());
    return shared_ptr<_Ty1>(_Other, _Ptr);
}

template <class _Ty1, class _Ty2>
_NODISCARD shared_ptr<_Ty1> const_pointer_cast(shared_ptr<_Ty2>&& _Other) noexcept {
    // const_cast for shared_ptr that properly respects the reference count control block
    const auto _Ptr = const_cast<typename shared_ptr<_Ty1>::element_type*>(_Other.get());
    return shared_ptr<_Ty1>(_STD move(_Other), _Ptr);
}

template <class _Ty1, class _Ty2>
_NODISCARD shared_ptr<_Ty1> reinterpret_pointer_cast(const shared_ptr<_Ty2>& _Other) noexcept {
    // reinterpret_cast for shared_ptr that properly respects the reference count control block
    const auto _Ptr = reinterpret_cast<typename shared_ptr<_Ty1>::element_type*>(_Other.get());
    return shared_ptr<_Ty1>(_Other, _Ptr);
}

template <class _Ty1, class _Ty2>
_NODISCARD shared_ptr<_Ty1> reinterpret_pointer_cast(shared_ptr<_Ty2>&& _Other) noexcept {
    // reinterpret_cast for shared_ptr that properly respects the reference count control block
    const auto _Ptr = reinterpret_cast<typename shared_ptr<_Ty1>::element_type*>(_Other.get());
    return shared_ptr<_Ty1>(_STD move(_Other), _Ptr);
}

#ifdef _CPPRTTI
template <class _Ty1, class _Ty2>
_NODISCARD shared_ptr<_Ty1> dynamic_pointer_cast(const shared_ptr<_Ty2>& _Other) noexcept {
    // dynamic_cast for shared_ptr that properly respects the reference count control block
    const auto _Ptr = dynamic_cast<typename shared_ptr<_Ty1>::element_type*>(_Other.get());

    if (_Ptr) {
        return shared_ptr<_Ty1>(_Other, _Ptr);
    }

    return shared_ptr<_Ty1>();
}

template <class _Ty1, class _Ty2>
_NODISCARD shared_ptr<_Ty1> dynamic_pointer_cast(shared_ptr<_Ty2>&& _Other) noexcept {
    // dynamic_cast for shared_ptr that properly respects the reference count control block
    const auto _Ptr = dynamic_cast<typename shared_ptr<_Ty1>::element_type*>(_Other.get());

    if (_Ptr) {
        return shared_ptr<_Ty1>(_STD move(_Other), _Ptr);
    }

    return shared_ptr<_Ty1>();
}
#else // _CPPRTTI
template <class _Ty1, class _Ty2>
shared_ptr<_Ty1> dynamic_pointer_cast(const shared_ptr<_Ty2>&) noexcept = delete; // requires /GR option
template <class _Ty1, class _Ty2>
shared_ptr<_Ty1> dynamic_pointer_cast(shared_ptr<_Ty2>&&) noexcept = delete; // requires /GR option
#endif // _CPPRTTI

#if _HAS_STATIC_RTTI
template <class _Dx, class _Ty>
_NODISCARD _Dx* get_deleter(const shared_ptr<_Ty>& _Sx) noexcept {
    // return pointer to shared_ptr's deleter object if its type is _Dx
    if (_Sx._Rep) {
        return static_cast<_Dx*>(_Sx._Rep->_Get_deleter(typeid(_Dx)));
    }

    return nullptr;
}
#else // _HAS_STATIC_RTTI
template <class _Dx, class _Ty>
_Dx* get_deleter(const shared_ptr<_Ty>&) noexcept = delete; // requires static RTTI
#endif // _HAS_STATIC_RTTI

// CLASS TEMPLATE _Ref_count_obj2
template <class _Ty>
class _Ref_count_obj2 : public _Ref_count_base { // handle reference counting for object in control block, no allocator
public:
    template <class... _Types>
    explicit _Ref_count_obj2(_Types&&... _Args) : _Ref_count_base() {
        _Construct_in_place(_Storage._Value, _STD forward<_Types>(_Args)...);
    }

    ~_Ref_count_obj2() {
        // nothing to do, _Storage._Value was already destroyed in _Destroy

        // N4849 [class.dtor]/7:
        // "A defaulted destructor for a class X is defined as deleted if:
        // X is a union-like class that has a variant member with a non-trivial destructor"
    }

    union {
        _Wrap<_Ty> _Storage;
    };

private:
    virtual void _Destroy() noexcept override { // destroy managed resource
        _Destroy_in_place(_Storage._Value);
    }

    virtual void _Delete_this() noexcept override { // destroy self
        delete this;
    }
};

#if _HAS_CXX20
template <size_t _Align>
struct _Alignas_storage_unit {
    alignas(_Align) char _Space[_Align];
};

enum class _Check_overflow : bool { _No, _Yes };

template <class _Refc, _Check_overflow _Check>
_NODISCARD size_t _Calculate_bytes_for_flexible_array(const size_t _Count) noexcept(_Check == _Check_overflow::_No) {
    constexpr size_t _Align = alignof(_Refc);

    size_t _Bytes = sizeof(_Refc); // contains storage for one element

    if (_Count > 1) {
        constexpr size_t _Element_size = sizeof(typename _Refc::_Element_type);

        size_t _Extra_bytes;

        if constexpr (_Check == _Check_overflow::_Yes) {
            _Extra_bytes = _Get_size_of_n<_Element_size>(_Count - 1); // check multiplication overflow

            if (_Extra_bytes > static_cast<size_t>(-1) - _Bytes - (_Align - 1)) { // assume worst case adjustment
                _Throw_bad_array_new_length(); // addition overflow
            }
        } else {
            _Extra_bytes = _Element_size * (_Count - 1);
        }

        _Bytes += _Extra_bytes;

        _Bytes = (_Bytes + _Align - 1) & ~(_Align - 1);
    }

#ifdef _ENABLE_STL_INTERNAL_CHECK
    using _Storage = _Alignas_storage_unit<_Align>;
    _STL_INTERNAL_CHECK(_Bytes % sizeof(_Storage) == 0);
#endif // _ENABLE_STL_INTERNAL_CHECK

    return _Bytes;
}

template <class _Refc>
_NODISCARD _Refc* _Allocate_flexible_array(const size_t _Count) {
    const size_t _Bytes     = _Calculate_bytes_for_flexible_array<_Refc, _Check_overflow::_Yes>(_Count);
    constexpr size_t _Align = alignof(_Refc);
    if constexpr (_Align <= __STDCPP_DEFAULT_NEW_ALIGNMENT__) {
        return static_cast<_Refc*>(::operator new(_Bytes));
    } else {
        return static_cast<_Refc*>(::operator new (_Bytes, align_val_t{_Align}));
    }
}

template <class _Refc>
void _Deallocate_flexible_array(_Refc* const _Ptr) noexcept {
    constexpr size_t _Align = alignof(_Refc);
    if constexpr (_Align <= __STDCPP_DEFAULT_NEW_ALIGNMENT__) {
        ::operator delete(static_cast<void*>(_Ptr));
    } else {
        ::operator delete (static_cast<void*>(_Ptr), align_val_t{_Align});
    }
}

template <class _NoThrowIt>
struct _Uninitialized_rev_destroying_backout {
    // struct to undo partially constructed ranges in _Uninitialized_xxx algorithms
    _NoThrowIt _First;
    _NoThrowIt _Last;

    explicit _Uninitialized_rev_destroying_backout(_NoThrowIt _Dest) noexcept
        : _First(_Dest), _Last(_Dest) {} // TRANSITION, P1771R1 [[nodiscard]] For Constructors

    _Uninitialized_rev_destroying_backout(const _Uninitialized_rev_destroying_backout&) = delete;
    _Uninitialized_rev_destroying_backout& operator=(const _Uninitialized_rev_destroying_backout&) = delete;

    ~_Uninitialized_rev_destroying_backout() {
        while (_Last != _First) {
            --_Last;
            _STD destroy_at(_STD addressof(*_Last));
        }
    }

    template <class... _Types>
    void _Emplace_back(_Types&&... _Vals) { // construct a new element at *_Last and increment
        _Construct_in_place(*_Last, _STD forward<_Types>(_Vals)...);
        ++_Last;
    }

    _NoThrowIt _Release() noexcept { // suppress any exception handling backout and return _Last
        _First = _Last;
        return _Last;
    }
};

template <class _Ty>
void _Reverse_destroy_multidimensional_n(_Ty* const _Arr, size_t _Size) noexcept {
    while (_Size > 0) {
        --_Size;
        if constexpr (is_array_v<_Ty>) {
            _Reverse_destroy_multidimensional_n(_Arr[_Size], extent_v<_Ty>);
        } else {
            _Destroy_in_place(_Arr[_Size]);
        }
    }
}

template <class _Ty>
struct _Reverse_destroy_multidimensional_n_guard {
    _Ty* _Target;
    size_t _Index;

    ~_Reverse_destroy_multidimensional_n_guard() {
        if (_Target) {
            _Reverse_destroy_multidimensional_n(_Target, _Index);
        }
    }
};

template <class _Ty, size_t _Size>
void _Uninitialized_copy_multidimensional(const _Ty (&_In)[_Size], _Ty (&_Out)[_Size]) {
    if constexpr (is_trivial_v<_Ty>) {
        _Copy_memmove(_In, _In + _Size, _Out);
    } else if constexpr (is_array_v<_Ty>) {
        _Reverse_destroy_multidimensional_n_guard<_Ty> _Guard{_Out, 0};
        for (size_t& _Idx = _Guard._Index; _Idx < _Size; ++_Idx) {
            _Uninitialized_copy_multidimensional(_In[_Idx], _Out[_Idx]);
        }
        _Guard._Target = nullptr;
    } else {
        _Uninitialized_rev_destroying_backout _Backout{_Out};
        for (size_t _Idx = 0; _Idx < _Size; ++_Idx) {
            _Backout._Emplace_back(_In[_Idx]);
        }
        _Backout._Release();
    }
}

template <class _Ty>
void _Uninitialized_value_construct_multidimensional_n(_Ty* const _Out, const size_t _Size) {
    using _Item = remove_all_extents_t<_Ty>;
    if constexpr (_Use_memset_value_construct_v<_Item*>) {
        _Zero_range(_Out, _Out + _Size);
    } else if constexpr (is_array_v<_Ty>) {
        _Reverse_destroy_multidimensional_n_guard<_Ty> _Guard{_Out, 0};
        for (size_t& _Idx = _Guard._Index; _Idx < _Size; ++_Idx) {
            _Uninitialized_value_construct_multidimensional_n(_Out[_Idx], extent_v<_Ty>);
        }
        _Guard._Target = nullptr;
    } else {
        _Uninitialized_rev_destroying_backout _Backout{_Out};
        for (size_t _Idx = 0; _Idx < _Size; ++_Idx) {
            _Backout._Emplace_back();
        }
        _Backout._Release();
    }
}

template <class _Ty>
void _Uninitialized_fill_multidimensional_n(_Ty* const _Out, const size_t _Size, const _Ty& _Val) {
    if constexpr (is_array_v<_Ty>) {
        _Reverse_destroy_multidimensional_n_guard<_Ty> _Guard{_Out, 0};
        for (size_t& _Idx = _Guard._Index; _Idx < _Size; ++_Idx) {
            _Uninitialized_copy_multidimensional(_Val, _Out[_Idx]); // intentionally copy, not fill
        }
        _Guard._Target = nullptr;
    } else if constexpr (_Fill_memset_is_safe<_Ty*, _Ty>) {
        _CSTD memset(_Out, static_cast<unsigned char>(_Val), _Size);
    } else {
        _Uninitialized_rev_destroying_backout _Backout{_Out};
        for (size_t _Idx = 0; _Idx < _Size; ++_Idx) {
            _Backout._Emplace_back(_Val);
        }
        _Backout._Release();
    }
}

// CLASS TEMPLATE _Ref_count_unbounded_array
template <class _Ty, bool = is_trivially_destructible_v<remove_extent_t<_Ty>>>
class _Ref_count_unbounded_array : public _Ref_count_base {
    // handle reference counting for unbounded array with trivial destruction in control block, no allocator
public:
    static_assert(is_unbounded_array_v<_Ty>);

    using _Element_type = remove_extent_t<_Ty>;

    explicit _Ref_count_unbounded_array(const size_t _Count) : _Ref_count_base() {
        _Uninitialized_value_construct_multidimensional_n(_Get_ptr(), _Count);
    }

    explicit _Ref_count_unbounded_array(const size_t _Count, const _Element_type& _Val) : _Ref_count_base() {
        _Uninitialized_fill_multidimensional_n(_Get_ptr(), _Count, _Val);
    }

    _NODISCARD auto _Get_ptr() noexcept {
        return _STD addressof(_Storage._Value);
    }

private:
    union {
        _Wrap<_Element_type> _Storage; // flexible array must be last member
    };

    ~_Ref_count_unbounded_array() {
        // nothing to do, _Ty is trivially destructible

        // See N4849 [class.dtor]/7.
    }

    virtual void _Destroy() noexcept override { // destroy managed resource
        // nothing to do, _Ty is trivially destructible
    }

    virtual void _Delete_this() noexcept override { // destroy self
        this->~_Ref_count_unbounded_array();
        _Deallocate_flexible_array(this);
    }
};

template <class _Ty>
class _Ref_count_unbounded_array<_Ty, false> : public _Ref_count_base {
    // handle reference counting for unbounded array with non-trivial destruction in control block, no allocator
public:
    static_assert(is_unbounded_array_v<_Ty>);

    using _Element_type = remove_extent_t<_Ty>;

    explicit _Ref_count_unbounded_array(const size_t _Count) : _Ref_count_base(), _Size(_Count) {
        _Uninitialized_value_construct_multidimensional_n(_Get_ptr(), _Size);
    }

    explicit _Ref_count_unbounded_array(const size_t _Count, const _Element_type& _Val)
        : _Ref_count_base(), _Size(_Count) {
        _Uninitialized_fill_multidimensional_n(_Get_ptr(), _Size, _Val);
    }

    _NODISCARD auto _Get_ptr() noexcept {
        return _STD addressof(_Storage._Value);
    }

private:
    size_t _Size;

    union {
        _Wrap<_Element_type> _Storage; // flexible array must be last member
    };

    ~_Ref_count_unbounded_array() {
        // nothing to do, _Storage was already destroyed in _Destroy

        // See N4849 [class.dtor]/7.
    }

    virtual void _Destroy() noexcept override { // destroy managed resource
        _Reverse_destroy_multidimensional_n(_Get_ptr(), _Size);
    }

    virtual void _Delete_this() noexcept override { // destroy self
        this->~_Ref_count_unbounded_array();
        _Deallocate_flexible_array(this);
    }
};

// CLASS TEMPLATE _Ref_count_bounded_array
template <class _Ty>
class _Ref_count_bounded_array : public _Ref_count_base {
    // handle reference counting for bounded array in control block, no allocator
public:
    static_assert(is_bounded_array_v<_Ty>);

    _Ref_count_bounded_array() : _Ref_count_base(), _Storage() {} // value-initializing _Storage is necessary here

    explicit _Ref_count_bounded_array(const remove_extent_t<_Ty>& _Val)
        : _Ref_count_base() { // don't value-initialize _Storage
        _Uninitialized_fill_multidimensional_n(_Storage._Value, extent_v<_Ty>, _Val);
    }

    union {
        _Wrap<_Ty> _Storage;
    };

private:
    ~_Ref_count_bounded_array() {
        // nothing to do, _Storage was already destroyed in _Destroy

        // See N4849 [class.dtor]/7.
    }

    virtual void _Destroy() noexcept override { // destroy managed resource
        _Destroy_in_place(_Storage); // not _Storage._Value, see N4849 [expr.prim.id.dtor]
    }

    virtual void _Delete_this() noexcept override { // destroy self
        delete this;
    }
};
#endif // _HAS_CXX20

// CLASS TEMPLATE _Ebco_base
template <class _Ty,
    bool = is_empty_v<_Ty> && !is_final_v<_Ty>>
class _Ebco_base : private _Ty { // Empty Base Class Optimization, active
private:
    using _Mybase = _Ty; // for visualization

protected:
    template <class _Other, enable_if_t<!is_same_v<_Remove_cvref_t<_Other>, _Ebco_base>, int> = 0>
    explicit _Ebco_base(_Other&& _Val) noexcept(is_nothrow_constructible_v<_Ty, _Other>)
        : _Ty(_STD forward<_Other>(_Val)) {}

    _Ty& _Get_val() noexcept {
        return *this;
    }

    const _Ty& _Get_val() const noexcept {
        return *this;
    }
};

template <class _Ty>
class _Ebco_base<_Ty, false> { // Empty Base Class Optimization, inactive
private:
    _Ty _Myval;

protected:
    template <class _Other, enable_if_t<!is_same_v<_Remove_cvref_t<_Other>, _Ebco_base>, int> = 0>
    explicit _Ebco_base(_Other&& _Val) noexcept(is_nothrow_constructible_v<_Ty, _Other>)
        : _Myval(_STD forward<_Other>(_Val)) {}

    _Ty& _Get_val() noexcept {
        return _Myval;
    }

    const _Ty& _Get_val() const noexcept {
        return _Myval;
    }
};

// CLASS TEMPLATE _Ref_count_obj_alloc3
template <class _Ty, class _Alloc>
class _Ref_count_obj_alloc3 : public _Ebco_base<_Rebind_alloc_t<_Alloc, _Ty>>, public _Ref_count_base {
    // handle reference counting for object in control block, allocator
private:
    static_assert(is_same_v<_Ty, remove_cv_t<_Ty>>, "allocate_shared should remove_cv_t");

    using _Rebound = _Rebind_alloc_t<_Alloc, _Ty>;

public:
    template <class... _Types>
    explicit _Ref_count_obj_alloc3(const _Alloc& _Al_arg, _Types&&... _Args)
        : _Ebco_base<_Rebound>(_Al_arg), _Ref_count_base() {
        allocator_traits<_Rebound>::construct(
            this->_Get_val(), _STD addressof(_Storage._Value), _STD forward<_Types>(_Args)...);
    }

    union {
        _Wrap<_Ty> _Storage;
    };

private:
    ~_Ref_count_obj_alloc3() {
        // nothing to do; _Storage._Value already destroyed by _Destroy()

        // See N4849 [class.dtor]/7.
    }

    virtual void _Destroy() noexcept override { // destroy managed resource
        allocator_traits<_Rebound>::destroy(this->_Get_val(), _STD addressof(_Storage._Value));
    }

    virtual void _Delete_this() noexcept override { // destroy self
        _Rebind_alloc_t<_Alloc, _Ref_count_obj_alloc3> _Al(this->_Get_val());
        this->~_Ref_count_obj_alloc3();
        _Deallocate_plain(_Al, this);
    }
};

#if _HAS_CXX20
template <class _Alloc>
class _Uninitialized_rev_destroying_backout_al {
    // class to undo partially constructed ranges in _Uninitialized_xxx_al algorithms

private:
    using pointer = _Alloc_ptr_t<_Alloc>;

public:
    _Uninitialized_rev_destroying_backout_al(pointer _Dest, _Alloc& _Al_) noexcept
        : _First(_Dest), _Last(_Dest), _Al(_Al_) {} // TRANSITION, P1771R1 [[nodiscard]] For Constructors

    _Uninitialized_rev_destroying_backout_al(const _Uninitialized_rev_destroying_backout_al&) = delete;
    _Uninitialized_rev_destroying_backout_al& operator=(const _Uninitialized_rev_destroying_backout_al&) = delete;

    ~_Uninitialized_rev_destroying_backout_al() {
        while (_Last != _First) {
            --_Last;
            allocator_traits<_Alloc>::destroy(_Al, _Last);
        }
    }

    template <class... _Types>
    void _Emplace_back(_Types&&... _Vals) { // construct a new element at *_Last and increment
        allocator_traits<_Alloc>::construct(_Al, _Unfancy(_Last), _STD forward<_Types>(_Vals)...);
        ++_Last;
    }

    pointer _Release() noexcept { // suppress any exception handling backout and return _Last
        _First = _Last;
        return _Last;
    }

private:
    pointer _First;
    pointer _Last;
    _Alloc& _Al;
};

template <class _Ty, class _Alloc>
void _Reverse_destroy_multidimensional_n_al(_Ty* const _Arr, size_t _Size, _Alloc& _Al) noexcept {
    while (_Size > 0) {
        --_Size;
        if constexpr (is_array_v<_Ty>) {
            _Reverse_destroy_multidimensional_n_al(_Arr[_Size], extent_v<_Ty>, _Al);
        } else {
            allocator_traits<_Alloc>::destroy(_Al, _Arr + _Size);
        }
    }
}

template <class _Ty, class _Alloc>
struct _Reverse_destroy_multidimensional_n_al_guard {
    _Ty* _Target;
    size_t _Index;
    _Alloc& _Al;

    ~_Reverse_destroy_multidimensional_n_al_guard() {
        if (_Target) {
            _Reverse_destroy_multidimensional_n_al(_Target, _Index, _Al);
        }
    }
};

template <class _Ty, size_t _Size, class _Alloc>
void _Uninitialized_copy_multidimensional_al(const _Ty (&_In)[_Size], _Ty (&_Out)[_Size], _Alloc& _Al) {
    using _Item = remove_all_extents_t<_Ty>;
    if constexpr (conjunction_v<is_trivial<_Ty>, _Uses_default_construct<_Alloc, _Item*, const _Item&>>) {
        _Copy_memmove(_In, _In + _Size, _Out);
    } else if constexpr (is_array_v<_Ty>) {
        _Reverse_destroy_multidimensional_n_al_guard<_Ty, _Alloc> _Guard{_Out, 0, _Al};
        for (size_t& _Idx = _Guard._Index; _Idx < _Size; ++_Idx) {
            _Uninitialized_copy_multidimensional_al(_In[_Idx], _Out[_Idx], _Al);
        }
        _Guard._Target = nullptr;
    } else {
        _Uninitialized_rev_destroying_backout_al _Backout{_Out, _Al};
        for (size_t _Idx = 0; _Idx < _Size; ++_Idx) {
            _Backout._Emplace_back(_In[_Idx]);
        }
        _Backout._Release();
    }
}

template <class _Ty, class _Alloc>
void _Uninitialized_value_construct_multidimensional_n_al(_Ty* const _Out, const size_t _Size, _Alloc& _Al) {
    using _Item = remove_all_extents_t<_Ty>;
    if constexpr (_Use_memset_value_construct_v<_Item*> && _Uses_default_construct<_Alloc, _Item*>::value) {
        _Zero_range(_Out, _Out + _Size);
    } else if constexpr (is_array_v<_Ty>) {
        _Reverse_destroy_multidimensional_n_al_guard<_Ty, _Alloc> _Guard{_Out, 0, _Al};
        for (size_t& _Idx = _Guard._Index; _Idx < _Size; ++_Idx) {
            _Uninitialized_value_construct_multidimensional_n_al(_Out[_Idx], extent_v<_Ty>, _Al);
        }
        _Guard._Target = nullptr;
    } else {
        _Uninitialized_rev_destroying_backout_al _Backout{_Out, _Al};
        for (size_t _Idx = 0; _Idx < _Size; ++_Idx) {
            _Backout._Emplace_back();
        }
        _Backout._Release();
    }
}

template <class _Ty, class _Alloc>
void _Uninitialized_fill_multidimensional_n_al(_Ty* const _Out, const size_t _Size, const _Ty& _Val, _Alloc& _Al) {
    if constexpr (is_array_v<_Ty>) {
        _Reverse_destroy_multidimensional_n_al_guard<_Ty, _Alloc> _Guard{_Out, 0, _Al};
        for (size_t& _Idx = _Guard._Index; _Idx < _Size; ++_Idx) {
            _Uninitialized_copy_multidimensional_al(_Val, _Out[_Idx], _Al); // intentionally copy, not fill
        }
        _Guard._Target = nullptr;
    } else if constexpr (_Fill_memset_is_safe<_Ty*, _Ty> && _Uses_default_construct<_Alloc, _Ty*, const _Ty&>::value) {
        _CSTD memset(_Out, static_cast<unsigned char>(_Val), _Size);
    } else {
        _Uninitialized_rev_destroying_backout_al _Backout{_Out, _Al};
        for (size_t _Idx = 0; _Idx < _Size; ++_Idx) {
            _Backout._Emplace_back(_Val);
        }
        _Backout._Release();
    }
}

// CLASS TEMPLATE _Ref_count_unbounded_array_alloc
template <class _Ty, class _Alloc>
class _Ref_count_unbounded_array_alloc : public _Ebco_base<_Rebind_alloc_t<_Alloc, remove_all_extents_t<_Ty>>>,
                                         public _Ref_count_base {
    // handle reference counting for unbounded array in control block, allocator
private:
    static_assert(is_unbounded_array_v<_Ty>);
    static_assert(is_same_v<_Ty, remove_cv_t<_Ty>>, "allocate_shared should remove_cv_t");

    using _Item    = remove_all_extents_t<_Ty>;
    using _Rebound = _Rebind_alloc_t<_Alloc, _Item>;

public:
    using _Element_type = remove_extent_t<_Ty>;

    explicit _Ref_count_unbounded_array_alloc(const _Alloc& _Al_arg, const size_t _Count)
        : _Ebco_base<_Rebound>(_Al_arg), _Ref_count_base(), _Size(_Count) {
        _Uninitialized_value_construct_multidimensional_n_al(_Get_ptr(), _Size, this->_Get_val());
    }

    explicit _Ref_count_unbounded_array_alloc(const _Alloc& _Al_arg, const size_t _Count, const _Element_type& _Val)
        : _Ebco_base<_Rebound>(_Al_arg), _Ref_count_base(), _Size(_Count) {
        _Uninitialized_fill_multidimensional_n_al(_Get_ptr(), _Size, _Val, this->_Get_val());
    }

    _NODISCARD auto _Get_ptr() noexcept {
        return _STD addressof(_Storage._Value);
    }

private:
    size_t _Size;

    union {
        _Wrap<_Element_type> _Storage; // flexible array must be last member
    };

    ~_Ref_count_unbounded_array_alloc() {
        // nothing to do; _Storage._Value already destroyed by _Destroy()

        // See N4849 [class.dtor]/7.
    }

    virtual void _Destroy() noexcept override { // destroy managed resource
        if constexpr (!conjunction_v<is_trivially_destructible<_Item>, _Uses_default_destroy<_Rebound, _Item*>>) {
            _Reverse_destroy_multidimensional_n_al(_Get_ptr(), _Size, this->_Get_val());
        }
    }

    virtual void _Delete_this() noexcept override { // destroy self
        constexpr size_t _Align = alignof(_Ref_count_unbounded_array_alloc);
        using _Storage          = _Alignas_storage_unit<_Align>;

        _Rebind_alloc_t<_Alloc, _Storage> _Al(this->_Get_val());
        const size_t _Bytes =
            _Calculate_bytes_for_flexible_array<_Ref_count_unbounded_array_alloc, _Check_overflow::_No>(_Size);
        const size_t _Storage_units = _Bytes / sizeof(_Storage);

        this->~_Ref_count_unbounded_array_alloc();

        _Al.deallocate(reinterpret_cast<_Storage*>(this), _Storage_units);
    }
};

// CLASS TEMPLATE _Ref_count_bounded_array_alloc
template <class _Ty, class _Alloc>
class _Ref_count_bounded_array_alloc : public _Ebco_base<_Rebind_alloc_t<_Alloc, remove_all_extents_t<_Ty>>>,
                                       public _Ref_count_base {
    // handle reference counting for bounded array in control block, allocator
private:
    static_assert(is_bounded_array_v<_Ty>);
    static_assert(is_same_v<_Ty, remove_cv_t<_Ty>>, "allocate_shared should remove_cv_t");

    using _Item    = remove_all_extents_t<_Ty>;
    using _Rebound = _Rebind_alloc_t<_Alloc, _Item>;

public:
    explicit _Ref_count_bounded_array_alloc(const _Alloc& _Al_arg)
        : _Ebco_base<_Rebound>(_Al_arg), _Ref_count_base() { // don't value-initialize _Storage
        _Uninitialized_value_construct_multidimensional_n_al(_Storage._Value, extent_v<_Ty>, this->_Get_val());
    }

    explicit _Ref_count_bounded_array_alloc(const _Alloc& _Al_arg, const remove_extent_t<_Ty>& _Val)
        : _Ebco_base<_Rebound>(_Al_arg), _Ref_count_base() { // don't value-initialize _Storage
        _Uninitialized_fill_multidimensional_n_al(_Storage._Value, extent_v<_Ty>, _Val, this->_Get_val());
    }

    union {
        _Wrap<_Ty> _Storage;
    };

private:
    ~_Ref_count_bounded_array_alloc() {
        // nothing to do; _Storage._Value already destroyed by _Destroy()

        // See N4849 [class.dtor]/7.
    }

    virtual void _Destroy() noexcept override { // destroy managed resource
        if constexpr (!conjunction_v<is_trivially_destructible<_Item>, _Uses_default_destroy<_Rebound, _Item*>>) {
            _Reverse_destroy_multidimensional_n_al(_Storage._Value, extent_v<_Ty>, this->_Get_val());
        }
    }

    virtual void _Delete_this() noexcept override { // destroy self
        _Rebind_alloc_t<_Alloc, _Ref_count_bounded_array_alloc> _Al(this->_Get_val());
        this->~_Ref_count_bounded_array_alloc();
        _Deallocate_plain(_Al, this);
    }
};
#endif // _HAS_CXX20

// FUNCTION TEMPLATE make_shared
template <class _Ty, class... _Types>
_NODISCARD
#if _HAS_CXX20
    enable_if_t<!is_array_v<_Ty>, shared_ptr<_Ty>>
#else // _HAS_CXX20
    shared_ptr<_Ty>
#endif // _HAS_CXX20
    make_shared(std::string f_ObjectName, _Types&&... _Args) { // make a shared_ptr to non-array object
    const auto _Rx = new _Ref_count_obj2<_Ty>(_STD forward<_Types>(_Args)...);
    shared_ptr<_Ty> _Ret;
    _Ret->m_MID = g_MID;
    g_MID++;
    _Ret->m_ObjectName = f_ObjectName;
    _Ret->m_TypeID = typeid(_Ty);
    _Ret._Set_ptr_rep_and_enable_shared(_STD addressof(_Rx->_Storage._Value), _Rx);
    return _Ret;
}

#if _HAS_CXX20
template <class _Refc>
struct _Global_delete_guard {
    _Refc* _Target;

    ~_Global_delete_guard() {
        // While this branch is technically unnecessary because N4849 [new.delete.single]/17 requires
        // `::operator delete(nullptr)` to be a no-op, it's here to help optimizers see that after
        // `_Guard._Target = nullptr;`, this destructor can be eliminated.
        if (_Target) {
            _Deallocate_flexible_array(_Target);
        }
    }
};

template <class _Ty>
_NODISCARD enable_if_t<is_unbounded_array_v<_Ty>, shared_ptr<_Ty>> make_shared(const size_t _Count) {
    // make a shared_ptr to an unbounded array
    using _Refc    = _Ref_count_unbounded_array<_Ty>;
    const auto _Rx = _Allocate_flexible_array<_Refc>(_Count);
    _Global_delete_guard<_Refc> _Guard{_Rx};
    ::new (static_cast<void*>(_Rx)) _Refc(_Count);
    _Guard._Target = nullptr;
    shared_ptr<_Ty> _Ret;
    _Ret._Set_ptr_rep_and_enable_shared(_Rx->_Get_ptr(), _Rx);
    return _Ret;
}

template <class _Ty>
_NODISCARD enable_if_t<is_unbounded_array_v<_Ty>, shared_ptr<_Ty>> make_shared(
    const size_t _Count, const remove_extent_t<_Ty>& _Val) {
    // make a shared_ptr to an unbounded array
    using _Refc    = _Ref_count_unbounded_array<_Ty>;
    const auto _Rx = _Allocate_flexible_array<_Refc>(_Count);
    _Global_delete_guard<_Refc> _Guard{_Rx};
    ::new (static_cast<void*>(_Rx)) _Refc(_Count, _Val);
    _Guard._Target = nullptr;
    shared_ptr<_Ty> _Ret;
    _Ret._Set_ptr_rep_and_enable_shared(_Rx->_Get_ptr(), _Rx);
    return _Ret;
}

template <class _Ty>
_NODISCARD enable_if_t<is_bounded_array_v<_Ty>, shared_ptr<_Ty>> make_shared() {
    // make a shared_ptr to a bounded array
    const auto _Rx = new _Ref_count_bounded_array<_Ty>();
    shared_ptr<_Ty> _Ret;
    _Ret._Set_ptr_rep_and_enable_shared(_Rx->_Storage._Value, _Rx);
    return _Ret;
}

template <class _Ty>
_NODISCARD enable_if_t<is_bounded_array_v<_Ty>, shared_ptr<_Ty>> make_shared(const remove_extent_t<_Ty>& _Val) {
    // make a shared_ptr to a bounded array
    const auto _Rx = new _Ref_count_bounded_array<_Ty>(_Val);
    shared_ptr<_Ty> _Ret;
    _Ret._Set_ptr_rep_and_enable_shared(_Rx->_Storage._Value, _Rx);
    return _Ret;
}
#endif // _HAS_CXX20

// FUNCTION TEMPLATE allocate_shared
template <class _Ty, class _Alloc, class... _Types>
_NODISCARD
#if _HAS_CXX20
    enable_if_t<!is_array_v<_Ty>, shared_ptr<_Ty>>
#else // _HAS_CXX20
    shared_ptr<_Ty>
#endif // _HAS_CXX20
    allocate_shared(const _Alloc& _Al, _Types&&... _Args) { // make a shared_ptr to non-array object
    // Note: As of 2019-05-28, this implements the proposed resolution of LWG-3210 (which controls whether
    // allocator::construct sees T or const T when _Ty is const qualified)
    using _Refoa   = _Ref_count_obj_alloc3<remove_cv_t<_Ty>, _Alloc>;
    using _Alblock = _Rebind_alloc_t<_Alloc, _Refoa>;
    _Alblock _Rebound(_Al);
    _Alloc_construct_ptr<_Alblock> _Constructor{_Rebound};
    _Constructor._Allocate();
    _Construct_in_place(*_Constructor._Ptr, _Al, _STD forward<_Types>(_Args)...);
    shared_ptr<_Ty> _Ret;
    const auto _Ptr = reinterpret_cast<_Ty*>(_STD addressof(_Constructor._Ptr->_Storage._Value));
    _Ret._Set_ptr_rep_and_enable_shared(_Ptr, _Unfancy(_Constructor._Release()));
    return _Ret;
}

#if _HAS_CXX20
template <class _Alloc>
struct _Allocate_n_ptr {
    _Alloc& _Al;
    _Alloc_ptr_t<_Alloc> _Ptr;
    size_t _Nx;

    _Allocate_n_ptr(_Alloc& _Al_, const size_t _Nx_) : _Al(_Al_), _Ptr(_Al_.allocate(_Nx_)), _Nx(_Nx_) {}

    ~_Allocate_n_ptr() {
        if (_Ptr) {
            _Al.deallocate(_Ptr, _Nx);
        }
    }

    _Allocate_n_ptr(const _Allocate_n_ptr&) = delete;
    _Allocate_n_ptr& operator=(const _Allocate_n_ptr&) = delete;
};

template <class _Ty, class _Alloc>
_NODISCARD enable_if_t<is_unbounded_array_v<_Ty>, shared_ptr<_Ty>> allocate_shared(
    const _Alloc& _Al, const size_t _Count) {
    // make a shared_ptr to an unbounded array
    using _Refc             = _Ref_count_unbounded_array_alloc<remove_cv_t<_Ty>, _Alloc>;
    constexpr size_t _Align = alignof(_Refc);
    using _Storage          = _Alignas_storage_unit<_Align>;
    _Rebind_alloc_t<_Alloc, _Storage> _Rebound(_Al);
    const size_t _Bytes         = _Calculate_bytes_for_flexible_array<_Refc, _Check_overflow::_Yes>(_Count);
    const size_t _Storage_units = _Bytes / sizeof(_Storage);
    _Allocate_n_ptr _Guard{_Rebound, _Storage_units};
    const auto _Rx = reinterpret_cast<_Refc*>(_Unfancy(_Guard._Ptr));
    ::new (static_cast<void*>(_Rx)) _Refc(_Al, _Count);
    _Guard._Ptr = nullptr;
    shared_ptr<_Ty> _Ret;
    _Ret._Set_ptr_rep_and_enable_shared(_Rx->_Get_ptr(), _Rx);
    return _Ret;
}

template <class _Ty, class _Alloc>
_NODISCARD enable_if_t<is_unbounded_array_v<_Ty>, shared_ptr<_Ty>> allocate_shared(
    const _Alloc& _Al, const size_t _Count, const remove_extent_t<_Ty>& _Val) {
    // make a shared_ptr to an unbounded array
    using _Refc             = _Ref_count_unbounded_array_alloc<remove_cv_t<_Ty>, _Alloc>;
    constexpr size_t _Align = alignof(_Refc);
    using _Storage          = _Alignas_storage_unit<_Align>;
    _Rebind_alloc_t<_Alloc, _Storage> _Rebound(_Al);
    const size_t _Bytes         = _Calculate_bytes_for_flexible_array<_Refc, _Check_overflow::_Yes>(_Count);
    const size_t _Storage_units = _Bytes / sizeof(_Storage);
    _Allocate_n_ptr _Guard{_Rebound, _Storage_units};
    const auto _Rx = reinterpret_cast<_Refc*>(_Unfancy(_Guard._Ptr));
    ::new (static_cast<void*>(_Rx)) _Refc(_Al, _Count, _Val);
    _Guard._Ptr = nullptr;
    shared_ptr<_Ty> _Ret;
    _Ret._Set_ptr_rep_and_enable_shared(_Rx->_Get_ptr(), _Rx);
    return _Ret;
}

template <class _Ty, class _Alloc>
_NODISCARD enable_if_t<is_bounded_array_v<_Ty>, shared_ptr<_Ty>> allocate_shared(const _Alloc& _Al) {
    // make a shared_ptr to a bounded array
    using _Refc    = _Ref_count_bounded_array_alloc<remove_cv_t<_Ty>, _Alloc>;
    using _Alblock = _Rebind_alloc_t<_Alloc, _Refc>;
    _Alblock _Rebound(_Al);
    _Alloc_construct_ptr _Constructor{_Rebound};
    _Constructor._Allocate();
    ::new (static_cast<void*>(_Unfancy(_Constructor._Ptr))) _Refc(_Al);
    shared_ptr<_Ty> _Ret;
    const auto _Ptr = static_cast<remove_extent_t<_Ty>*>(_Constructor._Ptr->_Storage._Value);
    _Ret._Set_ptr_rep_and_enable_shared(_Ptr, _Unfancy(_Constructor._Release()));
    return _Ret;
}

template <class _Ty, class _Alloc>
_NODISCARD enable_if_t<is_bounded_array_v<_Ty>, shared_ptr<_Ty>> allocate_shared(
    const _Alloc& _Al, const remove_extent_t<_Ty>& _Val) {
    // make a shared_ptr to a bounded array
    using _Refc    = _Ref_count_bounded_array_alloc<remove_cv_t<_Ty>, _Alloc>;
    using _Alblock = _Rebind_alloc_t<_Alloc, _Refc>;
    _Alblock _Rebound(_Al);
    _Alloc_construct_ptr _Constructor{_Rebound};
    _Constructor._Allocate();
    ::new (static_cast<void*>(_Unfancy(_Constructor._Ptr))) _Refc(_Al, _Val);
    shared_ptr<_Ty> _Ret;
    const auto _Ptr = static_cast<remove_extent_t<_Ty>*>(_Constructor._Ptr->_Storage._Value);
    _Ret._Set_ptr_rep_and_enable_shared(_Ptr, _Unfancy(_Constructor._Release()));
    return _Ret;
}
#endif // _HAS_CXX20

// CLASS TEMPLATE weak_ptr
template <class _Ty>
class weak_ptr : public _Ptr_base<_Ty> { // class for pointer to reference counted resource
public:
    constexpr weak_ptr() noexcept {} // construct empty weak_ptr object

    weak_ptr(const weak_ptr& _Other) noexcept { // construct weak_ptr object for resource pointed to by _Other
        this->_Weakly_construct_from(_Other);
    }

    template <class _Ty2, enable_if_t<_SP_pointer_compatible<_Ty2, _Ty>::value, int> = 0>
    weak_ptr(const shared_ptr<_Ty2>& _Other) noexcept { // construct weak_ptr object for resource owned by _Other
        this->_Weakly_construct_from(_Other);
    }

    template <class _Ty2, enable_if_t<_SP_pointer_compatible<_Ty2, _Ty>::value, int> = 0>
    weak_ptr(const weak_ptr<_Ty2>& _Other) noexcept { // construct weak_ptr object for resource pointed to by _Other
        this->_Weakly_construct_from(_Other.lock());
    }

    weak_ptr(weak_ptr&& _Other) noexcept { // move construct from _Other
        this->_Move_construct_from(_STD move(_Other));
    }

    template <class _Ty2, enable_if_t<_SP_pointer_compatible<_Ty2, _Ty>::value, int> = 0>
    weak_ptr(weak_ptr<_Ty2>&& _Other) noexcept { // move construct from _Other
        this->_Weakly_construct_from(_Other.lock());
        _Other.reset();
    }

    ~weak_ptr() noexcept {
        this->_Decwref();
    }

    weak_ptr& operator=(const weak_ptr& _Right) noexcept {
        weak_ptr(_Right).swap(*this);
        return *this;
    }

    template <class _Ty2>
    weak_ptr& operator=(const weak_ptr<_Ty2>& _Right) noexcept {
        weak_ptr(_Right).swap(*this);
        return *this;
    }

    weak_ptr& operator=(weak_ptr&& _Right) noexcept {
        weak_ptr(_STD move(_Right)).swap(*this);
        return *this;
    }

    template <class _Ty2>
    weak_ptr& operator=(weak_ptr<_Ty2>&& _Right) noexcept {
        weak_ptr(_STD move(_Right)).swap(*this);
        return *this;
    }

    template <class _Ty2>
    weak_ptr& operator=(const shared_ptr<_Ty2>& _Right) noexcept {
        weak_ptr(_Right).swap(*this);
        return *this;
    }

    void reset() noexcept { // release resource, convert to null weak_ptr object
        weak_ptr{}.swap(*this);
    }

    void swap(weak_ptr& _Other) noexcept {
        this->_Swap(_Other);
    }

    _NODISCARD bool expired() const noexcept {
        return this->use_count() == 0;
    }

    _NODISCARD shared_ptr<_Ty> lock() const noexcept { // convert to shared_ptr
        shared_ptr<_Ty> _Ret;
        (void) _Ret._Construct_from_weak(*this);
        return _Ret;
    }
};

#if _HAS_CXX17
template <class _Ty>
weak_ptr(shared_ptr<_Ty>) -> weak_ptr<_Ty>;
#endif // _HAS_CXX17

template <class _Ty>
void swap(weak_ptr<_Ty>& _Left, weak_ptr<_Ty>& _Right) noexcept {
    _Left.swap(_Right);
}

// CLASS TEMPLATE enable_shared_from_this
template <class _Ty>
class enable_shared_from_this { // provide member functions that create shared_ptr to this
public:
    using _Esft_type = enable_shared_from_this;

    _NODISCARD shared_ptr<_Ty> shared_from_this() {
        return shared_ptr<_Ty>(_Wptr);
    }

    _NODISCARD shared_ptr<const _Ty> shared_from_this() const {
        return shared_ptr<const _Ty>(_Wptr);
    }

    _NODISCARD weak_ptr<_Ty> weak_from_this() noexcept {
        return _Wptr;
    }

    _NODISCARD weak_ptr<const _Ty> weak_from_this() const noexcept {
        return _Wptr;
    }

protected:
    constexpr enable_shared_from_this() noexcept : _Wptr() {}

    enable_shared_from_this(const enable_shared_from_this&) noexcept : _Wptr() {
        // construct (must value-initialize _Wptr)
    }

    enable_shared_from_this& operator=(const enable_shared_from_this&) noexcept { // assign (must not change _Wptr)
        return *this;
    }

    ~enable_shared_from_this() = default;

private:
#if _HAS_IF_CONSTEXPR
    template <class _Yty>
    friend class shared_ptr;
#else // ^^^ _HAS_IF_CONSTEXPR // !_HAS_IF_CONSTEXPR vvv
    template <class _Other, class _Yty>
    friend void _Enable_shared_from_this1(const shared_ptr<_Other>& _This, _Yty* _Ptr, true_type) noexcept;
#endif // _HAS_IF_CONSTEXPR

    mutable weak_ptr<_Ty> _Wptr;
};


// CLASS TEMPLATE unique_ptr AND HELPERS

// STRUCT TEMPLATE default_delete
template <class _Ty>
struct default_delete { // default deleter for unique_ptr
    constexpr default_delete() noexcept = default;

    template <class _Ty2, enable_if_t<is_convertible_v<_Ty2*, _Ty*>, int> = 0>
    default_delete(const default_delete<_Ty2>&) noexcept {}

    void operator()(_Ty* _Ptr) const noexcept /* strengthened */ { // delete a pointer
        static_assert(0 < sizeof(_Ty), "can't delete an incomplete type");
        delete _Ptr;
    }
};

template <class _Ty>
struct default_delete<_Ty[]> { // default deleter for unique_ptr to array of unknown size
    constexpr default_delete() noexcept = default;

    template <class _Uty, enable_if_t<is_convertible_v<_Uty (*)[], _Ty (*)[]>, int> = 0>
    default_delete(const default_delete<_Uty[]>&) noexcept {}

    template <class _Uty, enable_if_t<is_convertible_v<_Uty (*)[], _Ty (*)[]>, int> = 0>
    void operator()(_Uty* _Ptr) const noexcept /* strengthened */ { // delete a pointer
        static_assert(0 < sizeof(_Uty), "can't delete an incomplete type");
        delete[] _Ptr;
    }
};

// STRUCT TEMPLATE _Get_deleter_pointer_type
template <class _Ty, class _Dx_noref, class = void>
struct _Get_deleter_pointer_type { // provide fallback
    using type = _Ty*;
};

template <class _Ty, class _Dx_noref>
struct _Get_deleter_pointer_type<_Ty, _Dx_noref, void_t<typename _Dx_noref::pointer>> { // get _Dx_noref::pointer
    using type = typename _Dx_noref::pointer;
};

template <class _Dx2>
using _Unique_ptr_enable_default_t =
    enable_if_t<conjunction_v<negation<is_pointer<_Dx2>>, is_default_constructible<_Dx2>>, int>;

// CLASS TEMPLATE unique_ptr SCALAR
template <class _Ty, class _Dx /* = default_delete<_Ty> */>
class unique_ptr { // non-copyable pointer to an object
public:
    using pointer      = typename _Get_deleter_pointer_type<_Ty, remove_reference_t<_Dx>>::type;
    using element_type = _Ty;
    using deleter_type = _Dx;

    template <class _Dx2 = _Dx, _Unique_ptr_enable_default_t<_Dx2> = 0>
    constexpr unique_ptr() noexcept : _Mypair(_Zero_then_variadic_args_t{}) {}

    template <class _Dx2 = _Dx, _Unique_ptr_enable_default_t<_Dx2> = 0>
    constexpr unique_ptr(nullptr_t) noexcept : _Mypair(_Zero_then_variadic_args_t{}) {}

    unique_ptr& operator=(nullptr_t) noexcept {
        reset();
        return *this;
    }

    template <class _Dx2 = _Dx, _Unique_ptr_enable_default_t<_Dx2> = 0>
    explicit unique_ptr(pointer _Ptr) noexcept : _Mypair(_Zero_then_variadic_args_t{}, _Ptr) {}

    template <class _Dx2 = _Dx, enable_if_t<is_constructible_v<_Dx2, const _Dx2&>, int> = 0>
    unique_ptr(pointer _Ptr, const _Dx& _Dt) noexcept : _Mypair(_One_then_variadic_args_t{}, _Dt, _Ptr) {}

    template <class _Dx2                                                                            = _Dx,
        enable_if_t<conjunction_v<negation<is_reference<_Dx2>>, is_constructible<_Dx2, _Dx2>>, int> = 0>
    unique_ptr(pointer _Ptr, _Dx&& _Dt) noexcept : _Mypair(_One_then_variadic_args_t{}, _STD move(_Dt), _Ptr) {}

    template <class _Dx2                                                                                      = _Dx,
        enable_if_t<conjunction_v<is_reference<_Dx2>, is_constructible<_Dx2, remove_reference_t<_Dx2>>>, int> = 0>
    unique_ptr(pointer, remove_reference_t<_Dx>&&) = delete;

    template <class _Dx2 = _Dx, enable_if_t<is_move_constructible_v<_Dx2>, int> = 0>
    unique_ptr(unique_ptr&& _Right) noexcept
        : _Mypair(_One_then_variadic_args_t{}, _STD forward<_Dx>(_Right.get_deleter()), _Right.release()) {}

    template <class _Ty2, class _Dx2,
        enable_if_t<
            conjunction_v<negation<is_array<_Ty2>>, is_convertible<typename unique_ptr<_Ty2, _Dx2>::pointer, pointer>,
                conditional_t<is_reference_v<_Dx>, is_same<_Dx2, _Dx>, is_convertible<_Dx2, _Dx>>>,
            int> = 0>
    unique_ptr(unique_ptr<_Ty2, _Dx2>&& _Right) noexcept
        : _Mypair(_One_then_variadic_args_t{}, _STD forward<_Dx2>(_Right.get_deleter()), _Right.release()) {}

#if _HAS_AUTO_PTR_ETC
    template <class _Ty2,
        enable_if_t<conjunction_v<is_convertible<_Ty2*, _Ty*>, is_same<_Dx, default_delete<_Ty>>>, int> = 0>
    unique_ptr(auto_ptr<_Ty2>&& _Right) noexcept : _Mypair(_Zero_then_variadic_args_t{}, _Right.release()) {}
#endif // _HAS_AUTO_PTR_ETC

    template <class _Ty2, class _Dx2,
        enable_if_t<conjunction_v<negation<is_array<_Ty2>>, is_assignable<_Dx&, _Dx2>,
                        is_convertible<typename unique_ptr<_Ty2, _Dx2>::pointer, pointer>>,
            int> = 0>
    unique_ptr& operator=(unique_ptr<_Ty2, _Dx2>&& _Right) noexcept {
        reset(_Right.release());
        _Mypair._Get_first() = _STD forward<_Dx2>(_Right._Mypair._Get_first());
        return *this;
    }

    template <class _Dx2 = _Dx, enable_if_t<is_move_assignable_v<_Dx2>, int> = 0>
    unique_ptr& operator=(unique_ptr&& _Right) noexcept {
        if (this != _STD addressof(_Right)) {
            reset(_Right.release());
            _Mypair._Get_first() = _STD forward<_Dx>(_Right._Mypair._Get_first());
        }
        return *this;
    }

    void swap(unique_ptr& _Right) noexcept {
        _Swap_adl(_Mypair._Myval2, _Right._Mypair._Myval2);
        _Swap_adl(_Mypair._Get_first(), _Right._Mypair._Get_first());
    }

    ~unique_ptr() noexcept {
        if (_Mypair._Myval2) {
            _Mypair._Get_first()(_Mypair._Myval2);
        }
    }

    _NODISCARD _Dx& get_deleter() noexcept {
        return _Mypair._Get_first();
    }

    _NODISCARD const _Dx& get_deleter() const noexcept {
        return _Mypair._Get_first();
    }

    _NODISCARD add_lvalue_reference_t<_Ty> operator*() const noexcept /* strengthened */ {
        return *_Mypair._Myval2;
    }

    _NODISCARD pointer operator->() const noexcept {
        return _Mypair._Myval2;
    }

    _NODISCARD pointer get() const noexcept {
        return _Mypair._Myval2;
    }

    explicit operator bool() const noexcept {
        return static_cast<bool>(_Mypair._Myval2);
    }

    pointer release() noexcept {
        return _STD exchange(_Mypair._Myval2, pointer());
    }

    void reset(pointer _Ptr = pointer()) noexcept {
        pointer _Old = _STD exchange(_Mypair._Myval2, _Ptr);
        if (_Old) {
            _Mypair._Get_first()(_Old);
        }
    }

    unique_ptr(const unique_ptr&) = delete;
    unique_ptr& operator=(const unique_ptr&) = delete;

private:
    template <class, class>
    friend class unique_ptr;

    _Compressed_pair<_Dx, pointer> _Mypair;
};

// CLASS TEMPLATE unique_ptr ARRAY
template <class _Ty, class _Dx>
class unique_ptr<_Ty[], _Dx> { // non-copyable pointer to an array object
public:
    using pointer      = typename _Get_deleter_pointer_type<_Ty, remove_reference_t<_Dx>>::type;
    using element_type = _Ty;
    using deleter_type = _Dx;

    template <class _Dx2 = _Dx, _Unique_ptr_enable_default_t<_Dx2> = 0>
    constexpr unique_ptr() noexcept : _Mypair(_Zero_then_variadic_args_t{}) {}

    template <class _Uty, class _Is_nullptr = is_same<_Uty, nullptr_t>>
    using _Enable_ctor_reset =
        enable_if_t<is_same_v<_Uty, pointer> //
                    || _Is_nullptr::value //
                    || (is_same_v<pointer, element_type*> //
                        && is_pointer_v<_Uty> //
                        && is_convertible_v<remove_pointer_t<_Uty> (*)[], element_type (*)[]>)>; // TRANSITION, GH-248

    template <class _Uty, class _Dx2 = _Dx, _Unique_ptr_enable_default_t<_Dx2> = 0, class = _Enable_ctor_reset<_Uty>>
    explicit unique_ptr(_Uty _Ptr) noexcept : _Mypair(_Zero_then_variadic_args_t{}, _Ptr) {}

    template <class _Uty, class _Dx2 = _Dx, enable_if_t<is_constructible_v<_Dx2, const _Dx2&>, int> = 0,
        class = _Enable_ctor_reset<_Uty>>
    unique_ptr(_Uty _Ptr, const _Dx& _Dt) noexcept : _Mypair(_One_then_variadic_args_t{}, _Dt, _Ptr) {}

    template <class _Uty, class _Dx2 = _Dx,
        enable_if_t<conjunction_v<negation<is_reference<_Dx2>>, is_constructible<_Dx2, _Dx2>>, int> = 0,
        class = _Enable_ctor_reset<_Uty>>
    unique_ptr(_Uty _Ptr, _Dx&& _Dt) noexcept : _Mypair(_One_then_variadic_args_t{}, _STD move(_Dt), _Ptr) {}

    template <class _Uty, class _Dx2 = _Dx,
        enable_if_t<conjunction_v<is_reference<_Dx2>, is_constructible<_Dx2, remove_reference_t<_Dx2>>>, int> = 0>
    unique_ptr(_Uty, remove_reference_t<_Dx>&&) = delete;

    template <class _Dx2 = _Dx, enable_if_t<is_move_constructible_v<_Dx2>, int> = 0>
    unique_ptr(unique_ptr&& _Right) noexcept
        : _Mypair(_One_then_variadic_args_t{}, _STD forward<_Dx>(_Right.get_deleter()), _Right.release()) {}

    template <class _Dx2 = _Dx, enable_if_t<is_move_assignable_v<_Dx2>, int> = 0>
    unique_ptr& operator=(unique_ptr&& _Right) noexcept {
        if (this != _STD addressof(_Right)) {
            reset(_Right.release());
            _Mypair._Get_first() = _STD move(_Right._Mypair._Get_first());
        }

        return *this;
    }

    template <class _Uty, class _Ex, class _More, class _UP_pointer = typename unique_ptr<_Uty, _Ex>::pointer,
        class _UP_element_type = typename unique_ptr<_Uty, _Ex>::element_type>
    using _Enable_conversion = enable_if_t<
        conjunction_v<is_array<_Uty>, is_same<pointer, element_type*>, is_same<_UP_pointer, _UP_element_type*>,
            is_convertible<_UP_element_type (*)[], element_type (*)[]>, _More>>; // TRANSITION, GH-248

    template <class _Uty, class _Ex,
        class = _Enable_conversion<_Uty, _Ex,
            conditional_t<is_reference_v<_Dx>, is_same<_Ex, _Dx>, is_convertible<_Ex, _Dx>>>>
    unique_ptr(unique_ptr<_Uty, _Ex>&& _Right) noexcept
        : _Mypair(_One_then_variadic_args_t{}, _STD forward<_Ex>(_Right.get_deleter()), _Right.release()) {}

    template <class _Uty, class _Ex, class = _Enable_conversion<_Uty, _Ex, is_assignable<_Dx&, _Ex>>>
    unique_ptr& operator=(unique_ptr<_Uty, _Ex>&& _Right) noexcept {
        reset(_Right.release());
        _Mypair._Get_first() = _STD forward<_Ex>(_Right._Mypair._Get_first());
        return *this;
    }

    template <class _Dx2 = _Dx, _Unique_ptr_enable_default_t<_Dx2> = 0>
    constexpr unique_ptr(nullptr_t) noexcept : _Mypair(_Zero_then_variadic_args_t{}) {}

    unique_ptr& operator=(nullptr_t) noexcept {
        reset();
        return *this;
    }

    void reset(nullptr_t = nullptr) noexcept {
        reset(pointer());
    }

    void swap(unique_ptr& _Right) noexcept {
        _Swap_adl(_Mypair._Myval2, _Right._Mypair._Myval2);
        _Swap_adl(_Mypair._Get_first(), _Right._Mypair._Get_first());
    }

    ~unique_ptr() noexcept {
        if (_Mypair._Myval2) {
            _Mypair._Get_first()(_Mypair._Myval2);
        }
    }

    _NODISCARD _Dx& get_deleter() noexcept {
        return _Mypair._Get_first();
    }

    _NODISCARD const _Dx& get_deleter() const noexcept {
        return _Mypair._Get_first();
    }

    _NODISCARD _Ty& operator[](size_t _Idx) const noexcept /* strengthened */ {
        return _Mypair._Myval2[_Idx];
    }

    _NODISCARD pointer get() const noexcept {
        return _Mypair._Myval2;
    }

    explicit operator bool() const noexcept {
        return static_cast<bool>(_Mypair._Myval2);
    }

    pointer release() noexcept {
        return _STD exchange(_Mypair._Myval2, pointer());
    }

    template <class _Uty, class = _Enable_ctor_reset<_Uty, false_type>>
    void reset(_Uty _Ptr) noexcept {
        pointer _Old = _STD exchange(_Mypair._Myval2, _Ptr);
        if (_Old) {
            _Mypair._Get_first()(_Old);
        }
    }

    unique_ptr(const unique_ptr&) = delete;
    unique_ptr& operator=(const unique_ptr&) = delete;

private:
    template <class, class>
    friend class unique_ptr;

    _Compressed_pair<_Dx, pointer> _Mypair;
};


// FUNCTION TEMPLATE make_unique
template <class _Ty, class... _Types, enable_if_t<!is_array_v<_Ty>, int> = 0>
_NODISCARD unique_ptr<_Ty> make_unique(_Types&&... _Args) { // make a unique_ptr
    return unique_ptr<_Ty>(new _Ty(_STD forward<_Types>(_Args)...));
}

template <class _Ty, enable_if_t<is_array_v<_Ty> && extent_v<_Ty> == 0, int> = 0>
_NODISCARD unique_ptr<_Ty> make_unique(size_t _Size) { // make a unique_ptr
    using _Elem = remove_extent_t<_Ty>;
    return unique_ptr<_Ty>(new _Elem[_Size]());
}

template <class _Ty, class... _Types, enable_if_t<extent_v<_Ty> != 0, int> = 0>
void make_unique(_Types&&...) = delete;

template <class _Ty, class _Dx, enable_if_t<_Is_swappable<_Dx>::value, int> = 0>
void swap(unique_ptr<_Ty, _Dx>& _Left, unique_ptr<_Ty, _Dx>& _Right) noexcept {
    _Left.swap(_Right);
}

template <class _Ty1, class _Dx1, class _Ty2, class _Dx2>
_NODISCARD bool operator==(const unique_ptr<_Ty1, _Dx1>& _Left, const unique_ptr<_Ty2, _Dx2>& _Right) {
    return _Left.get() == _Right.get();
}

template <class _Ty1, class _Dx1, class _Ty2, class _Dx2>
_NODISCARD bool operator!=(const unique_ptr<_Ty1, _Dx1>& _Left, const unique_ptr<_Ty2, _Dx2>& _Right) {
    return !(_Left == _Right);
}

template <class _Ty1, class _Dx1, class _Ty2, class _Dx2>
_NODISCARD bool operator<(const unique_ptr<_Ty1, _Dx1>& _Left, const unique_ptr<_Ty2, _Dx2>& _Right) {
    using _Ptr1   = typename unique_ptr<_Ty1, _Dx1>::pointer;
    using _Ptr2   = typename unique_ptr<_Ty2, _Dx2>::pointer;
    using _Common = common_type_t<_Ptr1, _Ptr2>;
    return less<_Common>()(_Left.get(), _Right.get());
}

template <class _Ty1, class _Dx1, class _Ty2, class _Dx2>
_NODISCARD bool operator>=(const unique_ptr<_Ty1, _Dx1>& _Left, const unique_ptr<_Ty2, _Dx2>& _Right) {
    return !(_Left < _Right);
}

template <class _Ty1, class _Dx1, class _Ty2, class _Dx2>
_NODISCARD bool operator>(const unique_ptr<_Ty1, _Dx1>& _Left, const unique_ptr<_Ty2, _Dx2>& _Right) {
    return _Right < _Left;
}

template <class _Ty1, class _Dx1, class _Ty2, class _Dx2>
_NODISCARD bool operator<=(const unique_ptr<_Ty1, _Dx1>& _Left, const unique_ptr<_Ty2, _Dx2>& _Right) {
    return !(_Right < _Left);
}

template <class _Ty, class _Dx>
_NODISCARD bool operator==(const unique_ptr<_Ty, _Dx>& _Left, nullptr_t) noexcept {
    return !_Left;
}

template <class _Ty, class _Dx>
_NODISCARD bool operator==(nullptr_t, const unique_ptr<_Ty, _Dx>& _Right) noexcept {
    return !_Right;
}

template <class _Ty, class _Dx>
_NODISCARD bool operator!=(const unique_ptr<_Ty, _Dx>& _Left, nullptr_t _Right) noexcept {
    return !(_Left == _Right);
}

template <class _Ty, class _Dx>
_NODISCARD bool operator!=(nullptr_t _Left, const unique_ptr<_Ty, _Dx>& _Right) noexcept {
    return !(_Left == _Right);
}

template <class _Ty, class _Dx>
_NODISCARD bool operator<(const unique_ptr<_Ty, _Dx>& _Left, nullptr_t _Right) {
    using _Ptr = typename unique_ptr<_Ty, _Dx>::pointer;
    return less<_Ptr>()(_Left.get(), _Right);
}

template <class _Ty, class _Dx>
_NODISCARD bool operator<(nullptr_t _Left, const unique_ptr<_Ty, _Dx>& _Right) {
    using _Ptr = typename unique_ptr<_Ty, _Dx>::pointer;
    return less<_Ptr>()(_Left, _Right.get());
}

template <class _Ty, class _Dx>
_NODISCARD bool operator>=(const unique_ptr<_Ty, _Dx>& _Left, nullptr_t _Right) {
    return !(_Left < _Right);
}

template <class _Ty, class _Dx>
_NODISCARD bool operator>=(nullptr_t _Left, const unique_ptr<_Ty, _Dx>& _Right) {
    return !(_Left < _Right);
}

template <class _Ty, class _Dx>
_NODISCARD bool operator>(const unique_ptr<_Ty, _Dx>& _Left, nullptr_t _Right) {
    return _Right < _Left;
}

template <class _Ty, class _Dx>
_NODISCARD bool operator>(nullptr_t _Left, const unique_ptr<_Ty, _Dx>& _Right) {
    return _Right < _Left;
}

template <class _Ty, class _Dx>
_NODISCARD bool operator<=(const unique_ptr<_Ty, _Dx>& _Left, nullptr_t _Right) {
    return !(_Right < _Left);
}

template <class _Ty, class _Dx>
_NODISCARD bool operator<=(nullptr_t _Left, const unique_ptr<_Ty, _Dx>& _Right) {
    return !(_Right < _Left);
}

template <class _OutTy, class _PxTy, class = void>
struct _Can_stream_unique_ptr : false_type {};
template <class _OutTy, class _PxTy>
struct _Can_stream_unique_ptr<_OutTy, _PxTy, void_t<decltype(_STD declval<_OutTy>() << _STD declval<_PxTy>().get())>>
    : true_type {};

template <class _Elem, class _Traits, class _Yty, class _Dx,
    enable_if_t<_Can_stream_unique_ptr<basic_ostream<_Elem, _Traits>&, const unique_ptr<_Yty, _Dx>&>::value, int> = 0>
basic_ostream<_Elem, _Traits>& operator<<(basic_ostream<_Elem, _Traits>& _Out, const unique_ptr<_Yty, _Dx>& _Px) {
    // write contained pointer to stream
    _Out << _Px.get();
    return _Out;
}

// GARBAGE COLLECTION
enum class pointer_safety { relaxed, preferred, strict };

inline void declare_reachable(void*) {}

template <class _Ty>
_Ty* undeclare_reachable(_Ty* _Ptr) {
    return _Ptr;
}

inline void declare_no_pointers(char*, size_t) {}

inline void undeclare_no_pointers(char*, size_t) {}

inline pointer_safety get_pointer_safety() noexcept {
    return pointer_safety::relaxed;
}

// STRUCT TEMPLATE owner_less
template <class _Ty = void>
struct owner_less; // not defined

template <class _Ty>
struct owner_less<shared_ptr<_Ty>> {
    _CXX17_DEPRECATE_ADAPTOR_TYPEDEFS typedef shared_ptr<_Ty> _FIRST_ARGUMENT_TYPE_NAME;
    _CXX17_DEPRECATE_ADAPTOR_TYPEDEFS typedef shared_ptr<_Ty> _SECOND_ARGUMENT_TYPE_NAME;
    _CXX17_DEPRECATE_ADAPTOR_TYPEDEFS typedef bool _RESULT_TYPE_NAME;

    _NODISCARD bool operator()(const shared_ptr<_Ty>& _Left, const shared_ptr<_Ty>& _Right) const noexcept {
        return _Left.owner_before(_Right);
    }

    _NODISCARD bool operator()(const shared_ptr<_Ty>& _Left, const weak_ptr<_Ty>& _Right) const noexcept {
        return _Left.owner_before(_Right);
    }

    _NODISCARD bool operator()(const weak_ptr<_Ty>& _Left, const shared_ptr<_Ty>& _Right) const noexcept {
        return _Left.owner_before(_Right);
    }
};

template <class _Ty>
struct owner_less<weak_ptr<_Ty>> {
    _CXX17_DEPRECATE_ADAPTOR_TYPEDEFS typedef weak_ptr<_Ty> _FIRST_ARGUMENT_TYPE_NAME;
    _CXX17_DEPRECATE_ADAPTOR_TYPEDEFS typedef weak_ptr<_Ty> _SECOND_ARGUMENT_TYPE_NAME;
    _CXX17_DEPRECATE_ADAPTOR_TYPEDEFS typedef bool _RESULT_TYPE_NAME;

    _NODISCARD bool operator()(const weak_ptr<_Ty>& _Left, const weak_ptr<_Ty>& _Right) const noexcept {
        return _Left.owner_before(_Right);
    }

    _NODISCARD bool operator()(const weak_ptr<_Ty>& _Left, const shared_ptr<_Ty>& _Right) const noexcept {
        return _Left.owner_before(_Right);
    }

    _NODISCARD bool operator()(const shared_ptr<_Ty>& _Left, const weak_ptr<_Ty>& _Right) const noexcept {
        return _Left.owner_before(_Right);
    }
};

template <>
struct owner_less<void> {
    template <class _Ty, class _Uty>
    _NODISCARD bool operator()(const shared_ptr<_Ty>& _Left, const shared_ptr<_Uty>& _Right) const noexcept {
        return _Left.owner_before(_Right);
    }

    template <class _Ty, class _Uty>
    _NODISCARD bool operator()(const shared_ptr<_Ty>& _Left, const weak_ptr<_Uty>& _Right) const noexcept {
        return _Left.owner_before(_Right);
    }

    template <class _Ty, class _Uty>
    _NODISCARD bool operator()(const weak_ptr<_Ty>& _Left, const shared_ptr<_Uty>& _Right) const noexcept {
        return _Left.owner_before(_Right);
    }

    template <class _Ty, class _Uty>
    _NODISCARD bool operator()(const weak_ptr<_Ty>& _Left, const weak_ptr<_Uty>& _Right) const noexcept {
        return _Left.owner_before(_Right);
    }

    using is_transparent = int;
};

// STRUCT TEMPLATE SPECIALIZATION hash
template <class _Ty, class _Dx>
struct hash<unique_ptr<_Ty, _Dx>> : _Conditionally_enabled_hash<unique_ptr<_Ty, _Dx>,
                                        is_default_constructible_v<hash<typename unique_ptr<_Ty, _Dx>::pointer>>> {
    static size_t _Do_hash(const unique_ptr<_Ty, _Dx>& _Keyval) noexcept(
        _Is_nothrow_hashable<typename unique_ptr<_Ty, _Dx>::pointer>::value) {
        return hash<typename unique_ptr<_Ty, _Dx>::pointer>{}(_Keyval.get());
    }
};

template <class _Ty>
struct hash<shared_ptr<_Ty>> {
    _CXX17_DEPRECATE_ADAPTOR_TYPEDEFS typedef shared_ptr<_Ty> _ARGUMENT_TYPE_NAME;
    _CXX17_DEPRECATE_ADAPTOR_TYPEDEFS typedef size_t _RESULT_TYPE_NAME;

    _NODISCARD size_t operator()(const shared_ptr<_Ty>& _Keyval) const noexcept {
        return hash<typename shared_ptr<_Ty>::element_type*>()(_Keyval.get());
    }
};

// FUNCTION align
inline void* align(size_t _Bound, size_t _Size, void*& _Ptr, size_t& _Space) noexcept /* strengthened */ {
    // try to carve out _Size bytes on boundary _Bound
    size_t _Off = static_cast<size_t>(reinterpret_cast<uintptr_t>(_Ptr) & (_Bound - 1));
    if (_Off != 0) {
        _Off = _Bound - _Off; // number of bytes to skip
    }

    if (_Space < _Off || _Space - _Off < _Size) {
        return nullptr;
    }

    // enough room, update
    _Ptr = static_cast<char*>(_Ptr) + _Off;
    _Space -= _Off;
    return _Ptr;
}

#if _HAS_CXX20 && 0
template <size_t _N0, class _Ty>
_NODISCARD constexpr _Ty* assume_aligned(_Ty* _Ptr) noexcept /* strengthened */ {
    // this enforces the requirement that _N0 be a power of two
    __builtin_assume_aligned(_Ptr, _N0);

    return _Ptr;
}
#endif // _HAS_CXX20 && 0

// SPIN LOCKS
_EXTERN_C
_CRTIMP2_PURE void __cdecl _Lock_shared_ptr_spin_lock();
_CRTIMP2_PURE void __cdecl _Unlock_shared_ptr_spin_lock();
_END_EXTERN_C

// WRAP SPIN-LOCK
struct _Shared_ptr_spin_lock { // class to manage a spin lock for shared_ptr atomic operations
    _Shared_ptr_spin_lock() { // lock the spin lock
        _Lock_shared_ptr_spin_lock();
    }

    ~_Shared_ptr_spin_lock() noexcept { // unlock the spin lock
        _Unlock_shared_ptr_spin_lock();
    }
};

template <class _Ty>
_CXX20_DEPRECATE_OLD_SHARED_PTR_ATOMIC_SUPPORT _NODISCARD bool atomic_is_lock_free(const shared_ptr<_Ty>*) {
    // return true if atomic operations on shared_ptr<_Ty> are lock-free
    return false;
}

template <class _Ty>
_CXX20_DEPRECATE_OLD_SHARED_PTR_ATOMIC_SUPPORT _NODISCARD shared_ptr<_Ty> atomic_load_explicit(
    const shared_ptr<_Ty>* _Ptr, memory_order) {
    // load *_Ptr atomically
    _Shared_ptr_spin_lock _Lock;
    shared_ptr<_Ty> _Result = *_Ptr;
    return _Result;
}

template <class _Ty>
_CXX20_DEPRECATE_OLD_SHARED_PTR_ATOMIC_SUPPORT _NODISCARD shared_ptr<_Ty> atomic_load(
    const shared_ptr<_Ty>* _Ptr) { // load *_Ptr atomically
    return _STD atomic_load_explicit(_Ptr, memory_order_seq_cst);
}

template <class _Ty>
_CXX20_DEPRECATE_OLD_SHARED_PTR_ATOMIC_SUPPORT void atomic_store_explicit(
    shared_ptr<_Ty>* _Ptr, shared_ptr<_Ty> _Other, memory_order) {
    // store _Other to *_Ptr atomically
    _Shared_ptr_spin_lock _Lock;
    _Ptr->swap(_Other);
}

template <class _Ty>
_CXX20_DEPRECATE_OLD_SHARED_PTR_ATOMIC_SUPPORT void atomic_store(
    shared_ptr<_Ty>* _Ptr, shared_ptr<_Ty> _Other) { // store _Other to *_Ptr atomically
    _STD atomic_store_explicit(_Ptr, _STD move(_Other), memory_order_seq_cst);
}

template <class _Ty>
_CXX20_DEPRECATE_OLD_SHARED_PTR_ATOMIC_SUPPORT shared_ptr<_Ty> atomic_exchange_explicit(
    shared_ptr<_Ty>* _Ptr, shared_ptr<_Ty> _Other, memory_order) {
    // copy _Other to *_Ptr and return previous value of *_Ptr atomically
    _Shared_ptr_spin_lock _Lock;
    _Ptr->swap(_Other);
    return _Other;
}

template <class _Ty>
_CXX20_DEPRECATE_OLD_SHARED_PTR_ATOMIC_SUPPORT shared_ptr<_Ty> atomic_exchange(
    shared_ptr<_Ty>* _Ptr, shared_ptr<_Ty> _Other) {
    // copy _Other to *_Ptr and return previous value of *_Ptr atomically
    return _STD atomic_exchange_explicit(_Ptr, _STD move(_Other), memory_order_seq_cst);
}

template <class _Ty>
_CXX20_DEPRECATE_OLD_SHARED_PTR_ATOMIC_SUPPORT bool atomic_compare_exchange_weak_explicit(shared_ptr<_Ty>* _Ptr,
    shared_ptr<_Ty>* _Exp, shared_ptr<_Ty> _Value, memory_order, memory_order) { // atomically compare and exchange
    shared_ptr<_Ty> _Old_exp; // destroyed outside spin lock
    _Shared_ptr_spin_lock _Lock;
    bool _Success = _Ptr->get() == _Exp->get() && !_Ptr->owner_before(*_Exp) && !_Exp->owner_before(*_Ptr);
    if (_Success) {
        _Ptr->swap(_Value);
    } else { // match failed
        _Exp->swap(_Old_exp);
        *_Exp = *_Ptr;
    }
    return _Success;
}

template <class _Ty>
_CXX20_DEPRECATE_OLD_SHARED_PTR_ATOMIC_SUPPORT bool atomic_compare_exchange_weak(
    shared_ptr<_Ty>* _Ptr, shared_ptr<_Ty>* _Exp, shared_ptr<_Ty> _Value) {
    // atomically compare and exchange
    return _STD atomic_compare_exchange_weak_explicit(
        _Ptr, _Exp, _STD move(_Value), memory_order_seq_cst, memory_order_seq_cst);
}

template <class _Ty>
_CXX20_DEPRECATE_OLD_SHARED_PTR_ATOMIC_SUPPORT bool atomic_compare_exchange_strong_explicit(shared_ptr<_Ty>* _Ptr,
    shared_ptr<_Ty>* _Exp, shared_ptr<_Ty> _Value, memory_order, memory_order) { // atomically compare and exchange
    return _STD atomic_compare_exchange_weak_explicit(
        _Ptr, _Exp, _STD move(_Value), memory_order_seq_cst, memory_order_seq_cst);
}

template <class _Ty>
_CXX20_DEPRECATE_OLD_SHARED_PTR_ATOMIC_SUPPORT bool atomic_compare_exchange_strong(
    shared_ptr<_Ty>* _Ptr, shared_ptr<_Ty>* _Exp, shared_ptr<_Ty> _Value) {
    // atomically compare and exchange
    return _STD atomic_compare_exchange_strong_explicit(
        _Ptr, _Exp, _STD move(_Value), memory_order_seq_cst, memory_order_seq_cst);
}

#if _HAS_CXX20
template <class _Ty>
class alignas(2 * sizeof(void*)) _Atomic_ptr_base {
    // overalignment is to allow potential future use of cmpxchg16b
protected:
    constexpr _Atomic_ptr_base() noexcept = default;

    _Atomic_ptr_base(_Ty* const _Px, _Ref_count_base* const _Ref) noexcept
        : _Ptr(_Px), _Repptr(reinterpret_cast<uintptr_t>(_Ref)) {}

    _NODISCARD _Ref_count_base* _Lock_and_load() const noexcept {
        constexpr uintptr_t _Low_bit = 1;
        uintptr_t _Rep               = _Repptr.load(memory_order::relaxed);
        for (;;) {
            _Rep &= ~_Low_bit;
            if (_Repptr.compare_exchange_weak(_Rep, _Rep | _Low_bit)) {
                return reinterpret_cast<_Ref_count_base*>(_Rep);
            }

            _YIELD_PROCESSOR();
        }
    }

    void _Store_and_unlock(_Ref_count_base* const _Value) const noexcept {
        _Repptr.store(reinterpret_cast<uintptr_t>(_Value));
    }

    _Ty* _Ptr = nullptr;
    mutable atomic<uintptr_t> _Repptr{0};
};

template <class _Ty>
struct atomic<shared_ptr<_Ty>> : private _Atomic_ptr_base<_Ty> {
private:
    using _Base = _Atomic_ptr_base<_Ty>;

public:
    using value_type = shared_ptr<_Ty>;

    static constexpr bool is_always_lock_free = false;

    _NODISCARD bool is_lock_free() const noexcept {
        return false;
    }

    void store(shared_ptr<_Ty> _Value, const memory_order _Order = memory_order::seq_cst) noexcept {
        _Check_store_memory_order(_Order);
        const auto _Rep = this->_Lock_and_load();
        _STD swap(this->_Ptr, _Value._Ptr);
        this->_Store_and_unlock(_Value._Rep);
        _Value._Rep = _Rep;
    }

    _NODISCARD shared_ptr<_Ty> load(const memory_order _Order = memory_order::seq_cst) const noexcept {
        _Check_load_memory_order(_Order);
        shared_ptr<_Ty> _Result;
        const auto _Rep = this->_Lock_and_load();
        _Result._Ptr    = this->_Ptr;
        _Result._Rep    = _Rep;
        _Result._Incref();
        this->_Store_and_unlock(_Rep);
        return _Result;
    }

    operator shared_ptr<_Ty>() const noexcept {
        return load();
    }

    shared_ptr<_Ty> exchange(shared_ptr<_Ty> _Value, const memory_order _Order = memory_order::seq_cst) noexcept {
        _Check_memory_order(_Order);
        shared_ptr<_Ty> _Result;
        _Result._Rep = this->_Lock_and_load();
        _Result._Ptr = this->_Ptr;
        this->_Ptr   = _Value._Ptr;
        this->_Store_and_unlock(_Value._Rep);
        _Value._Ptr = nullptr; // ownership of _Value ref has been given to this, silence decrement
        _Value._Rep = nullptr;
        return _Result;
    }

    bool compare_exchange_weak(shared_ptr<_Ty>& _Expected, shared_ptr<_Ty> _Desired, const memory_order _Success,
        const memory_order _Failure) noexcept {
        return compare_exchange_strong(_Expected, _STD move(_Desired), _Combine_cas_memory_orders(_Success, _Failure));
    }

    bool compare_exchange_strong(shared_ptr<_Ty>& _Expected, shared_ptr<_Ty> _Desired, const memory_order _Success,
        const memory_order _Failure) noexcept {
        return compare_exchange_strong(_Expected, _STD move(_Desired), _Combine_cas_memory_orders(_Success, _Failure));
    }

    bool compare_exchange_weak(shared_ptr<_Ty>& _Expected, shared_ptr<_Ty> _Desired,
        const memory_order _Order = memory_order::seq_cst) noexcept {
        return compare_exchange_strong(_Expected, _STD move(_Desired), _Order);
    }

    bool compare_exchange_strong(shared_ptr<_Ty>& _Expected, shared_ptr<_Ty> _Desired,
        const memory_order _Order = memory_order::seq_cst) noexcept {
        _Check_memory_order(_Order);
        auto _Rep = this->_Lock_and_load();
        if (this->_Ptr == _Expected._Ptr && _Rep == _Expected._Rep) {
            _STD swap(this->_Ptr, _Desired._Ptr);
            _STD swap(_Rep, _Desired._Rep);
            this->_Store_and_unlock(_Rep);
            return true;
        }
        _Ref_count_base* _Expected_rep = _Expected._Rep;
        _Expected._Ptr                 = this->_Ptr;
        _Expected._Rep                 = _Rep;
        _Expected._Incref();
        this->_Store_and_unlock(_Rep);
        if (_Expected_rep) {
            _Expected_rep->_Decref();
        }
        return false;
    }

    constexpr atomic() noexcept = default;

    atomic(const shared_ptr<_Ty> _Value) noexcept : _Base(_Value._Ptr, _Value._Rep) {
        _Value._Incref();
    }

    atomic(const atomic&) = delete;
    void operator=(const atomic&) = delete;

    void operator=(shared_ptr<_Ty> _Value) noexcept {
        store(_STD move(_Value));
    }

    ~atomic() {
        const auto _Rep = reinterpret_cast<_Ref_count_base*>(this->_Repptr.load(memory_order::relaxed));
        if (_Rep) {
            _Rep->_Decref();
        }
    }
};

template <class _Ty>
struct atomic<weak_ptr<_Ty>> : private _Atomic_ptr_base<_Ty> {
private:
    using _Base = _Atomic_ptr_base<_Ty>;

public:
    using value_type = weak_ptr<_Ty>;

    static constexpr bool is_always_lock_free = false;

    _NODISCARD bool is_lock_free() const noexcept {
        return false;
    }

    void store(weak_ptr<_Ty> _Value, const memory_order _Order = memory_order::seq_cst) noexcept {
        _Check_store_memory_order(_Order);
        const auto _Rep = this->_Lock_and_load();
        _STD swap(this->_Ptr, _Value._Ptr);
        this->_Store_and_unlock(_Value._Rep);
        _Value._Rep = _Rep;
    }

    _NODISCARD weak_ptr<_Ty> load(const memory_order _Order = memory_order::seq_cst) const noexcept {
        _Check_load_memory_order(_Order);
        weak_ptr<_Ty> _Result;
        const auto _Rep = this->_Lock_and_load();
        _Result._Ptr    = this->_Ptr;
        _Result._Rep    = _Rep;
        _Result._Incwref();
        this->_Store_and_unlock(_Rep);
        return _Result;
    }

    operator weak_ptr<_Ty>() const noexcept {
        return load();
    }

    weak_ptr<_Ty> exchange(weak_ptr<_Ty> _Value, const memory_order _Order = memory_order::seq_cst) noexcept {
        _Check_memory_order(_Order);
        weak_ptr<_Ty> _Result;
        _Result._Rep = this->_Lock_and_load();
        _Result._Ptr = this->_Ptr;
        this->_Ptr   = _Value._Ptr;
        this->_Store_and_unlock(_Value._Rep);
        _Value._Ptr = nullptr; // ownership of _Value ref has been given to this, silence decrement
        _Value._Rep = nullptr;
        return _Result;
    }

    bool compare_exchange_weak(weak_ptr<_Ty>& _Expected, weak_ptr<_Ty> _Desired, const memory_order _Success,
        const memory_order _Failure) noexcept {
        return compare_exchange_strong(_Expected, _STD move(_Desired), _Combine_cas_memory_orders(_Success, _Failure));
    }

    bool compare_exchange_strong(weak_ptr<_Ty>& _Expected, weak_ptr<_Ty> _Desired, const memory_order _Success,
        const memory_order _Failure) noexcept {
        return compare_exchange_strong(_Expected, _STD move(_Desired), _Combine_cas_memory_orders(_Success, _Failure));
    }

    bool compare_exchange_weak(
        weak_ptr<_Ty>& _Expected, weak_ptr<_Ty> _Desired, const memory_order _Order = memory_order::seq_cst) noexcept {
        return compare_exchange_strong(_Expected, _STD move(_Desired), _Order);
    }

    bool compare_exchange_strong(
        weak_ptr<_Ty>& _Expected, weak_ptr<_Ty> _Desired, const memory_order _Order = memory_order::seq_cst) noexcept {
        _Check_memory_order(_Order);
        auto _Rep = this->_Lock_and_load();
        if (this->_Ptr == _Expected._Ptr && _Rep == _Expected._Rep) {
            _STD swap(this->_Ptr, _Desired._Ptr);
            _STD swap(_Rep, _Desired._Rep);
            this->_Store_and_unlock(_Rep);
            return true;
        }
        const auto _Expected_rep = _Expected._Rep;
        _Expected._Ptr           = this->_Ptr;
        _Expected._Rep           = _Rep;
        _Expected._Incwref();
        this->_Store_and_unlock(_Rep);
        if (_Expected_rep) {
            _Expected_rep->_Decwref();
        }
        return false;
    }

    constexpr atomic() noexcept = default;

    atomic(const weak_ptr<_Ty> _Value) noexcept : _Base(_Value._Ptr, _Value._Rep) {
        _Value._Incwref();
    }

    atomic(const atomic&) = delete;
    void operator=(const atomic&) = delete;

    void operator=(weak_ptr<_Ty> _Value) noexcept {
        store(_STD move(_Value));
    }

    ~atomic() {
        const auto _Rep = reinterpret_cast<_Ref_count_base*>(this->_Repptr.load(memory_order::relaxed));
        if (_Rep) {
            _Rep->_Decwref();
        }
    }
};
#endif // _HAS_CXX20

#if _HAS_TR1_NAMESPACE
namespace _DEPRECATE_TR1_NAMESPACE tr1 {
    using _STD allocate_shared;
    using _STD bad_weak_ptr;
    using _STD const_pointer_cast;
    using _STD dynamic_pointer_cast;
    using _STD enable_shared_from_this;
    using _STD get_deleter;
    using _STD make_shared;
    using _STD shared_ptr;
    using _STD static_pointer_cast;
    using _STD swap;
    using _STD weak_ptr;
} // namespace tr1
#endif // _HAS_TR1_NAMESPACE

_STD_END
#pragma pop_macro("new")
_STL_RESTORE_CLANG_WARNINGS
#pragma warning(pop)
#pragma pack(pop)
#endif // _STL_COMPILER_PREPROCESSOR
#endif // _MEMORY_
