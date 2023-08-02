#ifndef DSA_SORT_HEADER
#define DSA_SORT_HEADER

#include <concepts>
#include <algorithm>
#include <ranges>
#include <vector>

/**
 * @brief Sorts a range of values in O(n^2) time.
 */
template <std::ranges::random_access_range R>
	requires std::sortable<std::ranges::iterator_t<R>>
void bubbleSort(R&& range) {
	bool sorted = false;
	for(auto it1 = range.end(); it1 != range.begin() && !sorted; it1--) {
		sorted = true;
		for(auto it2 = range.begin(); it2 != it1 - 1; it2++) {
			if(*(it2 + 1) < *it2) {
				std::iter_swap(it2 + 1, it2);
				sorted = false;
			}
		}
	}
}



/**
 * @brief Sorts a range of values in O(n^2) time.
 */
template <std::ranges::random_access_range R>
	requires std::sortable<std::ranges::iterator_t<R>>
void selectionSort(R&& range) {
	for(auto it = range.begin(); it != range.end(); it++) {
		std::iter_swap(it,
			std::min_element(it, range.end())
		);
	}
}



/**
 * @brief Sorts a range of values in O(n^2) time.
 */
template <std::ranges::random_access_range R>
	requires std::sortable<std::ranges::iterator_t<R>>
void insertionSort(R&& range) {
	for(auto it = range.begin(); it != range.end(); it++) {
		auto key = std::move(*it);
		auto insertPos = it;

		// find the right place to insert the value
		while(insertPos != range.begin() && *(insertPos - 1) > key) {
			*insertPos = std::move(*(insertPos - 1));
			insertPos--;
		}

		*insertPos = std::move(key);
	}
}



/**
 * @brief Sorts a range of values in O(n * lg n) time.
 */
template <std::ranges::random_access_range R>
	requires std::sortable<std::ranges::iterator_t<R>>
void mergeSort(R&& range) {
	// if the range contains only one element or no elements at all, there is nothing to sort
	if(std::ranges::size(range) <= 1) {
		return;
	}
	
	// find the midpoint of the range
	const auto mid = range.begin() + std::ranges::size(range) / 2;

	// split the range into two halves and sort them independently
	auto left = std::ranges::subrange(range.begin(), mid);
	mergeSort(left);

	auto right = std::ranges::subrange(mid, range.end());
	mergeSort(right);


	// allocate temporary storage for the result
	std::vector<std::ranges::range_value_t<R>> result;

	// iterate over the two ranges, saving the smallest element
	while(!std::ranges::empty(left) && !std::ranges::empty(right)) {
		if(left.front() < right.front()) {
			result.push_back(std::move(left.front()));
			left.advance(1);
		} else {
			result.push_back(std::move(right.front()));
			right.advance(1);
		}
	}

	// append remaining elements to the result
	std::ranges::move(left, std::back_inserter(result));
	std::ranges::move(right, std::back_inserter(result));

	// move the sorted elements back to the original sequence
	std::ranges::move(result, range.begin());
}



/**
 * @brief Sorts a range of values in O(n * lg n) time.
 */
template <std::ranges::random_access_range R>
	requires std::sortable<std::ranges::iterator_t<R>>
void quickSort(R&& range) {
	// if the range contains only one element or no elements at all, there is nothing to sort
	if(std::ranges::size(range) <= 1) {
		return;
	}

	// temporary storage for values less than and greater that or equal to the pivot
	std::vector<std::ranges::range_value_t<R>> less;
	std::vector<std::ranges::range_value_t<R>> greater;

	// find the pivot point for the range
	const auto pivotIt = range.begin() + std::ranges::size(range) / 2;
	auto pivot = std::move(*pivotIt);

	for(auto it = range.begin(); it != range.end(); it++) {
		// skip pivot point position
		if(it == pivotIt) {
			continue;
		}

		if(*it < pivot) {
			less.push_back(std::move(*it));
		} else {
			greater.push_back(std::move(*it));
		}
	}

	quickSort(less);
	quickSort(greater);

	// move sorted subsequences into the original range
	const auto outIt = std::ranges::move(less, range.begin()).out;
	*outIt = std::move(pivot);
	std::ranges::move(greater, outIt + 1);
}

#endif
