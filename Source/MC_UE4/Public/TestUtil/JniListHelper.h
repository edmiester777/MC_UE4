#pragma once
#include <TestUtil/JavaTestUtil.h>

class JniListHelper
{
public:
	/**
	 * Convert an int array from C++ to a java Int[].
	 * 
	 * @param ints List of integers to put into jvm.
	 */
	static jobjectArray ToIntegerArray(TArray<int> ints);

	/**
	 * Convert a java int array to a java List<int>.
	 * 
	 * @param ints Existing Integer array to convert.
	 */
	static jobject ToList(jobjectArray ints);

	/**
	 * Convert an TArray<int> to a java List<int>.
	 * 
	 * @param ints List of integers to put into a jvm list.
	 * 
	 * @see ToIntArray(TArray<int>)
	 * @see ToList(jintArray)
	 */
	static jobject ToList(TArray<int> ints);
};
