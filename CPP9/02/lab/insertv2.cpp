// Jacobsthal numbers adjusted for indexing
int jacobsthal_hardcoded_index_adjusted[] = {0, 2, 4, 10, 20, 42, 84, 170, 340, 682, 1364, 2730, 5460};

template<typename Container>
void jacobsthal_insertion(Container &pend, Container &main) {
    int insert_index = 0;
    int current_j = jacobsthal_hardcoded_index_adjusted[0];
    int insert_count = 0;
    int i = 0;

    typename Container::iterator position_of_insert;

    while (insert_count < static_cast<int>(pend.size())) {
        typename Container::iterator pend_it = pend.begin();
        std::advance(pend_it, insert_index); // Advance to the current insert index
        int pend_value = *pend_it;

        // Use lower_bound to find the correct position to insert the pend value in main
        position_of_insert = std::lower_bound(main.begin(), main.end(), pend_value);

        // Insert the pend value into the found position in main
        main.insert(position_of_insert, pend_value);
        insert_count++;

        // Update current_j and insert_index based on the Jacobsthal sequence
        if (insert_count == current_j + 1) {
            i++;
            if (i < sizeof(jacobsthal_hardcoded_index_adjusted)/sizeof(jacobsthal_hardcoded_index_adjusted[0]) && jacobsthal_hardcoded_index_adjusted[i] < static_cast<int>(pend.size())) {
                current_j = jacobsthal_hardcoded_index_adjusted[i];
            } else {
                current_j = pend.size() - 1; // Ensure it does not exceed bounds
            }
            insert_index = current_j;
        } else {
            insert_index--;
        }
    }
}


//===========================

//with additional checks

#include <vector>
#include <list>
#include <iterator>
#include <algorithm>
#include <iostream>

template<typename Container>
void jacobsthal_insertion(Container &pend, Container &main) {
    if (pend.empty()) return; // Early exit if pend is empty

    int jacobsthal_hardcoded_index_adjusted[] = {0, 2, 4, 10, 20, 42, 84, 170, 340, 682, 1364, 2730, 5460};
    int insert_index = jacobsthal_hardcoded_index_adjusted[0];
    int current_j = jacobsthal_hardcoded_index_adjusted[0];
    int insert_count = 0;
    int i = 0;

    typename Container::iterator position_of_insert;

    while (insert_count < static_cast<int>(pend.size())) {
        if (insert_index < static_cast<int>(pend.size())) {
            typename Container::iterator pend_it = pend.begin();
            std::advance(pend_it, insert_index); // Safe as insert_index is checked
            int pend_value = *pend_it;

            position_of_insert = std::lower_bound(main.begin(), main.end(), pend_value);
            main.insert(position_of_insert, pend_value);
            insert_count++;

            if (insert_count == current_j + 1 && i < sizeof(jacobsthal_hardcoded_index_adjusted)/sizeof(jacobsthal_hardcoded_index_adjusted[0]) - 1) {
                i++;
                current_j = jacobsthal_hardcoded_index_adjusted[i];
                insert_index = current_j < static_cast<int>(pend.size()) ? current_j : static_cast<int>(pend.size()) - 1;
            } else {
                insert_index = insert_index > 0 ? insert_index - 1 : 0;  // Prevent negative index
            }
        } else {
            break;  // Prevent out-of-bounds access if Jacobsthal numbers exceed pend size
        }
    }
}