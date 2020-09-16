#include <iostream>
#include <vector>
#include <deque>
#include <numeric>
#include <array>
using namespace std;

template<class InputIt, class OutputIt>
OutputIt MeadianFilterFunc(const InputIt first1, const InputIt last1, OutputIt d_first, unsigned short FilterLen)
{
    //1. prefill the working vector
    unsigned short halflen = FilterLen / 2;
    std::deque<InputIt::value_type> workdeque;
    auto firt1val = *first1;

    for (int i = 1; i < FilterLen; i++)
        workdeque.push_back(firt1val);

    //2. run filter
    InputIt itr_front = first1;

    OutputIt itr_out = d_first;
    int poscounter = 0;
    while (itr_front != last1)
    {
        workdeque.push_back(*itr_front);
        workdeque.pop_front();
        std::vector<InputIt::value_type> sortingvec(workdeque.begin(), workdeque.end());
        nth_element(sortingvec.begin(), sortingvec.begin() + halflen, sortingvec.end());
        if (poscounter >= halflen) {
            *itr_out = *(sortingvec.begin() + halflen);
            itr_out++;
        }
        itr_front++;
        poscounter++;
    }
    //3. extend the end
    auto last1val = *(last1 - 1);
    for (int i = 0; i < halflen; i++)
    {
        workdeque.push_back(last1val);
        workdeque.pop_front();
        std::vector<InputIt::value_type> sortingvec(workdeque.begin(), workdeque.end());
        nth_element(sortingvec.begin(), sortingvec.begin() + halflen, sortingvec.end());
        *itr_out = *(sortingvec.begin() + halflen);
        itr_out++;
    }
    return d_first;
}




template<class InputIt, class OutputIt>
OutputIt MAFilterFunc(InputIt first1, InputIt last1, OutputIt d_first, unsigned short FilterLen)
{
    //1. prefill the accumulator
    unsigned short halflen = FilterLen / 2;
    typename InputIt::value_type accu{ 0 };
    auto first1val = *first1;
    for (int i = 1; i < FilterLen; i++)
        accu += first1val;
    //2. run filter
    InputIt itr_front = first1;
    OutputIt itr_out = d_first;
    int poscounter = 0;
    auto itr_tail = first1;
    while (itr_front != last1)
    {
        if (poscounter >= FilterLen)
            itr_tail = itr_front - FilterLen;
        accu += *itr_front;
        accu -= *itr_tail;
        if (poscounter >= halflen) {
            *itr_out = accu / FilterLen;
            itr_out++;
        }
        itr_front++;
        poscounter++;

    }
    //3.extend the end
    auto last1value = *(last1 - 1);
    for (int i = 0; i < halflen; i++)
    {
        accu += last1value;
        accu -= *itr_tail;
        *itr_out = accu / FilterLen;
        itr_tail++;
        itr_out++;
    }
    return d_first;
}


int main()
{
    array<int, 211> input{537
    ,536
    ,535
    ,534
    ,533
    ,532
    ,531
    ,530
    ,529
    ,528
    ,527
    ,527
    ,526
    ,526
    ,525
    ,524
    ,524
    ,1523
    ,1523
    ,1523
    ,1523
    ,1523
    ,1523
    ,1523
    ,1523
    ,1523
    ,1523
    ,1523
    ,1523
    ,1523
    ,1523
    ,2523
    ,2673
    ,2523
    ,2100
    ,1523
    ,1523
    ,1523
    ,1523
    ,1523
    ,1523
    ,1523
    ,1523
    ,1523
    ,1523
    ,1523
    ,1523
    ,524
    ,524
    ,525
    ,526
    ,527
    ,528
    ,528
    ,529
    ,530
    ,531
    ,531
    ,532
    ,533
    ,534
    ,534
    ,536
    ,537
    ,538
    ,541
    ,542
    ,544
    ,546
    };
    array<int, 211> filtereddata;
    array<int, 211> medianfilered;
    MAFilterFunc(input.begin(), input.end(), filtereddata.begin(), 50);
    MeadianFilterFunc(input.begin(), input.end(), medianfilered.begin(),50);

    return 0;
}
