#pragma once

/**
 * A collection of utility functions for use with TSet.
 * 
 * @see TSet
 */
class SetUtil
{
public:
    /**
     * @brief Simple sort for ascending order.
     * 
     * Comparator for ascending results. This function relies on boolean
     * operator "<" being implemented on respective T type.
     * 
     * @tparam T Type of object being sorted.
     * @param set Set to sort.
     */
    template <typename T>
    static void SortAsc(TSet<T>& set);

    /**
     * @brief Simple sort for descending order.
     * 
     * Comparator for descending results. This function relies on boolean
     * operator "<" being implemented on respective T type.
     * 
     * @tparam T Type of object being sorted.
     * @param set Set to sort.
     */
    template <typename T>
    static void SortDesc(TSet<T>& set);
};

template <typename T>
void SetUtil::SortAsc(TSet<T>& set)
{
    set.Sort([](const T& a, const T& b) {
        return a < b;
    });
}

template <typename T>
void SetUtil::SortDesc(TSet<T>& set)
{
    set.Sort([](const T& a, const T& b) {
        return a > b;
    });
}