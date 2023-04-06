// Project UID c1f28c309e55405daf00c565d57ff9ad

#include "List.h"
#include "unit_test_framework.h"

using namespace std;

TEST(test_stub) {
    ASSERT_TRUE(true);
}

TEST(constructor1) {
    List <int> list1;
    ASSERT_TRUE(list1.empty());
}

TEST(basic_test1) {
    List <int> list1; //3, 2, 1
    list1.push_front(1);
    list1.push_front(2);
    list1.push_front(3);
    ASSERT_EQUAL(list1.front(), 3);
    ASSERT_EQUAL(list1.back(), 1);
    ASSERT_EQUAL(list1.size(), 3);
    ASSERT_FALSE(list1.empty());



    List <int> list2; //2, 4, 1
    list2.push_back(2);
    list2.push_back(4);
    list2.push_back(1);
    ASSERT_EQUAL(list2.front(), 2);
    ASSERT_EQUAL(list2.back(), 1);
    ASSERT_EQUAL(list2.size(), 3);
    ASSERT_FALSE(list2.empty());

    list2 = list1;

    List <int> list3(list2);

    List <int> list4; //7
    list4.push_front(7);
    ASSERT_EQUAL(list4.front(), 7);
    ASSERT_EQUAL(list4.back(), 7);
    ASSERT_EQUAL(list4.size(), 1);

    list1 = list4;

    List <int> list5; //3, 7, 6
    list5.push_front(7);
    list5.push_back(6);
    list5.push_front(3);
    ASSERT_EQUAL(list5.front(), 3);
    ASSERT_EQUAL(list5.back(), 6);
    ASSERT_EQUAL(list5.size(), 3);


    List <int> list6; //6, 3, 2
    list6.push_back(7);
    list6.push_back(6);
    list6.push_back(3);
    list6.push_back(2);
    list6.push_back(1);
    list6.pop_back();
    list6.pop_front();
    ASSERT_EQUAL(list6.front(), 6);
    ASSERT_EQUAL(list6.back(), 2);
    ASSERT_EQUAL(list6.size(), 3);

    List <int> list7; //nothing
    list7.push_back(9);
    list7.push_back(6);
    list7.pop_back();
    list7.pop_front();
    ASSERT_EQUAL(list7.size(), 0);
    ASSERT_TRUE(list7.empty());

    list4.clear();
    ASSERT_TRUE(list4.empty());
}


TEST(iterator_tests){
    List <int> list1; //3, 2, 9, 6, 8
    list1.push_back(3);
    list1.push_back(2);
    list1.push_back(9);
    list1.push_back(6);
    list1.push_back(8);

    List<int>::Iterator iter1 = list1.begin();
    ASSERT_EQUAL(*iter1, 3);
    ++iter1;
    ASSERT_EQUAL(*iter1, 2);
    ++iter1;
    ++iter1;
    ASSERT_EQUAL(*iter1, 6);
    --iter1;
    ASSERT_EQUAL(*iter1, 9); //points to 9, (index 2)

    List<int>::Iterator iter2 = list1.begin();
    List<int>::Iterator iter2Copy = list1.begin();
    ASSERT_TRUE(iter2==iter2Copy);
    ++iter2;
    ++iter2; //points to 9, (index 2)
    ASSERT_TRUE(iter1==iter2);

    List<int>::Iterator iter3 = list1.begin();
    ++iter3; //points to 2, (index 1)
    ASSERT_TRUE(iter1!=iter3);

    List<int>::Iterator iter6 = list1.begin();
    ASSERT_EQUAL(*iter6, 3); //points to 3, first elem, index 0

    List<int>::Iterator iter7 = list1.end(); //points to one past end

    list1.insert(iter1, 7); //3, 2, 7, 9, 6, 8
    --iter1;
    ASSERT_EQUAL(*iter1, 7);
    ASSERT_EQUAL(list1.size(), 6);

    list1.insert(iter6, 1); //1, 3, 2, 7, 9, 6, 8
    --iter6; //points to 1, (index 0)
    ASSERT_EQUAL(*iter6, 1);
    ASSERT_EQUAL(list1.size(), 7);

    list1.insert(iter7, 4); //1, 3, 2, 7, 9, 6, 8, 4
   
    List<int>::Iterator iter8 = list1.begin();
    ++iter8;
    ++iter8;
    ++iter8;
    ++iter8;
    ++iter8;
    ++iter8;
    ++iter8;
    ASSERT_EQUAL(*iter8, 4);

    //at this point, current information 
    //list 1: 1, 3, 2, 7, 9, 6, 8, 4
    //iter 1: points at 7
    //iter 2: points at 9
    //iter 3: points at 2
    //iter 5: points at 8
    //iter 6: points at 1
    //iter 8: points at 4
    //iter 7: points at one after 4

    list1.erase(iter1);
    list1.erase(iter8);
    list1.erase(iter6);

    //new list1: 3, 2, 9, 6, 8

    List<int>::Iterator tracker = list1.begin();
    ASSERT_EQUAL(*tracker, 3);
    ++tracker;
    ASSERT_EQUAL(*tracker, 2);
    ++tracker;
    ASSERT_EQUAL(*tracker, 9);
    ++tracker;
    ASSERT_EQUAL(*tracker, 6);
    ++tracker;
    ASSERT_EQUAL(*tracker, 8);
    ASSERT_EQUAL(list1.size(), 5);

    ASSERT_EQUAL(list1.front(), 3);
    ASSERT_EQUAL(list1.back(), 8);
}

TEST(random_extra_tests){
    List <int> list1;
    list1.push_back(3);
    list1.pop_front();
    ASSERT_TRUE(list1.empty());

    List <int> list2;
    list1.push_back(9);
    list1.pop_back();
    ASSERT_TRUE(list2.empty());

    List <int> list3;
    list3.clear();
    ASSERT_TRUE(list3.empty());

    List <int> list4;
    list4.push_front(4);
    List<int>::Iterator iter = list4.begin();
    list4.erase(iter);
    ASSERT_TRUE(list4.empty());

    List <int> list5;
    list5.push_back(7);
    list5.push_back(1);
    List<int>::Iterator iter2 = list5.begin();
    list5.erase(iter2);
    ASSERT_EQUAL(list5.front(), 1);


    List <int> list6;
    list6.push_back(9);
    list6.push_back(4);
    List<int>::Iterator iter3 = list6.begin();
    ++iter3;
    list6.erase(iter3);
    ASSERT_EQUAL(list6.front(), 9);

    List <int> list7;
    list7.push_back(4);
    list7.push_back(9);
    list7.push_back(2);
    List<int>::Iterator four = list7.begin();
    List<int>::Iterator nine = list7.begin();
    ++nine;
    List<int>::Iterator two = list7.begin();
    ++two;
    ++two;
    List<int>::Iterator lastPoint = list7.end();
    list7.insert(four, 5);
    list7.insert(nine, 3);
    list7.insert(two, 2);
    list7.insert(lastPoint, 1);

    List<int>::Iterator tracker = list7.begin();
    ASSERT_EQUAL(*tracker, 5);
    ++tracker;
    ASSERT_EQUAL(*tracker, 4);
    ++tracker;
    ASSERT_EQUAL(*tracker, 3);
    ++tracker;
    ASSERT_EQUAL(*tracker, 9);
    ++tracker;
    ASSERT_EQUAL(*tracker, 2);
    ++tracker;
    ASSERT_EQUAL(*tracker, 2);
    ++tracker;
    ASSERT_EQUAL(*tracker, 1);
}

TEST(compil_test) { 
    List<int> my_list;

    int size = 0;
    my_list.empty();
    my_list.size();
    cout << (my_list.size() == size) << endl;

    my_list.push_front(42);
    my_list.push_back(42);

    my_list.front() = 73;
    my_list.back() = 73;

    my_list.pop_front();
    my_list.pop_back();

    List<int> list2(my_list);
    list2 = my_list;

    List<int>::Iterator iter = my_list.begin();
    my_list.insert(iter, 42);
    iter = my_list.begin();
    my_list.erase(iter);
    iter = my_list.begin();

    List<int>::Iterator iter2 = my_list.end();
    const List<int>::Iterator iter3 = iter2;

    bool b = iter == iter2;
    b = iter3 == my_list.end();
    b = my_list.end() == iter3;
    my_list.push_front(42);
    my_list.push_back(42);
    iter = my_list.begin();
    b = iter != iter2;
    b = iter3 != my_list.end();
    b = my_list.end() != iter3;
    cout << b << endl;
    ++iter;

    cout << *iter << endl;

    List<int>::Iterator iter_cpy(iter);
    iter_cpy = iter;

    cout << *++--iter << endl;
    cout << *--++my_list.begin() << endl;

    my_list.insert(my_list.begin(), 3);
    my_list.erase(my_list.begin());

    List<int> list3;
    list3.push_back(3);
    cout << *list3.begin() << endl;

    List<int> list4;
    list4.push_back(4);
    cout << list4.size() << endl;

    my_list.clear();

    return;
}

TEST_MAIN()