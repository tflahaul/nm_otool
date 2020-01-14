/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libsimd.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 12:34:53 by thflahau          #+#    #+#             */
/*   Updated: 2020/01/14 10:38:49 by thflahau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __LIBSIMD_H__
# define __LIBSIMD_H__

# ifndef __SSE4_1__
#  error "Please add -msse4 to your compilation flags"
# endif
# include <smmintrin.h>
# include <sys/types.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdint.h>

# ifdef __GNUC__
#  define __CCV (__GNUC__ * 10000 + __GNUC_MINOR__ * 100 + __GNUC_PATCHLEVEL__)

#  if __CCV > 29600
#   define __likely(x)		__builtin_expect((x), 1)
#   define __unlikely(x)	__builtin_expect((x), 0)

#  else
#   define __likely(x)		(x)
#   define __unlikely(x)	(x)
#  endif /* __CCV */

#  if defined __STDC_VERSION__ && __STDC_VERSION__ >= 199901L
#   define __restrict		restrict
#  else
#   define __restrict	// Ignore
#  endif /* __STDC_VERSION__ */

# else
#  error "Your compiler does not use the C preprocessor, try using GCC"
# endif /* __GNUC__ */

# ifndef __pure
#  define __pure		__attribute__((pure))
# endif /* __pure */

# define FLAG_SBL	(_SIDD_SBYTE_OPS | _SIDD_CMP_EQUAL_EACH | _SIDD_LEAST_SIGNIFICANT)
# define FLAG_SBM	(_SIDD_SBYTE_OPS | _SIDD_CMP_EQUAL_ANY | _SIDD_MOST_SIGNIFICANT)
# define M128_SZ		16

struct				s_obj_string
{
	char			*str;
	size_t			length;
	size_t			capacity;
};

/*
**	Strings (regular C strings)
*/

/* Return the length of @str */
__pure size_t			ft_strlen(char const *__restrict str)
{
	char			*ptr = (char *)str;
	__m128i			chunk;
	__m128i			*longword = (__m128i *)__builtin_assume_aligned(ptr, M128_SZ);
	__m128i const		set = _mm_setzero_si128();

	if (__unlikely(!str[0]))
		return (0);
	for (;; longword++)
	{
		chunk = _mm_loadu_si128(longword);
		if (_mm_cmpistrc(set, chunk, FLAG_SBL))
		{
			ptr = (char *)longword + _mm_cmpistri(set, chunk, FLAG_SBL);
			return ((size_t)(ptr - (char *)str));
		}
	}
	return (0);
}

/* Find the first occurrence of @c in @str */
__pure char			*ft_strchr(char const *__restrict str, int c)
{
	__m128i			chunk;
	__m128i			*longword = (__m128i *)__builtin_assume_aligned(str, M128_SZ);
	__m128i const		set = _mm_setr_epi8(c, 0, 0, 0, 0, 0, 0, 0,
						0, 0, 0, 0, 0, 0, 0, 0);

	for (;; longword++)
	{
		chunk = _mm_loadu_si128(longword);
		if (_mm_cmpistrc(set, chunk, FLAG_SBM))
			return ((char *)longword + _mm_cmpistri(set, chunk, FLAG_SBM));
		else if (_mm_cmpistrz(set, chunk, FLAG_SBM))
			break ;
	}
	return (NULL);
}

/* Find the last occurrence of @c in @str */
__pure char			*ft_strrchr(char const *__restrict str, int c)
{
	char			*ptr = NULL;
	__m128i			chunk;
	__m128i			*longword = (__m128i *)__builtin_assume_aligned(str, M128_SZ);
	__m128i const		set = _mm_setr_epi8(c, 0, 0, 0, 0, 0, 0, 0,
							0, 0, 0, 0, 0, 0, 0, 0);

	for (;; longword++)
	{
		chunk = _mm_loadu_si128(longword);
		if (_mm_cmpistrc(set, chunk, FLAG_SBM))
			ptr = (char *)longword + _mm_cmpistri(set, chunk, FLAG_SBM);
		else if (_mm_cmpistrz(set, chunk, FLAG_SBM))
			break ;
	}
	return (ptr);
}

/*
**	Memory
*/

/* Set @size bytes of @ptr to 0 */
void				ft_bzero(void *__restrict ptr, size_t size)
{
	uint8_t			*mem;
	__m128i			*longword = (__m128i *)__builtin_assume_aligned(ptr, M128_SZ);
	__m128i const		set = _mm_setzero_si128();

	for (; size >= M128_SZ; size -= M128_SZ)
		_mm_storeu_si128(longword++, set);
	mem = (uint8_t *)longword;
	while (size-- > 0)
		*mem++ = 0;
}

/* Copy the first @size bytes of @src to @dst */
void				ft_memcpy(void *__restrict dst, void *__restrict src, size_t size)
{
	uint8_t			*ptd, *pts;
	__m128i			*dstlongword = (__m128i *)__builtin_assume_aligned(dst, M128_SZ);
	__m128i			*srclongword = (__m128i *)__builtin_assume_aligned(src, M128_SZ);

	for (; size >= M128_SZ; size -= M128_SZ)
		_mm_storeu_si128(dstlongword++, _mm_loadu_si128(srclongword++));
	ptd = (uint8_t *)dstlongword;
	pts = (uint8_t *)srclongword;
	while (size-- > 0)
		*ptd++ = *pts++;
}

/* Set the first @size bytes of @dst to @c */
void				*ft_memset(void *__restrict dst, int c, size_t size)
{
	uint8_t			*ptr;
	__m128i			*longword = (__m128i *)__builtin_assume_aligned(dst, M128_SZ);
	__m128i const		set = _mm_set1_epi8(c);

	for (; size >= M128_SZ; size -= M128_SZ)
		_mm_storeu_si128(longword++, set);
	ptr = (uint8_t *)longword;
	while (size-- > 0)
		*ptr++ = c;
	return (dst);
}

/* Compare the first @size bytes of @a and @b. Returns a boolean. */
__pure int			ft_memcmp(void *__restrict a, void *__restrict b, size_t size)
{
	uint8_t			*a8, *b8;
	__m128i			*a128 = (__m128i *)__builtin_assume_aligned(a, M128_SZ);
	__m128i			*b128 = (__m128i *)__builtin_assume_aligned(b, M128_SZ);

	for (; size >= M128_SZ; size -= M128_SZ)
		if (_mm_comineq_ss((__m128)_mm_loadu_si128(a128++), (__m128)_mm_loadu_si128(b128++)))
			return (1);
	a8 = (uint8_t *)a128;
	b8 = (uint8_t *)b128;
	while (size-- > 0)
		if (*a8++ != *b8++)
			return (1);
	return (0);
}

#endif /* __LIBSIMD_H__ */
