//*********************************************************
//
// This header provides the functions for ADL of Range concept
// to WIL's unique_something_string (wil::unique_any<PWSTR, ...>).
// The functions are data, begin, end, empty, size, etc.
// 
// This header also provides make_range_* to supports
// WIL's exception policy.
// 
// WIL is copyrighted by Microsoft under the MIT License.
//
//*********************************************************

#pragma once

#ifndef __WIL_COM_INCLUDED
#error "wil/com.h" or <wil/com.h> should be included.
#endif

namespace wil
{
	template <typename close_fn_t, close_fn_t close_fn>
	inline PWSTR data(wil::unique_any<PWSTR, close_fn_t, close_fn>& s) noexcept
	{
		return s.get();
	}
	template <typename close_fn_t, close_fn_t close_fn>
	inline PCWSTR data(const wil::unique_any<PWSTR, close_fn_t, close_fn>& s) noexcept
	{
		return s.get();
	}
	template <typename close_fn_t, close_fn_t close_fn>
	inline PWSTR begin(wil::unique_any<PWSTR, close_fn_t, close_fn>& s) noexcept
	{
		return s.get();
	}
	template <typename close_fn_t, close_fn_t close_fn>
	inline PCWSTR begin(const wil::unique_any<PWSTR, close_fn_t, close_fn>& s) noexcept
	{
		return s.get();
	}
	template <typename close_fn_t, close_fn_t close_fn>
	inline bool empty(const wil::unique_any<PWSTR, close_fn_t, close_fn>& s) noexcept
	{
		return !s;
	}

	template <typename close_fn_t, close_fn_t close_fn>
	size_t size(const wil::unique_any<PWSTR, close_fn_t, close_fn>& s)
	{
		wil::com_ptr<IMalloc> allocator;
		THROW_IF_FAILED(::CoGetMalloc(1, allocator.put()));
		return allocator->GetSize(s.get()) / sizeof(wchar_t);
	}
	template <typename close_fn_t, close_fn_t close_fn>
	size_t size_failfast(const wil::unique_any<PWSTR, close_fn_t, close_fn>& s) noexcept
	{
		wil::com_ptr_failfast<IMalloc> allocator;
		FAIL_FAST_IF_FAILED(::CoGetMalloc(1, allocator.put()));
		return allocator->GetSize(s.get()) / sizeof(wchar_t);
	}
	template <typename close_fn_t, close_fn_t close_fn>
	HRESULT size_nothrow(const wil::unique_any<PWSTR, close_fn_t, close_fn>& s, size_t& result) noexcept
	{
		wil::com_ptr_nothrow<IMalloc> allocator;
		RETURN_IF_FAILED(::CoGetMalloc(1, allocator.put()));
		result = allocator->GetSize(s.get()) / sizeof(wchar_t);
		return S_OK;
	}

	template <typename close_fn_t, close_fn_t close_fn>
	inline PWSTR end(wil::unique_any<PWSTR, close_fn_t, close_fn>& s)
	{
		return begin(s) + size(s);
	}
	template <typename close_fn_t, close_fn_t close_fn>
	inline PCWSTR end(const wil::unique_any<PWSTR, close_fn_t, close_fn>& s)
	{
		return begin(s) + size(s);
	}
	template <typename close_fn_t, close_fn_t close_fn>
	inline PWSTR end_failfast(wil::unique_any<PWSTR, close_fn_t, close_fn>& s) noexcept
	{
		return begin(s) + size_failfast(s);
	}
	template <typename close_fn_t, close_fn_t close_fn>
	inline PCWSTR end_failfast(const wil::unique_any<PWSTR, close_fn_t, close_fn>& s) noexcept
	{
		return begin(s) + size_failfast(s);
	}
	template <typename close_fn_t, close_fn_t close_fn>
	inline HRESULT end_nothrow(wil::unique_any<PWSTR, close_fn_t, close_fn>& s, PWSTR& result) noexcept
	{
		size_t size;
		RETURN_IF_FAILED(size_nothrow(s, size));
		result = begin(s) + size;
		return S_OK;
	}
	template <typename close_fn_t, close_fn_t close_fn>
	inline HRESULT end_nothrow(const wil::unique_any<PWSTR, close_fn_t, close_fn>& s, PCWSTR& result) noexcept
	{
		size_t size;
		RETURN_IF_FAILED(size_nothrow(s, size));
		result = begin(s) + size;
		return S_OK;
	}

	template <typename close_fn_t, close_fn_t close_fn>
	inline details::pointer_range<PWSTR> make_range(wil::unique_any<PWSTR, close_fn_t, close_fn>& s)
	{
		return wil::make_range(begin(s), end(s));
	}
	template <typename close_fn_t, close_fn_t close_fn>
	inline details::pointer_range<PWSTR> make_range_failfast(wil::unique_any<PWSTR, close_fn_t, close_fn>& s) noexcept
	{
		return wil::make_range(begin(s), end_failfast(s));
	}
	template <typename close_fn_t, close_fn_t close_fn>
	inline HRESULT make_range_nothrow(wil::unique_any<PWSTR, close_fn_t, close_fn>& s, details::pointer_range<PWSTR>& result) noexcept
	{
		PWSTR end;
		RETURN_IF_FAILED(end_nothrow(s, end));
		result = wil::make_range(begin(s), end);
		return S_OK;
	}

	template <typename close_fn_t, close_fn_t close_fn>
	inline details::pointer_range<PCWSTR> make_range(const wil::unique_any<PWSTR, close_fn_t, close_fn>& s)
	{
		return wil::make_range(begin(s), end(s));
	}
	template <typename close_fn_t, close_fn_t close_fn>
	inline details::pointer_range<PCWSTR> make_range_failfast(const wil::unique_any<PWSTR, close_fn_t, close_fn>& s) noexcept
	{
		return wil::make_range(begin(s), end_failfast(s));
	}
	template <typename close_fn_t, close_fn_t close_fn>
	inline HRESULT make_range_nothrow(const wil::unique_any<PWSTR, close_fn_t, close_fn>& s, details::pointer_range<PCWSTR>& result) noexcept
	{
		PCWSTR end;
		RETURN_IF_FAILED(end_nothrow(s, end));
		result = wil::make_range(begin(s), end);
		return S_OK;
	}
}