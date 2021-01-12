/*
 * This file is part of the CitizenFX project - http://citizen.re/
 *
 * See LICENSE and MENTIONS in the root of the source tree for information
 * regarding licensing.
 */

#pragma once

#include <cassert>
#include <vector>
#include <string_view>

#pragma warning(push)
#pragma warning(disable:4201)

namespace hook
{
	class pattern_match
	{
	private:
		void* m_pointer;

	public:
		inline pattern_match(void* pointer)
			: m_pointer(pointer)
		{
		}

		template<typename T>
		T* get(ptrdiff_t offset = 0) const
		{
			char* ptr = reinterpret_cast<char*>(m_pointer);
			return reinterpret_cast<T*>(ptr + offset);
		}
	};

	class pattern
	{
	private:
		std::basic_string<uint8_t> m_bytes;
		std::basic_string<uint8_t> m_mask;

#if PATTERNS_USE_HINTS
		uint64_t m_hash = 0;
#endif

		std::vector<pattern_match> m_matches;

		bool m_matched = false;

		uintptr_t m_rangeStart;
		uintptr_t m_rangeEnd;

	private:
		static ptrdiff_t get_process_base();

		void Initialize(std::string_view pattern);

		bool ConsiderHint(uintptr_t offset);

		void EnsureMatches(uint32_t maxCount);

		inline pattern_match _get_internal(size_t index) const
		{
			return m_matches[index];
		}

		inline pattern(uintptr_t module)
			: pattern( module, 0 )
		{
		}

		inline pattern(uintptr_t begin, uintptr_t end)
			: m_rangeStart(begin), m_rangeEnd(end)
		{
		}

	public:
		explicit pattern(std::string_view pattern)
			: pattern(get_process_base())
		{
			Initialize(std::move(pattern));
		}

		inline pattern(void* module, std::string_view pattern)
			: pattern(reinterpret_cast<uintptr_t>(module))
		{
			Initialize(std::move(pattern));
		}

		inline pattern(uintptr_t begin, uintptr_t end, std::string_view pattern)
			: m_rangeStart(begin), m_rangeEnd(end)
		{
			Initialize(std::move(pattern));
		}

		// Pretransformed patterns
		inline pattern(std::basic_string_view<uint8_t> bytes, std::basic_string_view<uint8_t> mask)
			: pattern(get_process_base())
		{
			assert( bytes.length() == mask.length() );
			m_bytes = std::move(bytes);
			m_mask = std::move(mask);
		}

		inline pattern&& count(uint32_t expected)
		{
			EnsureMatches(expected);
			assert(m_matches.size() == expected);
			return std::forward<pattern>(*this);
		}

		inline pattern&& count_hint(uint32_t expected)
		{
			EnsureMatches(expected);
			return std::forward<pattern>(*this);
		}

		inline pattern&& clear()
		{
			m_matches.clear();
			m_matched = false;
			return std::forward<pattern>(*this);
		}

		inline size_t size()
		{
			EnsureMatches(UINT32_MAX);
			return m_matches.size();
		}

		inline bool empty()
		{
			return size() == 0;
		}

		inline pattern_match get(size_t index)
		{
			EnsureMatches(UINT32_MAX);
			return _get_internal(index);
		}

		inline pattern_match get_one()
		{
			return std::forward<pattern>(*this).count(1)._get_internal(0);
		}

		template<typename T = void>
		inline auto get_first(ptrdiff_t offset = 0)
		{
			return get_one().get<T>(offset);
		}

		template <typename Pred>
		inline Pred for_each_result(Pred&& pred)
		{
			EnsureMatches(UINT32_MAX);
			for ( auto it : m_matches )
			{
				std::forward<Pred>(pred)(it);
			}
			return std::forward<Pred>(pred);
		}

	public:
#if PATTERNS_USE_HINTS && PATTERNS_CAN_SERIALIZE_HINTS
		// define a hint
		static void hint(uint64_t hash, uintptr_t address);
#endif
	};

	inline pattern make_module_pattern(void* module, std::string_view bytes)
	{
		return pattern(module, std::move(bytes));
	}

	inline pattern make_range_pattern(uintptr_t begin, uintptr_t end, std::string_view bytes)
	{
		return pattern(begin, end, std::move(bytes));
	}

	template<typename T = void>
	inline auto get_pattern(std::string_view pattern_string, ptrdiff_t offset = 0)
	{
		return pattern(std::move(pattern_string)).get_first<T>(offset);
	}
}

#pragma warning(pop)