template<typename T>
class InsertionSorter : public ISorter<PairSequence<T>> {
public:
    void sort(PairSequence<T>& seq, int (*cmp)(const T&, const T&)) override {
        int n = seq.get_length();
        for (int i = 1; i < n; ++i) {
            auto key = seq.get(i);
            int j = i - 1;

            while (j >= 0 && cmp(seq.get(j).get_second(), key.get_second()) > 0) {
                seq.set(j + 1, seq.get(j));
                --j;
            }
            seq.set(j + 1, key);
        }
    }
};
