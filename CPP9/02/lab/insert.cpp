
template <typename Container>
void insertPendGroup(Container& main, const Container& pend) {
    if (pend.empty()) 
        return;

    typename Container::iterator main_begin = main.begin();
    typename Container::const_iterator pend_a = pend.begin();
    typename Container::const_iterator pend_b = pend.begin();

    //comment 1: can we use something more universal such as an array 
    std::vector<int> jacobsthal = generateJacobsthal(pend.size() + 1);

    size_t pend_size = pend.size();
    //comment 2: see comment 1
    std::vector<bool> inserted(pend_size, false); // Track inserted elements
    int index_last_insert = 0;

    // Iterate until all elements are inserted
    while (std::find(inserted.begin(), inserted.end(), false) != inserted.end()) 
    {
        int to_insert_idx = 0; //comment 3: what is this for?
        
        // Find the right insert number from pend
        if (std::find(jacobsthal.begin(), jacobsthal.end(), index_last_insert) != jacobsthal.end()) //if last insert was jacobsthal
        {
            if (index_last_insert - 1 > pend_a && !inserted[index_last_insert - 1]) 
            {
                to_insert_idx = index_last_insert - 1;
                index_last_insert--;
            } else 
            {
                if (pend_b != pend.end()) {
                    pend_b = (index_last_insert + 1 < jacobsthal.size()) 
                             ? std::next(pend.begin(), jacobsthal[index_last_insert + 1]) 
                             : pend.end();
                }
                if (pend_a != pend.begin()) {
                    pend_a = (index_last_insert - 1 >= 0) 
                             ? std::prev(pend.begin(), jacobsthal[index_last_insert - 1]) 
                             : pend.begin();
                }
                to_insert_idx = index_last_insert;
                index_last_insert = (index_last_insert + 1 < jacobsthal.size()) 
                                    ? jacobsthal[index_last_insert + 1] 
                                    : pend_size;
            }
        } 
        else 
        {
            to_insert_idx = index_last_insert;
        }

        // Insert the element into main if it hasn't been inserted yet
        if (to_insert_idx >= 0 && to_insert_idx < pend_size && !inserted[to_insert_idx]) {
            typename Container::const_iterator pendIt = std::next(pend.begin(), to_insert_idx);

            // Find the correct location to insert in main
            typename Container::iterator itInsertPos = std::lower_bound(main.begin(), main.end(), *pendIt);

            // Insert the element into main
            main.insert(itInsertPos, *pendIt);
            inserted[to_insert_idx] = true;
        }
    }
}