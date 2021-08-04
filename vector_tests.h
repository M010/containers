#include "vector.hpp"
#include "test_runner.h"

void ft_vector_tests() {
    {
        std::vector<std::string> svect;
        ft::vector<std::string>  fvect;
        std::cout << svect.size() << " = " << fvect.size() << std::endl;
        std::cout << svect.capacity() << " = " << fvect.capacity() << std::endl;
        std::cout << svect.max_size() << " = " << fvect.max_size() << std::endl;

        std::vector<int> svectint;
        ft::vector<int>  fvectint;
        std::cout << svectint.size() << " = " << fvectint.size() << std::endl;
        std::cout << svectint.capacity() << " = " << fvectint.capacity() << std::endl;
        std::cout << svectint.max_size() << " = " << fvectint.max_size() << std::endl;

    }

    {
        std::cout << "-------------" << std::endl;
        std::vector<std::string> svect(7, "hello");
        ft::vector<std::string>  fvect(7, "hello");
        std::cout << svect.size() << " = " << fvect.size() << std::endl;
        std::cout << svect.capacity() << " = " << fvect.capacity() << std::endl;
        std::cout << svect.max_size() << " = " << fvect.max_size() << std::endl;

        {
            std::vector<std::string> svect2(svect);
            ft::vector<std::string>  fvect2(fvect);
            std::cout << svect2.size() << " = " << fvect2.size() << std::endl;
            std::cout << svect2.capacity() << " = " << fvect2.capacity() << std::endl;
            std::cout << svect2.max_size() << " = " << fvect2.max_size() << std::endl;
            ASSERT_EQUAL(svect2, fvect2);
            svect2.clear();
            fvect2.clear();
            std::cout << svect2.size() << " = " << fvect2.size() << std::endl;
            std::cout << svect2.capacity() << " = " << fvect2.capacity() << std::endl;
            std::cout << svect2.max_size() << " = " << fvect2.max_size() << std::endl;
            ASSERT_EQUAL(svect2, fvect2);

            std::vector<std::string> svect3(7, "hello");
            ft::vector<std::string>  fvect3(7, "hello");
            svect2 = svect3;
            fvect2 = fvect3;
            std::cout << svect2.size() << " = " << fvect2.size() << std::endl;
            std::cout << svect2.capacity() << " = " << fvect2.capacity() << std::endl;
            std::cout << svect2.max_size() << " = " << fvect2.max_size() << std::endl;
            ASSERT_EQUAL(svect2, fvect2);

            svect2.reserve(100);
            fvect2.reserve(100);
            std::cout << svect2.size() << " = " << fvect2.size() << std::endl;
            std::cout << svect2.capacity() << " = " << fvect2.capacity() << std::endl;
            std::cout << svect2.max_size() << " = " << fvect2.max_size() << std::endl;
            ASSERT_EQUAL(svect2, fvect2);
        }

        ASSERT_EQUAL(svect, fvect);

        std::cout << "front and back change" << std::endl;
        svect.front() = "front";
        svect.back()  = "back";
        fvect.front() = "front";
        fvect.back()  = "back";

        std::vector<std::string>::iterator sit = svect.begin();
        ft::vector<std::string>::iterator  fit = fvect.begin();

        for (size_t i = 1; sit != svect.end() && fit != fvect.end(); ++i) {
            *sit++ += ft_tostring(i);
            *fit++ += ft_tostring(i);
        }

        sit = svect.begin();
        fit = fvect.begin();

        while (sit != svect.end() && fit != fvect.end()) {
            std::ptrdiff_t sdist = std::distance(sit, svect.begin());
            std::ptrdiff_t fdist = std::distance(fit, fvect.begin());
            std::cout << sdist << "\t" << fdist << std::endl;
            sit = 1 + sit;
            fit = 1 + fit;
            sit = sit - 1;
            fit = fit - 1;
            sit = sit + 1;
            fit = fit + 1;
        }
    }

//    {
//        /*		this block is full of crap			*/
//        std::cout << "-------------" << std::endl;
//        std::vector<std::string>	svect(7, "hello");
//        ft::vector<std::string>		fvect(7, "hello");
//        std::vector<std::string>::reverse_iterator	sit = svect.rbegin();
//        ft::vector<std::string>::reverse_iterator	fit = fvect.rbegin();
//
//        std::vector<std::string>::const_reverse_iterator	sit2 = sit;
//        ft::vector<std::string>::const_reverse_iterator		fit2 = fit;
//
//        /*		this it the most painfull part		*/
//        std::cout << sit2 - sit << fit2 - fit;
//        if (sit <= sit2)
//            std::cout << "allo";
//        if (fit <= fit2)
//            std::cout << "allo\n";
//
//        while (sit != svect.rend() && fit != fvect.rend())
//        {
//            std::ptrdiff_t	sdist = std::distance(sit, svect.rbegin());
//            std::ptrdiff_t	fdist = std::distance(fit, fvect.rbegin());
//            std::cout << sdist << "\t" << fdist << std::endl;
//            ++sit;
//            fit = 1 + fit;
//        }
//        /*		i hate this part really much		*/
//    }

    {
        std::cout << "-------------" << std::endl;
        std::cout << "swapster" << std::endl;
        std::vector<int> sfoo(2, 100);   // two ints with a value of 100
        ft::vector<int>  ffoo(2, 100);   // two ints with a value of 100
        std::vector<int> sbar(4, 200);   // four ints with a value of 200
        ft::vector<int>  fbar(4, 200);   // four ints with a value of 200

        ASSERT_EQUAL(sfoo, ffoo);
        ASSERT_EQUAL(sbar, fbar);

        std::vector<int>::iterator sit1 = sfoo.begin();
        ft::vector<int>::iterator  fit1 = ffoo.begin();
        std::vector<int>::iterator sit2 = sbar.begin();
        ft::vector<int>::iterator  fit2 = fbar.begin();
        std::cout << sfoo.capacity() << " = " << ffoo.capacity() << std::endl;
        std::cout << sbar.capacity() << " = " << fbar.capacity() << std::endl;
        std::cout << *sit1 << " " << *sit2 << std::endl;
        std::cout << *fit1 << " " << *fit2 << std::endl;

        sfoo.swap(sbar);
        ffoo.swap(fbar);

        ASSERT_EQUAL(sfoo, ffoo);
        ASSERT_EQUAL(sbar, fbar);

        std::cout << sfoo.capacity() << " = " << ffoo.capacity() << std::endl;
        std::cout << sbar.capacity() << " = " << fbar.capacity() << std::endl;

        std::cout << *sit1 << " " << *sit2 << std::endl;
        std::cout << *fit1 << " " << *fit2 << std::endl;

        try { sfoo.at(2378); }
        catch (const std::exception &e) { std::cerr << e.what() << std::endl; }
        try { ffoo.at(2378); }
        catch (const std::exception &e) { std::cerr << e.what() << std::endl; }
        try { sfoo.resize(sfoo.max_size() + 1); }
        catch (const std::exception &e) { std::cerr << e.what() << std::endl; }
        try { ffoo.resize(ffoo.max_size() + 1); }
        catch (const std::exception &e) { std::cerr << e.what() << std::endl; }
        ASSERT_EQUAL(sfoo, ffoo);
        ASSERT_EQUAL(sbar, fbar);

        std::cout << "-------------" << std::endl;
        std::cout << "assignster" << std::endl;
        sfoo.assign(200, 666);
        ffoo.assign(200, 666);
        std::cout << sfoo.size() << " = " << ffoo.size() << std::endl;
        std::cout << sfoo.capacity() << " = " << ffoo.capacity() << std::endl;
        ASSERT_EQUAL(sfoo, ffoo);

        sfoo.assign(sbar.begin(), sbar.end());
        ffoo.assign(fbar.begin(), fbar.end());
        std::cout << sfoo.size() << " = " << ffoo.size() << std::endl;
        std::cout << sfoo.capacity() << " = " << ffoo.capacity() << std::endl;
        ASSERT_EQUAL(sfoo, ffoo);

        sbar.assign(400, 666);
        fbar.assign(400, 666);
        sfoo.assign(sbar.begin(), sbar.end());
        ffoo.assign(fbar.begin(), fbar.end());
        std::cout << sfoo.size() << " = " << ffoo.size() << std::endl;
        std::cout << sfoo.capacity() << " = " << ffoo.capacity() << std::endl;
        ASSERT_EQUAL(sfoo, ffoo);
    }

    {
        std::cout << "-------------" << std::endl;
        std::vector<int>::size_type ssz;
        std::vector<int>            sfoo;
        ft::vector<int>::size_type  fsz;
        ft::vector<int>             ffoo;
        ssz = sfoo.capacity();
        fsz = ffoo.capacity();
        std::cout << "making foo grow:\n";

        for (int i = 0; i < 100; ++i) {
            sfoo.push_back(i);
            ffoo.push_back(i);
            if (ssz != sfoo.capacity() || fsz != ffoo.capacity()) {
                ssz = sfoo.capacity();
                fsz = ffoo.capacity();
                std::cout << "capacity changed: " << ssz << "\t" << fsz << '\n';
            }
        }
        ASSERT_EQUAL(sfoo, ffoo);

        std::cout << "making foo smaller:\n";
        for (int i = 0; i < 64; ++i) {
            sfoo.pop_back();
            ffoo.pop_back();
            if (ssz != sfoo.capacity() || fsz != ffoo.capacity()) {
                ssz = sfoo.capacity();
                fsz = ffoo.capacity();
                std::cout << "capacity changed: " << ssz << "\t" << fsz << '\n';
            }
        }
        std::cout << "sizes changed: " << sfoo.size() << "\t" << ffoo.size() << '\n';
        ASSERT_EQUAL(sfoo, ffoo);
    }

    {
        std::cout << "-------------" << std::endl;
        std::vector<int> sfoo;
        ft::vector<int>  ffoo;

        // set some initial content:
        for (int i = 1; i < 10; i++) {
            sfoo.push_back(i);
            ffoo.push_back(i);
        }

        sfoo.resize(5);
        ffoo.resize(5);
        std::cout << sfoo.capacity() << " = " << ffoo.capacity() << std::endl;
        ASSERT_EQUAL(sfoo, ffoo);

        sfoo.resize(8, 100);
        ffoo.resize(8, 100);
        std::cout << sfoo.capacity() << " = " << ffoo.capacity() << std::endl;
        ASSERT_EQUAL(sfoo, ffoo);

        sfoo.resize(12);
        ffoo.resize(12);
        std::cout << sfoo.capacity() << " = " << ffoo.capacity() << std::endl;
        ASSERT_EQUAL(sfoo, ffoo);

        sfoo.resize(0);
        ffoo.resize(0);
        std::cout << sfoo.capacity() << " = " << ffoo.capacity() << std::endl;
        ASSERT_EQUAL(sfoo, ffoo);

        sfoo.resize(20, 6);
        ffoo.resize(20, 6);
        std::cout << sfoo.capacity() << " = " << ffoo.capacity() << std::endl;
        ASSERT_EQUAL(sfoo, ffoo);

        sfoo.resize(666, 666);
        ffoo.resize(666, 666);
        std::cout << sfoo.capacity() << " = " << ffoo.capacity() << std::endl;
        ASSERT_EQUAL(sfoo, ffoo);

        sfoo.resize(6, 6626);
        ffoo.resize(6, 6626);
        std::cout << sfoo.capacity() << " = " << ffoo.capacity() << std::endl;
        ASSERT_EQUAL(sfoo, ffoo);
    }

    {
        std::cout << "-------------" << std::endl;
        std::vector<int>           svect;
        ft::vector<int>            fvect;
        std::vector<int>::iterator sit;
        ft::vector<int>::iterator  fit;

        // set some values (from 1 to 10)
        for (int i = 1; i <= 10; i++) {
            svect.push_back(i);
            fvect.push_back(i);
        }
        std::cout << svect.capacity() << " = " << fvect.capacity() << std::endl;
        ASSERT_EQUAL(svect, fvect);

        // erase the 6th element
        sit = svect.erase(svect.begin() + 5);
        fit = fvect.erase(fvect.begin() + 5);
        ASSERT_EQUAL(*sit, *fit);
        ASSERT_EQUAL(svect, fvect);

        // erase the first 3 elements:
        svect.erase(svect.begin(), svect.begin() + 3);
        fvect.erase(fvect.begin(), fvect.begin() + 3);
        ASSERT_EQUAL(svect, fvect);

        svect.erase(svect.end() - 4, svect.end() - 1);
        fvect.erase(fvect.end() - 4, fvect.end() - 1);
        std::cout << svect.capacity() << " = " << fvect.capacity() << std::endl;
        ASSERT_EQUAL(svect, fvect);

        svect.erase(svect.begin(), svect.end());
        fvect.erase(fvect.begin(), fvect.end());
        std::cout << svect.capacity() << " = " << fvect.capacity() << std::endl;
        ASSERT_EQUAL(svect, fvect);
    }

    {
        std::cout << "--------------" << std::endl;
        std::vector<std::string> svect0;
        ft::vector<std::string>  fvect0;
        std::vector<std::string> svect1;
        ft::vector<std::string>  fvect1;

        svect0.push_back("vector");
        fvect0.push_back("vector");
        ASSERT_EQUAL(svect0, fvect0);

        svect1.push_back("vector");
        fvect1.push_back("vector");
        ASSERT_EQUAL(svect1, fvect1);

        svect0.push_back("vector2");
        fvect0.push_back("vector2");
        ASSERT_EQUAL(svect0, fvect0);

        svect1.push_back("vector5");
        fvect1.push_back("vector5");
        ASSERT_EQUAL(svect1, fvect1);

        std::cout << "member swap:" << std::endl;
        svect0.swap(svect1);
        fvect0.swap(fvect1);
        ASSERT_EQUAL(svect0, fvect0);
        ASSERT_EQUAL(svect1, fvect1);

        std::cout << "nonmember swap:" << std::endl;
        swap(svect0, svect1);
        swap(fvect0, fvect1);
        ASSERT_EQUAL(svect0, fvect0);
        ASSERT_EQUAL(svect1, fvect1);
    }

    {
        std::cout << "-------------" << std::endl << "vector of vectors" << std::endl;
        std::vector<std::vector<size_t> > svect;
        ft::vector<ft::vector<size_t> >   fvect;

        while (svect.size() < 20) {
            bool a(rand() % 10000000);
            svect.push_back(std::vector<size_t>(20, a));
            fvect.push_back(ft::vector<size_t>(20, a));
        }

        svect.erase(svect.begin() + 6, svect.end() - 8);
        fvect.erase(fvect.begin() + 6, fvect.end() - 8);

        ASSERT_EQUAL(svect.size(), fvect.size());

        for (size_t i = 0; i < svect.size(); i++) ASSERT_EQUAL(svect[i], fvect[i]);
        std::cout << std::endl;
    }
}

void reserve_test() {
    {
        ft::vector<std::string>  fvect(2, "hi");
        std::vector<std::string> svect(2, "hi");

//        fvect.reserve(100);
//        svect.reserve(100);

        ASSERT_EQUAL(fvect, svect);
        ASSERT_EQUAL(fvect.capacity(), svect.capacity());

//        fvect.reserve(10);
//        svect.reserve(10);

        ASSERT_EQUAL(fvect, svect);
        ASSERT_EQUAL(fvect.capacity(), svect.capacity());
    }

//    {
//        ft::vector<std::string> fvect(10, "HI");
//        std::vector<std::string> svect(10, "HI");
//
//        fvect.reserve(100);
//        svect.reserve(100);
//
//        ASSERT_EQUAL(fvect, svect);
//        ASSERT_EQUAL(fvect.capacity(), svect.capacity());
//
//        fvect.reserve(10);
//        svect.reserve(10);
//
//        ASSERT_EQUAL(fvect, svect);
//        ASSERT_EQUAL(fvect.capacity(), svect.capacity());
//    }
}

void push_back_test() {

    {
        ft::vector<int>  vecy;
        std::vector<int> vecx;

        vecy.push_back(2);
        vecx.push_back(2);
        vecy.push_back(2);
        vecx.push_back(2);

        vecy.push_back(2);
        vecx.push_back(2);
        vecy.push_back(2);
        vecx.push_back(2);

        ft::vector<int>  vecy1 = vecy;
        std::vector<int> vecx1 = vecx;

        ASSERT_EQUAL(vecx, vecy);
        ASSERT_EQUAL(vecx1, vecy1);
    }
    {
        ft::vector<std::string>  vecy;
        std::vector<std::string> vecx;

        vecy.push_back("2");
        vecx.push_back("2");
        vecy.push_back("2");
        vecx.push_back("2");

        vecy.push_back("2");
        vecx.push_back("2");
        vecy.push_back("2");
        vecx.push_back("2");

        ft::vector<std::string>  vecy1 = vecy;
        std::vector<std::string> vecx1 = vecx;

        ASSERT_EQUAL(vecx1, vecy1);
    }

}

void constructor_test() {

    {
        ft::vector<std::string>  vecy;
        std::vector<std::string> vecx;
        ASSERT_EQUAL(vecx, vecy);
    }

    {
        ft::vector<std::string>  vecy(3);
        std::vector<std::string> vecx(3);

        ASSERT_EQUAL(vecx, vecy);
    }

    {
        ft::vector<std::string>  vecy(3, "Hello");
        std::vector<std::string> vecx(3, "Hello");
        ASSERT_EQUAL(vecx, vecy);
    }

    {
        ft::vector<std::string>  vecy(13, "ello");
        std::vector<std::string> vecx(13, "ello");

        ASSERT_EQUAL(vecx, vecy);
    }

    {
        std::vector<std::string> tmp;

        for (int                 i = 0; i < 100; i++)
            tmp.push_back(test::to_string(i));
        ft::vector<std::string>  vecy(tmp.begin(), tmp.end());
        std::vector<std::string> vecx(tmp.begin(), tmp.end());

        ASSERT_EQUAL(vecx, vecy);
    }

    {
        ft::vector<std::string> tmp;

        for (int                 i = 0; i < 100; i++)
            tmp.push_back(test::to_string(i));
        ft::vector<std::string>  vecy(tmp.begin(), tmp.end());
        std::vector<std::string> vecx(tmp.begin(), tmp.end());

        ASSERT_EQUAL(vecx, vecy);
    }

    {
        ft::vector<std::string>  tmp;
        std::vector<std::string> stmp;

        for (int                 i = 0; i < 100; i++) {
            tmp.push_back(test::to_string(i));
            stmp.push_back(test::to_string(i));
        }
        ft::vector<std::string>  vecy(tmp.begin(), tmp.end());
        std::vector<std::string> vecx(tmp.begin(), tmp.end());

        ASSERT_EQUAL(vecx, vecy);
    }

    {
        ft::vector<int> tmp;

        for (int i = 0; i < 100; i++) {
            tmp.push_back(i);
        }

        ft::vector<int>  vecy(tmp.begin(), tmp.end());
        std::vector<int> vecx(tmp.begin(), tmp.end());

        ASSERT_EQUAL(vecx, vecy);
    }
}

void iterator_test() {
    {
        ft::vector<int>  fvect;
        std::vector<int> svect;

        for (int i = 0; i < 10; i++) {
            fvect.push_back(i);
            svect.push_back(i);
        }

        ft::vector<int>::iterator  fit = fvect.begin();
        std::vector<int>::iterator sit = svect.begin();

        for (int i = 0; i < 10; i++) {
            ASSERT_EQUAL(*fit, *sit);
            fit++;
            sit++;
        }
    }

    {
        ft::vector<int>  fvect;
        std::vector<int> svect;

        for (int i = 0; i < 10; i++) {
            fvect.push_back(i);
            svect.push_back(i);
        }

        ft::vector<int>::iterator  fit = fvect.end();
        std::vector<int>::iterator sit = svect.end();

        for (int i = 0; i < 10; i++) {
            fit--;
            sit--;
            ASSERT_EQUAL(*fit, *sit);
        }
    }

    {
        ft::vector<int>  fvect;
        std::vector<int> svect;

        for (int i = 0; i < 1; i++) {
            fvect.push_back(i);
            svect.push_back(i);
        }

        ft::vector<int>::iterator  fit = fvect.begin();
        std::vector<int>::iterator sit = svect.begin();

        for (; fit != fvect.end(); fit++, sit++) {
            ASSERT_EQUAL(*fit, *sit);
        }
    }

    {
        ft::vector<std::string>  fvect;
        std::vector<std::string> svect;

        for (int i = 0; i < 1; i++) {
            fvect.push_back(test::to_string(i));
            svect.push_back(test::to_string(i));
        }

        ft::vector<std::string>::iterator  fit = fvect.begin();
        std::vector<std::string>::iterator sit = svect.begin();

        for (; sit != svect.end(); fit++, sit++) {
            ASSERT_EQUAL(*fit, *sit);
        }
    }
}

void reverse_iterator_test() {
    {
        ft::vector<int>  fvect;
        std::vector<int> svect;

        for (int i = 0; i < 10; i++) {
            fvect.push_back(i);
            svect.push_back(i);
        }

        ft::vector<int>::reverse_iterator  fit = fvect.rbegin();
        std::vector<int>::reverse_iterator sit = svect.rbegin();

        for (int i = 0; i < 10; i++) {
            ASSERT_EQUAL(*fit, *sit);
            fit++;
            sit++;
        }
    }

    {
        ft::vector<int>  fvect;
        std::vector<int> svect;

        for (int i = 0; i < 10; i++) {
            fvect.push_back(i);
            svect.push_back(i);
        }

        ft::vector<int>::reverse_iterator  fit = fvect.rend();
        std::vector<int>::reverse_iterator sit = svect.rend();

        for (int i = 0; i < 10; i++) {
            fit--;
            sit--;
            ASSERT_EQUAL(*fit, *sit);
        }
    }

    {
        ft::vector<int>  fvect;
        std::vector<int> svect;

        for (int i = 0; i < 10; i++) {
            fvect.push_back(i);
            svect.push_back(i);
        }

        ft::vector<int>::reverse_iterator  fit = fvect.rbegin();
        std::vector<int>::reverse_iterator sit = svect.rbegin();

        for (; fit != fvect.rend(); fit++, sit++) {
            ASSERT_EQUAL(*fit, *sit);
        }
    }

    {
        ft::vector<std::string>  fvect;
        std::vector<std::string> svect;

        for (int i = 0; i < 10; i++) {
            fvect.push_back(test::to_string(i));
            svect.push_back(test::to_string(i));
        }

        ft::vector<std::string>::reverse_iterator  fit = fvect.rbegin();
        std::vector<std::string>::reverse_iterator sit = svect.rbegin();

        for (; sit != svect.rend(); fit++, sit++) {
            ASSERT_EQUAL(*fit, *sit);
        }
    }
}

template<class Container, class Container1>
void n_fill(Container &container1, Container1 &container2) {
    for (int i = 0; i < 10; ++i) {
        container1.push_back(i);
        container2.push_bask(i);
    }
}

template<class Container, class Container1>
void s_fill(Container &container1, Container1 &container2, int n = 10) {
    for (int i = 0; i < n; ++i) {
        container1.push_back(test::to_string(i));
        container2.push_back(test::to_string(i));
    }
}

void insert_test() {
    {

        ft::vector<std::string> hi;
        ft::vector<std::string> ki;
        ft::vector<std::string> ti;

        hi.insert(hi.begin(), "begin");
        ki.insert(ki.end(), "begin");
        ti.push_back("begin");
        ASSERT_EQUAL(ki, ti);
        ASSERT_EQUAL(hi, ti);
    }
    {

        ft::vector<std::string> hi(10);
        ft::vector<std::string> ti(10);

        hi.insert(hi.end(), "begin");
        ti.push_back("begin");
        ASSERT_EQUAL(hi, ti);
    }

    {
        ft::vector<std::string>  hi;
        std::vector<std::string> ti;
        s_fill(hi, ti);
        hi.insert(hi.begin(), 10, "loh");
        ti.insert(ti.begin(), 10, "loh");
        ASSERT_EQUAL(hi, ti);

        hi.insert(hi.end(), 10, "l9h");
        ti.insert(ti.end(), 10, "l9h");
        ASSERT_EQUAL(hi, ti);

        hi.insert(hi.begin() + 4, 10, "lh");
        ti.insert(ti.begin() + 4, 10, "lh");
        ASSERT_EQUAL(hi, ti);
    }
}

void all_vector_tests(TestRunner &tr) {
    RUN_TEST(tr, iterator_test);
    RUN_TEST(tr, reverse_iterator_test);
    RUN_TEST(tr, reserve_test);
    RUN_TEST(tr, constructor_test);
    RUN_TEST(tr, push_back_test);
    RUN_TEST(tr, insert_test);
    RUN_TEST(tr, ft_vector_tests);
}