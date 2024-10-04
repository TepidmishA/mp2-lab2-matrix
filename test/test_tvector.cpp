#include "utmatrix.h"

#include <gtest.h>

TEST(TVector, can_create_vector_with_positive_length)
{
  ASSERT_NO_THROW(TVector<int> v(5));
}

TEST(TVector, cant_create_too_large_vector)
{
  ASSERT_ANY_THROW(TVector<int> v(MAX_VECTOR_SIZE + 1));
}

TEST(TVector, throws_when_create_vector_with_negative_length)
{
  ASSERT_ANY_THROW(TVector<int> v(-5));
}

TEST(TVector, throws_when_create_vector_with_negative_startindex)
{
  ASSERT_ANY_THROW(TVector<int> v(5, -2));
}

TEST(TVector, can_create_copied_vector)
{
  TVector<int> v(10);

  ASSERT_NO_THROW(TVector<int> v1(v));
}

TEST(TVector, copied_vector_is_equal_to_source_one)
{
	TVector<int> a(10);
	for (int i = 0; i < 10; i++) {
		a[i] = i * i;
	}

	TVector<int> a_copy(a);

	EXPECT_EQ(a, a_copy);
}

TEST(TVector, copied_vector_has_its_own_memory)
{
	// изменить первый вектор, а копия остаётся неизменной
	// удалить или изменить
	TVector<int> a(10);
	for (int i = 0; i < 10; i++) {
		a[i] = i * i;
	}

	TVector<int> a_copy(a);
	for (int i = 0; i < 10; i += 2) {
		a[i] = -i * i;
	}

	EXPECT_NE(a, a_copy);
}

TEST(TVector, can_get_size)
{
  TVector<int> v(4);

  EXPECT_EQ(4, v.GetSize());
}

TEST(TVector, can_get_start_index)
{
  TVector<int> v(4, 2);

  EXPECT_EQ(2, v.GetStartIndex());
}

TEST(TVector, can_set_and_get_element)
{
  TVector<int> v(4);
  ASSERT_NO_THROW(v[0] = 4);  

  EXPECT_EQ(4, v[0]);
}

TEST(TVector, throws_when_set_element_with_negative_index)
{
	TVector<int> a(10);

	ASSERT_ANY_THROW(a[-1] = 4);
}

TEST(TVector, throws_when_set_element_with_too_large_index)
{
	TVector<int> a(10);

	ASSERT_ANY_THROW(a[12] = 4);
}

TEST(TVector, can_assign_vector_to_itself)
{
	TVector<int> a(10);
	for (int i = 0; i < 10; i++) {
		a[i] = i * i;
	}
	ASSERT_NO_THROW(a = a);

	for (int i = 0; i < 10; i++) {
		EXPECT_EQ(a[i], i * i);
	}
}

TEST(TVector, can_assign_vectors_of_equal_size)
{
	TVector<int> a(10), b(10);
	for (int i = 0; i < 10; i++) {
		a[i] = i * i;
	}
	ASSERT_NO_THROW(b = a);

	EXPECT_EQ(a, b);
}

TEST(TVector, assign_operator_change_vector_size)
{
	int a_size_1 = 10;
	TVector<int> a(a_size_1), b(a_size_1 * 2);

	a = b;
	int a_size_2 = a.GetSize();

	EXPECT_NE(a_size_1, a_size_2);
}

TEST(TVector, can_assign_vectors_of_different_size)	// ???
{
	TVector<int> a(10), b(20);
	for (int i = 0; i < 10; i++) {
		a[i] = i * i;
	}

	for (int i = 0; i < 20; i++) {
		b[i] = i * i * 2;
	}

	ASSERT_NO_THROW(a = b);
	EXPECT_EQ(a, b);
}

TEST(TVector, compare_equal_vectors_return_true)
{
	TVector<int> a(10);
	for (int i = 0; i < 10; i++) {
		a[i] = i * i;
	}

	TVector<int> a_copy(a);

	EXPECT_TRUE(a == a_copy);
}

TEST(TVector, compare_vector_with_itself_return_true)
{
	TVector<int> a(10);
	for (int i = 0; i < 10; i++) {
		a[i] = i * i;
	}

	EXPECT_TRUE(a == a);
}

TEST(TVector, vectors_with_different_size_are_not_equal)
{
	TVector<int> a(10), b(11);

	EXPECT_TRUE(a != b);
}

TEST(TVector, can_add_scalar_to_vector)
{
	TVector<int> a(10), res(10);
	for (int i = 0; i < 10; i++) {
		a[i] = i * i;
	}

	int val = 10;

	ASSERT_NO_THROW(res = a + 10);

	for (int i = 0; i < 10; i++) {
		EXPECT_TRUE(res[i] == a[i] + val);
	}
}

TEST(TVector, can_subtract_scalar_from_vector)
{
	TVector<int> a(10), res(10);
	for (int i = 0; i < 10; i++) {
		a[i] = i * i;
	}

	int val = 10;

	ASSERT_NO_THROW(res = a - 10);

	for (int i = 0; i < 10; i++) {
		EXPECT_TRUE(res[i] == a[i] - val);
	}
}

TEST(TVector, can_multiply_scalar_by_vector)
{
	TVector<int> a(10), res(10);
	for (int i = 0; i < 10; i++) {
		a[i] = i * i;
	}

	int val = 10;

	ASSERT_NO_THROW(res = a * 10);

	for (int i = 0; i < 10; i++) {
		EXPECT_TRUE(res[i] == a[i] * val);
	}
}

TEST(TVector, can_add_vectors_with_equal_size)
{
	TVector<int> a(10), b(10), res(10);
	for (int i = 0; i < 10; i++) {
		a[i] = i * i;
		b[i] = i;
	}

	ASSERT_NO_THROW(res = a + b);

	for (int i = 0; i < 10; i++) {
		EXPECT_TRUE(res[i] == a[i] + b[i]);
	}
}

TEST(TVector, cant_add_vectors_with_not_equal_size)
{
	TVector<int> a(10), b(12), res(10);
	for (int i = 0; i < 10; i++) {
		a[i] = i * i;
		b[i] = i;
	}

	ASSERT_ANY_THROW(res = a + b);
}

TEST(TVector, can_subtract_vectors_with_equal_size)
{
	TVector<int> a(10), b(10), res(10);
	for (int i = 0; i < 10; i++) {
		a[i] = i * i;
		b[i] = i;
	}

	ASSERT_NO_THROW(res = a - b);

	for (int i = 0; i < 10; i++) {
		EXPECT_TRUE(res[i] == a[i] - b[i]);
	}
}

TEST(TVector, cant_subtract_vectors_with_not_equal_size)
{
	TVector<int> a(10), b(12), res(10);
	for (int i = 0; i < 10; i++) {
		a[i] = i * i;
		b[i] = i;
	}

	ASSERT_ANY_THROW(res = a - b);
}

TEST(TVector, can_multiply_vectors_with_equal_size)
{
	TVector<int> a(10), b(10);
	for (int i = 0; i < 10; i++) {
		a[i] = i * i;
		b[i] = i;
	}

	int res = 0;
	ASSERT_NO_THROW(res = a * b);

	int test = 0;
	for (int i = 0; i < 10; i++) {
		test += a[i] * b[i];
	}

	EXPECT_EQ(res, test);
}

TEST(TVector, cant_multiply_vectors_with_not_equal_size)
{
	TVector<int> a(10), b(12);
	for (int i = 0; i < 10; i++) {
		a[i] = i * i;
		b[i] = i;
	}

	int res = 0;
	ASSERT_ANY_THROW(res = a * b);
}

