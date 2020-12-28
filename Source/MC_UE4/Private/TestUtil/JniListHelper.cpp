#include <TestUtil/JniListHelper.h>

jintArray JniListHelper::ToIntArray(TArray<int> ints)
{
	// allocating the jvm array
	jintArray arr = JNI_ENV->NewIntArray(ints.Num());

	// setting list items
	for (int i = 0; i < ints.Num(); ++i)
	{
		jint intVal = ints[i];
		JNI_ENV->SetIntArrayRegion(arr, i, 1, &intVal);
	}

	return arr;
}

jobject JniListHelper::ToList(jintArray ints)
{
	// using Arrays.asList(T ... a) builtin to convert.
	jclass arraysCls = JNI_ENV->FindClass("java/util/Arrays");
	jmethodID asListMethod = JNI_ENV->GetStaticMethodID(
		arraysCls,
		"asList",
		"([Ljava/lang/Object;)Ljava/util/List;"
	);
	jobject list = JNI_ENV->CallStaticObjectMethod(
		arraysCls, 
		asListMethod, 
		ints
	);

	return list;
}

jobject JniListHelper::ToList(TArray<int> ints)
{
	// converting list
	jintArray arr = ToIntArray(ints);
	jobject list = ToList(arr);

	// cleanup
	JNI_ENV->DeleteLocalRef(arr);

	return list;
}
